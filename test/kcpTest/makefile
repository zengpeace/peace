EXE="./test"

CC = gcc
XX = g++


CXXFLAGS = -Werror -Wall -g -Wunused -Wsign-compare -Wunreachable-code -DDEBUG_SYS_INFO -DJEMALLOC_MANGLE 
CFLAGS = $(CXXFLAGS) -std=gnu99 
LDFLAGS	= -L../../install/bin
LIBS = -lpeace -ljemalloc
			
##LIBS = ../../install/bin/libpeace.so 

INCLUDES =	-I../../install/include \
			-I./kcp \
			-I./logic  

DIR = ./

CSRC := $(shell find $(DIR) -name "*.c")
CXXSRC := $(shell find $(DIR) -name "*.cpp")

OBJS := $(CSRC:%.c=%.o) $(CXXSRC:%.cpp=%.o)

$(EXE): $(OBJS)
	$(XX) $(CXXFLAGS) $(LDFLAGS) -o $(EXE) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@D)/$(<F) -o $(@D)/$(@F)

%.o: %.cpp
	$(XX) $(CXXFLAGS) $(INCLUDES) -c $(@D)/$(<F) -o $(@D)/$(@F)

clean:
	$(RM) $(EXE) $(OBJS)

