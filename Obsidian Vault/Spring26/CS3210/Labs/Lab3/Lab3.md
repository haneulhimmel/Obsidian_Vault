**In summary**: Save scheduler state → Switch to user memory → Mark running → Execute process → Return from process → Switch back to kernel memory → Clear CPU proc pointer.

---
### Clone Walkthrough

User calls: clone(stack, size)
            ↓
Assembly in usys.S: movl $22, %eax; int $T_SYSCALL
            ↓
Kernel dispatcher sees: syscall number 22
            ↓
Dispatch table says: syscalls[22] = sys_clone
            ↓
sys_clone() extracts arguments
            ↓
kernel_clone() does the work
            ↓
Returns to user with result