# Banking Application

## Folder structure
```code
calculator/
│
├── src/                     # Source files
│   ├── main.cpp            # Main program entry
│   ├── calculator.cpp      # Calculator class implementation
│   └── utils.cpp           # Utility functions (input validation, etc.)
│
├── include/                 # Header files
│   ├── calculator.hpp      # Calculator class declaration
│   └── utils.hpp           # Utility functions declarations
│
├── tests/                  # Test files
│   ├── test_main.cpp      # Test runner
│   └── test_calculator.cpp # Calculator tests
│
├── build/                  # Build output (generated)
│   └── .gitkeep           # Empty file to track empty directory
│
├── docs/                   # Documentation
│   └── README.md          # Project documentation
│
├── CMakeLists.txt         # CMake build configuration
├── .gitignore             # Git ignore file
└── README.md              # Project overview
```

## Generate build files and compile:

```bash
cmake ..
make
```

## Run the calculator:
```bash
./calculator
```

## Build the project with tests:
```bash
cd build
cmake ..
make
```

## Execute the tests:
```bash
./calculator_tests
```

## Run cmake with:
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```