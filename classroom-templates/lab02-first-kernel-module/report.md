# Lab 02 report
- Student name: Danylo Yehorov
- GitHub username: yehorovd

Replace each placeholder with your own command output. Run HOST build commands
from this lab directory and BBB module commands from `/home/debian/labs/lab02`.
Keep the complete `vermagic`, not only its release prefix.

## Prerequisites and module metadata

### BBB: `uname -r`

```text
6.18.56-v8+
```

### HOST: `cat ~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release`

```text
6.18.56-v8+
```

### HOST: `file lab02_hello.ko`

```text
lab02_hello.ko: ELF 64-bit LSB relocatable, ARM aarch64, version 1 (SYSV), BuildID[sha1]=1a130f0dc7d8b62b890cf2c36d02979cbcdd9590, not stripped
```

### HOST: `modinfo lab02_hello.ko | grep vermagic`

```text
vermagic:       6.18.56-v8+ SMP preempt mod_unload modversions aarch64
```

Explain why the full kernel releases must match and whether yours match:

```text
Modules are compiled for a specific kernel version. Therefore, the compilation environment on the host computer must be configured to use the same kernel version as the one on the board. My kernel versions match because I updated it to the one that was compiled at the end of the first lab.
```

## Load, inspect, and unload on BBB

### `sudo insmod ./lab02_hello.ko name=Student` and `sudo dmesg | tail -20`

```text
[    7.596915] vc4-drm gpu: [drm] Cannot find any crtc or sizes
[    7.599276] vc4-drm gpu: [drm] Cannot find any crtc or sizes
[    7.730730] brcmfmac: brcmf_c_process_txcap_blob: no txcap_blob available (err=-2)
[    7.731222] brcmfmac: brcmf_c_preinit_dcmds: Firmware: BCM4345/6 wl0: Aug 29 2023 01:47:08 version 7.45.265 (28bca26 CY) FWID 01-b677b91b
[    8.239856] Bluetooth: hci0: BCM: features 0x2f
[    8.241126] Bluetooth: hci0: BCM43455 37.4MHz Raspberry Pi 3+-0190
[    8.241137] Bluetooth: hci0: BCM4345C0 (003.001.025) build 0382
[   10.427542] Bluetooth: BNEP (Ethernet Emulation) ver 1.3
[   10.427560] Bluetooth: BNEP filters: protocol multicast
[   10.427574] Bluetooth: BNEP socket layer initialized
[   10.445655] Bluetooth: MGMT ver 1.23
[   10.466996] NET: Registered PF_ALG protocol family
[   10.749027] Bluetooth: RFCOMM TTY layer initialized
[   10.749054] Bluetooth: RFCOMM socket layer initialized
[   10.749071] Bluetooth: RFCOMM ver 1.11
[   13.358836] bcmgenet fd580000.ethernet: configuring instance for external RGMII (RX delay)
[   13.363370] bcmgenet fd580000.ethernet eth0: Link is Down
[   13.375697] brcmfmac: brcmf_cfg80211_set_power_mgmt: power save enabled
[  630.422918] lab02_hello: loading out-of-tree module taints kernel.
[  630.423654] hello_module: Hello, Student, from kernel space on BBB!
```

### `lsmod | grep lab02_hello`

```text
lab02_hello            12288  0
```

### `sudo rmmod lab02_hello` and `sudo dmesg | tail -20`

```text
[    7.599276] vc4-drm gpu: [drm] Cannot find any crtc or sizes
[    7.730730] brcmfmac: brcmf_c_process_txcap_blob: no txcap_blob available (err=-2)
[    7.731222] brcmfmac: brcmf_c_preinit_dcmds: Firmware: BCM4345/6 wl0: Aug 29 2023 01:47:08 version 7.45.265 (28bca26 CY) FWID 01-b677b91b
[    8.239856] Bluetooth: hci0: BCM: features 0x2f
[    8.241126] Bluetooth: hci0: BCM43455 37.4MHz Raspberry Pi 3+-0190
[    8.241137] Bluetooth: hci0: BCM4345C0 (003.001.025) build 0382
[   10.427542] Bluetooth: BNEP (Ethernet Emulation) ver 1.3
[   10.427560] Bluetooth: BNEP filters: protocol multicast
[   10.427574] Bluetooth: BNEP socket layer initialized
[   10.445655] Bluetooth: MGMT ver 1.23
[   10.466996] NET: Registered PF_ALG protocol family
[   10.749027] Bluetooth: RFCOMM TTY layer initialized
[   10.749054] Bluetooth: RFCOMM socket layer initialized
[   10.749071] Bluetooth: RFCOMM ver 1.11
[   13.358836] bcmgenet fd580000.ethernet: configuring instance for external RGMII (RX delay)
[   13.363370] bcmgenet fd580000.ethernet eth0: Link is Down
[   13.375697] brcmfmac: brcmf_cfg80211_set_power_mgmt: power save enabled
[  630.422918] lab02_hello: loading out-of-tree module taints kernel.
[  630.423654] hello_module: Hello, Student, from kernel space on BBB!
[  705.371240] hello_module: Goodbye from kernel space on BBB!
```

## Parameter tests on BBB

After implementing the student tasks, rebuild, check metadata, and copy the
module again. Unload after every successful load before testing another case.
For each case record the command, result, and relevant `dmesg` output. Capture
`echo $?` immediately after `insmod` to record its exit status.

### Valid name: `name=YourName`

```text
pi@raspberrypi:~/labs/lab02$ sudo insmod ./lab02_hello.ko name=YourName
pi@raspberrypi:~/labs/lab02$ echo $?
0
pi@raspberrypi:~/labs/lab02$ sudo dmesg | tail -1
[ 1722.609320] hello_module: Hello, YourName, from kernel space on BBB! 1/1
```

### Invalid empty name: `name=` (must return `-EINVAL`)

```text
pi@raspberrypi:~/labs/lab02$ sudo insmod ./lab02_hello.ko name=
insmod: ERROR: could not insert module ./lab02_hello.ko: Invalid parameters
pi@raspberrypi:~/labs/lab02$ echo $?
1
```

### Valid count: test `count=1` and `count=10`

```text
pi@raspberrypi:~/labs/lab02$ sudo insmod ./lab02_hello.ko count=1
pi@raspberrypi:~/labs/lab02$ echo $?
0
pi@raspberrypi:~/labs/lab02$ sudo dmesg | tail -1
[ 1783.082288] hello_module: Hello, Danylo, from kernel space on BBB! 1/1
pi@raspberrypi:~/labs/lab02$ sudo rmmod lab02_hello
pi@raspberrypi:~/labs/lab02$ sudo insmod ./lab02_hello.ko count=10
pi@raspberrypi:~/labs/lab02$ echo $?
0
pi@raspberrypi:~/labs/lab02$ sudo dmesg | tail -10
[ 1813.004761] hello_module: Hello, Danylo, from kernel space on BBB! 1/10
[ 1813.004789] hello_module: Hello, Danylo, from kernel space on BBB! 2/10
[ 1813.004799] hello_module: Hello, Danylo, from kernel space on BBB! 3/10
[ 1813.004808] hello_module: Hello, Danylo, from kernel space on BBB! 4/10
[ 1813.004815] hello_module: Hello, Danylo, from kernel space on BBB! 5/10
[ 1813.004823] hello_module: Hello, Danylo, from kernel space on BBB! 6/10
[ 1813.004830] hello_module: Hello, Danylo, from kernel space on BBB! 7/10
[ 1813.004837] hello_module: Hello, Danylo, from kernel space on BBB! 8/10
[ 1813.004844] hello_module: Hello, Danylo, from kernel space on BBB! 9/10
[ 1813.004851] hello_module: Hello, Danylo, from kernel space on BBB! 10/10
```

### Invalid count: test `count=0` and `count=11` (must return `-EINVAL`)

```text
pi@raspberrypi:~/labs/lab02$ sudo insmod ./lab02_hello.ko count=11
insmod: ERROR: could not insert module ./lab02_hello.ko: Invalid parameters
pi@raspberrypi:~/labs/lab02$ echo $?
1
pi@raspberrypi:~/labs/lab02$ sudo insmod ./lab02_hello.ko count=0
insmod: ERROR: could not insert module ./lab02_hello.ko: Invalid parameters
pi@raspberrypi:~/labs/lab02$ echo $?
1
```

## Questions

1. Why does a kernel module not have `main()`?

   Kernel module doesn't have such entry point as it launches in different way then userspace program.

2. What does `module_init()` do?

   This function is called when the module is loaded into the kernel.

3. What does `vermagic` show?

   Kernel version for which module was compiled.

4. Why can `insmod` fail with `invalid module format`?

   Module was compiled for different kernel version.

5. What does the `name` parameter do, and what do its permissions `0444` mean?

   Parameter `name` sets name which will be used in greatings during module loading. Persmission `0444` means that file in sysfs will be accessible only for read be everybody (owner/group/others).
```text
pi@raspberrypi:~/labs/lab02$ ls -l /sys/module/lab02_hello/parameters/
total 0
-r--r--r-- 1 root root 4096 Oct 12 18:47 count
-r--r--r-- 1 root root 4096 Oct 12 18:47 name
```

Submit `src/hello.c`, `Makefile`, and this completed `report.md`. Do not commit
`.ko`, `.o`, `.mod`, `.mod.c`, `.cmd`, `Module.symvers`, or `modules.order`.
