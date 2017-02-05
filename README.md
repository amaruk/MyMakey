# MyMakey

## Background

**What's Makey Makey?**

> ![Makey Makey](http://www.makeymakey.com/makey-with-clips-toty.png)
>
> Makey Makey is an invention kit for the 21st century. Turn everyday objects into touchpads and combine them with the internet. It's a simple Invention Kit for Beginners and Experts doing art, engineering, and everything inbetween.
>
> ​											-- By [MakeyMakey Official Website](http://www.makeymakey.com/)

**What's Beagle Bone Black?**

> ![BBB](http://www.ti.com/diagrams/med_beaglebk_board_sideways.jpg)
>
> BeagleBone Black is a low-cost, open source, community-supported development platform for ARM® Cortex™-A8 processor developers and hobbyists. Boot Linux in under 10-seconds and get started on Sitara™ AM335x ARM Cortex-A8 processor development in less than 5 minutes with just a single USB cable.
>
> ​											-- By [TI Beagle Bone Black Official Website](http://www.ti.com/tool/beaglebk)

**What's the "MyMakey" repository**

> Try to implement a Makey Makey using the Beagle Bone Black.
>
> ​											-- By Amaruk

First things first. Let's see how the MyMakey works:

[MyMakey Youku video](https://v.youku.com/v_show/id_XMjQ5MDY1NDk3Ng==.html)
[MyMakey Youtube video](https://youtu.be/BkRS4S57fKg)



## Hardware Related

**Schematic**

I would really appreciate if you could kindly ignore all stupid things in the following schematic, for it is drawn by a software engineer.

> ![Schematic](https://amaruk.github.io/repos_images/MyMakey_Schematic.png)

VDD and seven ADC channel used is remarked by squares in **RED**.

>![MyMakey BBB Pin Mapping](https://amaruk.github.io/repos_images/MyMakey_BBB_pin_map.png)
>
>This is a modified version of BBB pin mapping. The [Original image](http://cn.mathworks.com/help/supportpkg/beagleboneio/ug/beaglebone-black-pin-map.html) comes from *mathworks*.

**Overview hardware connections**

![Overview](https://amaruk.github.io/repos_images/MyMakey_overview.jpg)

This photo shows everything you need to build the MyMakey:

* The logitech USB To 3.5mm Jack Audio Adapter and a loudspeaker: so that the BBB can play music.

  ![Audio adapter](https://amaruk.github.io/repos_images/MyMakey_logitech.jpg)

* The power bank provides 5V power for the BBB.

* The Debug UART is used during the dark age.

* Touch pads are made by foil.

* Some soldering work to implement the simple schematic

![Soldering work](https://amaruk.github.io/repos_images/MyMakey_soldering_work.png)

* And finally, a BBB.

![BBB](https://amaruk.github.io/repos_images/MyMakey_BBB_connection.jpg)

## Software Related

**OS**: Linux beaglebone 3.8.13-bone47 #1 SMP Fri Apr 11 01:36:09 UTC 2014 armv7l GNU/Linux

**Build instructions**:

* Clone this repository.
* Then you get a project that can be directly imported into EclipseCDT.
* You can build it directly using the X86 GCC.
* Copy the whole project into your BBB. By SSH or anyway you like.
* Login to the BBB.
* Enter into the Debug folder where makefiles are stored.
* Use the "make" command to build the project.
* Before launching myMakey, chmod the "wavPlayer" binary file so that it can be executed.
* Launch!

*The wavPlayer source code is also enclosed in "wavPlayer.tar.gz". Source code collected from the Internet.





