1. 2.2.2: Crystalline Structures
	1. Diamond Lattice - Silicon Crystal Structure
	2. Zincblende - GaAs Crystal Structure
2. Miller Indices -> 
	1. Process
		1. 
3. 2.3: Semiconductor Models
	1. 2.3.1 -> Electron States in Atoms
		1. Application of quantum mechanics -> wave equation: Schrodinger 
	2. 2.3.2 -> Semiconductor Bond Model
		1. Covalent bonds are formed due to sharing valence electrons
			1. Thermal energy at room temp. can break covalent bonds and free electrons -> contributing to material conduction
			2. Holes are the "missing" bonds/electrons (conceptual)
	3. Semiconductor Band Model
		1. Key concept -> Electrons occupy  well defined, discrete energy levels
		2. Bandstructure (allowed and forbidden energy bands) is formed from the discrete energy levels and interaction of neighboring atoms
			1. Energy level splitting -> Pauli Exclusion Principle: no 2 electrons can occupy the same state (wrt energy, momentum, spin)
		3. Valence and conduction bands separated by bandgap $\mathrm{E_{g}}$
			1. At T = 0K -> Completely filled valence band; completely empty conduction band ($\mathrm{E_{c}}$ is the lowest E of conduct. band; $\mathrm{E_{V}}$ is the highest E of valence band)
		4. Carriers -> Electrons and Holes
			1. When there is excitement of an electron from V to C bands -> That creates an electron/hole pair contributing to the current conduction
		5. Derivations
			1. Solve 3-D Schrodinger equation wrt to periodic potential of nuclei
			2. Reduced Planck's Constant relation w/ E(k), E(p) -> $\mathrm{p}=\hbar\mathrm{k}$
		6. Direct vs Indirect Bandgap
			1. ![[Pasted image 20260121092431.png]]
		7. **Simplification of E(k)**
			1. Approx. of band structure around band extrema w/ a parabolic E(k) relationship -> where $\mathrm{m_{eff}}$ is the effective mass$$\mathrm{E(k)} = \frac{\hbar^2 \mathrm{k^2}}{2\mathrm{m_{eff}}}$$
			2. Effective Mass $\mathrm{m_{eff}\ (m_{n}^*,m_{p}^*)}$
				1. Conceptually -> 
				2. 1-D: $$\mathrm{m_{eff}} = \frac{1}{\hbar^2} \frac{\partial^2\mathrm{E(k)}}{\partial \mathrm{k^2}}$$
				3. 3-D: $$(\frac{1}{m_{eff}})_{ij} = \frac{1}{\hbar^2} \frac{\partial^2\mathrm{E(k)}}{\partial k_{i}\partial k_{j}}$$
4. 2.4: Semiconductor Doping
	1. Concept -> W/ doping, the electrical conductivity of the material is adjustable over a wide range
	2. Doping in Bond Model (Changes in material conductivity)
		1. N-Type: Introduces electron in conduction band w/o introducing a hole in valence
		2. P-Type: Introduces hole in valence band w/o introducing an electron in conduction
	3. Doping in Band Model
		1. Doping atoms result in the creation of localized energy states in the band gap (periodicity distortion of crystal struct)
		2. N-Type: Additional electron states $E_{D}$ close to the bottom of the conduct band at room temp. -> electrons from states are excited into the conduction band
		3. P-Type: Additional electron states $E_{A}$ close to the top of the valence band at room temp -> these states are occupied by electrons from the valence band -> increase number of holes in valence band
	4. Carrier Concentration
		1. ![[Pasted image 20260121100734.png]]
5. 2.5: Carrier Statistic
	1. 2.5.1 -> Density of States
		1. How many allowed states are in the range E...E+dE $$\mathrm{g_{C}(E)dE = \frac{m_{n}^*\sqrt{2m_{n}^*(E-E_{c})}}{\pi^2\hbar^3}dE\ \alpha\ (E-E_{c})^{1/2}}$$$$\mathrm{g_{V}(E)dE = \frac{m_{p}^*\sqrt{2m_{p}^*(E_{V}-E)}}{\pi^2\hbar^3}dE\ \alpha\ (E_{V}-E)^{1/2}}$$
	2. Fermi Function & Fermi Energy
		1. Definition: The function represents the probability that a state is occupied or not