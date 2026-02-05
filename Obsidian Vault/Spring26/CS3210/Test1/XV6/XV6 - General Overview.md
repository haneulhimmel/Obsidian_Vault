-    Core Systems
	- Bootup Process
		- Before we can jump into main: have to bring the program to memory -> the process lives in its own section of virtual memory
		- What are initialized: Register State, CPU state, Stack
		- Steps of the Process (Booting Responsibilities)
			1. BIOS: ROM Firmware on the mother board  (Initialize lowest-level hardware details; load boot block) -> Heterogeneity? Hardware
				- Stored in a dedicated firmware hub or flash chip
				- Key Functionalities
					1. Initialize memory controller
					2. Initialize RAM: zero initialize (Why? To ensure security b/c existing memory there is unknown -> potential corruption/leaking)
			2. Bootloader: First block of the bootable disk (Initial processor setup; load kernel & execute)
				- MBR: Master Boot Record: First 512 Bytes that BIOS locates will contain the bootloader code -> Then loaded to RAM
				- Sv6 uses its own simpler bootblock -> bootasm.S and bootmain.c
				- TLDR: Prepares the system to launch kernel
				- Detailed Walkthrough:
					1. Set up an initial configuration of memory and load the kernel into it
						- For x86: Switch from "real-mode" to "protected-mode"
					- Bootasm.S: 52 loads a descriptor table that tells the CPU 
					- Preps the kernel's ELF
					- ELF headers are checked, parsed, and loaded to correct part of memory
					- Jump to kernel w/ no way to return
			3. Kernel: Beginning of Kernel Partition (Actual executing kernel) -> Heterogeneity? Software
				- Can the kernel jump straight to its main function? *No*
					1. Kernel's entry point: kernel/src/asm/entry.S
						- Set up Initial Stack
						- Set up Initial Page Table
						- Jumps to Main()
	- Virtual Memory
		- Main Virtual address spaces are mapped by page tables to limited physical address spaces
		- Minimum set of operations to provide from a VM system
			- Ability to create page tables
			- Switch between page tables
		- XV6
			- Implements VM in kernel/src/vm.c
			- A trick used by xv6
				- Maps all physical address to offset 0x80000000 -> Converted to binary, the MSB is 1 indicating communication w/ the kernel and not user
			- Ex: What about a user process's virtual address 0x1008?
				- if the user's PT is mapped, just access it
				- OR map their PT then access
				- OR walk the PT
	- Processes
		- Process Info -> proc.c
			- Processes are isolated units that run in xv6
	- System Calls and Traps
	- Filesystem

- Modern OS Design
	- Memory
		- Modern OS rarely refer to real, physical memory addresses when addressing code, stack, heap, etc.
		- VM is used to create the abstraction that every process has access to all of addressable memory