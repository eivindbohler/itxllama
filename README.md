## ITX-Llama User's Guide

- [Installing the SOM](#installing-the-som)
- [Jumper Configuration](#jumper-configuration)
  * [PS/2 and USB HID](#ps2-or-usb-hid)
  * [Line In](#line-in)
  * [Pi or Wavetable](#pi-or-wavetable)
- [Flashing the BIOS](#flashing-the-bios)
- [DOS](#dos)
- [Windows 98](#windows-98)

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
  <img src=images/usb-ps2.jpg title="SOM alignment" width=50%>
</p>
If you want to use a real PS/2 keyboard connected to the purple PS/2 port, place the two topmost jumpers (J15 and J16) to the leftmost position. For USB HID keyboard connected to one of the USB ports between the PS/2 and serial port, place the jumpers to the rightmost side.  
Same goes for PS/2 mouse and jumpers J7 and J12.

### Line In
Jumpers: J39, J40
<p>
  <img src=images/line-in.jpg title="SOM alignment" width=50%>
</p>
If you want to use an external audio source connected to the blue 3.5mm jack port, place both jumpers to the leftmost position.  
For using a Raspberry Pi Zero2 or Wavetable board as line-in to the sound card, place the two jumpers to the rightmost position.

### Pi or Wavetable
Jumpers: J25, J26, J27
<p>
  <img src=images/pi-wt.jpg title="SOM alignment" width=50%>
</p>
For using a Raspberry Pi (Zero2, 3 or 4) for converting MIDI to analog audio, place the three jumpers to the rightmost position.  
For using a wavetable board, place the jumpers to the leftmost position.

## Flashing the BIOS
If you've purchased the Vortex86EX system-on-module (SOM) from DMP, ICOP, etc - you need to flash the BIOS first.  
Since the BIOS that's pre-installed on the SOM is set up for another configuration, the microSD card slot isn't availble yet, and you need to use a USB flash drive.  
Format the flash drive with a DOS-bootable FAT16/32 partition and copy over the [ANYBIOS.EXE and ITXBIOS.ROM files](INITBIOS).  
Alternatively (and easier), just do a block-level transfer of the [INITBIOS.IMG](INITBIOS) file to the flash drive using [Balena Etcher][balena-etcher] or something similar.  
Then place the flash drive in one of the USB ports (the ones below the RJ45 port) and boot the system.  
Hopefully you'll get the DOS prompt, and from there just type:
```
anybios w itxbios.rom
```
Once done, shut down the computer and remove the flash drive.

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

## Windows 98
Before proceeding, I'd _strongly_ recommend using a SATA drive for Windows 98, as the performance is noticably better than running from an SD card or USB drive.  
  
Download Windows 98 SE from [WinWorldPC][winworldpc-win98]. Product keys are there as well.  
  
Prepare a bootable DOS drive (see the [DOS](#dos) section above), copy the `WIN98` folder over to the drive and run the `SETUP.EXE` from within.

Note: at some point during the installation, you'll get a crash. This is due to the IDE driver being incompatible with the Vortex86EX's IDE controller.  
Reboot, and choose "Safe Mode". From within Win98, install the [TBPLUS](WIN98-drivers/TBPLUS) drivers from R. Loew and then reboot again and complete the installation.  
  
An easier way is to install Windows 98 SE is using a [version I've prepared](WIN98) which has the IDE drivers "slipstreamed" (meaning that Windows will install the updated drivers automatically).

[balena-etcher]: https://www.balena.io/etcher
[winworldpc-win98]: https://winworldpc.com/download/417d71c2-ae18-c39a-11c3-a4e284a2c3a5