.PHONY: clean

# 定义变量
EXES=main
INCLUDE=./include
CFLAGS=-O3 -g -Wall

# 创建文件夹
MKDIR=mkdir
DIR_OBJS=objs
DIR_EXES=exes
DIRS=$(DIR_OBJS) $(DIR_EXES)
SRC:=$(wildcard *.c ./src/*.c)
SRC:=$(notdir $(SRC))

debug1:
	$(SRC)

OBJS:=$(patsubst %.c, %.o, $(SRC))

debug2:
	$(OBJS)

EXES:=$(addprefix ./$(DIR_EXES)/, $(EXES))

all: $(DIRS) $(EXES)

$(DIRS):
	$(MKDIR) $@


# 对汇编文件进行链接
$(EXES):./$(DIR_OBJS)/$(OBJS)
	gcc $^ -o $@ $(CFLAGS)

debug3:
	$(OBJS)
	$(EXES)

# 对源文件进行逐个汇编
./$(DIR_OBJS)/%.o:%.c
	gcc $< -c -o $@ $(CFLAGS) -I$(INCLUDE) 

# clean
clean:
	rm $(DIRS) -rf
