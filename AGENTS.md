## Cursor Cloud specific instructions

This is **TA-Lib** (Technical Analysis Library) — a pure C library providing 100+ financial market technical analysis functions. There are no external services, databases, or web servers.

### Build

```bash
cd /workspace
mkdir -p build && cd build
CC=gcc CXX=g++ cmake -DBUILD_DEV_TOOLS=ON ..
cmake --build . -j$(nproc)
```

**Gotcha:** The default C/C++ compiler on this VM is Clang, which fails CMake's CXX compiler check due to a missing `-lstdc++` linkage path. Always set `CC=gcc CXX=g++` when running cmake. The `CMakeLists.txt` uses `project(ta-lib)` without `LANGUAGES C`, so CMake tests both C and CXX compilers even though the project is pure C.

### Test

Run the regression test suite from the build directory:

```bash
./build/bin/ta_regtest
```

All tests should end with `* All tests succeeded. Enjoy the library. *`.

### Key directories

- `src/ta_func/` — core TA function implementations (one .c file per function)
- `src/ta_abstract/` — abstract interface / IDL describing function signatures
- `src/tools/gen_code/` — code generator (dev tool)
- `src/tools/ta_regtest/` — regression test suite
- `include/` — public API headers
