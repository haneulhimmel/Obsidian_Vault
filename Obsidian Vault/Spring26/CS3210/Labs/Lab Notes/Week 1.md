- XV6 Overview - High Level
	1. Process abstraction
		1.   Multiplexing, Isolation, Interaction
	2. Unix-Like
		1. 	1.Everything is a file -> read/write stream (sequence of data that can be accessed sequentially)
		2. Simplifies programming
		3. Enables composability
	3. Main Components
		1. Bootloader
			1. Initializes the sys by loading the kernel into mem and transferring control to it
		2. Mem management
			1. Manages PTs to translate VA to PA
		3. Processes and scheduler
			1. Procs are fundamental units of exec. XV6 can create, maintain, and preempt processes
			2. Scheduler allocates CPU time to process based on Round Robin (RR) algo.
		4. Traps and interrupts handler
			1. Handled by the kernel -> allows hardware and user requests to be handled promptly
		5. Filesystem
			1. Provides mechanisms for storing and retrieving data across reboots
			2. Support file ops like creation, deletion, reading, and writing
		6. Device drivers
			1. Manage communication between OS and hardware devices
		7. System calls
			1. API between user and kernel
	4. Lingo
		1. Kernel and User Space
			1. Kernel -> Privilege and direct access to hardware
			2. user -> Restricted access to hardware
				1. Interacts through system call
		2. System Call Routing
			1. User process can generate a sys call by starting a trap w/ the sys call trap num
		3. 