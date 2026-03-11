
---
### Passing Submission

![[Passing Submission.png]]

---
### Waveform for a Cycle of Addition (0:230ns)

![[Spring26/SiliconJacket/DD-Onboarding/Waveform.png]]
<div style="page-break-after: always;"></div>

---
### FSM Implementation

![[FSM_SJ.excalidraw 1.png | 500x800]]
<div style="page-break-after: always;"></div> 

---
### Write-Up

For my implementation of the FSM, I knew I had to incorporate states within to the diagram that would allow the signals to stabilize as working with unstable values would just be a pain to debug, so I initially started with a lot more setup states that I basically used as a wait to allow time for the values to stabilize. Instead of the one setup stages that I currently have, I had about two per each major instruction (read, add, and write) just to be safe. From there, once I had setup the logic for the controller and could use the Simvision tool to visualize the actual signals and when they were available, I could cut back on the number of states that I implemented to reduce clock cycles. 
Working with additional states to wait allowed me to experiment with the sequence of which I could raise flags and access values without messing up the timing in contrast to setting up a limited amount of wait states and dealing with timing and access conflicts. 

Walking through the cycle of addition, I follow the implementation described, reading in the 64-bit values to operands a and b before then splicing them into the lower and upper 32 bit in the READ states, incrementing the read pointers to keep track of the value that had just been read. A wait/setup state was incorporated in between these READs to allow for the r_ptr to stabilize to ensure that the right value is read in subsequent state. From there, I setup for the ADD states with the first one focused on lower bits of op_a and op_b using the initial carry_in value of 0 (no previous values calculation). Then I need to keep track of the carry_out with a logic variable that can be passed on to the following calculations for the upper bits. The tracked carry_out value then propagates to ADD2 where the upper bits of op_a and op_b are calculated and stored into an upper result that is 32 bits. The carry_out for this operation can be discarded since there are no other calculations for any higher bits that would be dependent on this value. Write_setup then concetenates the calculated values of the upper and lower together and stores it to the w_data before write increments to keep track of where it was written. This entire process will terminate when the write end address is reached, otherwise it will continually loop back to the read_setup and start again.