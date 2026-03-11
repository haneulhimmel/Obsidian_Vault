Kien Le
Lab Report
ECE2031 L09
10 February 2026
<div style="page-break-after: always;"></div>

![[Waveform 1.png]]
**Figure 1.** Simulation waveform demonstrating all 9 possible outcomes for the rock, paper, and scissors game between 2 players, while incorporating error cases that occur when a player has two inputs active simultaneously.

---
![[Spring26/ECE2031/Labs/Lab3/IMG REF/Schematic.png]]
**Figure 2.** Annotated schematic implementing the minimum SOP, Y = $\overline{(\overline{W\cdot\bar{Y}\cdot \bar{Z}}) + (\overline{X\cdot Y}) + (\overline{Y \cdot Z})}$, with descriptions of the max propagation delay under the temperature assumption of 20C. Setting X, Y, and Z to 1 and toggling the W value changes the critical path output, which passes through a NOT, NAND, and BOR/NAND gate with a total delay of 78 ns. 
<div style="page-break-after: always;"></div> 


![[Breadboard.jpg]]
**Figure 3.** Breadboard implementation of the minimum SOP, setting W, X, Y, and Z as switch pins 1, 2, 3, and 4, respectively. The output of the entire circuit is attached to the probe wire coming towards the screen to verify the values of the system.