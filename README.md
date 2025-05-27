# Currency Exchange Application

A fully Object-Oriented C++ console application for currency conversion and exchange rate management. This application provides real-time currency conversion capabilities using up-to-date exchange rates for various world currencies, built with modern OOP principles for maintainability and extensibility.

## Features

- Fully Object-Oriented architecture with clean separation of concerns
- Support for 170+ world currencies
- Real-time currency conversion
- User-friendly console interface
- Accurate exchange rates
- Easy-to-use menu system
- Modular and maintainable codebase

## Project Structure

```
currency-exchange/
├── main.cpp              # Main application entry point
├── currencies.txt        # Currency exchange rates database
├── include/             # Header files
│   ├── clsCurrencyUI.h  # Currency UI interface
│   ├── clsCurrency.h    # Currency class definition
│   ├── clsMainScreen.h  # Main screen interface
│   ├── clsString.h      # String utilities
│   ├── read.h           # File reading utilities
│   └── utils.h          # General utilities
├── src/                 # Source files
│   └── read.cpp         # File reading implementation
└── build/              # Compiled binaries
    └── output.exe      # Executable file
```

## Prerequisites

- C++ Compiler (GCC/G++)
- Make sure you have a C++11 (or later) compatible compiler

## Building the Project

To build the project, you can use the following command in the root directory:

```bash
g++ main.cpp src/*.cpp -I include -o build/output.exe -mconsole
```

Alternatively, if you're using Visual Studio Code, you can use the built-in build task:

1. Press `Ctrl+Shift+B` or
2. Select `Terminal > Run Build Task`

## Running the Application

After building, you can run the application by executing:

```bash
./build/output.exe
```

## Currency Data

The application uses `currencies.txt` as its database, which contains:

- Country names
- Currency codes (ISO 4217)
- Currency names
- Exchange rates (relative to USD)

## File Format

The currency data file uses the following format:

```
CountryName#//#CurrencyCode#//#CurrencyName#//#ExchangeRate
```

Example:

```
United States of America#//#USD#//#US Dollar#//#1.000000
France#//#EUR#//#Euro#//#0.900000
```

## License

This project is open source and available under the MIT License.
