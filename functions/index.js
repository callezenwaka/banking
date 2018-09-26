var functions = require("firebase-functions");
var admin = require("firebase-admin");
var cors = require("cors")({ origin: true });
var webpush = require("web-push");
var fs = require("fs");
var UUID = require("uuid-v4");
var os = require("os");
var Busboy = require("busboy");
var path = require('path');
var express = require('express');
var Kairos = require('kairos-api');
var JSONStream = require('JSONStream');
var bodyParser = require('body-parser');
var multipart = require('connect-multiparty');

var app = express();
app.use(cors());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// Multiparty middleware
var multipartMiddleware = multipart();

// API Configurations for KAIROS
let kairos_client = new Kairos('', '');

// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//

var serviceAccount = require("./kapture-app-fb.json");

var gcconfig = {
  projectId: "kapture-app",
  keyFilename: "kapture-app-fb.json"
};

var gcs = require("@google-cloud/storage")(gcconfig);

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://kapture-app.firebaseio.com/"
});

exports.storePostData = functions.https.onRequest((req, res) => {
  cors(req, res, () => {
    var uuid = UUID();

    var busboy = new Busboy({ headers: req.headers });
    // These objects will store the values (file + fields) extracted from busboy
    let upload;
    var fields = {};

    // This callback will be invoked for each file uploaded
    busboy.on("file", (fieldname, file, filename, encoding, mimetype) => {
      console.log(
        `File [${fieldname}] filename: ${filename}, encoding: ${encoding}, mimetype: ${mimetype}`
      );
      var filepath = path.join(os.tmpdir(), filename);
      upload = { file: filepath, type: mimetype };
      file.pipe(fs.createWriteStream(filepath));
    });

    // This will invoked on every field detected
    busboy.on('field', (fieldname, val, fieldnameTruncated, valTruncated, encoding, mimetype) => {
      fields[fieldname] = val;
    });

    // This callback will be invoked after all uploaded files are saved.
    busboy.on("finish", () => {
      var bucket = gcs.bucket("kapture-app.appspot.com");
      bucket.upload(
        upload.file,
        {
          uploadType: "media",
          metadata: {
            metadata: {
              contentType: upload.type,
              firebaseStorageDownloadTokens: uuid
            }
          }
        },
        (err, uploadedFile) => {
          if (!err) {
            admin
              .database()
              .ref("posts")
              .push({
                title: fields.title,
                location: fields.location,
                rawLocation: {
                  lat: fields.rawLocationLat,
                  lng: fields.rawLocationLng
                },
                image:
                  "https://firebasestorage.googleapis.com/v0/b/" +
                  bucket.name +
                  "/o/" +
                  encodeURIComponent(uploadedFile.name) +
                  "?alt=media&token=" +
                  uuid
              })
              .then(() => {
                webpush.setVapidDetails(
                  "mailto:12-30GP004@stuents.unilorin.edu.ng",
                  "BKapuZ3XLgt9UZhuEkodCrtnfBo9Smo-w1YXCIH8YidjHOFAU6XHpEnXefbuYslZY9vtlEnOAmU7Mc-kWh4gfmE",
                  "AyVHwGh16Kfxrh5AU69E81nVWIKcUwR6a9f1X4zXT_s"
                );
                return admin
                  .database()
                  .ref("subscriptions")
                  .once("value");
              })
              .then((subscriptions) => {
                subscriptions.forEach((sub) => {
                  var pushConfig = {
                    endpoint: sub.val().endpoint,
                    keys: {
                      auth: sub.val().keys.auth,
                      p256dh: sub.val().keys.p256dh
                    }
                  };

                  webpush.sendNotification(pushConfig,JSON.stringify({
                        title: "New Post",
                        content: "New Post added!",
                        openUrl: "/help"
                      })
                    )
                    if (err) {
                        console.log(err);
                    }
                    // .catch((err) => {
                    //   console.log(err);
                    // });
                });
                res.json({ message: "Data stored", id: fields.id });
                return null;
              })
              .catch((err) => {
                res.status(500).json({ error: err });
              });
          } else {
            console.log(err);
          }
        }
      );
    });

    // The raw bytes of the upload will be in request.rawBody.  Send it to busboy, and get
    // a callback when it's finished.
    busboy.end(req.rawBody);
    // formData.parse(reqst, function(err, fields, files) {
    //   fs.rename(files.file.path, "/tmp/" + files.file.name);
    //   var bucket = gcs.bucket("YOUR_PROJECT_ID.appspot.com");
    // });
  });
});

app.post('/upload', multipartMiddleware, function(req, res) {
    // get base64 version of image
    // then send that to Kairos for training
    let base64image = fs.readFileSync(req.files.image.path, 'base64');
    var params = {
        image: base64image,
        subject_id: req.body.name,
        gallery_name: 'rekognize',
    };
    console.log('sending to Kairos for training');
    kairos_client.enroll(params).then(function(result) {
        console.log('Image Attributes : \n' + result.body );
        return res.json({'status' : true });
    }).catch(function(err) {
        console.log(err);
        return res.json({'status' : false});
    });
});

app.post('/verify', multipartMiddleware, function(req, res) {
    // get base64 version of image
    // then send that to Kairos for recognition
    let base64image = fs.readFileSync(req.files.image.path, 'base64');
    var params = {
        image: base64image,
        gallery_name: 'rekognize',
    };
    console.log('sending to Kairos for recognition');
    kairos_client.recognize(params).then(function(result) {
        console.log('Server responded with : \n' + result);
        return res.json(result.body);
    }).catch(function(err) { 
        console.log(err);
        return res.json({'status' : false});
    });  
});
