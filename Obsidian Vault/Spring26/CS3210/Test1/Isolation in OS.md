# General

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
