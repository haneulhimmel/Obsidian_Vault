Kien Le
Lab Report
ECE2031 L09
19 February 2026
<div style="page-break-after: always;"></div> 

---
![[FSM-Lab4.drawio.png | center]]
**Figure 1.** UML diagram illustrating how the feeding and packing inputs determine the next state.
<div style="page-break-after: always;"></div> 

--- 
![[Transition_Table.png | center]]
**Figure 2.** State transition table visualizing the inputs and their effects on the next state. Outputs based on the current state are highlighted alongside the next states.
<div style="page-break-after: always;"></div> 

--- 
![[Spring26/ECE2031/Labs/Lab4/Ref/Schematic.png]]
**Figure 3.** Schematic labeled with the corresponding gates, chips, and pin numbers implementing the sum-of-products for the next state bits $\mathrm{q[1]\ \&\ q[0]}$ and the red and green outputs.

---

![[Spring26/ECE2031/Labs/Lab4/Ref/Waveform.png]]
**Figure 4.** Simulation waveform for demonstrating the test cases for the next-state bits. The waveform shows that the state machine does not transition immediately to red, but instead enters a wait stage that is still considered green.
<div style="page-break-after: always;"></div>

--- 
![[Protoboard.jpg]]
**Figure 5.** Protoboard implementation of the next-state logic expressions, incorporating the D flip flop to the right of the board.

---

![[Annotated Schematic.png]]
**Figure 6.** Annotated schematic including propagation delays and the D flip-flop setup time. The maximum calculated frequency, determined through the critical path, is around 8.5 MHz.