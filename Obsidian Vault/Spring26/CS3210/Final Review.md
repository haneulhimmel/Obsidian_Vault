### x86: Real Mode
![[Protection Scheme.png]]

### x86 Architecture and Boot: Food for thought
1. Segmentation not really used today (mostly disabled on x86_64) in favor of paging - why?
	1. Because segmentation requires contiguous memory (more fragmentation) and each segment requires permission vs full pages having permissions
	2. Paging solves fragmentation as it chops everything into pages (typically 4KB), so any free page works for any virtual page
2. Would we ever want segmentation over paging? 
	1. Determinism [Concept in which a given input, the output will always be the same through the same sequence of states] as a result of overhead (something more simpler and predictable)
	2. Essentially a deterministic system requires perfect predictability and control over the memory access times and protection
		1. Segmentation does not have to rely on the TLB (misses would be time-consuming and unpredictable)
		2. Segment has the permissions, so it only takes one step to check the info of the entire segment
		3. All segments of a real-time process is a resident in physical memory
3. Why does x86 still boot in 16-bit real mode? 
	1. Backwards compatibility -> Essentially since all of the older systems have their firmware (BIOS Rom, USB bootloaders, Hard Drive boot sectors) written in 16-bit, if we were to change it now, then all of those systems would be rendered
	2. Essentially domino effect of having to change all sorts of firmware and whatnot

### Isolation: Food for Thought
1. Tradeoffs: 
	1. ![[Pasted image 20260425201400.png | 400]]
2. If isolation isn't perfectly enforced, which kernel assumptions fall apart?
	1. You cannot guarantee integrity (you can't guarantee that something has not been tampered with)
3. Where would you draw the line between "too isolated to be useful" and "not isolated enough"?
	1. Depends on the application of the systems - Talked about this with Monolithic kernel vs Microkernel
4. What are the tradeoffs of having hardware-enforced versus software-enforce isolation?
	1. Flexible, performance, programmability, and rigidity

### Kernel Organization and APIs: Food for Thought
1. Monolithic versus microkernel tradeoffs given an application
	1. Performance
	2. Fault isolation
	3. Modularity
	4. Safety -> Microkernel; Performance -> Monolithic kernel
2. If you had to shrink the number of syscalls from hundreds to tens, what would be your selection criteria?
	1. Basically breaking down syscalls into primitive calls that could be used to compose them, hence deleting the cascaded syscall
	2. If everything is a file, it can brought down to the base: read, write, open, etc.
	3. Dependent on usability, performance consideration, or whatever tradeoff for the intended application

### Virtual Memory: Food for Thought
1. Single-level versus multi-level page tables
2. Why would we want smaller or larger pages?
	1. Smaller processes with smaller pages so we can avoid page walks
	2. Less memory overhead with larger pages ()
	3. Smaller pages give more granular control (increased efficiency when assigning RAM)
		1. E.g. if every page is 4MB and a process only needs 4KB, the extra space is wasted
	4. Larger pages reduce the overhead of managing pages
		1. E.g. system with 128GB of RAM has more pages to keep track of versus a system with 4GB of RAM
2. What does the TLB really buy you, and when does it stop helping?
	1. For example: a workload has a 95% TLB miss rate - where is time going?
	2. Working set is larger than what the TLB can store, so everything is essentially evicted when you return to it

### Copy-on-write: Food for Thought
1. What are the pros/cons of eager copy versus copy-on-write?
	1. When does copy-on-write stop being a "win"
	2. If you do a ton of writes, it will lead to you have to keeping copying pages
2. What happens if the kernel runs out of memory mid-CoW copy?
	1. One of main critiques about CoW
	2. It is not promised that we will have enough; the fork could succeed but it could require twice the memory but it was done in a lazy manner
3. Cases to consider:
	1. How do we know when we need to copy a page?
	2. How do we know when a page can be freed?
	3. What about child/grandchildren?
	4. How do we handle out-of-memory instances?
	5. Do we clean up all resources all the time?
4. Could copy-on-write exist outside of fork() ?
	1. This tackles the question if CoW is tied specifically to fork()
	2. as

### Lazy Allocation, Zero-paging, and swapping: Food for Thought
1. When does lazy allocation stop being a win?
	1. Risk over commitment of memory
	2. If you want predictable, low latency -> this is not a win
2. Clock algorithm variants (exam 1 practice)
	1. Tradeoffs of more/less complex algorithms

### Interrupts: Food for Thought
1. Interrupt-driven vs polling - when is one preferred over the other?
	1. See Exam 1 question
	2. Ex for polling: If the terminal is waiting for an input, it can just poll; A clicker being clicked continuously -> Paying the cost of constantly being interrupted
	3. Ex for interrupt: A clicker being clicked once is interrupt
2. Masking interrupts vs letting them preempt - what are the tradeoffs?
	1. Masking interrupts allow the OS to temporarily disable specific interrupts, preventing trigger during time-sensitive, critical sections of code (maintains data integrity and system stability)
		1. Cons: Can lead to missed events (data arriving at serial port)
		2. Re-entrant interrupt handlers that do not properly handle masking can cause stack overflows

### Concurrency: Food for Thought
1. Pros/cons of fine-grained vs coarse-grained locking
	1. Fine-grained
		1. Usage of multiple, smaller locks to protect individual data elements rather than entire structures
		2. Instead of a bigger lock (coarse-grained), allows parallelism, minimizes contention, and improves multiprocessor scalability by allowing multiple threads to access different parts of a data structure simultaneously
		3. More memory overhead and CPU time required
	2. Coarse-grained
		1. Uses larger scope locks to protect a bigger quantity of data to simplify synchronization and reduce overhead (less locks to manage; therefore, less memory overhead and decreased CPU time spent acquiring/releasing locks)
		2. Easier to implement; less prone to deadlocks
		3. Reduces parallelism as unrelated tasks will have to wait for the same lock since the entire data structure is locked
2. When should you use a spinlock versus a sleep lock?
	1. Spinlock
		1. Poll continuously (spinning) - busy waiting loops
		2. Better for shorter critical sections (low latency)
		3. Burn CPU cycles while waiting (potentially wasting resources)
		4. Can be used for interrupts
	2. Sleeplock
		1. Context switch (put current process to sleep)
		2. Better for longer critical sections (higher latency due to wakeup)
		3. Releases the CPU for other tasks
		4. Cannot be used for interrupts
	3. Pthread_mutex_lock is preferred in modern architecture because they spin for a short time before falling back to sleep
3. Correctness under DRF0, TSO, and compiler reorderings
	1. When we do have correctness violations?
		1. General: The program produces a result that is not a potential interleaving or layer of the operations of each thread, assuming the program is DRF0 (Data race free)
		2. DRF0
			1. Cannot guarantee sequential consistency if the program does have a data race
		3. TSO
			1. Even with DRF0 code, hardware can still reorder certain operations
	2. How do we prevent correctness violations?
		1. TSO
			1. Use atomic operations; avoid unsynchronized shared accesses
		2. Compiler reorderings
			1. If the code is DRF0, the compiler and hardware (via DRF0 + SC) to guarantee sequential consistency - except if you rely on TSO-specific behavior that is not SC
			2. Use atomic operations
	3. What does TSO promise? How does that relate to what the compiler can do afterwards?
		1.  Stores (writes) are totally ordered, but there isn't a guarantee over load (read) orderings
		2. Respects W-W and R-W dependencies but not W-R
		3. The compiler can reorder even more aggressively than TSO (says when the instruction executes) but the compiler can rearrange it, breaking TSO expectations
4. How do we detect deadlocks, and how do we break/avoid them?
	1. Enforce locking rules: programmer must know what locks should be held
	2. Disable interrupts to avoid deadlocks -> eliminates the possibility of preemption between a locker holder and a lock waiter
		1. Disabling interrupts on a uniprocessor prevents deadlocks that arise when an interrupt handler attempts to acquire a lock already held by the interrupted thread.

### OS and Networking: Food for Thought
1. UDP vs TCP - Which apps want which?
	1. TCP is used by applications that need reliable, in-order delivery—like web browsing (HTTP), email (SMTP), file transfers (FTP/SCP), SSH, and databases. These apps cannot tolerate lost or reordered data because a missing byte could corrupt a file or break a webpage. UDP is used by applications that prioritize low latency over reliability—like VoIP, video calls (Zoom), live streaming, online gaming (FPS), and DNS. These apps prefer occasional packet loss (which causes a glitch) over retransmission delays (which freeze the call or game). The rule: If missing data is worse than waiting, use TCP. If waiting is worse than missing data, use UDP.
2. Layering: what do we gain, and what performance do we pay?
	1. What we gain: Modularity, reuse, and interoperability. Each layer (physical, link, network, transport, application) can be developed and optimized independently. You can swap Ethernet for WiFi without changing TCP or HTTP. The same TCP implementation serves web, email, and SSH. This abstraction makes complex systems manageable.
	2. What we pay: Performance overhead. Each layer adds headers (e.g., TCP + IP + Ethernet = ~58 bytes per packet) and processing costs (checksums, buffer copies, context switching). For large transfers, this overhead is negligible. For tiny packets (e.g., IoT sensors, gaming), header overhead can exceed the actual data—this is called the header tax of layering.
3. At what point does reliability cost more than it's worth?
	1. Reliability costs more than it's worth when the delay or resource cost of ensuring delivery exceeds the value of the data being protected. For real-time applications like live video or voice calls, retransmitting a lost packet arrives too late to be useful—so retransmission is worse than just losing the packet. For sensor networks sending millions of readings, losing 1% of samples is fine; a reliability protocol that doubles latency or battery drain is not worth it. For file transfers or bank transactions, reliability is always worth the cost because a single lost byte corrupts the file or loses money. The breakeven point is when the application's utility curve has timeliness as steep as or steeper than accuracy—once data becomes stale faster than it can be retransmitted, reliability is a net loss.

### File Systems: Food for Thought
1. HDD vs. SSD - when does each win?
	1. HDD are cheaper; however, SSD are faster overall 
2. Small blocks vs large blocks
	1. Memory paging
	2. Small blocks are better for smaller, known data
	3. Large blocks are better for data streams that are larger and more inconsistent
3. With ext4: journaling vs ordered vs writeback tradeoffs
	1. Writeback offers no ordering guarantees
	2. Journaling writes out the data and metadata
4. Journaling vs shadowing vs no crash protection - what fits which workload?
	1. Journaling fits general-purpose workloads (servers, desktops) where you need fast recovery and moderate write overhead. Best for metadata-heavy workloads like creating/deleting many files.
	2. Shadowing fits small, critical updates (database pages, file replacements) where atomicity is essential and data is small. Not for primary FS because it doubles space and copies entire files.
	3. No crash protection fits scratch/temp data (e.g., /tmp), streaming workloads that can recompute data, or use cases where crash = just restart. Fastest but unsafe.
5. Buffer cache sizing and eviction - when might we not want to LRU (least recently used?
	1. Not so frequently used and critical blocks
	2. Do not use LRU when you have critical metadata or pinned blocks that must stay in cache regardless of access frequency. Examples: superblock, root directory inode, journal superblock. LRU would evict them if "not so frequently used," causing massive performance penalties when they're needed again. Also avoid LRU for sequential scans (e.g., full file read) because LRU caches useless blocks, evicting hot ones—use MRU (Most Recently Used) or 2Q (Two Queue) instead. For critical but rare blocks, use explicit pinning + a separate retention policy.
6. Where do locks go in the FS stack, and what's the cost of getting it wrong
	1. Locks belong at every shared layer:
		1. Inode table (protect inode metadata)
		2. Block cache (protect buffer state)
		3. Directory cache (protect name lookups)
		4. Journal/log (protect transaction state)
		5. File descriptor table (per-process open files)

### Distributed Systems: Food for Thought
1. Higher f (more failures tolerated) - what does it cost in latency and nodes?
	1. Nodes: Crash-tolerant consensus (Paxos/Raft) requires 2f+1 nodes. Byzantine (malicious) requires 3f+1.
	2. Latency: Larger quorums (f+1 for crash, 2f+1 for Byzantine) mean waiting for more acks. Also, more message rounds may be needed (e.g., view changes). Timeouts increase to avoid false failure detection.
2. Paxos vs Raft vs timeout-consensus tradeoffs
	1. Raft is simpler than Paxos (easier to implement) - Paxos is better with consensus
	2. **Raft:** Simpler to implement and understand (leader‑based, strong safety). Tradeoff: higher message overhead during leader elections.
	3. **Paxos:** More flexible and can be faster in some configurations, but notoriously subtle to get right.
	4. **Timeout tradeoffs:** Short timeout → fast failover but risk of unnecessary elections (lower throughput). Long timeout → stable leader but slow recovery after actual failure.
3. CAP: When would you pick AP over CP? CP over AP
	1. Pick AP when the system must remain available during a partition and stale reads are okay. Examples: social feeds, DNS, shopping carts.
	2. Pick CP when correctness is critical and unavailability is preferable to inconsistency. Examples: banking, stock trading, distributed locks, file system metadata.
4. Synchronous vs asynchronous networks - what changes about what's possible?
	1. Synchronous: Bounded message delay and clock drift. Enables deterministic failure detection and consensus with fewer nodes (e.g., f < n/2 for crash). Rare in real world.
	2. Asynchronous: No bounds on delay or drift. Cannot reliably distinguish dead from slow. FLP theorem says no deterministic consensus algorithm guarantees progress. Real systems must use timeouts and randomisation (e.g., Paxos/Raft).

