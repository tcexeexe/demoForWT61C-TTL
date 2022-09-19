VERSION  =1.00
CC   =gcc
DEBUG   = -DUSE_DEBUG
CFLAGS  = -Wall
SOURCES   = $(wildcard ./driver/*.c)
SOURCES   += $(wildcard ./test/*.c)
INCLUDES   = -I ./driver
# LIB_NAMES  =-lfun_a -lfun_so
# LIB_PATH  =-L ./lib
OBJ   =$(patsubst %.c, %.o, $(SOURCES))
TARGET  =app

#links
$(TARGET):$(OBJ)
	@mkdir -p output
	$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o output/$(TARGET)$(VERSION)
	@rm -rf $(OBJ)
 
#compile
%.o: %.c #模式匹配
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) $(TARGET) output
# -----------------------------------
# 几个Makefile通用模板分享！
# https://blog.51cto.com/u_15244533/5247086