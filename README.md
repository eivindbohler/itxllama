# ITX-Llama User's Guide
  
> **Note**  
> This document is still a work-in-progress.  
For feedback, suggestions, etc. - please add a post to the [Vogons thread][vogons-thread].

### Contents
- [Installing the SOM](#installing-the-som)
- [Jumper Configuration](#jumper-configuration)
  * [PS/2 and USB HID](#ps2-or-usb-hid)
  * [Line In](#line-in)
  * [Pi or Wavetable](#pi-or-wavetable)
- [Flashing the BIOS](#flashing-the-bios)
- [DOS](#dos)
  * [Mouse in DOS](#mouse-in-dos)
  * [Audio in DOS](#audio-in-dos)
- [Windows 98](#windows-98)
- [Windows 98 Drivers](#windows-98-drivers)
  * [TBPlus](#tbplus)
  * [USB](#usb)
  * [Crystal Audio](#crystal-audio)
  * [Ethernet](#ethernet)
- [Fans](#fans)

## Installing the SOM
When installing the Vortex86EX SOM, _carefully_ align the module as shown in the image below, and _gently_ push it down on the 64 pins.  
Note that the pins on the motherboard are quite thin and fragile, and if you misalign the SOM or use excessive force, they'll likely bend or break.  
Take your time, be careful and double-check the placement before proceeding further!
<p>
  <img src=images/som-alignment-1.jpg title="SOM alignment" width=100%>
  <img src=images/som-alignment-2.jpg title="SOM alignment" width=100%>
</p>

## Jumper Configuration
The board should come preinstalled with all the jumpers necessary.  
For changing the configuration, here's a quick walkthrough of the different jumpers and their functionality.

### PS/2 or USB HID
Jumpers: J7, J12, J15, J16
<p>
  <img src=images/usb-ps2.jpg title="PS/2 configuration" width=50%>
</p>
If you want to use a real PS/2 keyboard connected to the purple PS/2 port, place the two topmost jumpers (J15 and J16) to the leftmost position ("PS/2"). For USB HID keyboard connected to one of the white USB ports (between the PS/2 and serial port), place the jumpers to the rightmost side ("USB").  
Same goes for PS/2 mouse and jumpers J7 and J12.

### Line In
Jumpers: J39, J40
<p>
  <img src=images/line-in.jpg title="Line In" width=50%>
</p>
If you want to use an external audio source connected to the blue 3.5mm jack port, place both jumpers to the leftmost position ("EXT").  
For using a Raspberry Pi Zero2 or Wavetable board as line-in to the sound card, place the two jumpers to the rightmost position ("INT").

### Pi or Wavetable
Jumpers: J25, J26, J27
<p>
  <img src=images/pi-wt.jpg title="PI/WT configuration" width=50%>
</p>
For using a Raspberry Pi (Zero2, 3 or 4) for converting MIDI to analog audio, place the three jumpers to the rightmost position ("PI").  
For using a wavetable board, place the jumpers to the leftmost position ("WT").

## Flashing the BIOS
If you've purchased the Vortex86EX system-on-module (SOM) from DMP, ICOP, etc - you need to flash the BIOS first.  
Since the BIOS that comes pre-installed on the SOM is set up for another pinout/configuration, the microSD card slot isn't availble yet, and you need to use a USB flash drive for this part.  
  
Format the flash drive with a DOS-bootable FAT16/32 partition and copy over the [ANYBIOS.EXE and ITXBIOS.ROM files](INITBIOS).  
Alternatively (and easier), just do a block-level transfer of the [INITBIOS.IMG](INITBIOS) file to the flash drive using [Balena Etcher][balena-etcher], `dd` or something similar.  
Then place the flash drive in one of the USB ports (the ones below the RJ45 port). Plug a USB keyboard in the other port. **Note**: at this point, a keyboard plugged into one of the two _HID-only (white)_ ports won't work, you need to use the ones below the RJ45 port!  
Power up the system, and hopefully you'll get a DOS prompt. From there just type:
```
anybios w itxbios.rom
```
Once done, shut down the computer, remove the flash drive and move the keyboard to one of the HID ports.

## DOS
Follow these instructions to set up DOS on a microSD card, SATA drive or USB flash drive:  
(Note: a SATA drive is faster, but this isn't that important in DOS. I recommend using a microSD card, because you'll be able to use the "clicker" feature to simulate the seeking sounds of an old spinning drive, if you're interested in that)
1. Turn off the system, insert a drive of choice.
2. Boot the system, press ESC to bring up the boot menu.
3. Choose the Virtual Floppy drive.
4. Run `fdisk`, select and partition the drive however you want. Make sure to have at least one primary partition, and make it `Active`.
5. Quit fdisk and reboot the system.
6. Once again, boot the system using the Virtual Floppy drive.
7. Run `fdisk /mbr` to write the correct MBR bytes to the new drive.
8. Run `format c: /s` to format the new drive and copy over the necessary system files.
9. Shut down the machine and remove the drive.
10. Copy over DOS and whatever else you want from a modern computer.

### Mouse in DOS
Use [CuteMouse (CTMOUSE.EXE)](DOS-utils).

### Audio in DOS
The Crystal CS4237B sound chip is automatically initialized and configured from the BIOS, so you don't need any drivers in DOS.  
If you wish to change any of the mixer settings, use [CWDMIX.EXE](DOS-Utils).

## Windows 98
Before proceeding, I'd _strongly_ recommend using a SATA drive for Windows 98, as the performance is noticably better than running from an SD card or USB drive.  
  
Download Windows 98 SE from [WinWorldPC][winworldpc-win98]. Product keys are there as well.  
  
Prepare a bootable DOS drive (see the [DOS](#dos) section above), copy the `WIN98` folder over to the drive and run the `SETUP.EXE` from within.

Note: at some point during the installation, you'll get a crash. This is due to the IDE driver being incompatible with the Vortex86EX's IDE controller.  
Reboot, and choose "Safe Mode". From within Win98, install the [TBPLUS](WIN98-drivers/TBPLUS) drivers from R. Loew and then reboot again and complete the installation.  
  
An easier way is to install Windows 98 SE is using a [version I've prepared](WIN98) which has the IDE drivers "slipstreamed" (meaning that Windows will use the updated drivers automatically).

## Windows 98 Drivers

### TBPlus
If you installed the TBPlus drivers during the Windows 98 installation, or used the slipstreamed Windows 98 installer you're all set. If not, install the [TBPlus drivers](WIN98-drivers/TBPLUS).

### USB
In the BIOS Settings, you can choose to have USB flash drives appear to the system as fixed disks.  
With this setting enabled, they'll show up as regular hard drives in DOS and Windows.  
If you turn this setting _off_, you can use flash drives as removable storage in Windows 98. Use [nusb36e.exe](WIN98-drivers/USB) to install the required drivers.

### Crystal Audio
Run `SETUP.EXE` from the [Crystal Audio](WIN98-drivers/CWD-v286-1998-itx-llama) driver folder.

### Ethernet
From Device Manager, find the Ethernet device and install the [RDC R6040 driver](WIN98-drivers/r6040_win98).

## Fans
The Vortex86EX SOM doesn't draw much power, and shouldn't require active cooling if running at or below 300 MHz.  
If you do wish to add one or more fans, the motherboard has three separately controllable 4-pin PWM fan connectors:
<p>
  <img src=images/fan-1.jpg title="Fan header" width=50%>
</p>
Simply connect a modern 4-pin fan to one of these headers, and set the corresponding jumper to either 5V or 12V:
<p>
  <img src=images/fan-2.jpg title="Fan configuration" width=50%>
</p>

Note: Take care **not** to supply 12V to a 5V fan - you'll likely fry it.

[balena-etcher]: https://www.balena.io/etcher
[winworldpc-win98]: https://winworldpc.com/download/417d71c2-ae18-c39a-11c3-a4e284a2c3a5

[vogons-thread]: https://www.vogons.org/viewtopic.php?t=93480