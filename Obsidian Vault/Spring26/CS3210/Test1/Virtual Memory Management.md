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
### Bootup Page-Table in xv6

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
	1. 