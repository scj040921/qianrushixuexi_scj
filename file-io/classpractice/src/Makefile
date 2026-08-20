# 交叉编译器
CC = aarch64-buildroot-linux-gnu-gcc

# 编译选项：动态库需要 -fPIC，-Wall 显示警告，-O2 优化
CFLAGS = -Wall -O2 -fPIC -I../include

# 目标文件
TARGET = main
LIBS = libbmp.so libjpg.so liblcd.so

# 默认目标：编译所有
all: $(LIBS) $(TARGET)

# 生成 libbmp.so
libbmp.so: bmp.c
	$(CC) $(CFLAGS) -shared -o $@ $<

# 生成 libjpg.so（需要链接 libjpeg）
libjpg.so: jpg.c
	$(CC) $(CFLAGS) -shared -o $@ $< -ljpeg

# 生成 liblcd.so
liblcd.so: lcd.c
	$(CC) $(CFLAGS) -shared -o $@ $<

# 生成 main，链接 liblcd.so
main: main.c liblcd.so
	$(CC) $(CFLAGS) -o $@ main.c -L. -llcd -ldl
	scp main libbmp.so libjpg.so liblcd.so root@192.168.53.68:/tmp/

# 清理
clean:
	rm -f $(LIBS) $(TARGET)

.PHONY: all clean