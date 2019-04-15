TARGET  = serialtest

CROSS_COMPILE	:= /home/yaobo/work/source/swift_solution/US536_Linux_SDK/tools/toolchain/unione/arm-none-linux-gnueabi-4.6.4_linux-3.3/bin/arm-none-linux-gnueabi-
CC      	:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
AR		:= $(CROSS_COMPILE)ar

CFLAGS  := -Wall
CFLAGS  += -O2 -I./4Glib
# LDFLAGS	:= -L./4Glib -l4Gstat
#CFLAGS	+= -g
#CFLAGS	+= -D__DEBUG__

OBJS   := $(patsubst %.c,%.o,$(wildcard *.c))

ALL:$(TARGET)
$(TARGET):$(OBJS)
	@echo -e "\033[036m\c"
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "\033[0m\c"

%.o:%.c
	@echo -e "\033[032m\c"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "\033[0m\c"

.PHONY: clean dclean distclean
dclean:distclean
distclean: clean
	@echo "disclean clean ...."
	make dclean -C 4Glib
	rm -fr $(TARGET)
	@echo "disclean clean done!"
clean:
	@echo "clean ...."
	make clean -C 4Glib
	rm -fr *.o
	@echo "clean done!"
