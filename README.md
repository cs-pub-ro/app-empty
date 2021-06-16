# Unikraft Test Application

This builds a Unikraft application image with an empty main function.
It successfully does nothing.
It's useful for runnning-time and image-size measurements.

No Unikraft external libraries are required.

## Build

Configure the application via the configuration screen:
```
make menuconfig
```
The configuration is loaded from the `Config.uk` file.
As such, simply save the configuration and exit.

Build the application:
```
make
```
The first building of the application will take some time, as library files are downloaded, unpacked and built.
The resulting KVM image is `build/app-emtpy_kvm-x86_64`.
The resulting linuxu image is `build/app-emtpy_linuxu-x86_64`.
The image name may be updated in the configuration screen (`make menuconfig`), using the `Image name` option.

## Run

Run the linuxu application by using the executable image file:
```
./build/app-empty_linuxu-x86_64
```

Run the application in QEMU/KVM using the `qemu-guest` script (it's copied from the [kraft repositoriy](https://github.com/unikraft/kraft/blob/staging/scripts/qemu-guest)):
```
qemu-guest -k build/app-empty_kvm-x86_64
```
The above command requires `root` (`sudo`) privileges.
