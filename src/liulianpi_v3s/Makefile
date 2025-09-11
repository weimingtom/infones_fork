#CC = gcc
#gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf.tar.xz
CC = /home/wmt/work_v3s/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
TARBALL = InfoNES097J

# InfoNES
.CFILES =	./../K6502.cpp \
		./../InfoNES.cpp \
		./../InfoNES_Mapper.cpp \
		./../InfoNES_pAPU.cpp \
		./InfoNES_System_SDL.cpp

.OFILES	=	$(.CFILES:.cpp=.o)

#CCFLAGS = `gtk-config --cflags` -O6
#CCFLAGS_NOOPT = `gtk-config --cflags` -O0
#LDFLAGS = `gtk-config --libs gthread` -lstdc++		# gcc3.x.x

#CCFLAGS = `sdl-config --cflags` -O3 -pipe
#sdl-config --cflags
CCFLAGS += -I./include -I./include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -O3 -pipe -DMY_USE_MINLIB2=1
CCFLAGS_NOOPT = -O0 -pipe
#LDFLAGS = `sdl-config --libs` -lstdc++			# gcc3.x.x
LDFLAGS = -lSDL -lm -lz -lpthread -ldl -L./lib -lstdc++	# gcc3.x.x

all: InfoNES

InfoNES: $(.OFILES)
	$(CC) $(INCLUDES) -o $@ $(.OFILES) $(LDFLAGS) -lm -lz

# To avoid the gcc optimization bug
./../InfoNES_pAPU.o: ./../InfoNES_pAPU.cpp
	$(CC) $(INCLUDES) -c $(CCFLAGS_NOOPT) ./../InfoNES_pAPU.cpp -o ./../InfoNES_pAPU.o 

.cpp.o:
	$(CC) $(INCLUDES) -c $(CCFLAGS) $*.cpp  -o $@

clean:
	rm -f $(.OFILES) ../*~ ../*/*~ core InfoNES

cleanall:
	rm -f $(.OFILES) ../*~ ../*/*~ core InfoNES

release: clean all

tar:
	( cd ..; \
	tar cvf $(TARBALL).tar ./*; \
	gzip $(TARBALL).tar \
	)

install:
	install ./InfoNES /usr/local/bin

# End of Makefile
