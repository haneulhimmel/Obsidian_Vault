### Structure: [[Structure.pdf| Notes]]

##### Crystal Unit Cell
1. Primitive (unit) Cell -> Smallest unit cell possible
2. Using lattice constant ($\mathrm{\mathring{A} = 10^{-10}m})$, to determine the atoms per cubic volume (or whatever unit)

##### Lattices
1. FCC
2. BCC
3. Diamond Lattice
4. Zincblende Lattice

##### Miller Indices

---
### Basic Semiconductor Physics: [[Chapter 2 - Basic Semiconductor Physics | Notes]]

##### Materials: 

| Group III (Acceptors) | Group IV (Dopants) |
| --------------------- | ------------------ |
| 1. Boron (B)          | 1. Silicon (Si)    |
| 2. Aluminum (Al)      | 2. Germanium (Ge)  |
| 3. Indium (In)        | 3. Tin (Sn)        |
##### Band structure: 
1. Pauli Exclusion Principle: No 2 electrons in a system can be characterized by the same set of quantum numbers
2. Valence and Conduction bands are formed because of P.E.P. which are separated by the band-gap $\mathrm{E_{g}}$ 
	1. At T = 0K
			1. Completely filled valence band
			2. Completely empty conduction band
3. Carriers -> Electrons and Holes ![[Pasted image 20260216223539.png]]
	1. Continuing with the point of elevated T, when the electron is excited from the valence to the conduction band, the additional electron in the conduction band contributes to the current conduction; similarly, the missing electron, now hole, in the valence band contribute to the current conduction as well
4. Indirect vs Direct Bandgap
	1. ![[Pasted image 20260216224601.png | 400 x 250]]

##### Semiconductor Doping: [[Bandstructure.pdf#page=27 | Ref.]]

##### Band Bending by Electric Field: [[Carrier_Transport.pdf#page=12 | Ref.]]

##### Carrier - [[Carrier_Statistics.pdf | Carrier Statistics]]
1. 	Concentration
	1. 	Intrinsic (No doping $\mathrm{N_{A}, N_{D} = 0}$)
	2. Extrinsic (Doping concentration $\mathrm{N_{A}, N_{D} \neq 0}$)
		1. Assumption: Complete Ionization (occurs when nearly all dopant atoms (donors or acceptors) at room temperature (300K) are ionized)
			1. N-Type: $\mathrm{N_{D} \gg n_{i} \to n \approx N_{D}}$ 
			2. P-Type: $\mathrm{N_{A} \gg n_{i} \to p \approx N_{A}}$	
		2. [[Carrier_Statistics.pdf#page=9 | Visual]]
2. Density of States
	1. Defined as: number of available quantum states per unit volume, per unit energy interval at a specific energy level![[Pasted image 20260429185753.png]]
3. Fermi Function & Fermi Energy
	1. Function: where $\mathrm{E_{F}}$ is the Fermi Energy $$\mathrm{f(E)=\frac{1}{1+e^{E-E_{F}/kT}}}$$
	2. Properties
		1. Because of P.E.P. -> $\mathrm{0 \le f(E) \le 1}$
		2. Probability that a state is occupied at the Fermi energy is 50%
	3. Physical Interpretation
		1. At thermodynamic equilibrium, $\mathrm{E_{F}}$ is constant across the device
	4. Boltzmann/Classical Approximation 
		1. ![[Pasted image 20260429190504.png]]

##### Carrier - [[Carrier_Transport.pdf | Carrier Transport]]
1. Drift
	1. Scattering Mechanisms -> Limit the carrier mobility
		1. Impurity Scattering
			1. Dominant at low temps. -> At higher temps (interaction is reduced -> higher thermal velocities -> carrier is less time in close proximity to impurity);  slower carriers are more likely to be deflected by ions
		2. Lattice Scattering
			1. Dominant at high temps. -> more thermal lattice vibration -> more interaction with carriers -> less mobility
2. Diffusion
	1. Particle motion due to a gradient in the particle concentration
	2. Fick's Law $$\mathrm{F = -D\nabla N}$$
3. Einstein's Relation -> Relates drift and diffusion: [[Carrier_Transport.pdf#page=18|Ref.]]

##### Carrier - [[Carrier_GenerationAndRecombination.pdf | Recombination/Generation]]
1. *Perturbation* of semiconductor (alteration of carrier concentration) results in non-equilibrium conditions'
	1. If the perturbation is removed, recombination/generation (R-G) processes will restore equilibrium conditions; if perturbation is maintained, R-G processes will stabilize the (non-equilibrium) carrier concentrations
2. Processes -> All processes occur at all times (even in equilibrium) with the process having the highest rate dominating
	1. Band-to-band R-G
		1. Only involve electron in conduction band and hole in valence band
		2. In non-equilibrium settings, the *minority carrier lifetime $\mathrm{\tau_{p}}$* controls the recombination velocity after the distortion is switched off -> [[Carrier_GenerationAndRecombination.pdf#page=11 | ref.]]
	2. R-G center Generation/Recombination
		1. R-G center needed (lattice defect or impurity which generates states in the bandgap)
		2. Similarly there is also a *minority carrier lifetime $\mathrm{\tau_{n}}$* -> [[Carrier_GenerationAndRecombination.pdf#page=15 | ref.]]
	3. Auger Recombination
		1. 3 carriers are required (any combination)
	4. ![[Pasted image 20260429233008.png | 400]]
3. Band-to-Band vs R-G Center R-G processes
	1. Photons (light particles) -> carry energy but very little momentum
	2. Phonons (lattice vibration particles) carry momentum but very little energy
		1. Indirect semiconductors
			1. R-G center recombination dominates; Band-to-Band is slower as it requires the emission/absorption of a phonon (momentum conservation) in addition to photon emission
		2. Direct semiconductors
			1. Band-to-Band dominates as the previous cost of waiting for a phonon to bump the electron and change its momentum is removed; the electron can just drop directly to the hole (moment vector align) and recombine quicker
			2. Recombination proceeds at a faster rate, hence better for light emitting devices like LEDs and lasers
4. Perturbation
	1. Carrier Injection/Generation
		1. $\mathrm{pn > n_{i}^2}$
		2. Processes
			1. Photo-generation
			2. Operation of diode in forward direction
			3. Impact Ionization (process where high-energy charge carriers {electrons or holes} in a semiconductor, accelerated by a high electric field, collide with neutral atoms, creating new electron-hole pairs)
	2. Carrier Extraction/Recombination
		1. $\mathrm{pn < n_{i}^2}$
		2. Process
			1. Operation of diode in reverse direction
	3. Low-Level Injection
		1. Conditional and Approximations![[Pasted image 20260429235811.png]]
	4. High-Level Injection
		1. Conditional and Approximations ![[Pasted image 20260429235852.png]]

---
### PN Junctions: [[Chapter 3 - PN-Junctions | Notes]]

##### PN - Electrostatic

1. General ![[Pasted image 20260430001102.png | 300]]
2. Basic
	1. Net Doping: $\mathrm{N_{D}-N_{A}}$
	2. Doping Profile Approximations for PN Junctions
		1. Step Junction -> approximation for ion implantation or shallow diffusion into lightly doped wafer (low-temperature, brute-force technique to shoot atoms of a dopant (like Boron or Phosphorus) into a silicon wafer)
		2. Linearly Graded Junction -> Approximation for deep diffusion in moderately to heavy doped wafer
	3. Visual ![[Pasted image 20260430003631.png]]
3. PN Junction Band Diagram
	1. Electrons diffuse from n to p side, while holes diffuse from p to n side (leaves behind unbalanced dopant site charges)
	2. This space charge creates an electric field (band bending) -> carrier drift to balance the carrier diffusion
	3. 
4. Built-in Potential
	1. Can be derived from the band diagram: [[Chapter 3 - PN-Junctions#page=8 | Ref.]]
5. Depletion Approximation
	1. Used to approximate the charge distribution; to obtain quantitative solutions for the electrostatic variable
	2. We must solve the Poisson equation![[Pasted image 20260430010649.png]]
	3. Allows charge density to be modeled as perfectly rectangular areas![[Pasted image 20260430011335.png | 400]]
		1. Carrier concentration n and p is negligible in the depletion region
		2. Charge density outside the depletion region is zero
6. Charge distribution to electric field: [[Chapter 3 - PN-Junctions#page=10 | ref.]]
7. Band diagram (Modes)
	1. The shift is the built-in voltage -> Use this: $\mathrm{V_{bi}-V_{A}}$ to determine mode![[Pasted image 20260430013914.png]]
	2. Different Modes and Band Diagram ![[Pasted image 20260430021213.png]]

##### PN : I-V Characteristic
##### PN Analysis - Models and Circuits
1. Dynamic Behavior
	1. Small-Signal Behavior + Junction Capacitance : [[Chapter33_PN_Dynamic.pdf#page=3 | ref.]]

---
### BJTs: [[Chapter 4 | Notes]]

##### BJT Analysis - Models and Statics (Circuits)

---
### Mosfets: [[Chapter 5 | Notes]]

##### Mosfet Analysis - Models and Statics

---
### Single Transistor Amplifiers: [[Chapter 6 | Notes]]
