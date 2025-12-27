---
hide:
    - toc
---
Instructions are for installing the C/C++ shared, static libraries and headers on your system.

Latest release is [0.6.4 on Github](https://github.com/ta-lib/ta-lib/releases/latest)

For python and Rusers, see instead [ta-lib-python](https://github.com/TA-Lib/ta-lib-python) or [ta-lib-R](https://github.com/serkor1/ta-lib-R)

- [Linux](#linux)
    - [Debian packages](#linux-debian-packages)
    - [Build from source](#linux-build-from-source)


## Linux

### Linux Debian Packages

Recommended for all debian-based distributions (e.g. Ubuntu, Mint...)

1. **Download** the `.deb` package matching your platform:

    | Platform | Download |
    |------------------------|--|
    | Intel/AMD 64-bits | [ta-lib_0.6.4_amd64.deb](https://github.com/ta-lib/ta-lib/releases/download/v0.6.4/ta-lib_0.6.4_amd64.deb) |
    | ARM64 (e.g. Raspberry Pi)| [ta-lib_0.6.4_arm64.deb](https://github.com/ta-lib/ta-lib/releases/download/v0.6.4/ta-lib_0.6.4_arm64.deb) |
    | Intel/AMD 32-bits| [ta-lib_0.6.4_i386.deb](https://github.com/ta-lib/ta-lib/releases/download/v0.6.4/ta-lib_0.6.4_i386.deb) |

2. **Install or Update**:
   ```bash
   # For Intel/AMD (64 bits)
   sudo dpkg -i ta-lib_0.6.4_amd64.deb
   # or
   sudo dpkg -i ta-lib_0.6.4_arm64.deb
   # or
   sudo dpkg -i ta-lib_0.6.4_i386.deb
   ```
   If you choose to uninstall do:
    ```bash
    sudo dpkg -r ta-lib
    ```

### Linux Build from Source

1. **Download** latest [ta-lib-0.6.4-src.tar.gz](https://github.com/ta-lib/ta-lib/releases/download/v0.6.4/ta-lib-0.6.4-src.tar.gz) (or, alternatively, clone down [https://github.com/ta-lib/ta-lib/](https://github.com/ta-lib/ta-lib/) and checkout the main branch)

2. **Extract the Tarball** if you downloaded the source manually:
   ```bash
   tar -xzf ta-lib-0.6.4-src.tar.gz
   cd ta-lib-0.6.4
   ```

3. **Build and Install**:
   ```bash
   ./configure
   make
   sudo make install
   ```

    Follow the same procedure for an update (the older version is overwritten, no need to uninstall).

    If you choose to uninstall do:
    ```bash
    sudo make uninstall
    ```

