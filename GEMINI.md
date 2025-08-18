# GEMINI.md

## Project Overview

This is an Android kernel source tree for a OnePlus device based on the Qualcomm SM4350 platform (codename: holi). The kernel is based on the `android11-5.4` branch.

The project includes the full kernel source code, as well as tools and scripts for building and packaging the kernel for deployment on a device. The `AnyKernel3` directory contains a script for creating a flashable zip file that can be used to install the kernel on a device with a custom recovery.

## Building and Running

**Building the kernel:**

The kernel can be built using the provided build scripts and configuration files. The main build configuration is `arch/arm64/configs/vendor/holi_defconfig`.

To build the kernel, you would typically use a command like this:

```bash
# TODO: Add the exact build command here.
# It likely involves setting up the build environment and then running a make command.
# For example:
# . build/envsetup.sh
# lunch <target>
# make -j$(nproc)
```

**Running the kernel:**

Once the kernel is built, it can be packaged into a flashable zip file using the `AnyKernel3` script. This zip file can then be flashed to the device using a custom recovery like TWRP.

## Development Conventions

*   **Patch Submissions:** The `README.md` file contains detailed instructions on how to submit patches to the Android Common Kernels. It is important to follow these guidelines when contributing to the project.
*   **Coding Style:** The project follows the Linux kernel coding style. The `.clang-format` file in the root directory suggests that `clang-format` is used to enforce a consistent coding style.
*   **Configuration:** The kernel is configured using `defconfig` files. The main configuration for this device is `arch/arm64/configs/vendor/holi_defconfig`. Any changes to the kernel configuration should be made in this file.
