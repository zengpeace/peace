EXE="./test"

##PLATFORM = arm-arago-linux-gnueabi-
CC = $(PLATFORM)gcc
XX = $(PLATFORM)g++


CXXFLAGS = -Werror -Wall -g -Wunused -Wsign-compare -Wunreachable-code -DDEBUG_SYS_INFO 
CFLAGS = $(CXXFLAGS) -std=gnu99 $(MACRO)
LDFLAGS	=
			
LIBS = ../install/bin/libpeace.so

INCLUDES = -I../install/include

DIR = ./

CSRC := $(shell find $(DIR) -name "*.c")
CXXSRC = $(shell find $(DIR) -name "*.cpp")

OBJS := $(CSRC:%.c=%.o) $(CXXSRC:%.cpp=%.o)

$(EXE): $(OBJS)
	$(XX) $(CXXFLAGS) $(LDFLAGS) -o $(EXE) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(@D)/$(<F) -o $(@D)/$(@F)

%.o: %.cpp
	$(XX) $(CXXFLAGS) $(INCLUDES) -c $(@D)/$(<F) -o $(@D)/$(@F)

clean:
	$(RM) $(EXE) $(OBJS)

