# xv6 Overview

- Core Systems
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
					- Preps the kernel's ELF (Executable and Linkable Format)
						- ELF is the result of compiling a program's source code
					- ELF headers are checked, parsed, and loaded to correct part of memory
						- Exec syscall replaces calling process's memory with new memory location loaded from file stored in file system (fs)
						- Exec syscall : xv6 pg. 35 ([[XV6 Manual.pdf#page=35]])
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

![[xv6_intro.pdf]]

---

# x86 Overview
- Handover process -> Ensure Compatibility between different BIOSes, bootloaders, and kernels

- Bios
	- Reset Vector: First addr fetched and executed -> at 0xfffffff0
		- 12 MSB set high, 20 bits (1MB) of addressability
	- First 16 bytes of the ROM chip w/ instruct to exec
		- Bootloader must always contain a jump to the initialization code in those top 16 bytes
	- Bios Handover: Real Mode
		- 16 bit w/ 16 bit regs
		- Phys addr calculated as CS (Code segment) <<4 + IP
			- Phys addr = 16 * segment register + offset --> equivalent to above expression
			- Bits of memory allowed to address w/ this -> 
			- How do we get to addressing 1MB of phys addr space -> 
		- Combability to old kernel OS requires real mode
	- IVT: Interrupt handling
- Bootloader/Bootblock
	- State of CPU during exec of bootblock -> 16 bit real mode
	- State of memory subsys -> Naive memory addressing model
		- Physical access to mem
		- No aliasing
		- Need to transition to real-protected mode
	- Sets up
		- x86 state -> regs
		- Mem referencing model (segmentation etc.)
		- Switch processor to 32-bit protected
		- BIOS features (memory aliasing etc.)
	- **Reset Vector** stores an address at which an assembly instruct is held -> contains a jump to the main code to execute
- Kernel

![[x86_arch.pdf]]

---

# Isolation General

Within the system, isolation is desired at points of times - **NOT ALL THE TIME**

---
### Isolation Pros

1. Failure isolation:
	- failures don't propagate -> one of driving motivations for kernel design

2. Performance isolation: 
	- Aberrant resource consumption is controlled
	- Avoiding starvation (best effort vs guaranteed -> method comparison)

3. Correctness isolation:
	- Other programs should not be affected by the correctness of my program
---
### When is Isolation Needed

When we have **shared** resources:
1. Processes (memory is shared)

When we have **non-cooperative** entities:
1. 

---
### Potential Trade Offs

1. Safety: Corresponds w/ Isolation
2. Usability: Decreases w/ Isolation
3. Performance: Decreases w/ Isolation

---
### Use Cases

1. Kernel from user space
2. User process from one another
3. Memory
4. Security vs Non-security functions

---
### Mechanisms

#### Hardware isolation
1. Processor "rings"/protection levels (PLs)
	1. Ring 0 protects CPU's shared resources
		1. Writes to %CS (to defend current privilege level - CPL)
		2. Memory read/write is checked for privilege level (S/U)
	2. Transition between PLs
		1. Protected Control Transfer

#### Address Spaces (Segmentation, Virtual Memory/Page Mapping)
1. Isolate the memory
2. Segment Selector (EX: Interrupt Handler)
	- Interrupt Descriptor Table (IDT) contains CS + eip to the handler
	- Descriptor Privilege Levels (DPT) is checked against the CS descriptor that contains the CPL
3. Virtual Memory Management
	1. Gives every process an identical "virtual" address space
	2. Enforce privilege level at page granularity 

#### Time-slicing (Isolate the CPU)
1. CPU quantum to isolate access to CPU for processes -> Difficult to isolate w/ time quanta: leakage of data
2. Idea: Abstract CPU so each process perceives its own CPU
3. Scheduler
	1. Provides access to shared resource X to consumer P at time T
	2. Cooperative vs Preemptive (policy/how question) -> Yield vs Clock Driven
4. Multiple processes can share a CPU, processes can transit CPUs

#### System Call Interface (User vs Kernel)
1. Safe transfer of control from user to kernel
2. Essentially, breaking isolation in a controlled manner

![[os_isolation.pdf]]

---
# Kernel Organization and APIs

### Kernel Organization/Separation

#### Microservice Architecture: 
![[Microkernel.png]]
Definition: To reduce the risk of mistakes in the kernel, OS designers can minimize the amount of OS code that runs in kernel mode, and execute the bulk of the OS in user mode
For user spaces dependent on services on top of the kernel -> if OS service fails then user spaces and kernel are unaffected ONLY if the user space program is not dependent or connected to the service

Declarative and Imperative are ways to capture the dependency of the OS services, kernel, and user space programs. The following format is only possible for services that are separated from the kernel
- Un -> {s..., sn}

#### Monolithic Kernel: 

![[Pasted image 20260309204255.png]]
Definition: Entire OS resides in the kernel, so that implementations of all system calls run in kernel mode
1. xv6 is implemented as a monolithic kernel -> The kernel implements the complete OS
If the kernel has N dependent user spaces and fails -> The N user spaces will cease
However, if one of N user space fails -> Independent/Isolated, so it will not affect any other user spaces or the kernel

If the services are coupled with the kernels, the format will look more like the following
- Un -> {all s_i}
---
### Kernel Responsibilities

![[Kernel_Interface.png]]

#### What are the main ideas:
- Protection
- Isolation

#### Kernel APIs:
- echo Hello | cat -> Uses 3 processes: sh (shell), cat, echo -> These use syscalls to communicate from the user space to the kernel space
- Interface that lets programs in user-space request services from the OS kernel
	- Essentially a user side program that will eventually result in a syscall

#### Factored Operating System (FOS)
Form of organization: The OS is decomposed into subsystems
1. File Systems
2. Memory Management
3. Network Management
4. Interprocess Communication (IPC)
#### Microkernel:
What is the minimal task that we can allocate to the kernel -> which tasks can we move to user space (FS, IPC?, Mem, Net)

Kernel-User Space Divide: A lot of overhead w/ communication between the 2 spaces (expensive) -> We get a header to the process asking for inter-process communication (IPC) to reduce cost

#### Isolation Tradeoff:
Microkernel: Maximizes safety as the OS services are factored out (Isolation) -> At the cost of performance (speed), Hard to compartmentalize

Monolithic: Maximizes performance at the cost of safety

Ex: File Server (FS) failing won't affect the kernel -> However, a lot of processes are dependent on FS so regardless it doesn't matter if it's in the kernel or not (might as well shove it in kernel)

![[kernel_org.pdf]]

---
# Virtual Memory

![[VM_Layout.png]]

### Why is VM Important

1. Isolation
2. Resource Multiplexing -> Make 1 phys addr look like many virtual addr spaces
3. Protection
4. Masks resource limitations
	1. Can allocate more VM than current RAM
	2. Swapping
---
### x86 Address Translation

| Segmentation                                                                                                                                                                                                                           | Paging                                                            |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------- |
| - Avoids v2p translation overhead<br>- Reliant on: Global Descriptor Table (GDT) and Local Descriptor Table (List of mem. segs. private to each process)<br>- Segmentation registers (CS, DS, etc.) refer to GDT or LDT as appropriate | - Avoids Fragmentation<br>- Allows large virtual memory addresses |

---
### Bootup Page-Table in xv6 -> PTP Walk

1. ENTRYPGDIR: Only important during bootup process; One of the first instances of Memory Aliasing 
	1. KERNBASE >> PDXSHIFT: Number of bits shift to get the 10 MSB -> For a 32-bit address, shift by 22 to get the 10 MSB
	2. From there, we can observe 2 VFN being mapped to 1 PFN
2. PTE/PDE
	1. Paging Design Choices
		1. 2 Level Paging Sys
			1. (10, 10, 12)
			2. 1. CR3 -> Goes into the base of the PGDIR
			3. From there, the 10 MSBs of the address map to the Page Directory Entry (PDE)
			4. The next 10 bits map to the Page Table Entry (PTE), while the address stored at PDF is the address of the base of the Page Table Page (PTP) where the PTE is located in
			5. The last 12 bits map to the actual value/destination, while the address stored at PTE represents the base of the Page where the value is found in
		2. 1 Level Paging
			1. (10, 22)
			2. (20, 12)
		3. Overheads
			1. Memory: Sum of all PTs
			2. Latency: Page table walk
		4. Tradeoffs
			1. 2 Level: Less Mem, More Latency
			2. 1 Level: More Mem, Less Latency
		5. 4 Level Paging: x86-64
			1. a
3. Memory Management Unit 
	1. Hardware Support: VA -> PA translation
	2. Cache: TLB (Translation Lookaside Buffer)
4. Page Walking (Input: VA)
	1. Blah

---
### xv6 VMM Limitations

1. Expects kernel to map all of physical  memory (up to 2GB)
	1. Once the kernel and a user program (at most) can have a mapping to a physical page -> physical page can have no more mappings
2. No ability to have multiple virtual pages map to a single page
3. Other OS can have many user programs map VPs to the same PP

---
### VM : Lec. 3/4

1. Now have we VM -> b/c of paging
	1. What can we do with it? Already covered standard isolation
		1. Observe
		2. Monitor
		3. Change
		4. Interpose
	2. Paging: level of indirection that enables
		1. Interpose on control path
		2. Suspend reality and modify the behavior of underlying mechanisms
	3. Copy-on-write fork
		1. Guarantee: Child process has access to all of addr spaces of parent
		2. We do not want a complete copy of all the physical memory as that is time-demanding and a lot of work (especially with thousands of processes)
			1. Just set the pointers to the same set as parent's frames
		3. Those physical frames have PFNs, so the Page Tables have the same mapping to the same PFN between both child and parent (Page Tables are exactly the same -> Page Directory are exactly the same)
			1. If there are shared vertices in the mapping diagram of processes (child and parent), we should NOT allow the write to proceed to the pages (in the case with the shared page directory -> we cannot allow fs)
			2. We need to copy the page page and the corresponding page and separate the directories of the parent and child
			3. With this copy, we need to update the PTE as the VA -> PA mapping has now changed (Mutating the PT because of the new page mapping so copy PT must happen)
			4. As a result of that, we need to update the PDE as well as the PT mapping has changed as well with that copy (Mutating the PD because of the new page table mapping so copy of PD must happen)
			5. The parts that were not copied must still be accessible by both processes
			6. *Lab 2 does not use CoW PT/PD allocation - only CoW page allocation (CoW -> Copy on write)
				1. Focus on sharing to ensure CoW ops work
		5. Permissions
			1. Logical: Is it legal to access this memoru
			2. Physical: Should the CPU give me a trap for accessing this page
	4. Demand paging or lazy allocation
		1. saves us a swap; performance improvement
	5. On Demand Zero-filled pages & One zero-filled page
		1. Avoid getting physical pages that are already populated with other process' data
		2. Pointer to a preexisting frame that is already filled with 0s (0 page)
			1. Can have thousands of processes pointed to this one zero-filled frame
	6. Virtual Allocation
	7. Virtual Shared Memory
	8. Memory Mapped Files
	9. Paging to Disk
	10. Memory Oversubscription

---
### Copy-on-Write Fork : Lec 4/4

The main drawback of the built-in function is that is duplicates physical frames of memory on fork
- Essentially, Lab2 will make it so that only duplicate physical frame of memory when child needs to edit something at that address space
- Perform a copy within physical address space -> Change mapping of child process to new copy -> Then can apply write
- Throw TRAP for immutable areas that might get attempted to write (Then Inside Trap, Move on to the following) -> Backpropagate and copy Page, PT and PD to grant the child process permission and ability to edit
	- PTE points to a Page (Defined by PFN)
	- TLB: VFN to PTE **** REVIEW -> Only focus on the context of the current process
		- Context Switch
		- Invalidate only a single mapping during the PTE to PFN for CoW

Breakdown of the color-coded parent/child process mapping to physical address space:
1. Red -> Stack: Higher up in mem -> Deeper in User Space Programs
2. Green -> Whatever is in between Stack and ELF Header (Mapping of program)
3. Blue -> ELF Header -> Program mapping/Set of instructions

---
### Swapping Wrap Up: Virtual Memory Tips and Tricks

Memory Backing:
1. Physical memory is ***NOT*** limited by our RAM
2. Virtual memory does ***NOT*** have to be backed by RAM
	1. Swapping -> Saving mem. to disk when we run out of RAM - "swap" some mem. to disk
	2. Memory mapping -> Mapping file information into VAs and writing it back to the file

Swapping:
1. Optimally: We want the page that will be accessed latest -> However, we cannot know this, so we default to Least Recently Used (LRU) approximation
2. LRU is expensive to track
	1. Info needed: When the page was accessed (timestamp information)
	2. Expensive: Needed for each access (both reads and writes); Unnecessary overhead (even with infinite mem.)
	3. Complexity of tracking timestamp info: O(n) -> O(logn) -> O(1)
	4. Worst overhead: trap on every access (pg_flt for every load and store)	

Clock Algorithm/"Second Chance": *Page replacement algorithm used in OS to approximate LRU* - [[Stanford_OS_Principles.pdf]]
1. We add a reference bit -> Set whenever a page is read or written
2. When physical memory is full and we need to choose a page to remove, run the clock algorithm
3. Clock hand "sweeps" over pages, rotating back to start if reaching the end
4. Every time the hand visits a page, we ask: "Has this page been referenced since the last time the clock hand swept over it"
	1. If YES (Ref = 1): Mark it as not referenced (Ref = 0), and advance clock hand
	2. If NO (Ref = 0): Choose it for removal, advance clock hand, stop clock algorithm
5. The clock hand is saved for the next time the algorithm runs

Clock Algorithm Worst Case Analysis: 
1. Worst Time: O(n) -> Looping through N number of frames/physical pages
2. When all the pages have their reference bits set to 1, the algorithm needs to loop through each page and then set their bits to 0 before any removal can happen

![[vm1.pdf]]

![[vm2.pdf]]

![[vm3.pdf]]

![[vm_cow.pdf]]

---
# Interrupts and Concurrency I

### Syscalls, Interrupts, and Exceptions

General overview of what interrupts are needed for:
1. Exceptions: Paging, math & hard errors - power, mem.
2. Hardware: Timers, buffers, io-device
3. Debugging: software-breakpoints
4. Communication: Inter-processor-interrupts
5. Control Features: Watchdog, Non-maskable

Every exception/interrupt type is assigned a number (its vector)
![[Interrupt_Overview.png]]
1. NMI: Non-Maskable Interrupts
	1. Never ignored: power failure, memory corruption error
	2. xv6 -> get a non-maskable interrupt -> die
	3. x86 -> vector 2, prevents other interrupts from executing
2. INTR: Maskable
	1. Ignored when $\mathrm{[[IF]]}$ in EFLAGS is 0
	2. Enabling/disabling
	3. 'sti': set interrupt
	4. 'cli': clear interrupt
3. INTA
	1. Interrupt acknowledgement
4. "Software" interrupt: INT
	1. Intentionally interrupts
	2. x86 provides the INT instruction
	3. Invokes the interrupt handler for the vector (0-255)
	4. xv6: INT 0x40 for system calls
5. Entering: int N
6. Exiting: iret
	1. Special instruction to return from the interrupt handler that restores the saved state before going back to user space code
	
---
### Interrupt Handling: High Level

Switch stacks (from user stack to handler/kernel stack)
Setup our registers:
1. Save registers
2. Setup registers
Jump to kernel (set CS:IP to the handler code)

In xv6:
1. x86.h defines the "trap" frame. It gets filled up like a stack frame from bottom to top. The first part is filled by the hardware on 'int'
2. usys.S defines the interrupt for system calls
3. trapasm.S defines the interrupt for exiting back to user space
4. vector.S defines the interrupt vectors which jump to alltraps in trapasm.S
	1. Initial entry point in vector.S
	2. Kernel/src/trap.c -> the vast majority of the code you will need for future labs in this class

Interrupt Descriptor Table (IDT)
1. Table of 256 8-byte entries (similar to GDT - [[Virtual Memory Management]])
2. In xv6, each specifies a protected entry-point into the kernel located anywhere in memory
3. IDTR register (holds a ptr to current IDT)
	1. Stores current IDT
4. lidt instruction -> Setting up the IDT register
	1. Loads IDTR with address and size of the IDT
	2. Takes in a linear address
5. Initialized on boot in trap.c
	
![[IDTR Register.png]]

---
# Concurrency II

### Syscalls, Interrupts, and Exceptions

Interrupts are a psudo concurrency -> when we work in an interruptible environment, we need to figure out how to handle 

Problem Below: If both were reads, it would be fine, but one is a write; therefore, issue thrown
Even though the shared is being locked in the kernel to be written to, it is still able to accessed, which should not be possible

```
Kernel Code:              Int Handler
	Lock()                   Lock()      
	
	Shared = 7               X = shared
	
	Unlock()                 Unlock()
```

*Violate Correctness: If Int Handler expects a value within the lock of the kernel (deadlock)
1. Can't make interrupt handle ignore the locks
2. Whenever hold a lock, delay the interrupts
	1. Wait until the unlock occurs on the kernel code, before the lock begins for the Interrupt
	2. Make this entire process atomic

The approach below is our solution to the deadlock and reference issues: We set up an order and atomicity block, so that the kernel code disables interrupts before going about the lock then enables it to allow the interrupt handler to perform its lock without causing a deadlock
```
Kernel Code:              Int Handler:
	Interrupt disable()
	Lock()                   Lock()      
	
	Shared = 7               X = shared
	
	Unlock()                 Unlock()
	Interrupt enable()
```

--- 
### Classic Motivation Example

Universal Correctness must be assured

Exclusion principle

#### Too much Milk

Problem is we ended up with 2 milks instead of 1: these occurred concurrently
```
Bob:
	Check fridge -> no milk
	Go to store
	Buy milk
	Arrive home; milk -> fridge
```
```
Alice:
	Check fridge -> no milk
	Go to store
	Buy milk
	Arrive home; milk -> fridge
```

#### Formalizing this example

- Shared variables
	- Check fridge
	- Put milk in fridge
- Safety Property
	- At most one person buys milk
- Liveness
	- Someone buys milk when needed

Solving this example with atomic instructions: leaving a note does not fix safety or liveness because of concurrency issues

This is a spinlock, so it'll continuously loop in the while loop setting the lock to 1 and returning the original lock value until r = 0, so that it'll break the spin --> Spin until you lock
```
// lock == 1

r = 1
while (r != 0) {
	r= exchange(&lock, 1)
}
```
*Spin Diagram with 4 states

#### Example with $eax and $ebx

Initial: x = y = 0
```
T1:                            T2:
	movl $1, (x)                   movl $1, (y)
	movl (y), $eax                 movl (x), $ebx
```

TSO Description Space
1. Essentially, stores are totally ordered, but there isn't a guarantee over load orderings - they can be reordered
2. TSO: Respects W-W and R-W dependencies

Memory Model
1. We are not promised sequential consistency/execution by our CPU, programming language, or compiler
2. Writing concurrent code
	1. Require proper concurrency
	2. Locks, semaphores, condition variables, barriers, in (very) rare cases c11 atomics
3. Instead x86 promises Total Store Order (TSO) with ambiguous semantics
	1. If there is not write, then we can reason it as sequential code (data race free)
	2. Data race: Possibility of >1 access to a shared mem location, with at least one of them being a write
		1. Alternatively: 2 concurrent memory accesses to the same location, at least one of which is a write

---
### Multiprocessors and Locking

Data Races:
1. Occur in our kernel (e.g. Multiple process read/write the same file)
2. Use a critical section to protect
	1. Locking primitive
	2. Acquire and release
3. Race conditions are often hard to reproduce and troubleshoot
	1. Think about: primitives accessed by multiple threads
	2. Better to overlock than underlock (correctness > perf)
	
Deadlock: 
1. Definition: Two or more processes are permanently block because they are each waiting for the other to release a resource
2. Conditions
	1. Mutual Exclusion: Resources must be non-sharable
	2. Hold and Wait: A thread holds at least one resource while waiting to acquire other resources held by other processes
	3. No Preemption: Resources cannot be forcibly taken away; they must be released voluntarily
	4. Circular Wait: Closed chain of threads exists, where each thread waits for a resource held by the next in the chain
3. Handling Strategies
	1. Prevention: Design the system to structurally violate one off the four necessary conditions (above)
	2. Avoidance: Dynamically grant resources only if doing so maintains a Safe State
	3. Detection and Recovery: Allow deadlock to occur, then detect it (Resource-Allocation Graph)
	4. Ignoring the Problem: Ostrich Algorithm (common approach because deadlocks are rare and complex to prevent/avoid)
4. May need to hold multiple locks to execute a task
5. xv6 uses a max of 2 locks

Concurrency Considerations
1. Whenever a lock is being held, delay the interrupts
2. Instruction and Memory Reordering
	1. Modern Compilers and processor support out of order execution
		1. Concurrency may expose a hazard due to reordering
		2. Solution: Tell compiler not to reorder (use c11 atomic primitives)

Volatile
1. Misunderstood
	1. Keyword assigned to c/c++ variables to tell compiler that variable may change unexpectedly
		1. Not a substitute for atomic operations
		2. Does not enforce memory consistency or fencing
	2. Use Case: For writing memory mapped device drivers - that's it

Spinlock
1. Definition: Waiting threads repeatedly check in a tight loop ("spin") until the lock becomes available
2. Efficient for locks that are held for extremely short durations, as it avoids the overhead of putting a thread to sleep (thus, no context switching)
3. Shortfalls: 
	1. Complex groups of functions that may call each other (allocproc, fork, userinit, ptable.lock)
	2. Problem: If every acquires lock, we have deadlock
	3. Solution: Enforce Locking Rules
		1. Kernel programmer must have awareness of what locks should be held
		2. Another solution: recursive locks (complex)
		3. Other exs: pipe read/write complexity
	
![[Spinlock in xv6.png]]
![[Acquire_lock.png]]
![[Release_lock.png]]

Sleeplocks (mutexes)
1. Sleep locks cause waiting threads to suspend their execution, yielding the CPU to other processes until the lock becomes available
2. Better for longer lock-hold times or when shared CPU cores must remain available for other tasks

Real World
1. Concurrency and parallel programming are active areas of research
2. Better to use primitive locks to form higher level constructs
	1. Abstract away locking
	2. xv6 does not do this
	3. Libraries like pthread provide higher level locking capability
3. Can implement atomic locks without hardware support, but expensive and complex
4. Another option: lock free DSAs
5. Many issues with performance related to cache lines, multiple processors, etc.

![[concurrency1.pdf]]

![[concurrency2.pdf]]

---
# Scheduler I
### Scheduling Motivation

Why do we need schedulers?
$$\mathrm{\begin{matrix}
\mathrm{Multiple\ resouce\ consumers} \\ \mathrm{Scarce\ set\ of\ resources\ shared}
\end{matrix}\left.\vphantom{\begin{matrix}a\\b\\c\end{matrix}}\right\}\ multiplexing}$$
Scheduler is one of the mechanisms in the OS enabling: 
1. Process isolation
2. Resource multiplexing
	1. Fairness
	2. Resource utilization
The goal of the scheduler is maximizing the amount of work we care about (measure of success)

---
### Scheduling Goals

Throughput scheduling -> Throughput is defined as the total amount of work, such as processes, tasks, or data, successfully completed or transferred by the system per unit of time
1. Orders of magnitude performance diff as a f (access pattern)
2. Elevator scheduling
	1. Implicit assumption? Actuation Delay
	2. Support for Declarative Requests?
3. Scheduling to minimize response time
4. Scheduling to maximize latency SLO attainment 
5. Scheduling to minimize cost

(Optimization Problem Setup)
![[Optimization_Chart.png|597]]

Latency Distribution Functions
1. Probability Distribution Function\
	1. $\mathrm{y = P(X=x)}$
2. Cumulative Distribution Function
	1. $\mathrm{y = P(X\leq x)}$
3. What is Tail Latency?
	1. ![[Tail_latency.png]]

Scheduler Scenario: *Imagine 2 different CPU scheduling scenarios*
1. One with long running jobs: fcfs?
2. One with very short running jobs: preemptive?

Scheduling Costs
1. Costs
	1. Context Switching
		1. Switching Computation
		2. Caching Costs
	2. Scheduler Time Complexity
	3. Predictability: Consider RTOS -> Real-Time Operation System
		1. Specialized, deterministic operating system designed for embedded systems to manage tasks with strict, time-sensitive deadlines
2. Benefits
	1. Better Resource Utilization
	2. More work on important tasks (priority allocation to higher value work)
	3. Stronger quality of service (QOS) properties

---
### Scheduling

Round Robin
1. Advantages
	1. Simple: assign fixed time unit per process
	2. Starvation-free (no priority)
2. Disadvantages
	1. Doesn't distinguish urgency/priority of processes
	2. Deadline-unaware
	3. Doesn't handle the disparity between throughput and latency

Linux Schedule (Modern High-Performance)
1. Motivating Observation: Processes that constantly use full CPU are likely lower priority than those that mostly sleep
	1. Idea: Reduce priority from processes that always consume full CPU
2. Weighted Fair Queuing (WFQ) - Share resource proportionally to process "weight"
	1. If 2 procs run, A with weight 2 and B weight 1, A will get 2x resources as B

Real-Time Scheduling
1. Divided into 2 groups
	1. Hard real-time: Complete critical tasks within guaranteed time 
	2. Soft real-time: Critical receive priority over less critical
2. Notes
	1. Hard real-time impractical with secondary storage or virtual memory
	2. Soft real-time has two requirements:
		1. Priority scheduling (urgency-aware)
		2. Low dispatch latency: hard and often not met

Scheduling Policies in Linux
1. SCHED_OTHER: Normal time/schedule sharing (default)
2. SCHED_IDLE: Very low prioritized processes
3. SCHED_BATCH: CPU intensive processes
4. SCHED_FIFO: First in, first out, real time processes
5. SCHED_RR: Round robin real time processes

Context Switch - $[$Context: The state of a process (or thread)$]$
1. 2 kinds of switches:
	1. From a process's kernel context to CPU scheduler context
	2. From the scheduler context to a process's kernel context
2. xv6 ***NEVER*** directly switches from user-space to user--space
	1. User-kernel transition (syscall or interrupt, etc.)
	2. Context switch to scheduler
	3. Context switch to new process's kernel thread
	4. Trap return
3. Context Switching - Kernel Context
	1. Every xv6 process has its own kernel context: kernel stack and register set
	2. Every CPU has its own scheduler thread
	3. Switching from one thread to another
		1. Save and load CPU registers
	
![[Context_Switch_abstract.png]]
![[Context_switch_breakdown.png]]

---
# Scheduler II

### Waiting

What does locking enforce? *Hint: lock and mutex are synonymous*
Locks = Mutual Exclusion

![[MutexLock.png]]

Data Race: 2 unordered accesses to the same location in memory, at least one of which is a write
1. Locks provide us with an ordering mechanism
2. Locks enable dynamic ordering
3. Locks reduce the space of possibilities

![[Race_cond.png]]

Conditional Variables
1. Allows a thread to be signaled when something of interest to that thread occurs
2. If we have a queue of items to work on:
	1. Mutex ensures consistency among the queue's internals
	2. If the queue is empty, how can we notify the consumer thread when a task is added to the queue
3. Simple implementation could be to continuously poll the queue to check for new tasks
4. Using a condition variable lets the consumer find that when the queue is empty it can just wait on the condition variable indicating that the queue has had something put into it. No polling needed

Waiting with Ordering
1. Main waiting primitive is a Condition Variable (CV)
	1. Allows a process to wait on a condition
	2. Traditional interface (must know): 
		1. wait(lock $*$lk); --sleeps until notified (may have spurious wakeups)
		2. signal(); --wakes up one waiter
		3. broadcast(); --wakes up all waiters
2. When waiting for the mutex lock, ***MUST*** use while loop
	1. Due to race conditions (not data races) -> occurs when multiple processes or threads access and modify shared data simultaneously
3. Sleep(chan, &lk):
	1. Automatically release the provided lock (lk)
	2. Changes the current process's state to SLEEPING
	3. Adds the process to a waiting list associated with a unique channel (chan)
	4. Invokes the scheduler (sched()) to give the CPU to another runnable
4. wakeup(chan):
	1. Iterates through all processes
	2. Finds any process that is SLEEPING on the specified channel (chan)
	3. Changes their state to RUNNABLE

Signal Ordering
![[Signal_process.png]]

Waiting Mechanism
1. What happens on the CPU when a process waits for another?
	1. The CPU switches to running another process or it sleeps
2. What needs to be saved when sleeping?
	1. User address space - saved in proc's pagetable
	2. User context (regs) - saved on call to kernel
	3. Kernel address space
	4. Kernel context (regs) - needs to be saved explicitly
3. xv6 Switch Function - need to only save/restore callee saved registers
	1. Voluntary preemption mechanism (cooperative)
	2. Does the trap handler need to only save/restore callee saved registers
		1. Trap handler runs on an interrupt, not cooperative
		2. Caller did not save anything before ending up in the handler
	3. Step-by-Step Process
		1. Takes in 2 context structures
		2. Pushes all callee saved registers to the first
		3. Swaps to the new stack (From context structure)
		4. Pops all callee saved registers from the new stack
			1. Note: New stack's ret addr
		5. Returns (using the new stack's ret addr)
4. Where does a process go when it waits?
	1. Traditionally, use a wait list:
		1. Once process sleeps, put it on a wait list
		2. Can wake up processes from that waitlist when needed
	2. Develop a smaller lock - Better version of spinlock
		1. Sleep when lock is currently held by other
		2. Wake up a sleeper on lock release (sleeplock())

---
### Semantics

Weak Ordering Semantics
1. Weak Ordering (Relaxed Consistency)
	1. Hardware, compiler can reorder reads and writes as long as the result is correct from the executing thread's perspective
	2. Weak ordering does ***NOT*** concern itself with correctness across executing threads
	3. Stores from one thread can appear out of order to another thread
	4. Thread might see another thread's writes to different variables at different times
	5. Without explicit synchronization, almost no ordering guarantees exist
2. Lock acquire/release - mechanism for partial order
	1. Acquire -> All subsequent reads/writes in the curr thread happen ***after***
	2. Release -> All preceding reads/writes in the curr thread happen ***before***

Ordering Semantics
1. Unordered: $\mathrm{Rt_{1}, Rt_{2},Wt_{1},Wt_{2}}$
	1. Many possible interleavings
2. Partially Ordered (w/ locks)
	1. $\mathrm{Rt_{1}, Wt_{1},Rt_{2},Wt_{2}}$
	2. $\mathrm{Rt_{2}, Wt_{2},Rt_{1},Wt_{1}}$
3. Fully Ordered
	1. Exactly one globally visible sequence

---
### Clone

Similar to fork(); however, instead of creating a process, it creates a thread
1. The thread shares thee address space with its parent
2. Has a different stack from the parent

Copying Parent Stack for New Thread
1. clone(void $*$stack, int stack_size)
2. Clone must return gracefully if the passed in arguments are invalid (return -1)
	1. Think about edge cases
3. Traverse the stack (ref to backtrace - Lab1)
![[stack_visual.png]]

Thread Group
1. Threads within the same thread group share the same shared resources
	1. VA space, File Descriptors, Current Working Directory
2. Change to a shared resource in a thread group must be reflected in all treads
3. "The Thread Group Owner" is always the first process that called clone()
	1. If the thread group owner terminates before the other threads, this behavior is undefined
4. ***BRAINSTORM***: Thread Group Implementataion
	1. Change to a shared resource in a thread group must be reflected in all threads
		1. Thread 1 changes the working directory: all threads working directory should change
	2. Existing functions/syscalls may change shared variables. Ensure they work with your implementation
	3. Ensure there are no data races
5. waitpid()
	1. Similar to wait()
	2. Should only be able to call waitpid() on children
	3. pg_flt error if we were to prematurely free the VM of a thread
6. Don't go overboard with edge cases
	1. If a thread exits before its children, the behavior of those children (threads spawned by this thread) is undefined
	2. Calling fork or exec on a thread is undefined

**Project 3: Keep in mind the EBP of the thread stack is still linked to the parent address space stack from copy; Instruction segments are shared so we do not need to worry about that**

![[scheduler.pdf]]

![[scheduler2.pdf]]

---
# User and Kernel - Threading

![[threads(user_kernel).pdf]]

---

# User and Kernel Threads
### Why Threading?

Benefits: 
1. Parallelism with shared memory resources
2. An Abstraction (!) to share a resource (e.g. address space)
	1. A way to multi-process/manage concurrency with shared memory resources
3. Organization, processing asynchronous events (modular fashion)
	1. E.g. UI Thread + Background process
	2. Simultaneity, abstraction of concurrency/simultaneity of action
4. Responsiveness: Especially for interactive applications
	1. Threads give us the abstraction of concurrency
	2. Mechanism of Concurrency
5. Benefits other than performance?
	1. Performance with multi-processing
	2. Design: threading vs multi-processing vs event-based
		1. Achieve concurrency with single thread, core, and process
			1. Event loop for which you define handlers for types of event
	3. Reduce correctness violations

Challenges:
1. Synchronization
	1. Data Race -> 2 accesses to mem loc. with at least one of them being a write
	2. Primitives
		1. Waiting
		2. Spinlocks
		3. Mutexes
		4. Conditional Variables

Overview:
1. Definition: Two independent entities, doing computation, sharing memory
2. Abstraction of Concurrency
	1. Ability to seamlessly execute independent threads of execution at the same time
3. Single core multi-threading?
	1. Interactivity and interactive applications
4. Threads do have shared memory locations, while processes (assumed) to have their own individual virtual address space
5. Takeaway: Convenient abstraction of concurrency

Mechanisms of Concurrency: 
1. Threads
	1. Disruptive -> What if we break this isolation guarantee, deliberately
	2. Key property: Shared memory resources, by design
2. Multi-processing
	1. Processes that share compute resources, but not memory resources
	2. Key property guaranteed: memory space isolation
3. Event-based systems 
	1. Single thread, single process
	2. Voluntarily preemptive mechanism 

Design + Implementation
1. One-to-One (1:1) - Kernel Threading
	1. ![[kernel_threading.png]]
	2. Improved concurrency
		1. Multi-core system
	3. Can run in parallel on multiprocessor
	4. Additional overhead to create kernel thread for every user thread
		1. Increased resource consumption
			1. Time complexity of scheduler (O(n) -> n is num of user threads)
			2. Space complexity to store mem structs (O(n) -> n is num of user threads = num of kernel threads)
2. Many-to-one (n:1) - User Space Threading
	1. ![[Pasted image 20260309032431.png]]
		1. One kernel thread to multiplex to all the user threads
	2. Simple, efficient
	3. True concurrency is difficult (ex: one thread blocks all)
		1. Deadlock
	4. Only one thread can access kernel at a time, so no parallelism on multiprocessors
		1. All of these designs -> **Scheduling at kernel at the granularity of kernel thread**
		2. O(1) because only one kernel thread
3. Many to many (Aka M:N, AKA Hybrid Threading)
	1. M = User space threads; N = Kernel space threads
	2. Typically N = num of cores
	3. Can multiplex across a bunch of semantic irrelevant user space threads
	4. One kernel won't block the progress of other kernel threads -> sched moves to the next proc
	5. Hybrid vs User-Space
		1. Advantages
			1. User-space threads can run in parallel
			2. Fewer context switches
			3. Lighter weight user-space threads (small user space thread cost)
		2. Disadvantages
			1. Still subject to kernel thread stalls causing user space thread blocking
			2. Still not cooperative use of CPU

User-Space Threading Library
1. How does a user-space threading library work? (sched deck)
	1. The same as how xv6 manages "kernel" threads
		1. swtch - does context switch
		2. Scheduler chooses what to run
		3. Concurrency primitives are built from atomics and queues (can build in user-space)
		4. Context switch could happen in user space
2. Why a user-space threading library makes sense:
	1. Threading mechanism is designed with an implicit assumption of cooperation between units of execution
	2. Implication: Cooperative scheduler is sufficient
	3. User-space cooperative scheduler can switch between user-space threads without relying on preemption mechanisms available in/to the kernel
	4. Threads are cooperative
	5. Synchronization primitives can be built with user-space atomics and concurrency primitives
	6. No privileged instructions needed from the kernel
3. Thread context, stacks, register state available in user space
4. Can switch stacks in user space

Concurrency vs Parallelism
1. ![[Concurrency vs Parallelism.png]]

Kernel vs User-Space Threading
1. Kernel: Sched -> which proc next (many procs)
	1. Parallelism
	2. Preemption possible
	3. More info available to the kernel
	4. Ability to control resource utilization
	5. Thread-aware process sched
2. User: Sched -> which thread next  (one proc)
	1. Semantically-aware scheduling (application awareness)
		1. User space understands what this application is doing; semantic dependency
	2. Context switching overhead
		1. Much less (within user space, no context switching)
	3. Cache locality
	4. Lighter weight than kernel threading
	5. Overhead of thread creation
		1. More overhead in user-space creation, none in kernel

Modern Threading Libraries
1. Mostly kernel threading (pthreads)
2. However, many operations in user-space:
	1. "futex" syscall allow mostly user-space concurrency primitive construction
		1. Essentially kernel sleep/wakeup mechanism
		2. Allows user-space to do locking, but ask kernel for sleep/wakeup
3. Trade-off of user/kernel efficiency
	1. Kernel manages IO sleeping/process sleeping/scheduling
	2. User-space manages most concurrency primitives (lock, cv, semaphore)
4. In terms of XV6
	1. Kernel stack: Each proc has own kernel stack
	2. User threads: None

Creation of Thread $\mathrm{*}$Lab3
1. Add clone() syscall -> Create new proc that shares pgdir
2. Add user API for creating threads
3. Locking primitives

---


![[threads(user_kernel).pdf]]