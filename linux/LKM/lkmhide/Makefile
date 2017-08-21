TARGET=lkmhide
KDIR=/usr/src/kernels/2.6.32-696.6.3.el6.i686/
PWD=$(shell pwd)
obj-m:=$(TARGET).o
default:
	make -C $(KDIR) M=$(PWD) modules
