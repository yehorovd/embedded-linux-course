# Lab 01 report

- Student name: Danylo Yehorov
- GitHub username: yehorovd
- Image filename: 2026-10-06-raspios-trixie-arm64.img
- SHA-256 (paste the checksum and state whether it matches the lab):

2e0024bca282503a5cb6755500cbd7998cfc141c8f452808b59f9178623d2f0d

The cecksum doesn't much as image for raspberry pi used.

Replace each placeholder with your own command output. Label HOST and BBB
results. Do not include passwords or private keys.

## Running Linux on BBB

### BBB: `uname -r`

```text
6.18.56-v8+
```

### BBB: `cat /etc/os-release`

```text
PRETTY_NAME="Debian GNU/Linux 13 (trixie)"
NAME="Debian GNU/Linux"
VERSION_ID="13"
VERSION="13 (trixie)"
VERSION_CODENAME=trixie
DEBIAN_VERSION_FULL=13.7
ID=debian
HOME_URL="https://www.debian.org/"
SUPPORT_URL="https://www.debian.org/support"
BUG_REPORT_URL="https://bugs.debian.org/"
```

### BBB: `lsblk`

```text
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
loop0         7:0    0    2G  0 loop 
mmcblk0     179:0    0   58G  0 disk 
├─mmcblk0p1 179:1    0  512M  0 part /boot/firmware
└─mmcblk0p2 179:2    0 57.4G  0 part /
zram0       254:0    0    2G  0 disk [SWAP]
```

### BBB: `ip addr`

```text
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host noprefixroute 
       valid_lft forever preferred_lft forever
2: eth0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN group default qlen 1000
    link/ether dc:a6:32:27:b9:dc brd ff:ff:ff:ff:ff:ff
3: usb0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc fq_codel state DOWN group default qlen 1000
    link/ether a2:d3:e1:f3:c1:56 brd ff:ff:ff:ff:ff:ff
    inet 10.12.194.1/28 brd 10.12.194.15 scope global noprefixroute usb0
       valid_lft forever preferred_lft forever
4: wlan0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether dc:a6:32:27:b9:dd brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.113/24 brd 192.168.1.255 scope global dynamic noprefixroute wlan0
       valid_lft 82628sec preferred_lft 82628sec
    inet6 fe80::243a:b426:d7c1:a798/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
```

## First user-space program

### HOST, in this lab directory: `file build/hello`

```text
build/hello: ELF 64-bit LSB pie executable, ARM aarch64, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-aarch64.so.1, for GNU/Linux 3.7.0, not stripped
```

### BBB: `/home/debian/labs/lab01/hello`

```text
Hello from Lab 01 on BeagleBone Black!
```

## Shared kernel workspace

### HOST: `ls -lh ~/bbb-workspace/kernel/bb-kernel/deploy`

```text
-rw-r--r-- 1 qTAbNM qTAbNM  32K Oct 12 16:19 bcm2710-rpi-2-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  34K Oct 12 16:19 bcm2710-rpi-3-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  35K Oct 12 16:19 bcm2710-rpi-3-b-plus.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  33K Oct 12 16:19 bcm2710-rpi-cm0.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  32K Oct 12 16:19 bcm2710-rpi-cm3.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  33K Oct 12 16:19 bcm2710-rpi-zero-2.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  33K Oct 12 16:19 bcm2710-rpi-zero-2-w.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  56K Oct 12 16:19 bcm2711-rpi-400.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  56K Oct 12 16:19 bcm2711-rpi-4-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  56K Oct 12 16:19 bcm2711-rpi-cm4.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  39K Oct 12 16:19 bcm2711-rpi-cm4-io.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  53K Oct 12 16:19 bcm2711-rpi-cm4s.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  77K Oct 12 16:19 bcm2712d0-rpi-5-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  77K Oct 12 16:19 bcm2712-d-rpi-5-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  77K Oct 12 16:19 bcm2712-rpi-500.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  77K Oct 12 16:19 bcm2712-rpi-5-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  78K Oct 12 16:19 bcm2712-rpi-cm5-cm4io.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  78K Oct 12 16:19 bcm2712-rpi-cm5-cm5io.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  78K Oct 12 16:19 bcm2712-rpi-cm5l-cm4io.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  78K Oct 12 16:19 bcm2712-rpi-cm5l-cm5io.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  21K Oct 12 16:19 bcm2837-rpi-2-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  21K Oct 12 16:19 bcm2837-rpi-3-a-plus.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  22K Oct 12 16:19 bcm2837-rpi-3-b.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  22K Oct 12 16:19 bcm2837-rpi-3-b-plus.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  21K Oct 12 16:19 bcm2837-rpi-cm3-io3.dtb
-rw-r--r-- 1 qTAbNM qTAbNM  21K Oct 12 16:19 bcm2837-rpi-zero-2-w.dtb
-rw-r--r-- 1 qTAbNM qTAbNM 9.9M Oct 12 16:18 kernel8.img
drwxr-xr-x 2 qTAbNM qTAbNM  20K Oct 12 16:19 overlays
```

### HOST: `cat ~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release`

```text
6.18.56-v8+
```

Do the full HOST and BBB kernel-release strings match exactly?
```text
Yes.
```

Why must Lab 02 use a matching kernel tree?

```text
Modules must be compiled specifically for the version of the kernel on which the board is running.
```

Submit this completed report with `src/hello.c` and `Makefile`. Do not commit
images, executables, toolchains, kernel sources, or build artifacts.
