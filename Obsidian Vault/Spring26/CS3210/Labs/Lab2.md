child attempts write to shared page
    → CPU checks PTE, sees PTE_W is not set (read-only)
    → CPU raises a page fault exception
    → CPU stores the faulting virtual address in CR2
    → CPU jumps to the trap handler in trap.c
    → trap() is called with the trapframe
    → switch hits T_PGFLT case
    → cow_handler(myproc(), rcr2()) is called
        → copies the page
        → copies the PT
        → copies the PD
        → updates child's pgdir to new PD
        → flushes TLB
    → returns back to trap()
    → trap() returns
    → child retries the write instruction
    → this time PTE_W is set, write succeeds

parent's PTE is currently mapped and active in virtual address space
    → TLB has cached this mapping WITH write permission
    → you modify the PTE to remove PTE_W and add PTE_COW
    → but TLB still has the OLD cached entry with write permission
    → CPU uses TLB cache first, never even checks the updated PTE
    → write goes through without triggering COW fault

1. First Part: Probably in vm.c and kalloc.c -> edit copyuvm (SET UP flags and change the mapping to pointers of child and parent to same thing), kalloc, kfree
2. Second Part: trap.c  -> On page fault trigger the trap (switch statement), sends to the COW function or copyuvm (based on development)
3. Third Part: the fucking cow function or copyuvm (vm.c?):  -> invlpg(void *vaddr)


bit 0 (P)  → 0 = page not present
             1 = page present (protection violation)

bit 1 (W)  → 0 = fault caused by a read
             1 = fault caused by a write

bit 2 (U)  → 0 = fault happened in kernel mode
             1 = fault happened in user mode

err: 0x7 = 0b111 → present + write + user mode
           → user process tried to write to a present but read-only page
           → this is your expected COW fault

err: 0x4 = 0b100 → not present + read + user mode
           → user process tried to read a page that doesn't exist
           → this is a genuine invalid access

err: 0x6 = 0b110 → not present + write + user mode
           → user process tried to write to a non-existent page