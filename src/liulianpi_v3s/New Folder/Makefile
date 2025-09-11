#gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf.tar.xz
CC := /home/wmt/work_v3s/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
RM := rm -rf

CFLAGS := 
CFLAGS += -g0 -O2 
CFLAGS += -DZLIB 
CFLAGS += -DNDEBUG
CFLAGS += -DHAVE_CONFIG_H -DMY_USE_NOSOUND
 
CFLAGS += -DNOFRENDO_DEBUG

#sdl-config --cflags
CFLAGS += -I./include -I./include/SDL -D_GNU_SOURCE=1 -D_REENTRANT

CFLAGS += -I.. 
CFLAGS += -I../cpu     
CFLAGS += -I../libsnss  
CFLAGS += -I../sndhrdw
CFLAGS += -I../mappers  
CFLAGS += -I../nes
CFLAGS += -I../sdl
CFLAGS += -I../unix

LDFLAGS :=
LDFLAGS += -lSDL -lm -lz -lpthread -ldl -L./lib

OBJS := 
OBJS += ../cpu/nes6502.o
OBJS += ../libsnss/libsnss.o
OBJS += ../sndhrdw/fds_snd.o
OBJS += ../sndhrdw/nes_apu.o
OBJS += ../sndhrdw/vrcvisnd.o
OBJS += ../sndhrdw/mmc5_snd.o
OBJS += ../mappers/map000.o
OBJS += ../mappers/map001.o
OBJS += ../mappers/map002.o
OBJS += ../mappers/map003.o
OBJS += ../mappers/map004.o
OBJS += ../mappers/map005.o
OBJS += ../mappers/map007.o
OBJS += ../mappers/map008.o
OBJS += ../mappers/map009.o
OBJS += ../mappers/map011.o
OBJS += ../mappers/map015.o
OBJS += ../mappers/map016.o
OBJS += ../mappers/map018.o
OBJS += ../mappers/map019.o
OBJS += ../mappers/map024.o
OBJS += ../mappers/map032.o
OBJS += ../mappers/map033.o
OBJS += ../mappers/map034.o
OBJS += ../mappers/map040.o
OBJS += ../mappers/map041.o
OBJS += ../mappers/map042.o
OBJS += ../mappers/map046.o
OBJS += ../mappers/map050.o
OBJS += ../mappers/map064.o
OBJS += ../mappers/map065.o
OBJS += ../mappers/map066.o
OBJS += ../mappers/map070.o
OBJS += ../mappers/map073.o
OBJS += ../mappers/map075.o
OBJS += ../mappers/map078.o
OBJS += ../mappers/map079.o
OBJS += ../mappers/map085.o
OBJS += ../mappers/map087.o
OBJS += ../mappers/map093.o
OBJS += ../mappers/map094.o
OBJS += ../mappers/map099.o
OBJS += ../mappers/map160.o
OBJS += ../mappers/map229.o
OBJS += ../mappers/map231.o
OBJS += ../mappers/mapvrc.o
OBJS += ../nes/mmclist.o
OBJS += ../nes/nes.o
OBJS += ../nes/nes_mmc.o
OBJS += ../nes/nes_pal.o
OBJS += ../nes/nes_ppu.o
OBJS += ../nes/nes_rom.o
OBJS += ../nes/nesinput.o
OBJS += ../nes/nesstate.o
OBJS += ../sdl/sdl.o
OBJS += ../unix/osd.o
OBJS += ../bitmap.o 
OBJS += ../config.o 
OBJS += ../event.o 
OBJS += ../gui.o 
OBJS += ../gui_elem.o 
OBJS += ../intro.o 
OBJS += ../log.o 
OBJS += ../memguard.o 
OBJS += ../nofrendo.o 
OBJS += ../pcx.o 
OBJS += ../vid_drv.o

all: nofrendo
nofrendo: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

*.o: *.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) nofrendo 


