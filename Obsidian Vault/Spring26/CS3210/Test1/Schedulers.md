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
