# NESLA (NESL-Assembler)

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE.md) [![Build Status](https://github.com/majestic53/nesla/workflows/Build/badge.svg)](https://github.com/majestic53/nesla/actions/workflows/build.yml) [![Test Status](https://github.com/majestic53/nesla/workflows/Test/badge.svg)](https://github.com/majestic53/nesla/actions/workflows/test.yml)

### A lightweight NES assembler, written in C.

This project assembles source files to be run on the [NESL emulator](https://github.com/majestic53/nesl).

__NOTE__: This project is a still a work-in-progress. Some features may be incomplete or may contain bugs.

## Latest release

The latest release can be found here: `TBD`

## Building from source

__NOTE__: This project has been tested under Linux, using the GCC compiler. Some modifications may be required to build with a different OS/compiler.

### Cloning the project

Clone the project from the repo:

```bash
git clone https://github.com/majestic53/nesla
```

### Building the project

Navigate into the project directory and run make to build the binary:

```bash
cd nesla && make
```

## Using the binary

Launch the binary from `build/`:

```
nesla [options] file
```

### Options

The following options are available:

|Option|Description             |
|:-----|:-----------------------|
|-h    |Show help information   |
|-o    |Set output directory    |
|-v    |Show version information|

#### Examples

To assemble a file into the current directory, run the following command:

```bash
nesla file
```

To assemble a file into a specific output directory, run the following command:

```bash
nesl -o directory file
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](LICENSE.md).
