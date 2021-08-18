# Unikraft Application With 9pfs Support

This builds a Unikraft application image with (persistent) 9pfs support and command line arguments.
It is used to simulate the update of a (persistent) state with command line argument values.

The resulting executable is passed two command line arguments:

* the file in the filesystem that is to be updated (it contains a serialized integer value);
  the file has to be part of the filesystem
* the value (integer, positive or negative) that will be added to the value in the file

[lib-newlib](https://github.com/unikraft/lib-newlib) is required.

## Configure

Update the `Makefile` to point to the correct location for the Unikraft (`UK_ROOT`) and libraries folders (`UK_LIBS`, `LIBS`).

Configure the application via the configuration screen:
```
make menuconfig
```
The basic configuration is loaded from the `Config.uk` file.
Then add support for 9pfs, by selecting `Library Configuration` -> `vfscore: VFS Core Interface` -> `vfscore: VFS Configuration`.
The select `Automatically mount a root filesystem (/)` and select `9pfs`.
For the `Default root device` option fill `fs0`.
You should end up with an image such as the one in `9pfs_config.png`.
Save the conifugration and exit.

## Build

Build the application:
```
make
```
The first building of the application will take some time, as library files are downloaded, unpacked and built.
The resulting KVM image is `build/app-emtpy_kvm-x86_64`.
The image name may be updated in the configuration screen (`make menuconfig`), using the `Image name` option.

## Run

Create the `rootfs/` folder where the persistent state is going to be stored.
Create a file to store the state:
```
mkdir rootfs
touch rootfs/state
```

Run the application in QEMU/KVM using the `qemu-guest` script (it's copied from the [kraft repositoriy](https://github.com/unikraft/kraft/blob/staging/scripts/qemu-guest)):
```
$ ./qemu-guest -k build/app-empty_kvm-x86_64 -a "state 73" -e rootfs
```
The `-a "state 73"` option means adding `73` to the value in `state`.
As there is nothing in `state`, the new value will be `73`.
```
$ xxd rootfs/state
00000000: 4900 0000                                I...
```

You can also use negative values:
```
$ ./qemu-guest -k build/app-empty_kvm-x86_64 -a "state -72" -e rootfs
$ xxd rootfs/state
00000000: 0100 0000
```

Running the `qemu-guest` command requires `root` (`sudo`) privileges.
