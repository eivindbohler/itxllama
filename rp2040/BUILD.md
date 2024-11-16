# Build

Get the Raspberry Pi Pico SDK version 1.5.1 and compiler:

```sh
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
git clone https://github.com/raspberrypi/pico-sdk
export PICO_SDK_PATH=/path/to/pico-sdk
cd $PICO_SDK_PATH
git checkout 1.5.1
git submodule update --init
```

Update to the latest TinyUSB release 0.17.0 and apply the dual USB patch:
```sh
cd $PICO_SDK_PATH/lib/tinyusb
git checkout 0.17.0
patch -p1 < /path/to/itxllama/rp2040/tinyusb-0.17.0-dualusb.patch
```

Generate the UF2 file:
```sh
cd /path/to/itxllama/rp2040
git submodule update --init
mkdir build
cd build
cmake ..
make
```