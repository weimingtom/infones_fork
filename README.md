# infones_fork
[WIP] My InfoNES fork

## Ref
* (origin) https://web.archive.org/web/20080107090123/http://www.geocities.co.jp/SiliconValley/5604/infones.html
* (origin, dead) http://prdownloads.sourceforge.jp/infones/19061/InfoNES097JRC1_SDL.tar.gz
* (origin, dead) http://sourceforge.jp/projects/infones
* (origin, dead) http://www.geocities.co.jp/SiliconValley/5604/infones.html
* https://web.archive.org/web/20041201054524/http://infones.seesaa.net/article/418671.html
* https://web.archive.org/web/20080118074851/http://mopeopage.hp.infoseek.co.jp
* (InfoNES v0.76bJ for PocketPC) https://web.archive.org/web/20080118074851/http://mopeopage.hp.infoseek.co.jp/file/InfoNES076aJ_src.zip
* (origin? search InfoNES097JRC1_SDL.tar.gz) https://www.aep-emu.de/Emus-file-emus_detail-id-464.html
* (rpi3) infones_rpi_v1.rar
```
树莓派3b运行infones，GPIO操纵中景园1.3寸ips屏（240*240）显示。
有点卡，因为逻辑与刷屏是同一个线程，这个情况是正常的，
因为我在windows下用类似的方式刷屏也会卡。
InfoNES的Windows版用了多线程和定时器，所以才不会卡。
目前没有输入功能，所以只能看。显示区域是溢出的，
右边有一小块被截掉了，因为NES的分辨率比240*240稍大。
移植不容易，最初我基于SDL版的代码去移植，没成功。
这个成功的版本是基于windows版的，而且ips屏用
的是RGB565而非24位RGB，所以还需要另外想办法转换，
反正这里又是折腾了好久才成功。
移植infones目前只是尝试，还没有完善它的计划，
现在只是概念试验性质，不过看来这个思路是可行的，
刷屏帧率可以到达24fps（如果用pthread多线程的话）

(TODO) How to convert 24bit RGB to RGB565
```
* (vc6) infones_src_v5_min_calloc.rar
* (origin) InfoNES097JRC1_SDL.tar.gz
* (win) InfoNES097JRC1_SDL_v2.rar
* (stm32) infones_stm32f407ve_v1.rar
* https://github.com/weimingtom/wmt_stm32_study/?tab=readme-ov-file#infones-stm32f4--esp32
* https://github.com/weimingtom/wmt_rpi_study#infones
* https://github.com/weimingtom/wmt_link_collections_in_Chinese/blob/master/emulator.md
* (TODO) https://gitee.com/whycan/f1c100s_buildroot/tree/master/board/f1c100s/apps/infones

## (WIP) (TODO) How to build for LiuLianPi V3S (Allwinner v3s, ARM 32bit Cortex-A7)  
* Get toolchain gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf.tar.xz  
https://w.electrodragon.com/w/ARM_GCC  
https://releases.linaro.org/components/toolchain/binaries/6.3-2017.05/arm-linux-gnueabihf/  
https://releases.linaro.org/components/toolchain/binaries/6.3-2017.05/arm-linux-gnueabihf/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf.tar.xz  
* Cross compile static libs libSDL.a and libz.a, see  
https://github.com/weimingtom/nofrendo_fork/blob/master/vendor/v3s/work_v3s_readme.txt  
* See src/liulianpi_v3s/Makefile, tar xf gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf.tar.xz to /home/wmt/work_v3s/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf
* $ cd src/liulianpi_v3s  
* $ make clean
* $ make -j8
* Copy file "InfoNES" and "DEMO.NES" and "libstdc++.so.6" (from libstdc++.so.6.0.22 of gcc toolchain) to tf card
* Login UART (COMx) console with Putty
* \# mkdir /mnt/SDCARD
* \# mount /dev/mmcblk0p1 /mnt/SDCARD/
* \# cd /mnt/SDCARD/infones/
* \# ls ./libstdc++.so.6
* \# SDL_NOMOUSE=1 LD_LIBRARY_PATH=. ./InfoNES ./DEMO.NES

## (TODO) qt4-nes
* qt4-nes_v13_boot.tar.gz, qt4-nes_v5_xiaozhi.tar.gz (old, use v13_boot instead)       
* (origin) https://github.com/nejidev/arm-NES-linux  
* (origin) 《小白通过buildroot搭建哪吒D1开发环境详细步骤，并且在HDMI显示器上玩上了魂斗罗(基于QT5)》  
https://whycan.com/t_7253.html  
(origin) qt4-NES4_5_512_480_640_480.7z  
(origin) qt4-NES4_5_512_480_640_480_try_high_speed.7z  
https://github.com/rvboards/d1_nezha_doc/blob/master/zh_mkdocs/docs/NES模拟器.md  
* whycan, 为了V3S不吃灰，移植NES游戏  
https://whycan.com/t_5139.html  
* (TODO) site.txt, copy.txt, search qt-everywhere-opensource-src-4.8.6_xiaozhi_v2.tar.gz
* (TODO) How to build or cross compile Qt4, search build_host_x86.txt, build_x_riscv64.txt

## (TODO) InfoNES ASM version by ye781205
* 梁山派, nes, asm code from ye781205 (from 正点原子论坛 http://www.openedv.com ? )
* https://gitee.com/lcsc/liangshan-pi-nes-game-console
* https://gitee.com/lcsc/game-ex-base-code
* https://blog.csdn.net/2302_81678505/article/details/144169437
* https://whycan.com/p_76805.html
* https://github.com/VeiLiang/BoloRTT/tree/master/bsp/f1c/package/vnes
