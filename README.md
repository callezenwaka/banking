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

## From source directory
```bash
rm -rf build     # Clean previous build
mkdir build      # Create new build directory
cd build         # Enter build directory
cmake ..         # Configure
cmake --build .  # Build
ctest --output-on-failure  # Run tests
```

## Generate build files and compile:
```bash
cd build          # Make sure you're in the build directory
cmake --build .   # Rebuild the project
```

## Run the bank app:
```bash
./bank
```

## Execute the bank tests:
```bash
./bank_tests
```

## Run cmake with:
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

## Some useful CTest commands
```bash
# Run tests with detailed output
ctest --output-on-failure

# Run tests verbosely (shows the actual test output)
ctest -V

# Run specific tests using regex
ctest -R test_account    # Runs tests matching "test_account"

# Run tests in parallel (with 4 threads)
ctest -j4

# List all available tests without running them
ctest -N

# Run tests with a label
ctest -L unit_tests

# Show test execution time
ctest --output-on-failure -D ExperimentalTest
```