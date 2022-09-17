#��Ŀ·��
INC_DIR = ../inc
LIB_DIR = ../lib
TAR_DIR = ../tar/
#Ŀ��
TARGET = mytar
#ͷ�ļ�
INCLUDE = -I$(INC_DIR) -I./ -I$(LIB_DIR)
#�� .a��ʾ�Լ�����Ŀ� -l����ı�ʾʹ�õ�������
LDFLAGS = $(LIB_DIR)/xxx.a
LIBS =-lm -lpthread
#������������ѡ��
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