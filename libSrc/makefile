TARGET_BIN = ./peace 
TARGET_SO = ./libpeace.so
TARGET_LIB = ./libpeace.a

CC = gcc
XX = g++
AR = ar
AS = as


MACRO = 
CXXFLAGS = -Werror -Wall -g -Wunused -Wsign-compare -Wunreachable-code -DDEBUG_SYS_INFO -fPIC -fstack-protector-all -DJEMALLOC_MANGLE
CFLAGS = $(CXXFLAGS) -std=gnu99 $(MACRO)
LDFLAGS	= -L../interInstall/lib  
			
LIBS = -lz -lpthread -ljemalloc

INC = -I./ \
	-I../interInstall/include/jemalloc

DIR = ./


sSRC := $(shell find $(DIR) -name "*.s")
SSRC := $(shell find $(DIR) -name "*.S")
CSRC := $(shell find $(DIR) -name "*.c")
CXXSRC := $(shell find $(DIR) -name "*.cpp")
CCSRC := $(shell find $(DIR) -name "*.cc")

##ifeq ( $1, "so")
##CXXSRC := $(CXXSRC) ../tmp/main.cpp 
##else
##CXXSRC := $(CXXSRC) ../tmp/main.cpp 
##endif

soFLAGS = -fPIC 

OBJS := $(CSRC:%.c=%.o) $(CXXSRC:%.cc=%.o) $(SSRC:%.S=%.o) $(sSRC:%.s=%.o) $(CCSRC:%.cpp=%.o)

so:$(TARGET_SO)
$(TARGET_SO): $(OBJS)
	rm -f $@
	$(XX) -shared $(soFLAGS) $(INC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

lib:$(TARGET_LIB)
$(TARGET_LIB): $(OBJS)
	$(AR) cr $@ $(OBJS)

bin:$(TARGET_BIN)
$(TARGET_BIN): $(OBJS)
	$(XX) $(CXXFLAGS) $(LDFLAGS) $(INC) -o $(TARGET_BIN) $(OBJS) $(LIBS)

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
	cp $(TARGET_SO) ../install/bin 
	##mv $(TARGET_LIB) ../install/lib 
	cp ./peaceInterface.h ../install/include
	cp ./types.h ../install/include
	cp ../interInstall/include/jemalloc/jemalloc.h ../install/include
	cp ../interInstall/lib/libjemalloc.so.2 ../install/bin/libjemalloc.so
	mv $(TARGET_SO) /lib

##clean:
##	$(RM) $(TARGET_SO) $(TARGET_LIB) $(OBJS)

