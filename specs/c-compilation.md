# C Compilation Specification

## Overview

TA-Lib supports two build systems: **CMake** (primary, modern) and **Autotools** (legacy, for Unix-like systems). The library compiles to both shared and static libraries, with platform-specific configurations for Linux, Windows, and other Unix-like systems.

## Build Systems

### CMake (Primary)

CMake is the primary and recommended build system, defined in `CMakeLists.txt`.

#### Requirements
- **CMake**: Version 3.18 or higher
- **Windows**: CMake 3.30 or higher (due to Wix packaging requirements)
- **C Compiler**: C11-compatible compiler (GCC, Clang, MSVC)

#### Configuration

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

#### Key CMake Options

- `BUILD_DEV_TOOLS`: Build development tools (`gen_code`, `ta_regtest`). Default: `ON`
- `CMAKE_BUILD_TYPE`: Build configuration (`Release`, `Debug`, `RelWithDebInfo`). Default: `Release`
- `CMAKE_INSTALL_PREFIX`: Installation directory. Platform-specific defaults:
  - Linux/Unix: `/usr/local`
  - Windows 64-bit: `C:/Program Files/TA-Lib`
  - Windows 32-bit: `C:/Program Files (x86)/TA-Lib`

#### Library Targets

CMake creates two library targets:

1. **`ta-lib`** (SHARED): Shared library
   - Linux: `libta-lib.so`
   - Windows: `ta-lib.dll` + `ta-lib.lib` (import library)
   - macOS: `libta-lib.dylib`

2. **`ta-lib-static`** (STATIC): Static library
   - Linux/Unix: `libta-lib.a`
   - Windows: `ta-lib-static.lib`

#### Source Organization

```
src/
├── ta_common/      # Common utilities (version, retcode, global state)
├── ta_abstract/    # Abstract layer (IDL, function registration)
└── ta_func/        # Indicator implementations (164+ files)
```

All sources are compiled into a single library.

### Autotools (Legacy)

Autotools support is provided for Unix-like systems using:
- `configure.ac`: Autoconf configuration
- `Makefile.am`: Automake makefiles
- `autogen.sh`: Bootstrap script

#### Build Process

```bash
./autogen.sh
./configure
make
sudo make install
```

#### Library Output

Autotools builds `libta-lib.la` (libtool archive) which can generate both shared and static libraries based on configuration.

## Compilation Process

### Source Compilation

1. **Common Sources**: Compiled first
   - `ta_global.c`: Global state management
   - `ta_retcode.c`: Return code definitions
   - `ta_version.c`: Version information

2. **Abstract Layer**: IDL system
   - `ta_abstract.c`: Abstract interface implementation
   - `ta_def_ui.c`: UI definitions
   - `ta_func_api.c`: Function API registration
   - `table_*.c`: 26 table files (a-z) defining indicators

3. **Indicator Functions**: 164+ implementation files
   - Each indicator in `src/ta_func/ta_*.c`
   - All compiled and linked into library

4. **Frames**: Abstract layer support
   - `ta_frame.c`: Frame management

### Compiler Flags

#### Standard C

- **C Standard**: C11 (`CMAKE_C_STANDARD 11`)
- **Include Directories**:
  - `${CMAKE_CURRENT_SOURCE_DIR}/include`
  - `${CMAKE_CURRENT_SOURCE_DIR}/src/ta_abstract`
  - `${CMAKE_CURRENT_SOURCE_DIR}/src/ta_abstract/frames`
  - `${CMAKE_CURRENT_SOURCE_DIR}/src/ta_common`
  - `${CMAKE_CURRENT_SOURCE_DIR}/src/ta_func`

#### Platform-Specific Flags

**Linux/Unix (GCC/Clang)**:
- Standard optimization flags for Release builds
- Math library linking (`-lm`)

**Windows (MSVC)**:
- `/deterministic`: Reproducible builds
- `/Brepro`: Reproducible linker output
- No math library needed (included in standard library)

### Deterministic Builds

TA-Lib supports deterministic/reproducible builds:

1. **SOURCE_DATE_EPOCH**: Set from Git commit timestamp or version-based fallback
2. **MSVC Flags**: `/deterministic` and `/Brepro` for reproducible binaries
3. **Version Control**: Uses last commit timestamp of `include/ta_common.h`

## Platform Support

### Linux

#### Supported Architectures
- **x86_64** (amd64): Primary 64-bit
- **i386** (i686): 32-bit x86
- **aarch64** (arm64): ARM 64-bit
- **armv7l** (armhf): ARM 32-bit
- **ppc64le**: PowerPC 64-bit little-endian
- **s390x**: IBM Z

#### Toolchain Files

CMake toolchain files in `cmake/`:
- `toolchain-linux-x86_64.cmake`
- `toolchain-linux-i386.cmake`
- `toolchain-linux-arm64.cmake`

#### Package Generation

- **Debian**: `.deb` packages (via CPack)
- **RPM**: `.rpm` packages (via CPack)
- **Source Tarball**: `.tar.gz` with autotools support

### Windows

#### Requirements
- **Visual Studio**: Community or Professional edition
- **CMake**: 3.30 or higher
- **Platform Environment**: Must set `Platform` env var via `vcvarsall.bat`

#### Supported Architectures
- **x64**: 64-bit (default on x64 hosts)
- **x86**: 32-bit (cross-compilation)
- **arm**: ARM 32-bit (cross-compilation)
- **arm64**: ARM 64-bit (cross-compilation)

#### Build Configuration

Windows builds require:
```cmd
vcvarsall.bat x64  # or x86, arm, arm64
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
```

#### Package Generation

- **MSI**: Windows Installer packages (via CPack/Wix)
- **ZIP**: Portable distribution packages

### macOS

Supported via CMake (standard Unix build process). No special configuration required.

## Development Tools

### gen_code

Code generation tool that creates:
- Function prototypes in `include/ta_func.h`
- Implementation boilerplate
- Language bindings (SWIG, Java, Rust)
- XML function descriptions

**Build**: Enabled by default (`BUILD_DEV_TOOLS=ON`)

**Output**: `bin/gen_code` (copied automatically)

### ta_regtest

Regression testing tool for validating indicator calculations.

**Build**: Enabled by default (`BUILD_DEV_TOOLS=ON`)

**Output**: `bin/ta_regtest` (copied automatically)

**Dependencies**: Links against `ta-lib-static` and math library (`-lm` on Unix)

## Installation

### CMake Install

```bash
cmake --install . --prefix /usr/local
```

Installs:
- **Libraries**: `lib/ta-lib.so` (shared), `lib/ta-lib.a` (static)
- **Headers**: `include/ta-lib/*.h`
- **Development Tools**: `bin/gen_code`, `bin/ta_regtest` (if built)
- **pkg-config**: `lib/pkgconfig/ta-lib.pc`

### Windows Install

Installs to:
- **64-bit**: `C:\Program Files\TA-Lib\`
- **32-bit**: `C:\Program Files (x86)\TA-Lib\`

Contents:
- `bin/ta-lib.dll`: Shared library
- `lib/ta-lib.lib`: Import library
- `lib/ta-lib-static.lib`: Static library
- `include/*.h`: Header files

### Cleanup Script

On Unix systems, CMake install includes a cleanup script that:
- Removes deprecated `ta_lib` libraries (old naming)
- Removes headers from `/usr/include` and `/usr/local/include` (now in subdirectory)
- Handles conflicts between `/usr` and `/usr/local` installations

## Packaging

### CPack Integration

CMake includes CPack configuration for generating distribution packages:

#### Debian Packages (`.deb`)
- Architecture detection: `amd64`, `i386`, `arm64`, `armhf`, etc.
- Dependencies: `libc6`
- Section: `libs`
- Priority: `optional`

#### RPM Packages (`.rpm`)
- Architecture detection: `x86_64`, `i386`, `aarch64`, etc.
- Group: `Development/Libraries`
- License: `BSD`
- Requires: `glibc`

#### Windows MSI (`.msi`)
- Uses Wix Toolset (version 4+)
- Product GUID: Generated from version and upgrade GUID
- Upgrade GUID: Architecture-specific (never changes)
- License: Includes `LICENSE.rtf`

### Package Naming

- **Source**: `ta-lib-{version}-src.tar.gz`
- **Debian**: `ta-lib_{version}_{arch}.deb`
- **RPM**: `ta-lib-{version}.{arch}.rpm`
- **Windows ZIP**: `ta-lib-{version}-windows-{arch}.zip`
- **Windows MSI**: `ta-lib-{version}-windows-{arch}.msi`

## Build Artifacts

### Libraries

**Shared Library**:
- Linux: `libta-lib.so.{version}` (with symlinks)
- Windows: `ta-lib.dll` + `ta-lib.lib`
- macOS: `libta-lib.{version}.dylib`

**Static Library**:
- Linux/Unix: `libta-lib.a`
- Windows: `ta-lib-static.lib`

### Headers

Public API headers (installed):
- `ta_abstract.h`: Abstract layer interface
- `ta_common.h`: Common types and functions
- `ta_defs.h`: Type definitions and enums
- `ta_func.h`: Indicator function prototypes (generated)
- `ta_libc.h`: Main header (includes all others)
- `ta_config.h`: Configuration (generated from `ta_config.h.cmake`)

### Development Tools

- `gen_code`: Code generator executable
- `ta_regtest`: Regression test executable

## Compiler Compatibility

### Tested Compilers

- **GCC**: 4.8+ (C11 support)
- **Clang**: 3.3+ (C11 support)
- **MSVC**: Visual Studio 2015+ (C11 support via `/std:c11`)

### C Standard Features Used

- C11 standard library functions
- `_Static_assert` (C11)
- Standard integer types (`stdint.h`)
- Standard boolean support

## Build Configuration Examples

### Release Build (Linux)

```bash
mkdir build-release
cd build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

### Debug Build

```bash
mkdir build-debug
cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### Cross-Compilation (ARM64)

```bash
mkdir build-arm64
cd build-arm64
cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-linux-arm64.cmake \
  -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Windows Build

```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## References

- CMake Configuration: `CMakeLists.txt`
- Autotools Configuration: `configure.ac`, `Makefile.am`
- Toolchain Files: `cmake/toolchain-*.cmake`
- Packaging Scripts: `scripts/package.py`
- Installation Documentation: `docs/install.md`

