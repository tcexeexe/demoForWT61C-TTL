#项目路径
INC_DIR = ../inc
LIB_DIR = ../lib
TAR_DIR = ../tar/
#目标
TARGET = mytar
#头文件
INCLUDE = -I$(INC_DIR) -I./ -I$(LIB_DIR)
#库 .a表示自己编译的库 -l后面的表示使用的其他库
LDFLAGS = $(LIB_DIR)/xxx.a
LIBS =-lm -lpthread
#编译器及编译选项
CC = gcc
CSTRIP = strip
CFLAGS = -O2 -Wall -g -fpic
FILES = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(FILES))
RM = rm -f
$(TAR_DIR)/$(TARGET):$(OBJS)
$(CC) -o $@ $^ $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LIBS)
$(OBJS):%.o:%.c
$(CC) -c $(INCLUDE) $(LIBS) $(CFLAGS) $< -o $@
strip:
-$(CSTRIP) $(CENTER_DIR)/$(TARGET)
clean:
-$(RM) $(TARGET) $(OBJS)