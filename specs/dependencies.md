# Dependencies Specification

## Overview

TA-Lib has minimal external dependencies, relying primarily on standard C library functions and the math library. The build system requires additional tools for compilation and packaging, but the runtime library itself is self-contained.

## Runtime Dependencies

### System Libraries

#### Standard C Library (libc)

**Required**: Yes (always present on all systems)

TA-Lib uses standard C library functions extensively. The following functions are checked during configuration:

**String Functions**:
- `strcasecmp`: Case-insensitive string comparison
- `strchr`: Character search in string
- `strerror`: Error message retrieval
- `strncasecmp`: Case-insensitive string comparison (limited length)
- `strrchr`: Reverse character search
- `strstr`: Substring search
- `strtol`: String to long conversion
- `strtoul`: String to unsigned long conversion
- `strcoll`: Locale-aware string comparison
- `strftime`: Formatted time string

**Memory Functions**:
- `memmove`: Memory copy (handles overlapping regions)
- `memset`: Memory initialization

**Character Functions**:
- `isascii`: ASCII character check
- `mblen`: Multi-byte character length

**Locale Functions**:
- `localeconv`: Locale-specific numeric formatting

**I/O Functions**:
- `vprintf`: Variable argument printf

All these functions are part of the standard C library and available on all compliant systems.

#### Math Library (libm)

**Required**: Yes (on Unix-like systems)

**Windows**: Math functions are included in the standard library, no separate linking needed.

**Unix/Linux**: Must link against `-lm` (math library)

**Functions Used**:
- `floor`: Floor function
- `modf`: Extract fractional part
- `pow`: Power function
- `sqrt`: Square root

These are standard math functions used throughout indicator calculations.

### Required Headers

The following standard headers are checked and used:

- `float.h`: Floating-point limits and characteristics
- `inttypes.h`: Fixed-width integer types
- `limits.h`: Integer limits
- `locale.h`: Locale-specific functions
- `stddef.h`: Standard definitions (NULL, size_t, ptrdiff_t)
- `stdint.h`: Fixed-width integer types
- `stdlib.h`: Standard library functions
- `string.h`: String manipulation functions
- `unistd.h`: POSIX operating system API (Unix only)
- `wchar.h`: Wide character support
- `wctype.h`: Wide character classification

All headers are part of the standard C library or POSIX standard.

### Type Dependencies

**Standard Types**:
- `size_t`: Size type (checked for existence)
- `ptrdiff_t`: Pointer difference type (checked for existence)

**Platform-Specific**:
- `struct tm`: Time structure (checked for location: `sys/time.h` or standard headers)

## Build Dependencies

### Required Build Tools

#### C Compiler

**Required**: Yes

**Supported Compilers**:
- **GCC**: 4.8+ (C11 support required)
- **Clang**: 3.3+ (C11 support required)
- **MSVC**: Visual Studio 2015+ (C11 support via `/std:c11`)

**C Standard**: C11 (`-std=c11` or equivalent)

#### CMake (Primary Build System)

**Required**: Yes (for CMake builds)

**Version Requirements**:
- **Minimum**: 3.18
- **Windows**: 3.30 or higher (for Wix packaging support)

**Download**: https://cmake.org/download/

#### Autotools (Legacy Build System)

**Required**: Only for Autotools-based builds

**Components**:
- **Autoconf**: 2.71 or higher
- **Automake**: 1.4 or higher (foreign mode)
- **Libtool**: For shared library support

**Bootstrap**: `autogen.sh` script handles autotools setup

### Optional Build Tools

#### SWIG (For Language Bindings)

**Required**: No (only for building Python/Perl wrappers)

**Version**: 1.3.21 or higher (1.3.x family)

**Purpose**: Generate Python and Perl bindings

**Download**: http://www.swig.org

#### Python Development Headers

**Required**: No (only for building Python wrapper)

**Purpose**: Compile Python extension modules

**Package Names**:
- Debian/Ubuntu: `python3-dev` or `python-dev`
- Red Hat/CentOS: `python3-devel` or `python-devel`
- macOS: Included with Python installation

#### Java Development Kit (JDK)

**Required**: No (only for generating Java bindings)

**Version**: OpenJDK 21 or compatible

**Purpose**: Generate Java bindings via `gen_code`

**Package Names**:
- Debian/Ubuntu: `openjdk-21-jdk`
- Red Hat/CentOS: `java-21-openjdk-devel`

#### mcpp (C Preprocessor)

**Required**: No (only for code generation)

**Purpose**: Used by `gen_code` for preprocessing C templates

**Package Names**:
- Debian/Ubuntu: `mcpp`
- Red Hat/CentOS: `mcpp` (may need EPEL)

**Alternative**: System C preprocessor (`cpp`) may work

### Packaging Dependencies

#### CPack (Included with CMake)

**Required**: For generating distribution packages

**Generators**:
- **DEB**: Debian package generation
- **RPM**: RPM package generation (requires `rpmbuild`)
- **WIX**: Windows MSI generation (requires Wix Toolset)

#### Wix Toolset (Windows Only)

**Required**: For generating Windows MSI installers

**Version**: Wix 4 or higher

**Download**: https://wixtoolset.org/

#### rpmbuild (Linux Only)

**Required**: For generating RPM packages

**Package Names**:
- Debian/Ubuntu: `rpm` (from RPM project)
- Red Hat/CentOS: `rpm-build` (usually pre-installed)

## Platform-Specific Dependencies

### Linux

#### Runtime
- **glibc**: Standard C library (version 2.17+ recommended)
- **libm**: Math library (part of glibc)

#### Build
- **GCC** or **Clang**: C compiler
- **make**: Build tool
- **pkg-config**: For library discovery (optional)

#### Package Dependencies (from .spec/.deb)

**Debian/Ubuntu**:
- `libc6`: Standard C library (runtime)

**Red Hat/CentOS**:
- `glibc`: Standard C library (runtime)

### Windows

#### Runtime
- **MSVCRT**: Microsoft Visual C++ Runtime (included with Windows)
- **UCRT**: Universal C Runtime (Windows 10+)

#### Build
- **Visual Studio**: 2015 or higher
  - Community Edition is sufficient
  - Requires C++ build tools
- **CMake**: 3.30 or higher
- **Wix Toolset**: For MSI generation (optional)

#### No External Runtime Dependencies

TA-Lib on Windows is statically linked or uses DLLs that are part of Windows, requiring no additional runtime dependencies.

### macOS

#### Runtime
- **libSystem**: System library (includes libc and libm)

#### Build
- **Xcode Command Line Tools**: Includes Clang and make
- **CMake**: For modern builds

## Dependency Checking

### Autotools Checks

The `configure.ac` script performs the following checks:

**Header Checks**:
```autoconf
AC_CHECK_HEADERS([float.h inttypes.h limits.h locale.h stddef.h stdint.h stdlib.h string.h unistd.h wchar.h wctype.h])
```

**Function Checks**:
```autoconf
AC_CHECK_FUNCS([floor isascii localeconv mblen memmove memset modf pow sqrt strcasecmp strchr strerror strncasecmp strrchr strstr strtol strtoul])
```

**Type Checks**:
```autoconf
AC_CHECK_TYPES([ptrdiff_t])
AC_TYPE_SIZE_T
```

**Library Checks**:
```autoconf
LT_LIB_M  # Checks for math library
```

### CMake Checks

CMake performs similar checks in `CMakeLists.txt`:

```cmake
check_include_files(float.h HAVE_FLOAT_H)
check_function_exists(floor HAVE_FLOOR)
check_type_size(size_t SIZEOF_SIZE_T)
```

These checks configure `ta_config.h` with `HAVE_*` defines.

## pkg-config Support

TA-Lib provides a `ta-lib.pc` file for pkg-config integration:

```
prefix=/usr/local
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include/ta-lib

Name: ta-lib
Description: TA-Lib : Technical Analysis Library
URL: https://github.com/TA-Lib/ta-lib
Version: 0.6.4
Cflags: -I${includedir}
Libs: -L${libdir} -lta-lib
```

**Usage**:
```bash
pkg-config --cflags ta-lib
pkg-config --libs ta-lib
```

## Version Requirements Summary

### Minimum Versions

| Component | Minimum Version | Notes |
|-----------|----------------|-------|
| CMake | 3.18 | 3.30+ on Windows |
| GCC | 4.8 | C11 support |
| Clang | 3.3 | C11 support |
| MSVC | 2015 | C11 support |
| Autoconf | 2.71 | For autotools builds |
| SWIG | 1.3.21 | For wrappers only |
| Python | 2.3+ | For wrapper only |
| JDK | 21 | For Java bindings only |

### Recommended Versions

- **CMake**: Latest stable (3.28+)
- **GCC**: 7.0+ or Clang 10.0+
- **Python**: 3.6+ (for wrapper)

## Dependency Installation Examples

### Debian/Ubuntu

```bash
# Build dependencies
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    automake \
    libtool \
    autogen \
    mcpp

# Optional: For Python wrapper
sudo apt install -y swig python3-dev

# Optional: For Java bindings
sudo apt install -y openjdk-21-jdk

# Optional: For packaging
sudo apt install -y rpm
```

### Red Hat/CentOS/Fedora

```bash
# Build dependencies
sudo yum install -y \
    gcc \
    cmake \
    automake \
    libtool \
    autoconf \
    mcpp

# Optional: For Python wrapper
sudo yum install -y swig python3-devel

# Optional: For Java bindings
sudo yum install -y java-21-openjdk-devel

# Optional: For packaging
sudo yum install -y rpm-build
```

### macOS (Homebrew)

```bash
# Build dependencies
brew install cmake automake libtool

# Optional: For Python wrapper
brew install swig

# Optional: For Java bindings
brew install openjdk@21
```

### Windows

1. Install Visual Studio (Community Edition sufficient)
2. Install CMake 3.30+
3. (Optional) Install Wix Toolset for MSI generation

## No External Runtime Dependencies

**Important**: Once compiled, TA-Lib has **no external runtime dependencies** beyond the standard C library and math library, which are part of all operating systems. This makes TA-Lib highly portable and easy to distribute.

## References

- Build Configuration: `CMakeLists.txt`, `configure.ac`
- Dependency Checks: `configure.ac` (lines 22-40)
- pkg-config: `ta-lib.pc.in`
- Package Specs: `ta-lib.spec.in`, `ta-lib.dpkg.in`

