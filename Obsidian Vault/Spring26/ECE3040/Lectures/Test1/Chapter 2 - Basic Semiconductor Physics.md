
![[Pasted image 20260217141756.png]]
# 2.1: Semiconductor Materials

### General Overview

Material classification by resistivity where:
1. Insulators: $10^5 < \rho$
2. Semiconductors: $10^{-3} < \rho < 10^5 (-10^8)$
3. Conductors: $\rho < 10^{-3}$

Semiconductor Elements
1. Elemental: Silicon (Si) and Germanium (Ge)
2. Compound Semiconductors: Fixed Ratios with stoichiometry
	1. Gallium Arsenide (III-V)
	2. Zinc Selenide (II-VI)
	3. Silicon Carbide (IV-IV)
3. Alloy Semiconductors: Variable stoichiometry
	1. Binary: $\mathrm{Si_{1-x}Ge_{x}}$
	2. Ternary: $\mathrm{Al_{x}Ga_{1-x}As}$

---
# 2.2: Crystal Structure

![[Structure Reference]]
### 2.2.1: Unit Cell

Definitions for Structure Terms
1. Crystal: Period 3-D arrangement of atoms
2. Unit Cell: Small portion of the crystal that can be used to reproduce the crystal
3. Primitive (Unit) Cell = Smallest unit cell possible

Cubic Crystal Structure
![[Unit Cell.png | 250 x 250]]
1. Simplest of all 3-D Unit Cells
2. Cube with an atom position at each corner -> 1/8 of each corner atom is inside the unit cell
3. Each atom has 6 nearest neighbors
4. Side length is called the lattice constant *a*

Face-Centered-Cubic (fcc) Unit Cell
![[Pasted image 20260216214945.png | 250 x 250]]
1. Additional atom in the center of the cube
2. 2 atoms per unit cell
3. 8 nearest neighbors

Body-Centered-Cubic (bcc) Unit Cell
![[Pasted image 20260216215022.png | 250x250]]
1. Additional atoms in the center of each face of the cube
2. 4 atoms per unit cell
3. 12 nearest neighbors
---
### 2.2.2: More Crystalline Structures

Diamond Lattice
![[Pasted image 20260216215531.png | 250 x 250]]
Silicon and germanium have this structure, which constructed through two interpenetrating fcc lattices shifted by one-quarter of the cube body diagonal
1. The silicon unit cell has a lattice constant of $5.43 \mathring{A}$ at T=300K where 1 $\mathring{A}=\mathrm{10^{-10}cm}$
 
 Zincblende Lattice
![[Pasted image 20260216215605.png | 250 x 250]]
Most III-V semiconductors have a zincblende lattice, which consist of two interpenetrating fcc lattices shifted by one-quarter of the cube body diagonal but with different atoms occupying each fcc sublattice
1. Lattice constant of $5.65\mathring{A}$ at T=300K
---
### 2.2.3: Miller Indices

Brief Overview
1. Used to specify crystallographic planes and directions
2. Planes: (100), (010), (001), (/100), (0/10), (00/1) --> {100}
	1. Equivalent because of symmetry and summarized as the abovezS

Steps to finding the indices
1. Record where the plane intersects coordinate axes in in units of *a*
	1. 1a, 2a, 3a, etc.
2. Invert Intercept Values
	1. 1/1, 1/2, 1/3, etc.
3. Multiply with a constant to get smallest possible set of whole numbers
	1. 6, 3, 2, etc.
4. Enclose set with curvilinear bracket
	1. (632)
	2. (6 -3 2) -> ($\mathrm{6\bar{3}2}$)

Crystal Planes and Directions
1. Visual for the miller indices and the planes and vectors created by them
![[Pasted image 20260216220437.png | 250x]]


---
# 2.3: Band Structure

### 2.3.1: Electron States in Atoms

Quantum Mechanics
1. Systems with atomic dimensions are described with quantum mechanics instead of classic Newtonian methods
2. Time-dependent Schrödinger equation describes the dynamic behavior of a single-particle system $$-\frac{\hbar^2}{2m}\nabla^2\Psi + U(x,y,z)\Psi = -\frac{\hbar}{i}\frac{\partial \Psi}{\partial t}$$
	1. Where m is the particle mass, U is the system's PE, and i is the sqrt of -1

Hydrogen Atom
1. Solve the Schrödinger equation for the electrostatic potential U of the H nucleus
	1. $\mathrm{U=-\frac{q^2}{4\pi \epsilon_{0}r}}$
2. Yielding the wavefunctions of the different electron states and their energies
	1. $\mathrm{E_{n} = \frac{13.6}{n^{2}}eV}$

Multi-Electron Atoms
![[Pasted image 20260216221848.png]]
1. Electrons states in multi-electron atoms are uniquely characterized by 4 quantum numbers *n, l, m, & s*
2. ==Pauli Exclusion Principle: No 2 electrons in a system can be characterized by the same set of quantum numbers
	1. At T=0K, electron states are filled from the one with the lowest energy on with the available electrons

### 2.3.2: Semiconductor Bond Model

Silicon
1. Bonding to next neighbors is achieved through sharing valence electrons to form covalent bonds
2. Atomic number = 14 -> Number of electrons
3. Number of valence electrons = 4

General 
1. Valence electrons are weakly bound
2. Thermal energy at room temperature can break covalent bonds and "free" electrons which now contribute to the materials conduction
3. Holes are the "missing" bonds/electrons, also contributing to the overall conduction

### 2.3.3: Semiconductor Band Model

![[Pasted image 20260216222425.png | 600 x 400]]

General
1. Single Atom
	1. From Bohr's atom model, the electrons are said to occupy well defined, discrete energy levels
2. Crystal
	1. Because of interaction of neighboring atoms, the discrete energy levels split up and a band structure is developed with allowed and forbidden energy bands
	2. Valence band and conduction band are formed because of Pauli Principle which are separated by the bandgap $\mathrm{E_{{g}}}$
		1. At T=0K
			1. Completely filled valence band
			2. Completely empty conduction band
	3. With elevated T, some electrons can be excited from the valence to the conduction band

Simplified Model![[Simplified Band Model.png]]

Carriers: Electrons and Holes
1. Completely filled band and empty band do not contribute to the overall current conduction
2. Continuing with the point of elevated T, when the electron is excited from the valence to the conduction band, the additional electron in the conduction band contributes to the current conduction; similarly, the missing electron, now hole, in the valence band contribute to the current conduction as well
	1. This process of thermal excitation has created an electron/hole pairs
![[Pasted image 20260216223539.png]]

Bandgap & Material Classification: Based on the simplified model
1. Insulator: The bandgap is very wide, preventing many electrons from exciting from the valence to the conduction band
2. Semiconductor: The bandgap is moderate, allowing thermal excitation to be moderately easy
	1. $\mathrm{E_{g} = 1.43eV\ (GaAs)}$
	2. $\mathrm{E_{g} = 1.12eV\ (Si)}$
	3. $\mathrm{E_{g} = 0.66eV\ (Ge)}$
3. Metals: The band gap is very narrow of just overlapped

Band Structure
1. Derivation
	1. Solving Schrödinger's 3-D equation leads to the relationship of the wavenumber *k* and crystal momentum *p* to be: $\mathrm{p=\hbar k}$
2. Indirect vs Direct Bandgap
	1. Direct bandgap: If the top of the valence band corresponds with the bottom of the conduction band
	2. ![[Pasted image 20260216224601.png | 400 x 250]]

Simplification of E(k) Band Structure within ECE3040
1. Essential Parts to look at:
	1. Top of valence band: $\mathrm{E_{v}}$
	2. Bottom of conduction band: $\mathrm{E_{c}}$
2. Approximation of band structure around the band extrema by parabolic E(k) relationship
	1. $$E(k) = \frac{\hbar^2k^2}{2m_{eff}}$$
	2. Used to sub in the above equation$$E=\frac{\hbar^2 k^2}{2m_{0}}\left.\vphantom{\begin{matrix}a\\b\\c\end{matrix}}\right\}\ \begin{matrix}\mathrm{p=m_{0}v}\\\mathrm{E_{kin}=\frac{1}{2}m_{0}v^2}\\\mathrm{p=\hbar k=\frac{h}{\lambda}}\end{matrix}$$
	3. Electron behavior in the crystal is similar to free electron behavior with 
		1. $\mathrm{m_{e}=m_{eff} \neq m_{0}}$

Effective Mass
1. Definitions
	1. 1-D: $$\mathrm{m_{eff}}^{-1} = \mathrm{\frac{1}{\hbar^2}\frac{\partial^2E(k)}{\partial k^2}}$$
	2. 3-D: $$\mathrm{\left( \frac{1}{m_{eff}} \right)_{ij}= \mathrm{\frac{1}{\hbar^2}}\frac{\partial^2E(k)}{\partial k_{i}\partial k_{j}}}$$
	3. Values for T=300k
		1. ![[Effective Masses.png]]
2. Concept
	1. Movement of carriers (electrons and holes) inside the semiconductor crystal can be described by classical mechanics relation by relation the free electron  mass $\mathrm{m_{0}}$ with the effective mass for either holes or electrons $$\mathrm{F=m_{n}^*\frac{dv_{n}}{dt}} \mathrm{\ and\ \mathrm{F=m_{p}^*\frac{dv_{p}}{dt}}}$$
	2. Effectives masses are tensors: meaning the carrier acceleration generally varies with direction of travel in the crystal

---
# 2.4: Semiconductor Doping

Silicon Doping
1. Doping with donor atom (group 5): Phosphorous (P) or Arsenic (As), which both have 5 valence electrons and yields ==N-type silicon
2. Doping with acceptor atoms (group 3): Boron (B), which has 3 electron electrons and yields ==P-type silicon

Doping in Bond Model
	![[Pasted image 20260216230855.png | 250 x 350]]
1. N-Type Doping
	1. Fifth valence electron does not participate in covalent bonds to next neighbors; only small energy is required to "free" this electron, thus contributing to the materials conductivity
2. P-type Doping
	1. Doping with three valence electrons results in one electron missing for the covalent bonds to the four next neighbors; this hole can hop from covalent bond to bond, also contributing to the materials conductivity

Doping in Band Model
	![[Pasted image 20260216231614.png | 250 x 400]]
1. As a result of the doping atoms, the periodicity of the single-crystal crystal structure is distorted, creating allowed (localized) energy states in the band gap
2. N-Type Doping
	1. Additional electron states $E_D$ close to the bottom of the conduction band; At room temperature, the electrons from these states are excited into the conduction band, increasing the conductivity
3. P-Type Doping
	1. Additional electron states $E_A$ close to the top of the valence band; At room temperature, the electrons from the valence band are excited to the $E_A$ band, increasing the number of holes in the valence band and, thus, the conductivity

Carrier Concentration
1. Intrinsic Semiconductor (no doping: $\mathrm{N_{A}, N_{D}=0}$)
	1. Carrier concentration: $\mathrm{n=p=n_{i}}$
2. Extrinsic (doping concentration: $\mathrm{N_{A}, N_{D} \neq 0}$)
	1. Assumption: Complete Ionization
		1. All dopant atoms are ionized, meaning donor atoms are positively charged and acceptor atoms are negatively charged
		2. Under complete ionization, the free carrier concentration (n or p) equals the net doping concentration
	2. Majority Carrier Concentrations:
		1. N-Type Semiconductor:
			1. Density of donor atoms: $\mathrm{N_{D}\ [cm^-3]}$
			2. Density of electrons ($\mathrm{N_{D} \gg n_{i}}$): $\mathrm{n \approx N_{D}\ [cm^-3]}$
		2. P-Type Semiconductor:
			1. Density of acceptor atoms: $\mathrm{N_{A}\ [cm^-3]}$
			2. Density of holes ($\mathrm{N_{A} \gg n_{i}}$): $\mathrm{p \approx N_{A}\ [cm^-3]}$

---
# 2.5: Carrier Statistic

### 2.5.1: Density of States

General
1. How many allowed states are in the range E...E+dE
	1. $$\mathrm{g_{C}(E)dE = \frac{m_{n}^*\sqrt{2m_{n}^*(E-E_{c})}}{\pi^2\hbar^3}dE\ \alpha\ (E-E_{c})^{1/2}}$$$$\mathrm{g_{V}(E)dE = \frac{m_{p}^*\sqrt{2m_{p}^*(E_{V}-E)}}{\pi^2\hbar^3}dE\ \alpha\ (E_{V}-E)^{1/2}}$$
	2. ![[Pasted image 20260216232838.png]]

### 2.5.2: Fermi Function & Fermi Energy

Definition
	![[Pasted image 20260216233303.png | 250 x 350]]
1. Fermi Function f(E): probabilty function which gives the probability whether a state is occupied or not
	1. $$f(E) = \frac{1}{1+e^{E-E_{F}/kT}}$$
	2. where $\mathrm{E_{F}}$ is the fermi energy
2. Characteristics of Fermi Function
	1. Because of Pauli Principle: $\mathrm{0 \le f(E) \le 1}$
	2. The probability that a state is occupied at the fermi energy is 50%: $\mathrm{f(E=E_{F})=0.5}$
	3. f(E) is symmetrical around $\mathrm{E_{F}}$
3. Physical Interpretation of Fermi Energy ($\mathrm{E_{F}}$)
	1. In thermodynamic equilibrium, $\mathrm{E_{F}}$ is constant across the device

Boltzmann/Classical Approximation
1. For $\mathrm{|E-E_{F}|>3kT}$: The fermi function can be approximated by exponential functions
	1. $$\mathrm{E-E_{F} > 3kT \rightarrow f(E) \approx e^{-(E-E_{F}/kT)}}$$$$\mathrm{(E_{F}-E) > 3kT \rightarrow f(E) \approx 1- e^{(E-E_{F}/kT)}}$$
### 2.5.3: Carrier Densities

General
1. The carrier densities of electrons *n* and holes *p* can be calculated from the density of states g(E) and the fermi function f(E)
	1. $$\mathrm{n=\int_{E_{C}}^{Top \rightarrow \infty}g_{C}(E)f(E)dE}$$$$\mathrm{p=\int_{Bottom\rightarrow \infty}^{E_{V}}g_{V(E)}(1-f(E))dE}$$

Carrier Concentration
	![[Pasted image 20260216234436.png]]

Carrier Density - Boltzmann Approximation
![[Pasted image 20260216234706.png | 250 x 300]]
1. Electrons: $\mathrm{(E_{C}-E_{F})\ge 3kT}$
	1. ![[Pasted image 20260216234731.png]]
2. Holes: $\mathrm{E_{F}-E_{V}\ge_{3}kT}$
	1. ![[Pasted image 20260216234854.png]]

Intrinsic Semiconductor: No doping
1. From Boltzmann Approximation of $\mathrm{E_{F} =E_{i}}$
	1. $\mathrm{n=N_{C}e^{(E_{i}-E_{C})/kT}=n_{i}}$
	2. $\mathrm{p=N_{V}e^{(E_{V}-E_{i})/kT}=n_{i}}$
2. Therefore solving for $\mathrm{n_{i}}$
	1. $\mathrm{np=n_{i}^2=N_{C}N_{V}e^{(E_{V}-E_{{C}})/kT}}$
	2. $\mathrm{\therefore n_i = \sqrt{N_{C}N_{V}}e^{-E_{g}/2kT}\approx 10^{10}cm^{-3}}$
3. Location of $E_{i}$
	1. $\mathrm{E_{i} = \frac{E_{C}+ E_{V}}{2}+\frac{3}{4}kT\ln\left( \frac{m_{p}^*}{m_{n}^*} \right)}$
	2. The intrinsic fermi level is only in the center of the band gap if $\mathrm{m_{p}^* = m_{n}^*}$

Extrinsic Semiconductor: With doping
1. From Boltzmann Approximation
	1. $$\mathrm{n=N_{C}e^{(E_{F}-E_{C})/kT}}=\mathrm{N_{C}e^{(E_{i}-E_{C})/kT}e^{(E_{F}-E_{i})/kT}}$$
	2. Mass-Action-Law
		1. $$\mathrm{np=n_{i}^2}$$
### 2.5.4: Charge Neutrality Relationship

Definition
1. In equilibirum, charge neutrality is fulfiled:
	1. $$\mathrm{p-n+N_{D}^+ - N_{A}^-=0}$$
	2. P = holes, n = electrons, $\mathrm{N_{D^+}}$=ionized donors, $\mathrm{N_{A}^-}$=ionized acceptors
2. Electron and Hole Concentration
	1. ![[Pasted image 20260217002827.png]]
### 2.5.5: Non-Complete Ionization (Temperature Dependence of Carrier Density)
![[Pasted image 20260217002911.png]]


---
# 2.6: Carrier Transport

### 2.6.1: Carrier Drift

Drift is defined as charged particle motion in response to an applied electric field. Drift carrier densities: $J_{p}$ and $J_{{n}}\ \mathrm{\left[ \frac{A}{cm^2} \right]}$
1. $$\mathrm{\vec{J}_{p,drift}=qp\vec{v}_{d,p}}$$$$\mathrm{\vec{J}_{n,drift}=-qn\vec{v}_{d,n}}$$

For small electric fields, the drift velocity is proportional to the applied electrical field with the mobility $\mathrm{\mu}$ as a proportionality factor
1. $$\mathrm{\vec{v}_{d,p}=\mu_{p} \varepsilon }$$$$\mathrm{\vec{v}_{d,n}=-\mu_{n} \varepsilon }$$
The mobility plays a central role as the parameter characterizing the carrier drifts
![[Pasted image 20260217015629.png]]

Carrier Mobility
1. Definition: 
	1. $$\mathrm{\mu_{p}\equiv\frac{V_{d_,p}}{ \varepsilon}};\ \mathrm{\mu_{n}\equiv\frac{V_{d_,n}}{ \varepsilon}}$$

Charged particles are accelerated by the electric field and lose energy by collisions with impurities and the crystal lattice -> impurity scattering and lattice scattering
The drift of a particle is superimposed on the random thermal motion

Scatter Mechanisms I
1. Impurity (a) and lattice (b) scattering limit the carrier mobility
	1. $$\mathrm{\mu=\frac{q_{\tau}}{m^*}}$$
	2. Where $\mathrm{\tau}$ represents the mean free time between collisions
	3. Mobility decreases with increasing total doping concentration ($N_{A}+N_{D}$)

Scattering Mechanisms II
1. T-dependency of the mobility
	1. Lattice Scattering in Si
		1. Reducing the temperature means less thermal lattice vibration -> less interacting with carriers -> higher mobility
	2. Impurity Scattering in Si
		1. Dominant scattering mechanism at low temperatures -> interaction is reduced at higher temperatures -> higher thermal velocities -> because carrier is less time in close proximity to impurity
		2. $$\mathrm{\mu=\mu(T,N_{A}+N_{D})}$$

Resistivity
1. Definition of conductivity $\sigma$ and resistivity $\rho [\ohm cm]$ tensor
	1. $$\mathrm{\vec{J}=\sigma \vec{\varepsilon } = \frac{1}{\rho} \vec{\varepsilon}  }$$
	2. From the drift current, the resistivity is given by: $$\mathrm{\rho=\frac{1}{q(\mu_{n}n+\mu_{p}p)}}$$
2. Can be determined by a current-voltage measurement using a four-point probe$$\mathrm{\rho=\frac{V}{I}WCF}$$
	1. Where W is the substrate thickness and CF a correction factor

Band Bending by Electric Field
	![[Pasted image 20260217021128.png | 300 x 400]]
1. Presence of the electric field results in the $\mathrm{E_{c}}$ and $\mathrm{E_{v}}$ being no longer constant
2. Electrostatic Potential V:
	1. $$\mathrm{V=-\frac{1}{q}(E_{c}-E_{ref})}$$
3. Electrostatic field $\mathrm{ \varepsilon }$
	1. $$ \begin{align}
&\varepsilon = -\nabla V \\ \\ &\varepsilon =\frac{1}{q}\frac{dE_{V}}{dx}=\frac{1}{q}\frac{dE_{V}}{dx}=\frac{1}{q}\frac{dE_{i}}{dx}
\end{align}$$
![[Pasted image 20260217021605.png]]
### 2.6.2: Carrier Diffusion

Diffusion is defined as the particle motion due to a gradient in the particle concentration. Fick's Law describes diffusion as the particle flux density F $[particles/cm^2s]$ is proportional to the negative gradient of the particle concentration: $F=-D\nabla_{\eta}$

Diffusion Current
1. $$\begin{align}
&\mathrm{J_{p,diff}=-qD_{p}\nabla p} \\ \\&\mathrm{J_{n,diff}=qD_{n}\nabla n}
\end{align}$$

### 2.6.3: Total Current Equations

Summing up drift and diffusion current densities, we can obtain the following equations
1. $$\begin{align}
&\mathrm{\vec{J}_{p}=q\mu_{p}p \vec{ \varepsilon }-qD_{p} \vec{\nabla}p} \\ &\mathrm{\vec{J}_{p}=q\mu_{p}p \vec{ \varepsilon }-qD_{p} \vec{\nabla}p} \\ \\ &\mathrm{\vec{J}=\vec{J}_{n}+\vec{J}_{p}}
\end{align}$$

### 2.6.4: Einstein Relations

Relate drift ($\mathrm{\mu}$) and diffusion (D): 
![[Pasted image 20260217022614.png]]


---
# 2.7: Carrier Generation/Recombination

Perturbation (disturbance) of the semiconductor (excess/deficit in carrier concentration) with respect to the equilibrium values is created -> resulting in non-equilibrium conditions
1. Perturbation: Carrier Injection/Generation$$\mathrm{pn>n_{i}^2}$$
	1. Photogeneration
	2. Operation of diode in forward direction
	3. Impact Ionization
2. Perturbation: Carrier Extraction/Recombination$$\mathrm{pn <n_{i}^2}$$
	1. Operation of diode in reverse direction
3. After switching off the distortion, the system returns to the equilibrium state ($\mathrm{pn=n_{i}^2}$)

### 2.7.1: Generation and Recombination Processes
![[Pasted image 20260217022946.png]]

<span style="color:rgb(255, 0, 0)"> Band-to-band R-G</span>
1.  "Only" involve electron in conduction band and hole in valence band

<span style="color:rgb(255, 0, 0)">R-G center generation/recombination</span>
1. Requires R-G center (lattice defects or impurity which generates states in the bandgap)

<span style="color:rgb(255, 0, 0)">Auger recombination</span>
1. Requires 3 carriers (either 2 holes and 1 electron, or vice versa)
2. All process occur at all time (even in equilibrium) with the process having the highest rate dominating

Momentum Considerations (Band-to-band vs R-G center R-G processes)
1. Photons carry energy but very little momentum; Phonons carry momentum but very little energy
	1. Photons are fundamental, massless particles of electromagnetic radiation (light)
	2. Phonons are quasiparticles that represent lattice vibrations (sound/heat)
2. In <span style="color:rgb(255, 0, 0)">indirect semiconductors</span>, band-to-band recombination requires the emission/absorption of a phonon in addition to photon emission, making this process negligible compared to R-G center recombination
3. In <span style="color:rgb(255, 0, 0)">direct semiconductors</span>, band-to-band recombination proceeds at a much faster rate, making these materials suitable for light emitting devices (LEDs and lasers)

Low-Level/High-Level Injection
1. Low-Level Injection
	1. $$\begin{align}
&\mathrm{\Delta n=\Delta p\ll N_{D}} \\ \\ 
&\mathrm{n_{n}=n_{n_{0}}+\Delta n \approx n_{n_{0}}} \\
&\mathrm{p_{n}=p_{n_{0}}+\Delta p \approx \Delta p<n_{n_{0}}}
\end{align}$$
2. High-Level Injection
	1. $$\begin{align}
&\mathrm{\Delta n=\Delta p\ge N_{D}} \\ \\ 
&\mathrm{n_{n}=n_{n_{0}}+\Delta n > n_{n_{0}}} \\
&\mathrm{p_{n}=p_{n_{0}}+\Delta p \approx \Delta p>n_{n_{0}}}
\end{align}$$
![[Pasted image 20260217025115.png]]
![[Pasted image 20260217025138.png]]

### 2.7.2: R-G Statistics

Band-to-Band Recombination
1. Likely in direct semiconductors, such as GaAs
2. Unlikely in indirect semiconductors, such as Si (b/c of required momentum conservation)
3. At thermal equilibrium: the thermal generation rate $\mathrm{G_{th}}$ equals the recombination rate $\mathrm{R_{th}}$
4. At non-equilibrium, the change in minority carrier concentration is
	1. $$\mathrm{\frac{dp_{n}(t)}{dt}=G_{L}+G_{th}-R}$$
	2. Assuming steady state and low-level injection ($\mathrm{\Delta p,\ p_{n_{0}}\ll n_{n_{0}}}$): $$\mathrm{U=\beta n_{n_{0}}\Delta p=\frac{p_{n}-p_{n_{0}}}{\frac{1}{\beta n_{n_{0}}}}=\frac{p_{n}-p_{n_{0}}}{\tau_{p}}}$$
5. The minority carrier lifetime $\mathrm{\tau_{p}}$ controls the recombination "velocity" after the distortion is switched off
	1. ![[Pasted image 20260217030205.png]]

R-G Center Recombination
1. Dominant recombination process in indirect semiconductors, such as Si
2. Indirect recombination and generation of electron-hole pairs via localized energy states in the band gap, so called recombination centers or R-G centers
3. These centers are characterized by their energy $\mathrm{E_{t}}$ and their density $\mathrm{N_{t}}$
4. Minority carrier lifetimes:
	1. ![[Pasted image 20260217030409.png]]

### 2.7.3: Continuity Equations

Net change of carrier concentration due to currents and R/G
![[Pasted image 20260217030447.png]]

1-D Continuity Equations:
![[Pasted image 20260217030518.png]]

Sample Problems:
![[Pasted image 20260217030535.png]]