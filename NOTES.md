Chapter 1: Computer Systems Overview
Q.1.1
1.1 Introduction
What does a Computer System consists of (hardware)?
•
•
•
•
A
1.2 Registers
FEW examples of user-visible registers and control/status registers
Q.1.2 User-visible registers
• data registers =
• address registers =
– e.g., base register:
– e.g., index register:
Q.1.3 Processor control and status registers
• program counter =
• instruction register =
• program status word (PSW):
– condition codes (or ﬂags) =
– interrupt enable/disable bit =
– kernel/user mode bit =
• interrupt register =
Q.1.4
1.3 Instruction Execution
What is the instruction execution cycle?
Q.1.5
1.4 Interrupts
Deﬁnition of an interrupt ...
Many events may cause an interrupt
• hardware means of communication (example?)
• request of service (example?)
• error occurrence in process (example?)
13
Q.1.6 Why have interrupts?
Q.1.7 What should the CPU do during the wait of the user program in Figure 1.9b?
Q.1.8 How does the CPU know an interrupt has occurred?
we’ll assume interrupted process will resume execution after the interrupt is processed
Events associated with an interrupt:
4.
3. CPU learns an interrupt has occurred
2. complete current executing instruction
1. interrupt occurs from some device
NEW: CPU disables interrupts
5. CPU saves information of current process on system control stack
only store information that interrupt handler may/will overwrite
(NOTE: steps 4 and 6 in text)
6. CPU loads PC of interrupt handler
an interrupt vector now tells CPU where to divert control based on interrupt type
a polling device used to tell CPU interrupt type
8. CPU restores saved information from stack
7. process interrupt
(NOTE: steps 8 and 9 in text)
thus, next instruction to be executed is from interrupted process
9. NEW: CPU enables interrupts
Q.1.9 At a minimum, what must the OS save about the interrupted process?
Q.1.10 How are multiple interrupts handled?
2.
1.
14Q.1.11 Suppose THREE interrupts occur at ’same’ time (during one instruction)
What priority order should you give to the following three items?
disc write done interrupt
new communication message (internal) interrupt
printer ﬁnished interrupt
Storage Hierarchy:
1A: Performance Characteristics of Memory
1.6 Cache Memory
1.5 The Memory Hierarchy
2. secondary storage or secondary memory or auxiliary memory
1. magnetic tape
may also include electronic disks (ﬂash)
includes magnetic disks (ﬂoppy and hard drives), CD-ROM, CD-RW, DVD-RW, etc.
3. main memory or primary memory or just memory
• only large storage media that the CPU can access directly
• usually too small to store all needed programs and data
5. registers
4. cache
Q.1.12 How do these ﬁve storage media di↵er?
Q.1.13 What is the di↵erence between cache and registers?
Q.1.14 What are transfer sizes between storage media?
To/from CPU to/from cache:
byte or word transfer

To/from cache to/from memory: block transfer

To/from memory to/from disc:
frame/page transfer


Q.1.15 Deﬁnition of hit ratio ...
Q.1.16 locality of reference
•
How does an OS use temporal locality?
temporal locality:
15
•
How does an OS use spatial locality? loops, arrays, seq, code execution

spatial locality:
Q.1.17 OS design issues:
• implementation policy = what transfer size should be used in the system page size? block size? etc.
• fetch policy = when to assign a data item to a given storage media
	2 EXTREMES FOR FETCH:
		1) As soon as there is room, it fetches everything it possibly can
		2) Don't fetch it until you absolutely need it (Fetch on Demand)
• placement policy = where to place data item within storage media
• replacement policy = if storage media is full, what data should be replaced
• write policy = if a data item is modified, when should it be written back


Exective Access Time (EAT)
EAT = how long it takes on average to access data once requested
• suppose a two-level storage hierarchy exists: cache (to hold data) and memory
• suppose time to update cache/etc. is negligible
suppose 80% hit ratio in cache
suppose cache access time = 50 ms
suppose memory access time = 750 ms
• Q.1.18 EAT = (H_c)(T_c)+(H_c)(T_c+T_m)
			 = (T_c)+(1-H_c)(T_m)
			 = (50)(.8)+(.2)(50+750)

Q.1.19
1.7 I/O Communication Techniques
NOTE: Equation 1.1 in Appendix 1A generalizes this example
What are three techniques for I/O operations?
1. Programmed I/O
2. Interrupt-drive I/O
3. Direct Memory Access (DMA)

Q.1.20
1.8 Multiprocessor/Multicore
What are three popular approoaches for providing parallelism?
1.  Symmetric Multi Processing (SMP) [Figure 1.19 in textbook]
		Replicating processors multiple identical processors (tightly coupled)

2.	Multicore computers: multi-processors on the SAME chip
		8-core system = 2 processors with 4 cores

3.  Clusters
		Clusters used extensively to build large super computers
------------------------------------------------------------
-Caches are critical to modern high speed processors
-Miltiple copies of a block can easily get inconsistent
	SOLUTIONS ARE HARDWARE BASED

CHAPTER 1 EXTRAS:
What is the largest single "user" of microprocessers today?
	1. Embedded devices
		Typically embedded means designed to perform ONE of a few dedicated functions
	2. Cars
	3. Cell phones

Recent changes in chip design = more complexity
	Previous focus: increasing number of transistros
	Current focus: increasing the number of cores
	Multicore: just a 'few' cores
	ManyCore: 64? 128? Cores
/**************/

Chapter 2: Operating Systems Overview
2.1 Introduction
Q.2.1 What is an Operating System?
• 	a program that provides an interface between the user and the hardware
• 	a program that manages resources
	-> everything a vendor ships
What are the overall goals of an Operating System?
• 	Convenience for the user
• 	Efficent for the system
•	Ease of evolution
Q.2.2 What is the kernel?
What services does the kernel provide?
• most frequently used functions of the OS
• portions of the OS currently in use
• the one process that runs ALL the time on the computer
• central CORE of the OS
• implements processes/threads
• coordinates access to the processing
• synchronizes processes/threads
• manages storage (e.g., MM)
• provides I/O services
• implements file system
• provides protection
• boot process
• system security


OS is just a program
	YES A HUGE PROGRAM, but just a program

	**NO UNIVERSALLY ACCEPTED DEFINITION OF A KERNAL**
How the kernel provides some of these services is the topic of this course?

Q.2.3 What language is used to write an OS?
	Past: assembly
	Now, high-level languages: C or C++

Q.2.4 Deﬁnitions
• turnaround time: they delay between job submission and job completion
• multiprogramming: concurrent execution of processes
	*by definition, a processes are in memory*
• time slice: each process gets the CPU for a slice of time or until process blocks/terminates
	-at the end of time slice
	-process
• context/process switch: when the OS switches from one process (or context) to another
• parallel processing versus concurrent processing: actual vs illusion of simultaneous operation

2.2 Evolution of Operating Systems
Early Systems (serial processing systems)
• no operating system
• large single-process machines
• input devices: card readers, tape drices, toggle switches, etc.
• output devices: line printers, tape drivers, card pucnhes, and display lights

PROBLEM: setup time ws unacceptable (WAY TOO LONG)

Batch Systems
• operating system called a monitor
• Q.2.5 The main feature of a batch system is ...lack of user interaction whiles jobs are 
• operator sorts submitted jobs by job type
batch similar jobs together ! less set-up time for monitor
• monitor does automatic job sequencing
• this early OS included protection of system:
– memory protection
– CPU protection
– DEVICE PROTECTION
	led to concept of MODES of operation today
	kernel mode: execute privileged intructions
	user mode: execute user programs

• Q.2.6 What was turnaround time for a job submitted to a batch system?
	Minutes, hours, days
• problem 1: CPU and I/O(extremely slow) did not process in parallel
	Solution: Multiprogrammed Batch Systems, allowed multiple things to be operating in parallel
• problem 2: User response time was LONG
	Solution: Time share systems

Time Sharing systems
• Q.2.7 The main features of a time share system are ...user interacts with system
• time sharing systems became common in the early 1970’s
Multiprogrammed Batch Systems vs. Time Sharing systems

Modern operating systems

• Consider System Types:
– Mainframe Computers
– Personal Computers (one CPU)
– Parallel Systems (multi-processor systems)
⇤ SMP (symmetric multiprocessors) = tightly coupled systems
⇤ MultiCore and ManyCore systems
⇤ clusters = loosely coupled systems
– Real-time Systems
⇤ when there exists rigid time requirements on the operation
⇤ embedded systems often run real-time operating systems
– Handheld Systems
⇤ PDAs, Pocket-PCs, cell phones, etc.
⇤ often have special-purpose embedded operating system

• Q.2.8 Summary of System Types:
-enormous scale
-very heterogenous
-huge dynamic range

OS development today is pretty complex!
Today's OS:
-multi user
-multi-processor
-multi-threaded

• Q.2.9 Consider Challenges for OS Developers
– CPUs: range from single sensor motes to GPUS
	Cores: from one -> 100s of cores
	Clusters: few machines -> 10,000 of machines

– Network: range from data centers to Internet to networks in home, etc
	Latency: from nanoseconds -> seconds (satellite)
	Bandwidth: from Kbps -> Gbps
		Terabit networks...in future(2015?)
– Storage: range from caches to huge disks
	Size: mb -> tb
	Acces time: few nanosecs -> millisecs
LOTS of variablility and complexity exists in systems today

think about how complex the OS must be for today’s systems
/**********************************SEP 12 2013*************************************/
Q.2.10 How do we tame complexity?
Virtual Machines
	DO NOT CALL THEM VM

• Q.2.11 Deﬁnition:
•	Illusion of own private computer

• Q.2.12 Beneﬁts:
– if each vmac has low utilization, then share one real processor more efficiently
– "sanitary" env; if doing something risky, execution is contained (GREAT FOR OS DEVELOPMENT)
– host machine is protected from the vmac machines
-- can rapidly port/test new applications in different OS environments
-- can execute SEVERAL execution environments (different OSs) concurrently on ONE hardware

• Q.2.13 Cons:
– running each virtual machine has overhead
– virtual machine concept is difficult to implement
-- format of virtual machine needs to be standardized (current status??)
	-- current status: (check piazza)

• Q.2.14 Possible implementations:
1. process virutal machine
	basically, the virtual machine gets created when the user process is created (and terminated when the user process is terminated)
2. system virtual machine
	runs as an application on a host OS
	--> virtualization layer is the HEART of the virtual machine

202.3 Topics of an Undergraduate OS Course
1. Processes
• Q.2.15 Deﬁnition of a process ... a program in execution
• process components:
-- an executable program
-- an associated data needed by the program
-- execution context (stack and PCB)

• Consider an example of how processes may be implemented
– suppose block of contiguous memory allocated to each process
– each process recorded in a process list, maintained by the OS

– Q.2.16 Deﬁnitions: (see Figure 2.8, 8.1, 8.2)
⇤ process index = the index of the process currently executing
⇤ program counter = location of the NEXT instruction to fetch
⇤ base register = starting address of process (b)
⇤ limit register = size of the executing process (h)

• Activities associated with processes:
– process creation and deletion (fork and kill)
– CPU scheduling of processes
– process communication (pipes)
– process synchronization

• Multithreading
– a multithreaded process allows concurrent threads to execute
in ONE process

– Q.2.17 Deﬁnitions:
⇤ a thread is ... a dispatchable unit of work
⇤ a process is ... a collection of one or more threads (and associated system resources)
	MS DOS: single process; one thread
	Windows/Linux/etx: multiple process; multiple thread

Memory (Storage) Management
• OS must manage the cache, main memory and secondary storage units
responsibilities include:
– prevent processes from interfering with each other’s memory
– make allocation of storage transparent
– handle shared memory

• Virtual memory (VM) allows ...  The execution of a process that may not be complete in memory
• VM Details:
– A process consists of multiple pages
VM allows individual pages to be swapped in and out during execution
– VM hides the features of the real memory system from the users
conceals the fact that memory is limited
– virtual address spaces can be much larger than real address space
– VM overallocates memory to increase the degree of multiprogramming

/**AVERAGE AMOUNT OF MEMORY WASTED PER PROCESS!!!!!!
 * 
 * 1/2 page per process on average
 * 
**/

Main memory = number of fixed length FRAMES
Process = number of fixed length PAGES
|page| = |frame| (in most systems)

DOM = degree of multiprogramming


– Q.2.18 VM addressing:
⇤ virtual or logical address = the address the CPU reads during execution
...then the OS creates...
⇤ real or physical address = where instruction or data is actually kept
...the address will have both a page number and an offset...

IF the page size and the frame size are equivalent, then the offsets are equivalent


(see Figure 2.10)
• Activities associated with memory management: 
– tracking which parts of memory are being used and by which processes
– allocating memory when space becomes available
– dynamic mapping between virtual and real addresses

• Activities associated with ﬁle management:
– create/modify/delete ﬁles/directories
– mapping of ﬁles onto secondary storage

3. Information Protection and Security
As the Internet grows, there is an increase in concern for the protection of information

Q.2.19 Much of work in this area falls into four categories:
• availability -
• conﬁdentiality -
• data integrity -
• authenticity -
224. Scheduling and Resource Management
• any resource allocation and scheduling policy must consider three factors:
– fairness to users
– e!ciency for system
– di↵erential responsiveness
• Q.2.20 Schedulers:
– short-term (or CPU) scheduler:
– medium-term (or swapper) scheduler:
– long-term (or job) scheduler:
• I/O queues exist for each I/O device
5. System Structure
• Monolithic systems: no partition of OS into smaller parts
one HUGE program
– structure = no structure
all procedures for OS mixed together
– problem: as OS grows, complexity of system becomes overwhelming
– Example: OS/360, version 1
created by 5,000 programmers over ﬁve years
in 1964: over a million lines of code
– Example: Multics
in 1975: over 20 million lines of code
• Layered systems:
– divide OS functions into a number of layers
each layer built on top of other layers
– bottom layer (layer 0) is the hardware
highest layer (layer N) is the user interface
a layer communicates with the layer directly above and directly below
– easier to debug with separate layers
– allows one layer to change without needing to change other layers
23
– Q.2.21 Problems with layered approach
⇤
⇤
⇤
• Microkernels:
– moved from horizontal layers to vertical layers
– deﬁne kernel as small as possible
– implement rest of OS as user processes
– kernel should be the ONLY code that is machine/device dependent
– client/server communication model (one interface)
– Q.2.22 Advantages of a microkernel over layered system are ...
⇤
⇤
⇤
⇤
⇤
⇤
⇤
– Q.2.23 Disadvantage of a microkernel:
• Modular systems: needed modular software for growing operating systems
– Past: original Unix had two modules deﬁned
– Current: many modules use OO programming techniques
– Q.2.24 Advantages of modular design:
⇤
⇤
⇤
242.4 Modern OS Developments
• modular design
• multithreading
• symmetric multiprocessing
• distributed operating systems
2.5 System Calls
Section 1: General Commands
1. ﬁle management: touch, rm, cp, chmod, mv, ls, cat, cp
2. ﬁle modiﬁcation: vi, emacs, awk
3. status information: time, du, cal, df
4. PL support: gcc, java
5. communications: mail, rsync, rcp
Section 2: System Calls
• Q.2.25 Deﬁnition of a system call ...
• Q.2.26 one possible classiﬁcation of System Calls in Unix:
1.
2.
3.
4.
5.
• Q.2.27 Deﬁnition of a system program ...
25
2.6 Unix Processes
Process creation:
• cpid = fork();
creates copy of the process that executed fork();
– address spaces for the two processes are (almost) identical
– both processes have identical open ﬁles
– both processes have PC pointing to statement after the fork() command
– fork() example:
#include <unistd.h> /* include file for fork/exec */
main() {
int cpid;
cpid = fork();
cout << "Hello there ... " << cpid << endl;
}
Q.2.28 Questions:
– When this code is executed, what is printed?
– What is the di↵erence between the two processes?
• The process tree for this example has a parent process pointing to a child process
• NOTE: communication between these two processes is not available
must use IPC paradigm or shared memory system calls for communication
Process trees
• fork() fork() example:
main() {
int cpid1=-111;
int cpid2=-222; // LINE A
cpid1 = fork(); // LINE B
cpid2 = fork(); // LINE C
cout << "Hello there ... " << cpid1 << " " << cpid2 << endl;
}
Q.2.29 Questions:
– What is the process tree in the double fork example?
– How are the processes distinguished?
Process execution
• execv(file, arg list);
execl, execlp, execle, execv, execvp, execvP
26• process that calls exec() is demolished
exec() overlays (most of) address space of caller with executable file
• NOTE: open ﬁles inherited
Process Synchronization:
• cpid done = wait(status);
caller sleeps until any child terminates
• cpid done = waitpid(pid, status, options);
caller sleeps until child with pid terminates
• returns integer which is the pid of terminating child
• if status is not NULL, then stores status of child termination
• Questions (for unix environment):
– What happens to child if parent is killed?
– What if child exits before the parent waits?
Typical use:
• primary purpose of forking a child is to execute some other program
typically use “exec” to overlay new process on top of old process
• typically parent “wait”s until child is ﬁnished
then, after execution of the other process, the parent gains control again
• Example:
fork()
if child
exec()
else
wait()
27
In fact, a shell (e.g., /bin/sh) basically does:
while (not EOF) do
{
parse command line; (get command, arguments, I/O redirection, etc)
if ((cpid = fork()) == 0) then
{
redirect I/O
exec(cmd, args)
}
else
{
if (command doesn’t end with &), then wait();
}
}
2.7 Unix Pipes for Interprocess Communication (IPC)
Unix IPC: through the ﬁlesystem
ﬁle descriptors, read()/write(), pipes
What is a Unix pipe?
Pipes:
• pipe allows a one-way communication ﬂow between two processes
• pipe construct shared thru process hierarchy inheritance rules
common ancestor must establish pipe
• produces a totally reliable byte stream between two processes communicating
FIFO queue of bytes
Deﬁnition of a pipe:
int fd[2];
int pipe(int *fd);
• fd[0]: opened for reading
• fd[1]: opened for writing
To obtain IPC between two processes:
deﬁne pipe
fork child
have parent close one end of pipe
have child close the other end of pipe
read/write
close other two pipe ends
Q.2.30 How to do two-way communication?
28/*********************************/
/* FORK EXAMPLE */
/********************************/
#include <iostream>
#include <errno.h> /* include file for perror */
#include <unistd.h> /* include file for fork/exec */
#include <sys/types.h> /* include file for wait */
#include <sys/wait.h> /* include file for wait */
#include <stdio.h>
using namespace std;
main()
{
int cpid;
int cpid2;
if ((cpid = fork()) == -1) {
perror(‘‘fork failed’’);
return(-1);
}
cout << ‘‘The child is started.’’ << endl << endl;
if (cpid == 0) { /* This is the child. */
cout << endl << ‘‘I’m the child and my pid is ‘‘ << getpid() << endl;
cout << ‘‘I’m waiting for the execute sacrifice.’’ << endl << endl;
execl(‘‘/bin/ls’’, ‘‘ls’’, ‘‘-l’’, (char *)0); /* execute a process */
perror(‘‘exec failed’’);
return(-1);
}
else { /* This is the parent. */
cout << endl << ‘‘I’m the parent. I’ll wait on my child.’’ << endl;
cpid2 = wait( (int *) 0); /* wait for child to finish */
cout << endl << ‘‘The child with pid = ‘‘
<< cpid2 << ‘‘ is done.’’ << endl;
return(0);
}
}
29
/*********************************/
/* PIPE EXAMPLE */
/********************************/
#include <iostream>
#include <errno.h> /* include file for perror */
#include <unistd.h> /* include file for pipes */
#include <stdio.h>
#define DATA "There are 10 types of people ... "
using namespace std;
main()
{
int the_pipe[2];
int child;
if (pipe(the_pipe) < 0) { /* Creates a pipe */
perror("opening pipe");
return(-1);
}
if ((child = fork()) == -1) {
perror("fork");
return(-1);
}
if (child == 0) { /* This is the child. */
close(the_pipe[0]); /* It writes msg to its parent */
cout << "I’m the child; listen to my message!" << endl << endl;
if (write(the_pipe[1], DATA, sizeof(DATA)) < 0)
perror("writing message");
close(the_pipe[1]);
}
else {
char buf[1024]; /* This is the parent. */
close(the_pipe[1]); /* It reads the child’s message */
cout << "I’m the parent; I should listen to my child." << endl << endl;
if (read(the_pipe[0], buf, 1024) < 0)
perror("reading message");
cout << "My child says: " << buf << endl;
close(the_pipe[0]);
}
return(0);
}
30