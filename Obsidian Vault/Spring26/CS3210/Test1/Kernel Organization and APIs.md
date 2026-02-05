### Kernel Organization/Separation

#### Microservice Architecture: 
For user spaces dependent on services on top of the kernel -> if OS service fails then user spaces and kernel are unaffected ONLY if the user space program is not dependent or connected to the service

Declarative and Imperative are ways to capture the dependency of the OS services, kernel, and user space programs. The following format is only possible for services that are separated from the kernel
- Un -> {s..., sn}

#### Monolithic Kernel: 
If the kernel has N dependent user spaces and fails -> The N user spaces will cease
However, if one of N user space fails -> Independent/Isolated, so it will not affect any other user spaces or the kernel

If the services are coupled with the kernels, the format will look more like the following
- Un -> {all s_i}
---
### Kernel Responsibilities

#### What are the main ideas:
- Protection
- Isolation

#### Kernel APIs:
- echo Hello | cat -> Uses 3 processes: sh (shell), cat, echo -> These use syscalls to communicate from the user space to the kernel space

#### Microkernel:
What is the minimal task that we can allocate to the kernel -> which tasks can we move to user space (FS, IPC?, Mem, Net)

Kernel-User Space Divide: A lot of overhead w/ communication between the 2 spaces (expensive) -> We get a header to the process asking for inter-process communication (IPC) to reduce cost

#### Isolation Tradeoff:
Microkernel: Maximizes safety as the OS services are factored out (Isolation) -> At the cost of performance (speed), Hard to compartmentalize

Monolithic: Maximizes performance at the cost of safety

Ex: FS failing won't affect the kernel -> However, a lot of processes are dependent on FS so regardless it doesn't matter if it's in the kernel or not (might as well shove it in kernel)