CROSS_COMPILE ?= aarch64-buildroot-linux-gnu-
JPEG_PREFIX ?= /home/scj/jpeg-9d/aarch64-install

CFLAGS := -std=c11 -Wall -Wextra -Wconversion -Wshadow
CPPFLAGS := -I. -I$(JPEG_PREFIX)/include
LDFLAGS := -L$(JPEG_PREFIX)/lib
LDLIBS := -ljpeg

0502: 0502.c jpg.c LCD.c LCD.h
	$(CROSS_COMPILE)gcc $(CFLAGS) $(CPPFLAGS) 0502.c jpg.c LCD.c $(LDFLAGS) $(LDLIBS) -o $@

# 兼容原作业中直接执行 make 的习惯
all: 0502

deploy: 0502
	scp 0502 off.jpg on.jpg root@192.168.44.203:/tmp/

clean:
	rm -f 0502
