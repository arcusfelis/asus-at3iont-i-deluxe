MODULE_NAME := hid-philips-asus
ifeq "$(KERNEL_LOCATION)" ""
	KERNEL_LOCATION:=/lib/modules/$(shell uname -r)/build
endif
KERNEL_MODDIR := updates/
PWD := $(shell pwd)


obj-m += $(MODULE_NAME).o

modules:
	$(MAKE) -C $(KERNEL_LOCATION) M=$(PWD) modules
install: modules
	$(MAKE) -C $(KERNEL_LOCATION) M=$(PWD) INSTALL_MOD_DIR=$(KERNEL_MODDIR) \
		modules_install
	@depmod -a
clean:
	$(MAKE) -C $(KERNEL_LOCATION) M=$(PWD) clean
all: modules

clean-files := Module.symvers modules.order Module.markers modules.order
