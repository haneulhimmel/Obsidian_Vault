# x86 Architecture and Boot Process
[[x86_arch.pdf]]

# Isolation
[[os_isolation.pdf]]
### Available Isolation Mechanisms
1. Hardware Isolation

# Kernel Organization and APIs
### UNIX system call's original goal:
1. Concatenate programs together using the shell in a terminal on a shared mainframe

# Virtual Memory
### Three things at once: Isolation, Multiplexing, Protection
### Paging
### TLB Caching
### VA translation
### Single-Level Pages in x86
1. There's no hard rule that says we must use a two-level hierarchy
### MMU and TLB

### Copy-on-Write
1. Permission bits
	1. P (Present): Page is in physical memory
	2. U (User): If set, page can be accessed by user processes
	3. W (Writable): If not set, page is Read-Only -> The key for CoW
2. Permissions can be separated into two types
	1. Logical -> Is it legal to access this memory?
	2. Physical -> Should the CPU give me a trap for accessing this page?

# Lazy Allocation, Zero-paging, and swapping: high level
1. Clock algorithm

# Interrupts
### Types of interrupts
1. Maskable
	1. Ignored when *IF* bit in EFLAGS register is  0
		1. EFLAGS represent the status register that contains the current state of the x86 CPU
	2. Enable with *sti* (set interrupt) instruction
	3. Disable with *cli* (clear interrupt) instruction
2. Nonmaskable
	1. Can never be ignored (e.g. power failure, memory corruption error)
	2. In xv6, if we get an NMI the OS dies
	3. In x86, vector 2 prevents other interrupts from executing
### How do syscalls and traps work in xv6?
1. Some interrupts (NMI) cannot be masked at all
2. Masking prevents self-deadlock but delays other events
### Interrupts vs polling
1. Core design choice

# Concurrency
### Building a Lock
### Spinlock
### Deadlock
### Race Conditions

### Total Store Ordering (TSO)
1. Idea: Stores (writes) are totally ordered, but there isn't a guarantee over load (read) orderings
2. Respects W-W and R-W dependencies but not W-R (at hardware level)
	1. ![[Pasted image 20260426165251.png | 400]]
	2. All of these are possible: because of the idea of TSO

### Memory Model Summary
1. Naturally assume "Sequential consistency" when programming
	1. Each statement executes in order
2. Wrong assumption: the CPU does not promise this
	1. x86 promises TSO with ambiguous semantics
3. If you write data race free code, then you are guaranteed your code will behave in a sequentially consistent manner
	1. Utilize locks to enable data race free code

# Multiprocessors and Locking
### Deadlock
1. Definition: Two processes/threads cannot make progress because they are stuck waiting on the other to take some action
2. Conditions: All of which must be true
	1. Mutual exclusion: Resource can only be held by one process at a time
	2. Hold and wait: Request more than one resource while another resource is currently held
	3. No preemption: A resource can be taken away involuntarily
	4. Circular Wait: e.g. process A is waiting for a resource that process B holds, and process B is waiting for a resource that processes A holds
		1. Problem occurs when: A, B, B, A
		2. No problem with: A, B, A, B

# OS and Networking: [[Exam2Lec.pdf#page=103 | Ref.]]
### Abstraction to OS
1. Network Interface Card (NIC) to NIC -> Direct point to point communication
2. There is a medium between (server or something distribution) between these NIC points
3. Orthogonality
	1. Relatively small set of primitive constructs that can be combined in a relatively small number of ways to build
4. Composability
	1. Deals with inter-relationship of components (combine and assemble components to satisfy specific user requirements)
5. Internet (abstract provided to OS users/apps)
	1. Communication starts with frames from NIC -> to next NIC with routers and switches in between (the user abstracts the concept to them simply directly communicating with the network)
	2. Point-to-point but higher level (application to application)

### Faults
1. Network bits are not guaranteed to arrive and even if it does it is not guaranteed to not have errors
2. Within the network system, the switches, routers, and even distance can lead to potential package misses or just error-ed data

### Gap between the network and OS provided abstractions
1. As the initial data/payload propagates to through the protocol layers, it adds layers upon that data
2. OSI Layers Mnemonic -> Typically these 7 layers are grouped in sectors; hence differentiation is often discarded
	1. All: Application
	2. People: Presentation
	3. Seem: Session
	4. To: Transport (L4)
	5. Need: Networking (L3)
	6. Data: Datalink (L2)
	7. Processing: Physical (L1)
3. Above session and transport, those layers are within the user space so we typically do not worry about them: [[Exam2Lec.pdf#page=117| ref.]]
4. Via Encapsulation (each layer contains nested info)
5. NIC -> Frames
6. Transport/Network -> Packets

### Internet Layers
1. Internet Layer (L3)
	1. Each node of the distributed system contains a routing table and are responsible for propagating the source IP to the destination IP by rewritten either the source IP or the destination IP in the L3 header
2. Transport Layer (L4)
	1. TCP Abstractions
		1. Stream interface (data comes in a stream, not packets): Just want to deal with the byte stream and not the underlying layers
			1. Application should not care about this; OS should handle it
		2. Reliable (data not loss)
		3. Point-to-point (host communication)
	2. How is the stream interface provided?
		1. We coalesce very small writes into a larger Ethernet frame
		2. For large writes, we want to break it up into the standard Ethernet size
		3. So we use multiple packets per write, or put multiple writes in a packet
	3. Addressing Failure Modalities
		1. Sequence Numbers: Addresses out of order packages
		2. Checksum: data received without errors; duplicates
		3. Timeouts or re-transmission: Correct for dropped package
			1. Time is hard to set for a distributed system: there is no ground truth - we do not know how long to wait for the package

# File Systems: [[Exam2Lec.pdf#page=134|Part I]] & [[Exam2Lec.pdf#page=184|Part II]]
### General
1. What is it? Why do we need a file system?
	1. Persistent vs ephemeral state
2. How does it relate to a disk?
	1. We do not need a disk for the file system to be useful
	2. Primary way FS is used are on disks
3. OS should handle the scare resources in a way that the application developer does not need to worry about it
4. Buffer cache: cashing disk blocks in RAM -> writing/reading are time-intensive

### File Descriptor
1. Integer index into a per-process `ofile` table; each entry points to a file struct

### File Struct
1. Represents an open file stores reference count, offset, and pointer to its inode

### Inode
1. Overhead storing the metadata
2. Indirect block pointer -> holds pointers to more blocks
	1. Design with 128 indirect block, 12 direct block:
		1. 12 * 512 + 128 * 512 = 6K + 64K => 70K
		2. Waste if we only end up using 2 of the 128 addr. of the indirect block since it is still allocated in space
3. Every file and directory has exactly one inode
4. On-disk metadata

### Directory Structure
1. Why do we use an array of dirents (directory entries)? Why not a binary tree?
	1. xv6 has 13 dirents within the directory structure
	2. Algorithm complexity that result in more overhead; most systems just use the simple directory array -> It's typically not a bottleneck
2. ![[Pasted image 20260428032841.png]]
	1. BLOCK_SIZE = 512 bytes
	2. 15 $\mathrm{\ge}$ 12 so it is an indirect block 
3. Users cannot write to it directly
# Ordering and Atomicity: [[Exam2Lec.pdf#page=221 | ref.]]
### General
1. With respect to the FS: What happens when my machine crashes, shuts down, or stops unexpectedly?
	1. You are not guaranteed to have data written or saved to disk (even with synchronous blocking I/O ops like read/write)

### Timeline (Crashes and Unexpected Stops)
1. First Example
	1. Timeline
		1. Write() -> For this the inode has attributes (inum, size, datablocks); to actually write to the datablock, a copy must be made on the disk then the connection is severed before the pointer is set to the new block created
		2. Crash
		3. Recovery
		4. Read()
	2. Best Case Scenario
		1. The writes on blocks x,y,z are mutated and end up on the secondary storage; where we can read from them with the newly mutated data
	3. Worst Case Scenario
		1. Copy and allocate the new block but the pointers are not set to the new block, so it is like a memory leak (partial state persistence scenarios)
		2. Update the inode but not the new data block; Also new blocks have been copied but not written to them (pointers may point to these new blocks)
			1. Violates correctness and isolation 
2. Second Example
	1. Timeline
		1. Write(fd1) - {db: 7, 8, 9}
		2. Write(fd2) - {db: 2}
		3. Crash
	2. Best Case Scenario
		1. The writes on both file descriptors are mutated and persist to disks; where we can read from them with the newly mutated data
	3. Worst Case Scenario
		1. Writes to datablocks 7,8,9 from fd1 partially succeed (some fail to persist or mapping); Write to datablock 2 succeeds
			1. Principle of sequential consistency is not guaranteed by lower levels of the hardware
3. Third Example: Cardinality of Reordering [[Exam2Lec.pdf#page=230 | ref.]]
	1. Set N = {7, 77, 52}
	2. Set K = {5, 6, 4}
	3. The permutation of the possible ordering of these sets is (N + K)!
	4. However with flushing -> N! * K! < (N + K)!
4. Motivating Examples
	1. What happens if mkdir is synced to disk after open?
		1. Directory Block -> Array of Dirents (filename, inum {pointer to struct that carries metadata for y on disk - inode}, etc.) -> inode (inum, size, dbs) -> datablocks
			1. All of this on disk
			2. Open = 1 (inserting dirent) + 2 (creating the inode and address pointer to datablocks relative to the file)
		2. End up with file that does not belong to any dir (b/c mkdir may not persist)
	2. What happens if metadata is corrupted for y?
	3. What happens if direntry is written before y's inode/data
5. To guarantee from user space that a write occurs and persists to disk before a subsequent write; we need an ordering primitive
	1. Disk provides a flush (ordering primitive) - semantic is everything that happens before flush will persist to disk
	2. Happens-before relationship
	3. Establish total order if we flush after every write

### Shadowing
1. Only the flip of the shadow bit must be atomic as crashes or interrupts during this could result in the system pointing partially to the old data and partially to the new data, corrupting the file
	1. It cannot be partial because it's a single boolean decision; shadowing is atomic
2. Copying data doesn't need to be  -> shadowblock is inactive; so crashes leave the original intact
3. Update shadowblock -> same concept as above; original is still active
4. Cons
	1. Memory expensive [[Exam2Lec.pdf#page250 | ref.]]
		1. Ensure that copy data and update persist to the disk before the consecutive writes (insert a flush in between the writes for shadowing - {3, 6})
	2. Shadow as a separate bit requires own disk block
		1. Heavy space
5. Does it make sense to use shadowing as our primary method of atomicity in the FS?
	1. Why or why not?
		1. No b.c of space overhead (at least 2 x space because of current + shadow), metadata complexity (shadow bit/pointer for each inode), and no partial updates
6. What alt. can we create?
	1. Copy-on-write
	2. Journaling

### Logging
Journaling -> Does not persist to disk immediately
1. Logging -> Goal: writes to disk are all or nothing (atomic) operations
	1. Does not necessarily mean "all at once" just means that its there or not (data)
		1. Need to ensure the system crash does not break the filesystem
	2. During the log process, it is possible for commits to be missing (crashes can happen at any time)
	3. Uncommitted cases are possible
		1. We should not treat those entries as valid
	4. Preserve a prefix semantic of the log -> as soon as we reach an entry with its commit invalid, we are to going to disregard everything that happens after that invalid entry
		1. We lost writes but crash consistency is to ensure that the file system on disk in a sane state (not self-inconsistent) through the prefix logging
	5. Example (Committed): [[Exam2Lec.pdf#page254 | Prob. 1]]
		1. If I read block 7, where do I get my data from? Log or Data Blocks?
			1. Log -> "Hello World" as the prefix semantic since commit 1 for the first entry was valid it supersedes the metadata/datablock
				1. An invalid entry preceding a commit entry would render that chain of entries invalid (trick question on exam)
	6. Example (Uncommitted): [[Exam2Lec.pdf#page=255| Prob. 2]]
		1. If I read block 6, where do I get my data from? Log or data blocks?
			1. Datablock since that entry on the log was uncommitted and invalid
			2. Bottom line: if an entry is uncommitted, we consider that the data invalid (Happens-before relation with commit and Entry mutation)
				1. ![[log.png]]

### Commit Mechanisms
1. Commit mechanism gives us the atomicity; not the log itself
		1. Commit mechanism 1 gives us the assurance of happens-before relationship of entries within the log
		2. Commit mechanism 2 -> Atomic "commit" -> checksum
			1. An entry is only committed if all entries before it are committed
			2. If checksum doesn't match - not committed (invalid entry)
			3. We don't care if a crash happens, if those entries have been fully persisted yet -> because at recovery time, we will computer a checksum on the entry and if that fails we can invalidate the entry 
				1. This gives us atomicity - design space tradeoff : reduction in write latency for an increase in computational cost and complexity
			4. Any order -> NOT spatial but temporal
2. Can we detect the entry was written erroneously (mistakenly) but the commit is valid?
	1. No because the commit says nothing about the validity (or errors) of the entry

### Logging and Recovery
1. Log merge -> overwrite the "normal" with log version (if invalid entry is encountered; anything afterwards is also invalid so break) -> Clear log
2. What happens if we crash in the middle of a log merge? [[Exam2Lec.pdf#page266 | ref.]]
	1. Log merge consists of multiple disk I/O operations that are not atomic
	2. Are we immune to that? No
3. xv6 uses a synchronous, blocking write-ahead log where all syscalls funnel through a single commit path protected by log.xv6 uses a synchronous, blocking write-ahead log where all syscalls funnel through a single commit path protected by log.lock. It batches operations via group commit — the last end_op() to finish triggers the commit for everyone — which helps average latency but creates high tail latency, since the commit-triggering thread must pay for sequential bwrite calls for every dirty block (write_log → write_head → install_trans), each sleeping until the virtio disk interrupts back. Threads that miss a commit window simply wait for the next one. 
4. Looking at the CDF of latency, most operations complete quickly and the curve rises steeply at low latency values — these are the threads piggybacking on someone else's commit — but the CDF then flattens out into a long, heavy right tail representing the commit-triggering threads paying full disk cost. This shape indicates high variance: the p50 may look acceptable while the p99/p999 can be many multiples higher, growing with the number of dirty blocks in the batch. There is no async path, no background commit thread, and no way to hide disk round-trip latency — the tail is the disk, by design, since xv6 prioritizes simplicity and correctness over performance.

### Tradeoffs: [[Exam2Lec.pdf#page279|ref.]]

# Distributed Systems
### General
1. What distributed systems are, and why they're hard (clocks, links, failure)
	1. A distributed system is a collection of independent computers that work together and appear to the user as a single, coherent system (many nodes working together)
	2. Collection of processors that do not share memory or a clock - no access to shared clock
	3. Clocks (No Global Time)
		1. Each machine has its own local clock. Clocks drift at different rates. There is no "now" across the system. You cannot determine event order by looking at timestamps alone. Solutions: Logical clocks (Lamport timestamps), vector clocks, or expensive hardware (GPS/atomic clocks like Spanner's TrueTime).
	4. Links (Unreliable Network)
		1. Messages can be lost, delayed, duplicated, or reordered. You never know if a message is slow or never arrived. Timeouts are guesses, not facts. The network is the biggest source of unpredictability.
	5. Failure (Partial Failure)
		1. In a single machine, something either works or crashes entirely. In a distributed system, parts fail independently—one node crashes, another slows down, a third loses network, a fourth works fine. Detecting failure is impossible (only timeouts). Nodes can be "alive but unreachable" or "dead but pretending to be alive" (Byzantine).
2. FLP Theorem
3. Horizontal scaling because some software don't fit on one node anymore
4. The core primtive: Consensus(achieving agreement among multiple nodes on a single value or state)
5. Synchronous systems operate on a shared clock with known upper bounds on execution time, offering high predictability but low flexibility. Asynchronous systems have independent clocks, high-latency variability, and non-blocking interactions, offering higher scalability, resilience, and efficiency in distributed environments. 

### OS Connection Abstractions
1. Similar abstractions to those we see within the OS, its essentially a multi-PC OS
	1. Isolation
	2. Capacity

### Difficulties
1. Two computers communicate over an unreliable channel (packets get dropped and delayed)
### FLP Theorem
1. Fisher, Lynch, Paterson state that in a fully asynchronous distributed system, it is impossible to guarantee consensus if even one process experiences a crash failure
2. ![[Pasted image 20260428162711.png]]
### Single-node OS vs Distributed Systems: [[Exam2Lec.pdf#page=308|ref.]]
1. Single-node
	1. No failures -> if the node fails, everything stops working
	2. Single clock source
2. Distributed sys.
	1. Failures -> If any node(s)
	2. Independent clock source
3. Two general problem: impossibility
	1. The proof: [[Exam2Lec.pdf#page=314|ref.]]
### Achieving consensus
1. Recap: we want to have tens-of-thousands of computers working together to solve the same problem
2. Problem: Impossible for 2 computers to come to consensus on anything without prior knowledge
3. How do we do this?
	1. Use timeouts -> Can we construct a consensus protocol that uses timeouts? Assume if we have 2f+1 nodes, f may fail.
		1. Round 1 -> Proposal
		2. Round 2 -> Decision
		3. Round 3 -> Acceptance
		4. ![[Quorum.png]]

### Paxos
1. [[Exam2Lec.pdf#page=326 | ref.]]
2. Paxos loses "availability" when the leader dies
3. Provides CP -> Consistency and Partition Tolerance

### Byzantine
1. [[Exam2Lec.pdf#page=322|ref.]]
### CAP Theorem
1. Distributed Sys. have three properties
	1. consistency -> Same view of all data in the distributed sys.
	2. Availability -> Remains available in the case of machine failures
	3. Partition Tolerance -> If nodes become partitioned (half the machines can talk to each other but the half can't, the distributed sys. keeps working
2. Impossible: only two of these properties can be achieved at a time