TARGET = display-your-name
OBJS = display-your-name.o

KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

obj-m += $(TARGET).o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean	