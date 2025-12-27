# TA-Lib Specification Documents

This directory contains comprehensive specification documentation for the TA-Lib project, covering technical indicators, Python wrappers, C compilation, and system dependencies.

## Overview

TA-Lib is a Technical Analysis Library written in C/C++ that provides over 200 technical analysis indicators. The library uses a sophisticated code generation system to maintain consistency across multiple language bindings and platforms.

## Specification Documents

### [Technical Indicators](specs/technical-indicators.md)

Comprehensive documentation of the technical indicator system:

- **Architecture**: Three-layer system (Abstract, Implementation, Code Generation)
- **Indicator Categories**: 10 functional groups (Overlap Studies, Momentum, Volatility, etc.)
- **Code Generation**: How indicators are automatically generated from abstract definitions
- **Implementation Patterns**: Common patterns and utility functions
- **Adding New Indicators**: Step-by-step guide for contributors

**Key Topics**:
- Abstract layer (IDL system) and table files
- Indicator implementation structure
- Function signature patterns
- Lookback calculations
- Utility functions and memory management

### [Python Wrapper](specs/python-wrapper.md)

Documentation of the SWIG-based Python bindings:

- **SWIG Architecture**: How C functions are wrapped for Python
- **Typemaps**: Type conversion rules for Python-specific behavior
- **Error Handling**: TA_RetCode to Python exception conversion
- **API Mapping**: How C function signatures translate to Python
- **Build Process**: Prerequisites and build steps
- **Usage Examples**: Python code examples

**Key Topics**:
- SWIG interface files and typemaps
- Array handling (input/output)
- Optional parameter support
- Memory management
- Testing framework

### [C Compilation](specs/c-compilation.md)

Build system and compilation documentation:

- **Build Systems**: CMake (primary) and Autotools (legacy)
- **Platform Support**: Linux configurations
- **Compilation Process**: Source organization and build steps
- **Library Targets**: Shared and static library generation
- **Packaging**: CPack integration for distribution packages
- **Development Tools**: gen_code and ta_regtest

**Key Topics**:
- CMake configuration and options
- Platform-specific build requirements
- Cross-compilation support
- Installation process
- Package generation (DEB, RPM, MSI, ZIP)

### [Dependencies](specs/dependencies.md)

System and build dependency documentation:

- **Runtime Dependencies**: Standard C library and math library
- **Build Dependencies**: Compilers, CMake, Autotools
- **Optional Dependencies**: SWIG, Python headers, JDK
- **Platform-Specific**: Requirements for Linux
- **Version Requirements**: Minimum and recommended versions
- **Dependency Checking**: How the build system verifies dependencies

**Key Topics**:
- Required headers and functions
- Build tool requirements
- Packaging dependencies
- Installation examples by platform
- pkg-config support

## Quick Reference

### For Developers

- **Adding Indicators**: See [Technical Indicators](specs/technical-indicators.md#adding-new-indicators)
- **Building from Source**: See [C Compilation](specs/c-compilation.md#build-configuration-examples)
- **Python Integration**: See [Python Wrapper](specs/python-wrapper.md#usage-examples)

### For System Administrators

- **Installation**: See [C Compilation](specs/c-compilation.md#installation)
- **Dependencies**: See [Dependencies](specs/dependencies.md#dependency-installation-examples)
- **Packaging**: See [C Compilation](specs/c-compilation.md#packaging)

### For Users

- **Python API**: See [Python Wrapper](specs/python-wrapper.md#python-api-mapping)
- **C API**: See [Technical Indicators](specs/technical-indicators.md#function-signature-pattern)
- **Indicator Categories**: See [Technical Indicators](specs/technical-indicators.md#indicator-categories)

## Document Organization

All specification documents are located in the `specs/` directory:

```
specs/
├── technical-indicators.md    # Indicator architecture and implementation
├── python-wrapper.md          # Python bindings via SWIG
├── c-compilation.md           # Build systems and compilation
└── dependencies.md            # System and build dependencies
```

## Related Documentation

- **API Documentation**: `docs/api.md` - C/C++ API reference
- **Installation Guide**: `docs/install.md` - Installation instructions
- **Function List**: `docs/functions.md` - Complete list of indicators
- **Wrappers**: `docs/wrappers.md` - Language binding information
- **Developer README**: `README-DEVS.md` - Development guidelines

## Contributing

When contributing to TA-Lib:

1. Review the relevant specification document for your area
2. Follow the patterns and conventions documented
3. Update specifications if you make architectural changes
4. Ensure code generation compatibility (if modifying indicators)

## Version Information

These specifications correspond to **TA-Lib version 0.6.4**.

For the latest version information, see:
- `VERSION` file
- `src/ta_common/ta_version.c`
- GitHub releases: https://github.com/TA-Lib/ta-lib/releases

