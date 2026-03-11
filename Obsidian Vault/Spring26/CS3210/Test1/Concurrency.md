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