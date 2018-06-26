TARGET_SO = ./libpeace.so
TARGET_LIB = ./libpeace.a
##PLATFORM = arm-arago-linux-gnueabi-

CC = $(PLATFORM)gcc
XX = $(PLATFORM)g++
AR = $(PLATFORM)ar
AS = $(PLATFORM)as


MACRO = 
CXXFLAGS = -Werror -Wall -g -Wunused -Wsign-compare -Wunreachable-code DDEBUG_SYS_INFO -fPIC 
CFLAGS = $(CXXFLAGS) -std=gnu99 $(MACRO)
LDFLAGS	= 
			
LIBS = -lz -lpthread

INC = -I./

DIR = ./


sSRC = $(shell find $(DIR) -name "*.s")
SSRC = $(shell find $(DIR) -name "*.S")
CSRC = $(shell find $(DIR) -name "*.c")
CXXSRC = $(shell find $(DIR) -name "*.cpp")
CCSRC = $(shell find $(DIR) -name "*.cc")

soFLAGS = -fPIC 

OBJS := $(CSRC:%.c=%.o) $(CXXSRC:%.cc=%.o) $(SSRC:%.S=%.o) $(sSRC:%.s=%.o) $(CCSRC:%.cpp=%.o)

so:$(TARGET_SO)
$(TARGET_SO): $(OBJS)
	rm -f $@
	$(XX) -shared $(soFLAGS) $(INC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

lib:$(TARGET_LIB)
$(TARGET_LIB): $(OBJS)
	$(AR) cr $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $(@D)/$(<F) -o $(@D)/$(@F)

%.o: %.cc
	$(XX) $(CXXFLAGS) $(INC) -c $(@D)/$(<F) -o $(@D)/$(@F)

%.o: %.cpp 
	$(XX) $(CXXFLAGS) $(INC) -c $(@D)/$(<F) -o $(@D)/$(@F)

%.o: %.s
	$(CC) $(INC) -c $< -o $@ $(sFLAGS)

%.o: %.S
	$(CC) $(INC) -c $< -o $@ $(SFLAGS)


install:
	mv $(TARGET_SO) ../install/bin 
	##cp $(TARGET_LIB) ../install/lib 
	cp ./peaceInterface.h ../install/include
	cp ./types.h ../install/include

##clean:
##	$(RM) $(TARGET_SO) $(TARGET_LIB) $(OBJS)

