             INSTALLATION INSTRUCTIONS FOR TBPLUS PATCH PACKAGE

                             Version 3.0

                              11/02/2015

                        Copyright (C) 2010-2015
                          By Rudolph R. Loew


This Package contains the Patched System Files and SATA INF Files to support
the following features.

1. Large Sector Size support up to 32KB per Sector in DOS.
2. Large Sector Size support up to 4KB per Sector in Windows 98SE.
3. 256 Sector (128KB to 1MB/8MB) Cluster Size support for DOS and Windows.
4. Full 48-Bit LBA Addressing Support for Windows 98SE.
5. Support for 40-Bit Partition Addresses (RFDISK ExtMBR Feature).
6. Boot DOS using any or all above Features.
7. Patched Partitioning bug when using Multiple Primary Partitions.
8. Support for Multiple Extended Partitions.
9. Support for Large Sector Floppy Disks.
10. Native Mode support for SATA Controllers for Windows 98SE.
11. Support for 64-Bit Addressing for SCSI and USB.
12. Generic Drivers for RAID and RAID/AHCI SATA/PATA Controllers.
13. Driver for SI 3512 SATA Controller.
14. Windows Only Partitions.

The Patch files are based on the most recent Versions of the Windows 98SE
files for the English Version, except DISKTSD which is upgraded to the
Windows ME Version.



INSTALLATION

To Install the full Package run the INSTALL.BAT Script using the following
Syntax:

INSTALL [[WinDir] WinBootDir]

Where "WinDir" is the Path to the Windows Folder (ex. C:\WINDOWS).
Where "WinBootDir" is the Path to the Windows Boot Folder (ex. C:\WIN98) if
 running Windows 98 not 98SE.
These arguments are optional if running from a DOS Box in Windows.

If you have an early VIA Controller that does not support AHCI and you plan
to set it to RAID Mode, remove the WINDOWS\INF\ATA0104A.INF File. Otherwise
remove the WINDOWS\INF\ATA0104.INF File.

If you have an early VIA Controller and you plan to set it to IDE Mode, run
the PATCHPCI Porgram to prevent a possible hang.



UNINSTALL

To Uninstall the full Package run the UNINST.BAT Script using the following
Syntax:

UNINST [[WinDir] WinBootDir]

Where "WinDir" is the Path to the Windows Folder (ex. C:\WINDOWS).
Where "WinBootDir" is the Path to the Windows Boot Folder (ex. C:\WIN98) if
 running Windows 98 not 98SE.
These arguments are optional if running from a DOS Box in Windows.

If you ran PATCHPCI during Install, rerun it to Uninstall the Patch.



PARTIAL INSTALLATIONS

To Install or Uninstall only the Windows Patches use:

INSTALLW [WinDir]
or
UNINSTW [WinDir]

Where "WinDir" is the Path to the Windows Folder (ex. C:\WINDOWS).
This argument is optional if running from a DOS Box in Windows.

Follow instructions relating to VIA Controllers in INSTALL Section above.



To Install or Uninstall only the DOS Patches use:

INSTALLD [[DOSDir] BOOTDir]
or
UNINSTD [[DOSDir] BOOTDir]

Where DOSDir is the Path to the Folder that contains the SMARTDRV.EXE Program.
Where BOOTDir is the Path to the Folder that contains the DBLBUFF.SYS File
 if different.
These arguments are optional if running from a DOS Box in Windows.



You will need to reboot for the Patches to take effect.


IMPORTANT: The DOS ATTRIB.EXE Command must be in the current PATH to update
           IO.SYS for the Full or DOS Patch Installation. Copy the ATTRIB.EXE
           to the current Directory otherwise.

           If you have an AHCI Only SATA Controller in your Computer, you
           must remove the ATA0106.INF File from your WINDOWS\INF Folder after
           you Install the Patch and before you Reboot.
