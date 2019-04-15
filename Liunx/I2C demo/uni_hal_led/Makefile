
export SYSTEM_DIR	?=/home/yaobo/data/rk/hf_rk3308_rongbang
export CROSS_COMPILE	?=$(SYSTEM_DIR)/buildroot/output/rockchip_rk3308_32_release/host/bin/arm-rockchip-linux-gnueabihf-

RK3308SDK_DIR	:=$(SYSTEM_DIR)
CC		:= $(CROSS_COMPILE)gcc
LD              := $(CROSS_COMPILE)ld
AR              := $(CROSS_COMPILE)ar
STRP		:= $(CROSS_COMPILE)strip

SYSROOT		:=$(RK3308SDK_DIR)/buildroot/output/rockchip_rk3308_32_release/host/arm-rockchip-linux-gnueabihf/sysroot
#BLUEZALSA	:=$(RK3308SDK_DIR)/buildroot/output/rockchip_rk3308_32_release/build/bluez-alsa/src
SYSINCLUDE	:=$(SYSROOT)/usr/include
UNISYSDIR	:=./

SYSLIBDIR	:=$(SYSROOT)/usr/lib
INCLUDES 	:= -I./ -Iinclude -I$(SYSINCLUDE) -I$(SYSROOT)/usr/include -I$(UNISYSDIR)

CFLAGS		:= -O2
CFLAGS		+= -fPIC -Wall 
LDFLAGS		:= -lunii2chal -luniledhal -lpthread  -L$(SYSLIBDIR) -L.
LDFLAGSO	:=  -lpthread  -lunii2chal  -L$(SYSLIBDIR) -L.

OBJS   := $(patsubst %.c,%.o,$(wildcard *.c))


.PHONY:all
all:  libuniledhal.so led
	@echo "building all"


libunii2chal.so:uni_i2c_hal.o 
	@echo -e "\033[032m\c"
	$(CC) $^ -o $@ -fPIC -shared -ldl  $(INCLUDE) $(LDFLAGS)
	$(STRP) $@
	@echo -e "\033[0m\c"

libuniledhal.so:uni_led_hal.o
	@echo -e "\033[032m\c"
	$(CC) $^ -o $@ -fPIC -shared -ldl  $(INCLUDE) $(LDFLAGSO)
	$(STRP) $@
	@echo -e "\033[0m\c"

led:hal_led_test.o
	@echo -e "\033[032m\c"
	$(CC) -o $@ $^  -L. $(INCLUDES) $(LDFLAGS)
	$(STRP) $@
	@echo -e "\033[0m\c"

%.o:%.c
	@echo -e "\033[036m\c"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "\033[0m\c"

.PHONY:clean distclean
distclean:clean
	rm -fr led
clean:
	rm -fr *.o libuniledhal.so led
