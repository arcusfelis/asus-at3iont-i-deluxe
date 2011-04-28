include modules.conf

ifeq "$(KVERS)" ""
	KVERS:=$(shell uname -r)
endif
ifeq "$(KSRC)" ""
	KSRC:=/lib/modules/$(KVERS)/build
endif
KERNEL_LOCATION = $(KSRC)
CC = gcc -D__KERNEL__ -I $(KSRC)/include
CFLAGS= -O2 -g -Wall
DEFS=-DHAVE_CONFIG_H -I. -I../..

KEXT=ko

export KERNEL_LOCATION CC

REMOTE=hid-philips-asus
BLUETOOTH=ath3k

DRIVERS=$(subst ", ,$(MODULES:,=))
all: $(DRIVERS)

test:
	@echo '$(KERNEL_LOCATION)'
	@echo '$(KVERS)'
	@echo '$(MODULES)'

UNCONFIGURED: #Do nothing if the user didn't configure which drivers to build

dkms: $(subst ", ,$(MODULES:,=))

modules:
	mkdir modules

sanity-check:
	@if \
		expr "$(DEFS)" : '.*UNCONFIGURED'> /dev/null;\
	then \
		echo ;\
		echo "##########################";\
		echo "## CONFIGURATION ERROR: ##";\
		echo "##########################";\
		echo ;\
		echo "You should reconfigure asus-at3iont-i-deluxe";\
		echo ;\
		echo "Hint1: use \"dpkg-reconfigure asus-at3iont-i-deluxe\"";\
		echo "Hint2: you may instead edit /etc/asus-at3iont-i-deluxe.conf";\
		exit 1;\
	fi

$(REMOTE): modules sanity-check
	$(MAKE) -C drivers/$(REMOTE)
	cp drivers/$(REMOTE)/$(REMOTE).$(KEXT) modules
	@echo $(KVERS) $(KSRC) > modules/$(REMOTE).$(KEXT).KVERS

$(BLUETOOTH): modules sanity-check
	$(MAKE) -C drivers/$(BLUETOOTH)
	cp drivers/$(BLUETOOTH)/$(BLUETOOTH).$(KEXT) modules
	@echo $(KVERS) $(KSRC) > modules/$(BLUETOOTH).$(KEXT).KVERS

install.real:
	@for file in modules/*.$(KEXT); \
	do \
		kvers=`cut -d" " -f1 $$file.KVERS` && \
		ksrc=`cut -d" " -f2 $$file.KVERS` && \
		dir="$(prefix)/lib/modules/$$kvers/updates/" && \
		( [ -d $$dir ] || mkdir -p $$dir ) && \
		cp -v $$file $$dir ; \
	done

depmod:
	@for file in modules/*.$(KEXT); \
	do \
		kvers=`cut -d" " -f1 $$file.KVERS` && \
		ksrc=`cut -d" " -f2 $$file.KVERS` && \
		dir="$(prefix)/lib/modules/$$kvers/updates/" && \
		if [ -f $$ksrc/System.map ];then \
			/sbin/depmod -r -b $(prefix)/ -a $$kvers \
					-F $$ksrc/System.map ; \
		elif [ -f /boot/System.map-$$kvers ];then \
			/sbin/depmod -r -b $(prefix)/ -a $$kvers \
					-F /boot/System.map-$$kvers; \
		else \
			/sbin/depmod -a ;\
		fi ;\
	done

install: install.real depmod

clean:
	@for driver in $(DRIVERS); \
	do \
		$(MAKE) clean -C drivers/"$$driver" ;\
	done
	rm -rf modules
