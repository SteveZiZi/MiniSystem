#********define executable file name**********
#定义可执行程序的名称，需要根据实际情况进行更改
EXECUTABLE := sysipc.a

export CC=arm-uclibc-gcc

ifeq ($(CC),cc)
CC=arm-uclibc-gcc
endif


# Now alter any implicit rules' variables if you like, e.g.:
# 现在来改变任何你想改动的隐含规则中的变量，例如
CFLAGS := -Wall -O2 -D ARCH_ARM -D DEV_6100
CPPFLAGS := $(CFLAGS) 
CPPFLAGS += -MMD


%.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
%.o:%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	
SOURCE_DIRS =include systemserver sysipc debug

SOURCE := $(wildcard *.c) $(wildcard *.cpp) 

	

SOURCE +=$(foreach DIR,$(SOURCE_DIRS),$(wildcard $(DIR)/*.c $(DIR)/*.cpp))
ALLOBJS :=$(foreach DIR,$(SOURCE_DIRS),$(wildcard $(DIR)/*.o))
ALLDEPS = $(wildcard *.d)
ALLDEPS +=$(foreach DIR,$(SOURCE_DIRS),$(wildcard $(DIR)/*.d))

OBJS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

include $(ALLDEPS)



$(EXECUTABLE) : $(OBJS)
	ar rc $(EXECUTABLE) $(OBJS)

	$(CC) $(OBJS) -shared -fPIC -o libsysipc.so
	echo "11111 "
.PHONY : clean
clean:
	rm -f *.o *.a *.d *.so
	
