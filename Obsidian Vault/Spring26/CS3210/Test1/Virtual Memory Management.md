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