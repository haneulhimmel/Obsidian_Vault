INSTRUCTIONS:

NOTE: These are the anticipated instructions for the midterm exam. This practice exam is ungraded and you are not required to follow them for the _practice_ exam.

Please answer all questions to the best of your ability.

Partner/collaboration policy

1. No partner is allowed – all exams in this class must be the sole work of each individual student.
2. **Nothing** about the exam may be discussed with any other individual except the course staff, in any format whatsoever (including but not limited to chat, email, in person).
3. Everyone must turn in their own exam
4. Anyone seen or caught violating these policies will be subject to immediate dismissal from the exam and can receive a grade of zero on the exam.

Exam instructions:

- The exam will be _in-person_, in-class, on your laptop. Please bring your laptop charged AND your adapter. It is your responsibility to ensure that your laptop is fully charged and has enough battery charge for the exam.
- The course staff will not have capacity to loan laptops or chargers to students.
- The exam will be released, on Canvas, at the typical start time for your supervised lab (i.e., Tue 6:30pm), and access to the exam will end exactly 80 minutes later (i.e. 7:50pm).
- **Buzzcard**: you are required to bring your buzzcard with you to the exam. Your GTID will be recorded to ensure that you took the exam _in person_. **Do NOT** leave the exam room without checking in with course staff. If we haven’t seen your buzzcard, you may be flagged as absent.
- Please answer all questions to the best of your ability. Write down any reasonable assumptions you had to make.
- [No Internet] All use of internet, other than to access the exam through canvas is strictly disallowed. This is an _open notes,_ **_closed internet_** _exam_. Please note that this implies, but is not limited to the following:
    - You may not consult any "answer" sites such as chegg, Stack Overflow, Quora, Yahoo Answers, or any other Q&A sites or forums. This is strictly prohibited.
    - Google search and its Gemini-generated AI overview is not allowed.
    - Students are forbidden from using **ChatGPT, Gemini, CoPilot, Grok, Claude**, and all other Generative AI technologies or services for any reason whatsoever. Doing so is considered _plagiarism_, is academically dishonest, and constitutes cheating. Instances of this will be referred directly to the Office of Student Integrity (OSI). We are trying to test YOUR knowledge and YOUR ability to think. Circumventing this intent is a matter of academic integrity.
- You may use: a local copy of class notes, the xv6 book, lecture slides.
- You’re not allowed to use lecture recordings during the exam – it’s logistically complicated.
- In pursuit of fairness, you are encouraged to report any instances or suspected instances of cheating on the exam in the provided exam space. With the exact time and place of occurrence.
- If a question asks for an explanation **no credit will be given without explanation**.

**Question 1:**

Micro-kernels provide additional memory-space isolation by separating not only the kernel from user-space, but also subsystems within the kernel from each other.

1. What are the costs of using a micro-kernel over a monolithic kernel? Please explain why these costs are fundamental to a micro-kernel.  
      
	 Isolation/Compartmentalized -> Error in one subsystem won't affect the others from running
	 
    Trade offs -> Isolation vs. Performance  -> Communicating between subsystems require:
	$\mathrm{[}$kernel -> fs -> page cache -> disk service -> block cache -> fs$]$
      1. Context Switching
      2. APIs
      
    Factored OS -> interprocess communications -> cascade of calls within the user space
      
    True Parallelism is non-achievable because the user space processes are treated as non-cooperative and must be preempt; however, for monolithic kernel, we can assume that processes are cooperative, and we can place them on separate cores to let them run parallel
        
     
2. What benefits does a system get from the isolation provided by a micro-kernel?  
      
      Isolation
      Fault-Protection
      Security (narrow attack surface)
      Modularity -> SWE : How it relates to a micro-kernels implementation 
      1. Implement loose coupling between components
      2. System breakdown into separate, well-defined components
      3. Each component has a clear interface
      
     
3. Please discuss one use-case where the advantages of a micro-kernel over a monolithic kernel would not benefit the overall system and explain why.
      
      Consider:
      1. Predictability
      2. Tight control over what's happening in the system
      3. Embedded microcontrollers
      4. Trusted environment
  
  
  
  
  
  

**Question 2:**

Your friend Harry is highly concerned about the isolation on his system. So much so, that he wishes to provide "perfect" CPU isolation between processes. More specifically he wishes to guarantee a given process cannot determine how many other processes are running based on its own CPU utilization. He asks you about your opinion in doing so.

You may assume that Harry is using a processor where caching and micro-architectural effects will not break CPU isolation.

1. Please explain how perfect CPU isolation between processes is incompatible with an OS's abstraction of having infinite processes available.  
      
      Definitions
      1. Perfect CPU Isolation: an ideal where a process has a CPU that is entirely dedicated to it, giving completely predictable, uncontested execution
      2. Abstraction: A simplified interface that hides the complexity of the underlying hardware or system implementation. The OS creates abstractions so that programs don’t need to deal with raw hardware directly.
      3. Infinite Process Abstraction: You can run as many processes as you want, even though the system only has a few CPU cores. This is possible because of CPU scheduling and time sharing
	      1. The OS hides: 
		      1. CPU scheduling
		      2. context switching
		      3. limited hardware cores
		  2. Each process behaves as if it has its own processor, even though the CPU is actually shared
      
      Allocate finite space time / n where n represents the number of infinite process, so that approaches 0 
      
      RR: Time quantum given to a process that has not finished, the time required to cycle back to that with an infinite number of process would also be infinite
      
      Both of the above show how the abstraction breaks because there is isolation between processes, so communication time is chopped
      
      
      
     
2. Harry is insistent that he wants and needs the best isolation he can get between his running processes. He's willing to provide an upper limit (N) on the number of processes live in his OS at any given time. How might Harry leverage this fact to allocate processes CPU time in a way that doesn't leak the number of processes running?  
      
      What can a process observe?
      1. how often it gets scheduled
      2. how much CPU time it receive
      3. how long it waits between run
      4. So CPU time allocation must not change when more processes appear

      Normal Scheduler: CPU Share = $\mathrm{\frac{1}{\#Processes}}$
      
      Set a M amount for the time quantum -> make it so that the time is independent of the N number of processes (constant function in terms of N) -> so time quantum for i will refer to proc i

	  Harry could allocate CPU time using a fixed schedule with N slots, where N is the maximum number of processes. Each slot has a constant time quantum M and is assigned to a specific process ID. If fewer than N processes are active, unused slots remain idle. Because each process always receives M time every N slots, the CPU share is constant and independent of the number of running processes, preventing processes from inferring how many others exist

     Even if a slot has no process assigned, the scheduler still waits for the same time quantum 𝑀 before moving to the next slot. This way, regardless of the number of processes that occupy the slots, the schedule never changes and the process always observes the same pattern.
      
     
2. What are the inefficiencies in this design vs a more traditional scheduler (one that doesn’t provide such strong isolation between processes)?  
      
      Because when slots are idle:
      1. the CPU does nothing
      2. Useful work could have been done
      3. So the system wastes CPU time

     Compared to a traditional scheduler, Harry’s fixed-slot design wastes CPU cycles in idle slots, reduces CPU utilization and throughput, increases latency, and scales poorly when N is large. These inefficiencies arise because the scheduler reserves CPU time for all possible N processes to prevent timing side channels, rather than dynamically allocating time only to active processes
      
      Side Channel: Any unintended way information leaks from a system; Not through the normal output but through indirect signal (A timing side channel specifically uses time differences)
      A timing side channel is a type of information leak where a program can infer secret or hidden information by measuring how long operations take
	3. execution time
	4. power consumption
	5. cache usage
	6. electromagnetic signals
      
     

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

**Question 3:**

Your friend Robert is constructing a new 32-bit CPU architecture and considering making the virtual-memory page-size on his architecture 32 bytes, much smaller than a classic 4KB page.

1. Would you expect a kernel running on top of Robert’s architecture to be more or less memory efficient than a classic 4KB page architecture. Please explain why.

    How to approach this problem: Analyze the linear address breakdown
   1. Page offset, pfn, 
  
	64 bits -> 8 byte size PTEs

    Robert’s 32-byte page:
    1. Page offset bits = log₂(32) = 5 bits
    2. PFN bits = 32 – 5 = 27 bits

	32-byte is 2^5; 27 bits for pfn, 5 for flags
	For every 32-bit word (32-system, so natural word size is 32 bits), we are using 4 byte PTE to address it - (1/8 of memory to address PT)
	1. $$\mathrm{\frac{(2^{pfn}\times 4\ bytes\ (pte))}{2^{32}} = \frac{2^{29}}{2^{32}} = \frac{1}{8}}$$

	 Robert’s 32-byte pages would be far less memory efficient than classic 4 KB pages.
	 Reason: so many tiny pages require huge page tables, which can consume a large fraction of memory, even before considering actual process memory.
	
	 While smaller pages reduce internal fragmentation, the overhead of page tables dominates in this case

	The VPN still indexes into the page table to retrieve a PTE containing the PFN and permission bits. Adding 6 permission/control bits exceeds the original 5-bit flag field, requiring larger PTEs, increasing page table memory overhead, and adding complexity to hardware access and permission checking. This is especially costly with very small pages because the number of PTEs is enormous
  
  

2. Robert also wants his hardware to have a robust tracking and permission system, adding a permission bit for reading, writing, user/superuser, a control bit to disable hardware caching, and some hardware monitoring bits for accessed, and dirty to each page. What implications does adding these permission bits have on the architecture’s page table structure?

	  Basic PT Structure: 
	  1. VPN: upper bits of virtual address (after splitting off page offset)
	  2. Index into PT: VPN tells you which entry to look at
	  3. PTE: contains PFN (Physical Frame Number) + flag bits (permissions, status, etc.)
	  4. PFN: points to the actual physical page in memory
	  
     Trying to add 6 bits to track, but we only have 5 bits for flags 
  
     The VPN still indexes into the page table to retrieve a PTE containing the PFN and permission bits. Adding 6 permission/control bits exceeds the original 5-bit flag field, requiring larger PTEs, increasing page table memory overhead, and adding complexity to hardware access and permission checking. This is especially costly with very small pages because the number of PTEs is enormous.
     5. 32-bit/4 byte PTE would not be big enough (pfn=27 + flags+6 = 33 > 32)
  
	  Implications:
	  1. Increase PTE size -> Drastically increase the size of the PTs as well; worse memory overhead
	  2. Reduce PFN -> Impossible without reducing physical memory; increase page size
	  3. Architecturally -> PTs already consume 1/8 of total memory and doubling the PTE size would result in 1/4 of total memory being consumed
  
  

  
  
**Question 4**

Modern architectures add a 3rd protection bit to the page-table, the X (or execute) bit. This bit determines if the virtual address space can be used to execute from as code. If the bit is cleared and the memory is used by the EIP register, then the processor will trigger a page-fault.

1. Please give and explain one advantage there may be to marking xv6's user-space stack as non-executable.  
      
      EIP reg -> points to next instruction
      
      Security and Stack Overflow (buffer overflow)
      1. Buffer overflow -> Writes more than a specific byte size for the buf then it would overwrite adjacent stack memory, possibly overwriting saved EBP (previous stack frame pointer), ret address (addr of caller instruction), other local variables
      2. Dangling pointers/memory bugs -> process accidentally writes to the wrong stack location (potential pointer error), it can corrupt stack contents
      3. Malicious exploits -> Bugs to inject machine instruct onto the stack
      
      Stack contains data, not instruction -> CPU uses it to the track the execution state of the process
      4. Store local variables
      5. Store function call return addresses
      6. Store saved registers during function calls
      
      
      
      
      
      
      
      
      
      
     
1. Now, imagine you wanted to modify xv6 to set the execute bit on the user-space binary’s code space, but clear it for the binary’s static data space. What would you have to change about exec to make this work within xv6? 

	 Approach:
	 1. Where the code and data are located in VA space? Low mem. close to 0 and located close to each other -> ELF binary
	 2. Granularity of the PT protection mechanism? Page size
	 3. User-space binary code space -> Instructions to Run (Execute bit)
	 4. Binary static data space -> Contains global and static variables (No execute bit; read/write-only)
	 
	 Specific Breakdown
	 1. When exec reads the ELF file, it loops over the program headers (struct proghdr)
	 2. Each program header tells you:
		 1. Start VA (p_va)
		 2. Size of segment (p_memsz)
		 3. Permissions (p_flags) - E, W, X
	3. Allocate user virtual memory
		1. Pages are actually allocated for the process
		2. Allocate separate pages for each segment that needs different protection

	Even if 2 16-byte fit into a 32-byte page and can be pointed to with 1 PTE, if you want to incorporate protection you need to separate the data and code into 2 separate pages with their own PTE so as to set the protection bit

**Question 5:**

You've now been tasked with building a disk swapping algorithm using clock-based eviction. However, the architecture you're building this system for has a very primitive hardware paging system, with the only permission bit on the paging system being "present" (no write bit, all pages are writable) and no automatic hardware tracking of page accesses or writes.

1. The architecture does not have an “Accessed” bit, although you need to track the accessed state to manage a clock algorithm. Please explain how you can efficiently track the accessed state using the paging system.
	
	Look at the most simple approach: pgflt on every page access -> would have metadata for every time that page is read/written to -> inefficient but works

	To improve the above solution, when should we trap on page read -> So essentially we have 2 states for the accessed bit and access = 1 can go from 1 to 0 (clk algo) or remain 1. The transition from 0 to 1 can be done using the PTE_P -> so basically when access = 0, we set PTE_P to 0 (temporarily) then pgflt, then in the handler (software) essentially set access = 1 and set back PTE_P = 1
	
2. How does the lack of write tracking and the write permission bit in the paging system affect the efficiency of the clock algorithm’s eviction behavior? Please explain why this inefficiency exists.

	There's no way to differentiate between whether it read/written to on access, so safe assumption is that it was written to on access (could be dirty), so we should swap it back to disk
  
 

**Question 6:**

Your friend Robin has written some clever code to make singleton initialization code more efficient

if (p == (void *)0) {  
acquire(lock);  
if (p == (void *)0) {  
p = malloc();

initialize(p);  
}

release(lock);

}

You should assume malloc() will not fail.

1. What behavior(s) could Robin see at runtime when running this code? Please explain why.  
      
     Approach:
	1. Need to understand what it's trying to do: singleton -> class with only 1 instance
	2. Once you have a high level idea, identify critical shared resource: p
	
	Data Race: The outside if is an access to the shared resource, so with additional threads there would be 2 or more threads trying to access the shared resource, with one of them being a write (the malloc)
	Therefore, the behavior would be undefined

  
 

1. If you were to suggest an improvement to this code, what would change or changes would you suggest, and why?

	 The approach is clever because of the motive was to reduce the lock every time because of mutexs being expensive (the first access)

	 The improvement would be to remove the outer if statement (lower semantics)