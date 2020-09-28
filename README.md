# RISC-V Barcode SDK 
**Version 7.6**

The repository aims to help developers to build `riscv64` barcode reader apps.

## Download
Dynamsoft Barcode Reader library for 64-bit RISC-V: [libDynamsoftBarcodeReader.so](https://www.dynamsoft.com/handle-download?productId=1000003&productVersionId=1000355&productEditionId=1000007&downloadLink=https://download.dynamsoft.com/test/libDynamsoftBarcodeReader.so)

## SDK License Key
Apply for a [free 30-day trial license](https://www.dynamsoft.com/customer/license/trialLicense) from Dynamsoft customer portal.

## RISC-V GNU Compiler Installation

You can either follow the [online tutorial](https://github.com/riscv/riscv-gnu-toolchain) to build and install the RISC-V compiler from source code, or install the compiler via `apt-get` commands:

```
sudo apt install g++-riscv64-linux-gnu gcc-riscv64-linux-gnu
```

## Linking Dynamsoft Barcode Library for RISC-V
Set the license key string in `ReadBarcode.cpp`:

```
reader.InitLicense("LICENSE-KEY");
```

Compile and build the sample code:

```
riscv64-linux-gnu-g++ -o ReadBarcode ReadBarcode.cpp -lDynamsoftBarcodeReader -L<library directory> -Wl,-rpath=.
```

You can get more sample code from [Dynamsoft Barcode Reader Linux edition](https://www.dynamsoft.com/Downloads/Dynamic-Barcode-Reader-Download.aspx).

## Running App on RISC-V Emulator
Download and build [QEMU](https://www.qemu.org/download/#source) for `RISCV64`:

```
wget https://download.qemu.org/qemu-5.1.0.tar.xz
tar xvf qemu-5.1.0.tar.xz
cd qemu-5.1.0
./configure --target-list=riscv64-softmmu && make
```

Download [Fedora prebuilt images](https://dl.fedoraproject.org/pub/alt/risc-v/repo/virt-builder-images/images/).

![risc-v emulator images](https://www.dynamsoft.com/codepool/wp-content/uploads/2020/09/riscv-emulator-qemu.png)

Boot Fedora using RV64GC qemu:

```
  qemu-system-riscv64 \
   -nographic \
   -machine virt \
   -smp 4 \
   -m 2G \
   -kernel Fedora-Minimal-Rawhide-*-fw_payload-uboot-qemu-virt-smode.elf \
   -bios none \
   -object rng-random,filename=/dev/urandom,id=rng0 \
   -device virtio-rng-device,rng=rng0 \
   -device virtio-blk-device,drive=hd0 \
   -drive file=Fedora-Minimal-Rawhide-20200108.n.0-sda.raw,format=raw,id=hd0 \
   -device virtio-net-device,netdev=usernet \
   -netdev user,id=usernet,hostfwd=tcp::10000-:22
```
- User name: `riscv`
- Password: `fedora_rocks!`

Copy the `ReadBarcode`, `libDynamsoftBarcodeReader.so` and the testing image `AllSupportedBarcodeTypes.tif` from your host OS to the guest OS with `scp`:

```
scp <user-name>@<ip address>:/<file path> ./
```

Run the command-line barcode reader app on RISC-V emulator:

```
./ReadBarcode AllSupportedBarcodeTypes.tif
```

![risc-v barcode sdk](https://www.dynamsoft.com/codepool/wp-content/uploads/2020/09/riscv-barcode-sdk.png)

### QEMU RISCV Documentation 
https://wiki.qemu.org/Documentation/Platforms/RISCV.

## License Agreement
https://www.dynamsoft.com/Products/barcode-reader-license-agreement.aspx

## Contact Us
If there are any questions, please feel free to contact support@dynamsoft.com.
