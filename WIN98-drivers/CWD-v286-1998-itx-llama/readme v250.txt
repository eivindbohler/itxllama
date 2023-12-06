30-12-2008 included here because it contains more info
------------------------------------------------------


README.DOC for Crystal Semiconductor Corp. 2.50 Windows 95 Drivers

This Document contains the following:
1. Version Numbers
2. List of files
3. File Summary
4. Installing Crystal Audio Drivers
5. Uninstalling Crystal Audio Drivers
6. Dos Mode
7. Multiple Crystal Audio Cards
	8. Crystal 3D Audio - CWB3DSND.EXE
	9. Crytal Digital Assisted Joystick


1. Version Numbers:  

2.01 T2		CWBINIT.EXE  
4.03.2500		CWBAUDIO.DRV 
4.03.2500		CWBAUDIX.VXD 
4.03.2500		CWBFM.DRV    
4.03.2500		CWB3DSND.EXE 
4.03.2500		CWBJOY.VXD   
4.03.2500		CWBMIDI.DRV  
4.03.2500		CWBMIDI.VXD  
4.03.2500		CWBMIX.EXE   
4.03.2500		CWBPCPLE.DLL 
0.01.000		MSGLOOP.EXE  
4.03.2500		SETUP.EXE    
0.01.000		VWSTREAM.VXD 
0.01.000		WSTREAM.DLL  

Microcode:
79   		CS4232 Microcode
6     	CS4232A Microcode
55		CS4236 Microcode
17		CS4236B/CS4237B/CS4238B Microcode

2. List of Files:

CWBMIDI  DRV         9,392  06-24-97  2:50a 
CWBAUDIO BIN         8,225  06-24-97  2:50a 
CWBAUDIO DRV       228,208  06-24-97  2:50a 
CWBAUDIO INF        27,104  06-24-97  2:50a 
CWBAUDIO INI           774  06-24-97  2:50a 
CWBAUDIX VXD       115,224  06-24-97  2:50a 
CWBFM    DRV        21,776  06-24-97  2:50a 
CWBINIT  EXE        95,840  06-24-97  2:50a 
CWBJOY   VXD        10,109  06-24-97  2:50a 
CWB3DSND EXE       261,120  06-24-97  2:50a 
CWBMIDI  VXD        29,326  06-24-97  2:50a 
CWBMIX   EXE       239,070  06-24-97  2:50a 
CWBPCPLE DLL        37,376  06-24-97  2:50a 
MSGLOOP  EXE         4,112  06-24-97  2:50a 
SETUP    EXE       248,832  06-24-97  2:50a 
VWSTREAM VXD         5,175  06-24-97  2:50a 
WSTREAM  DLL         9,712  06-24-97  2:50a 
WSTRM    TXT         1,750  06-24-97  2:50a 
README   DOC
3. File Summary:

CWBINIT.EXE   	CS4232/36/36b/37b/38b Configuration Program.  A DOS device driver used to initialize and configure the card.  It will download Microcode from CWBAUDIO.BIN.  Using the /X option, it will download resource data from RESOURCE.BIN, CS32RES.BIN, or CS36RES.BIN.

CWBMIX.EXE	DOS mixer used to set or adjust Sound Blaster mixer settings.  It will run as a GUI application or as a command line utility.

CWBAUDIO.BIN  	Data file containing Microcode for the CS4232, CS4232A, CS4236, CS4236B, CS4237B and CS4238B.  It is used by CWBAUDIX.VXD and CWBINIT.EXE.  

CWBAUDIO.INI	Default initialization parameters for CWBINIT.EXE.  It is only used if PnP is overridden (/O) or if not using the Win 95 option on a non PnP system (no /W).  

CWBAUDIO.INF	Windows 95 installation file.  It will install the files, update the registry, install CWBINIT.EXE /A in the CONFIG.SYS, and it will install CWBINIT.EXE /A in the DOS mode CONFIG.SYS.  It should be modified by OEM's to meet their specific needs.  

CWBFM.DRV	Crystal FM MIDI driver.

CWBAUDIX.VXD	CS4232/36/36B/37B/38B Windows 95 virtual device driver.

CWBAUDIO.DRV	CS4232/36/36B/37B/38B Windows 95 wave, aux, and mixer driver.

CWB3DSND.EXE	CS4237B/38B 3D Audio Control Applet.  

CWBMIDI.VXD	Crystal MPU-401 MIDI virtual device driver.

CWBMIDI.DRV	Crystal MPU-401 MIDI Driver.

CWBPCPLE.DLL	Windows 95 Power Control Panel extension.  This file will create an extension to the default Windows 95 Power Control Panel, enabling new features such as idle time-out and power down now.  This is not installed by default and requires a change to the install .INF.

CWBJOY.VXD	Crystal Digital Assisted Joystick virtual device driver.

SETUP.EXE	Crystal Windows 95 uninstall program.  Running this program will clean out any Crystal registry entries, delete Crystal files, clean the CONFIG.SYS, and prompt the user to restart.  When Windows 95 restarts, the Crystal drivers should install using the default Windows 95 installation.

VWSTREAM.VXD	It is the main WaveStream engine.  It resides between
			WSTREAM.DLL and CWBAUDIX.VXD.  It does the Software 				WaveTable Synthesis, SoundBlaster, and mixing.	This 				VXD is provided in our kit to hook up with the 					Brooktree WaveStream CD.	
	
WSTREAM.DLL		It is the WaveStream component which communicates with 			cwbaudio.drv and in turn passes information down to 				vwstream.vxd.  This DLL is provided in our kit to hook
			up with the Brooktree WaveStream CD.

MSGLOOP.EXE		It is a WaveStream component which is provided in our 			kit to hook up with the Brooktree WaveStream CD.


4. Installing Crystal Audio Drivers
1.1.Turn PC off and insert audio card into an ISA slot unless audio device is present in your motherboard.
2.2.Turn PC on and start up Win95.
3.3.Win95 is a PnP OS.  It automatically recognizes new PnP audio hardware and creates a database for the hardware.  The following shows the the Crystal logical devices:
D.Win95 detects the Crystal PnP Audio System Codec.  Win95 asks for the manufacturer's Disk.  Please select the approriate drive.  If the Windows default driver is not grayed out, installing DirectSound games replaces Crystal drivers with Microsoft Windows Sound System drivers.  
E.Win95 detects the Crystal PnP Audio System Joystick (Joystick in some platforms).  On certain versions of Windows 95, Windows will prompt for the Win 95 CD in order to re-install the joystick drivers.
F.Win95 detects the Crystal PnP Audio System Control Registers (CS4232 Support Registers in some platforms.)
G.Win95 detects the Crystal PnP Audio System MPU-401 Compatible.
H.Win95 detects the Crystal PnP Audio System CD-ROM.  This device may not be found if the Plug and Play resources do not reference a CD.  If your audio device is not using the CD-ROM interface, this device will not be detected.

If any of the above (A thru E) is not detected, a previous Win95 sound card installation was done.  For a clean reinstallation, the user should see the Uninstalling Crystal Audio drivers section below.  

5. Uninstalling Crystal Audio Drivers
1.From Win95, run setup.exe provided in the Crystal installation diskette. The Setup will do an automatic cleaning up of the Win95 Crystal Audio registry entries. Many problems with reinstallation occur because of existing registry entries from previous installations and because of the \WINDOWS\INF\OEMx.INF files.  After running setup, the various Crystal devices from the Control Panel should disappear.  It is recommended that prior to running Setup, remove the device entries in the Sound, Video, and Game Controller of the System Device Manager, and Crystal entries (if any) in the Other detected devices section of the Device Manager.
2.Shutdown and turn off your PC.  
3.Turn PC on, Start Win95, Win95 will now detect new hardware, create an information database, and proceed with the installation of Crystal device drivers.  

6. Dos Mode
A.  Restarting the computer in MS-DOS mode.
Shutting down to MS-DOS mode from the Shutdown Win95 Menu will automatically run the CWBINIT.EXE /A in dosstart.bat.  Therefore, shutting down to MS-DOS mode will automatically have the audio card configured for Dos games.

B.  Enabling Dos support in Dos prompt icon.
To enable real DOS mode with CS4232/36/36b/37b/38b support:
1.Select a DOS prompt icon.
2.Select Properties.
3.Go to the Program tab.
4.Select the Advanced... button.
5.Click MS-DOS Mode.
6.Click "Specify a new MS-DOS configuration."
7.The following line will be automatically placed into the new MS-DOS configuration (with right path):
        DEVICE=C:\WIN95\CWBINIT.EXE /A 

7. Multiple Crystal Audio Cards
To enable a CS4232/36/36B/37B/38B audio card in a system that 
contains multiple Crystal audio cards:
1.  Add the following option to the CWBINIT.EXE 
    entry in the CONFIG.SYS.
    Device=C:\WINDOWS\CWBINIT.EXE /W /Sxx
    where xx is the OEM ID number for the Crystal Part
    audio card to be enabled.
2.  The OEM ID number can be obtained from the 
    manufacturer.

8.  Crystal 3D Audio - CWB3DSND.EXE
The 3D audio accessory allows you to control the 3D audio features of your audio system. Depending on the specific audio device in your system you may have SRS® 3D Audio or QSound™ 3D Audio. The accessory runs each time you start your computer where it appears in the notification area of the task bar. The task bar is where the start button resides. The notification area is where the clock normally appears on the task bar. The accessory is activated by clicking with the left mouse button on the SRS or QSound logo in the notification area (If you have trouble finding the accessory, move the mouse over each icon in the notification area until you find the icon with a tool tip that says "Crystal SRS 3D Audio" or "Crystal QSound 3D Audio"). You can also click on the logo with the right mouse button to see a menu with options for activating the control "Settings", viewing the about box "About", or exiting the accessory "Exit".

Note: If for some reason the Crystal 3D Audio icon is missing, you can run it by choosing Programs | Accessories | Multimedia| Crystal 3D Audio Control from the Start menu.  If you still do not see the 3D audio Icon it may be that the chip you have installed does not support 3D.  Only the CS4237B and CS4238B chips support 3D audio. 

Controlling your 3D audio
There are two sliders for controlling the sound of your 3D audio: on SRS systems they are labeled Center and Space, on QSound systems they are labeled Volume and Space. Moving the slider toward the plus sign increases the effect, moving the slider toward the minus sign decreases the effect. You may find that you prefer different settings for different types of music. You can save up to 3 configurations using the preset buttons. You can disable your 3D audio by un-checking the Enabled check box at the bottom of the accessory.

Preset Buttons
The 3D audio accessory provides three preset buttons, labeled 1, 2, and 3, that allow you to save your favorite 3D audio settings. To activate the settings click on the preset button with the left mouse button. To store your settings, change the description of the button that appears in the tool tip, or to restore the button to the factory defaults click with the right mouse button on the preset button to see the menu of options.

9.  Crystal Digital Assisted Joystick
The Crystal Digital Assisted Joystick must be manually enabled for proper Digital Joystick configuration. This can easily be done by opening the Joystick Properties in the Control Panel and selecting the Joystick configuration to Crystal Digital Assisted Joystick.





	






