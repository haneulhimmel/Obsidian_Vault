- `inode` — **what** the file is (exists on disk)
- `struct file` — **a particular open instance** of it (exists in memory, temporarily)
- `file descriptor` — **a process's handle** to that open instance (just an integer)

You'd work with `struct file` when implementing operations that are about the **open session**, not the file itself. In xv6 the main cases are:

- **`open()`** — allocates a new `struct file`, sets `readable`/`writable` based on the mode flags, links it to the inode, initializes `off = 0`
- **`read()`/`write()`** — advances `f->off` after each operation
- **`dup()`** — increments `f->ref` so two file descriptors share the same `struct file` and therefore the same offset
- **`close()`** — decrements `f->ref`, frees the `struct file` when it hits zero

![[Pasted image 20260415221026.png]]

![[Pasted image 20260415222357.png]]

User password
     ↓
[Add salt]
     ↓
[SHA256 hash]  → 32 bytes of hash
     ↓
[AES256 encrypt]  → 32 bytes of encrypted hash
     ↓
[Convert to hex]  → 64 hex characters
     ↓
Store in /etc/shadow