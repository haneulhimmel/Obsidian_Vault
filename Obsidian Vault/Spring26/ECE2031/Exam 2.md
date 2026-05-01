# Lab 2
### Logic Thresholds
1. $\mathrm{V_{OH}}$ - Minimum voltage that the gate will output for a logical high
2. $\mathrm{V_{IH}}$ - Minimum input voltage that a gate is guaranteed to interpret as logic high
3. $\mathrm{V_{IL}}$ - Maximum input voltage that the gate is guaranteed to interpret as logic low
4. $\mathrm{V_{OL}}$ - Maximum voltage that the gate will supply when outputting a logical low
5. Key Conds
	1. $\mathrm{V_{OH}}$ > $\mathrm{V_{IH}}$ - So that high output is guaranteed to be interpreted as a high input
	2. $\mathrm{V_{OL}}$ < $\mathrm{V_{IL}}$ - So that a low output is guaranteed to be interpreted as a low input

### Breadboard and Chips
1. DIP - > Dual-Inline-Package chips
2. The power rails run up and down the breadboard; the pins run horizontally

### Switches and Pull-Up Resistors
1. Terminology for switches
	1. Contacts: Pieces of metal that touch to make the connection
	2. Terminals; Connections into the switch
	3. Open/Closed: Open - Terminals are not connected; Closed - Terminals are connected
	4. Normal Position: Position of switch when not being actuated
2. Poles and Throw
	1. Pole: Terminal that can be connected to one of several other terminals
	2. Throws: Number of other terminals that the pole can be connected to

# Lab 8
### Tri-State Drivers
1. High/Low refers to *Voltage* ; Active/Inactive refers to *Behavior*
2. so w