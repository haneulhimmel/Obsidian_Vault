### Problem 1.
Your lab partner is an architect. They designed a 16 bit architecture which supports two types of pages: a 64 byte “normal” page and a 2KB “largepage.” They are now trying to decide what kind of paging system to use. They knows from CS3210 that for 32 bit architecture, a two level paging system seemed like a good idea. We will define the memory efficiency of a given paging system as the total bytes used by all the page table pages (this includes pgdir) divided by the total bytes of virtual memory allocated to a process. Code, data lives in low memory, and the stack will be in high memory.

**1A.** Describe the two level paging system best suited for this 16 bit architecture. Describe exactly how the 16 bits of the linear address are allocated. ![[Pasted image 20260428171634.png]]

**1B.** What is the memory efficiency of this two level paging system for the small processes described above? Calculate based on the definition provided.![[Pasted image 20260428172001.png]]

**1C.** We know that 2 level paging is not the only way we can structure the paging system. Your lab partner is asking you if you could help design a one level paging system. They assure you they will support the pagesize bit as part of the PDE flags. Describe the one level paging system you could implement for this 16 bit architecture. Describe exactly how the 16 bits of the linear address are allocated.

Pgszie bit -> Part of PDE flags

A one level paging system that could be implemented would be just to have a large page table with the actual pages that are mapped to frames instead of having a page directory that maps to different page tables. In a similar fashion as above, the lower 11 bits will be used for mapping to the actual value for the pages. However, instead of splitting the 5 bits, we can instead allocate of it to the page table in this one-level system.

**1D.** What is the memory efficiency of this one level paging system for the small processes described above? Calculate based on the definition provided.
![[Pasted image 20260428172547.png]]

**1E.** There’s another way to build a 1 level paging system. Describe exactly how the 16 bits of linear address are allocated.

Another way to build the 1 level paging system is to swap the bits around, so the upper 10 bits would be the page table, while the bottom 6 bits would be the mapping for the pages. As we could use the 64-byte pages as the pages to implement, which would require 6 bits to map.

**1F.** What is the memory efficiency of this one level paging system for the small processes described above. Calculate based on the definition provided.
![[Pasted image 20260428172750.png]]

**1G.** Which of the three paging system design points would you prefer? If there’s a clear winner, specify and explain the reason. If there’s not a clear winner, list two you consider “Pareto optimal” and specify the advantages and disadvantages of each, for the processes described as representative workload. Clearly explain the tradeoff between them.

1. The two‑level system matches the natural sparse layout (low and high addresses) by allocating page tables only for the 2 KB regions that contain actual code, data, and stack. The one‑level system forces a full 2 KB page table regardless of how little memory the process uses, making it unacceptable for very small processes.
2. Tradeoff summary (if one insisted on Pareto comparison)
	1. Two‑level advantages: Low overhead for small/sparse processes, scales well with process size, supports both page sizes via PDE flags.
	2. Two‑level disadvantage: Two memory accesses per translation (slightly higher latency), but on a 16‑bit system this is acceptable.
	3. One‑level advantages: Simpler hardware (single table lookup), slightly faster translation.
	4. One‑level disadvantage: Fixed high overhead (2 KB) penalizes small processes, wastes memory when address space is sparsely used.
	5. Given the representative workload of small processes, the two‑level system is the clear winner because memory efficiency dominates the small performance cost of an extra level.

**1H.** Is it possible for the memory efficiency of one of these three paging systems to be > 1? If not, why not? If yes, describe a type of process AND the choice of a paging system that can make it happen.

Yes, it is possible. Memory efficiency > 1 means the page table overhead exceeds the actual virtual memory allocated to the process. This happens when a process uses very little memory but the paging system forces a large fixed overhead.

![[Pasted image 20260428173137.png]]

---
![[Pasted image 20260428173152.png]]

**2B.** Your friend argues that %eax=2, %ebx=1 is a valid outcome. Again, assuming TSO and that compiler optimizations are possible, explain why they are correct/incorrect in 1-2 sentences.

Under TSO, stores can be delayed and loads can bypass older stores to different addresses. Here, T2’s movl $2, (x) can be reordered before its first movl (x), %eax (store-load reordering), allowing %eax to read the value 2. Then T1 writes 1 to x between T2’s two loads, so the second load reads 1 into %ebx. Compiler optimizations (e.g., reordering instructions) could also produce this outcome, making %eax=2, %ebx=1 valid.

2C. Does this code have a correctness violation? If not, explain why not. If yes, name and define the correctness violation.

Yes

**2D.** Explain what will happen to the number of interleaving possibilities compared to not having locks?

Adding the locks will reduce the number of interleaving possibilities drastically. In the case of these two codes blocks it would make it so that the reads/writes depending on acquire or release would happen before or after. There would be two main possibilities: Rt1, Wt1, Rt2, Wt2 or Rt2, Wt2, Rt1, Wt1.

**2E.** How would your answer to **2A** change with locking? Enumerate all possible (%eax, %ebx) outcomes.

With locking it would it make so the only possible outcomes would be:

i). %eax = 2, %ebx = 2
ii). %eax = 0, %ebx = 0

---
![[Pasted image 20260428174218.png | 600]]

---
![[Pasted image 20260428174243.png | 600]]

**4.** If v $==$ 1 at the end of T2 execution, what can T2 conclude about w?

If T2 sees v $==$ 1 (i.e., flag was set to 1 by T1), T2 cannot conclude that w == 10. The lock only guarantees that T1’s write to flag happens before T2’s read of flag. However, T1 sets x = 10 after releasing the lock, so there is no happens‑before relationship between T1’s write to x and T2’s read of x. Consequently, the read of x may observe either the old value (0) or the new value (10), depending on scheduling and memory ordering. Therefore, T2 can conclude nothing about the value of w — it is nondeterministic.

---
![[Pasted image 20260428174556.png]]

**5A.** Are the application objectives homogeneous or heterogeneous?

Justify your answer, stating precisely ONE **success metric** _most relevant_ for the text editor and ONE **success metric** _most relevant_ for the compression job

The application objectives are heterogeneity as the most relevant success metric for the text editor is minimizing latency, while the most relevant success metric for the compression job is maximizing throughput. These objectives are contradicting.

![[Pasted image 20260428174704.png]]

Heterogeneity means the application objectives differ across workloads (e.g., one cares about latency, another about throughput). Homogeneity means all workloads share the same success metric (e.g., all need high throughput).

**5B.** Describe the response time CDF for the text editor. Precisely specify the expected behavior of the CDF function.
![[Pasted image 20260428175221.png]]

**5C.** Describe the response time CDF for the compression job. Precisely specify the expected behavior of the CDF function.

![[Pasted image 20260428175411.png]]

![[Pasted image 20260428174954.png]]

---
![[Pasted image 20260428175024.png]]

---
### Problem 7.
A program spawns 1,000 user threads to process elements from a larger array that fits in memory. Each thread performs its computation and exits (i.e., no system calls or I/O are involved). Would you expect many-to-one or one-to-one threading to be more efficient? Be sure to specify the specific factors that you consider when measuring efficiency.

![[Pasted image 20260428175615.png]]

---
### Problem 8.
A storage controller generates _R_ I/O completions per second. Each interrupt has an overhead of _Ci_ microseconds (e.g., saving registers, IDT lookup, etc.). Alternatively, the system’s CPU can poll for completions at a cost of Cp microseconds of per second, regardless of how many completions occur. As a function of R, _Ci_, and Cp, at what point does polling become more efficient than interrupts. Explain why in 2-3 sentences.

![[Pasted image 20260428175708.png]]

---
![[Pasted image 20260428175744.png]]

![[Pasted image 20260428175758.png]]

---
![[Pasted image 20260428175248.png]]

**10A.** Your friend argues that this won’t deadlock because interrupts are disabled _before_ we acquire the lock. Briefly explain why they are or are not correct. If the code can deadlock, describe how to fix it.

![[Pasted image 20260428175843.png]]

A global order (or total order) for locks means that every thread in the system acquires locks in the same fixed sequence (e.g., always lock A first, then B, then C). 

**10B.** A different friend claims that _on a single-core system, you do not need the lock – if you disable interrupts around the access to the shared variable, that is enough to protect the access from the interrupt handler_. Are they correct? Briefly explain in 2-3 sentences MAX.

Your friend is correct on a single-core system. Disabling interrupts prevents the only thing that can interleave execution (an interrupt handler) from running, so the critical section becomes atomic with respect to the interrupt handler. Without interrupts, no other thread can run because there is only one CPU and no preemption. Thus, the lock is unnecessary in this specific single‑core scenario.

---
![[Pasted image 20260428175309.png]]

![[Pasted image 20260428175316.png]]

![[Pasted image 20260428175326.png]]