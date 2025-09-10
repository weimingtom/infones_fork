# infones_fork
[WIP] My InfoNES fork

## Ref
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
