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
		4. Conditional Varaibles

Overview:
1. Definition: Two independent entities, doing computation, sharing memory
2. Abstraction of Concurrency
	1. Ability to seamlessly execute independent threads of execution at the same time
3. Single core multi-threading?
	1. Interactivity and interactive applications
4. Threads do have shared memory locations, while processes (assumed) to have their own individual virtual address space
5. Takeaway: Convenient abstraction of concurrency

Mechanisms of Concurrency
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
	1. Ssemantically-aware scheudling (applicatio awareness)
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
		1. Essentilly kernel sleep/wakeup mechanism
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