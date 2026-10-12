KDIR = $(HOME)/Downloads/uni/linux/workspace/kernel/linux
ARCH = arm64
CROSS_COMPILE = $(HOME)/Downloads/uni/linux/workspace/downloads/aarch64--glibc--bleeding-edge-2026.08-1/bin/aarch64-linux-

MODULE_NAME = lab02_hello

obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-objs := src/hello.o

.PHONY: all clean

all:
	make -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
