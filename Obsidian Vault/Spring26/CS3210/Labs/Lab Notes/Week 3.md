## Bootloader Review
#### Booting Overview
1. BIOS initializes Hardware
2. Bootblock loaded into mem. at 0x7C00
	1. Located in first 512-byte sector of boot disk

#### Bootloader to Kernel
1. Bootloader switches CPU from real mode -> protected mode
	1. Global Descriptor Table (GDT): works w/ a limited version -> defines basic mem. funcs. so that protected mode can work
2. Bootloader loads the xv6 kernel into PA 0x00100000 (1 MB)
	1. Lower addresses are reserved for the BIOS and I/O devices
3. entry.S sets up a bootstrap page directory w/ 2 entries
	1. Entry 0: Identify map where VA = PA, so instructions keep running after paging is enabled
	2. Entry 512: Maps VA KERNBASE - KERNBASE + 4MB -> Physical Address 0-4 MB, so kernel's high VA resolve to where it physically resides