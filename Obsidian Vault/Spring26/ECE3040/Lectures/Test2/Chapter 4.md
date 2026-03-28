
# 4.1: BJT - Overview

![[Chapter41_BJT_Basics_v2.pdf]]

### 4.1.1: BJT - Structure & Fabrication

1. Definition: Bipolar Junction Transistor
	1. Bipolar: Electrons and holes are involved within the conduction process -> polarity (charges)
	2. Junction: 2 coupled pn-junctions with a joint base region
	3. Transistor: Action requires that the base width W is much smaller than the minority carrier diffusion length L in the base$$\mathrm{W \ll L=\sqrt{ D\tau }}$$
### 4.1.2: BJT - Symbols and Schematic
1. PNP: Simpler to explain and understand
	1. ![[PNP.png| 200 x 100]]![[pnp_schematic.png| 200 x 100]]
	2. $\mathrm{N_{A,E}\gg N_{D,B}>N_{A,C}}$
2. NPN: More common in device applications because of the larger mobility of the minority carriers (electrons) in the base
	1. ![[NPN.png | 200 x 100]]![[NPN_Schematic.png | 200 x 100]]
	2. $\mathrm{N_{D,E}\gg N_{A,B}>N_{D,C}}$
3. Dictating Current/Voltage Formulas
	1. $\mathrm{I_{E}=I_{B} + I_{C}}$
	2. $\mathrm{V_{EB}+V_{BC}+V_{CE}=0}$ with $\mathrm{V_{ab}=-V_{ba}}$
		1. First subscript represent the (+) terminal and the following represents the (-) terminal
4. Modes of Operation
	1. ![[Pasted image 20260324160952.png | 200]] $\mathrm{*}$ [[pierret-1996.pdf#page=100]] for Detailed Graph

### 4.1.3: BJT - Basic Operation (Walkthroughs with PNP)
1. Equilibrium 
	1. Doping: $\mathrm{N_{A,E}\gg N_{D,B}>N_{A,C}}$
	2. Depletion Regions (DR):
		1. E-B Junction: DR mainly in B
		2. B-C Junction: DR mainly in C
	3. Fermi Level $\mathrm{E_{F}}$: Flat across BJT because of equilibrium
	4. Effective Base Width W: smaller than base width $\mathrm{W_{B}}$ because of depletion regions
	5. ![[Example_Relations.png | 200]]
2. Active Mode
	1. Assumption: PNP transistor in common-base configuration with forward-biased E-B junction and reverse-biased B-C junction
	2. In case $\mathrm{W\ll L_{B}}$, holes injected from the emitter into the base can diffuse across without recombination and are then swept into the collector
	3.  ![[PNP_Active.png| 300]]Hole Inject (Cutoff Term)
	4. Currents (Flow and Diagram)
		1. ![[PNP_Currents_I.png]]
		2. ![[PNP_Current_II.png| 300]]
	5. Common Base Current Gain
		1. Important Formulas![[CommonBase_Formulas.png]]
		2. Circuit Configurations ![[circuit_config.png]]
		3. Circuit Characteristic ![[circuit_characteristics.png]]
	6. Common Emitter Characteristics ![[emitter_circuit_characteristics.png]]


---
# 4.2: BJT - Static Analysis

![[Chapter42_BJT_Statics.pdf]]

### BJT: Ideal Static Analysis
1. Setup
	1. Goal: 
		1. Calculate BJT currents and transistor parameters $\mathrm{\alpha_{0}\, I_{CB_{0}}\, \beta_{0}}$
	2. Assumptions (Similar to pn-junction analysis)
		1. 1-D model with homogeneous doping ($\mathrm{N_{A}(x)=N_{D}(x) = const}$)
		2. Low-level injection
		3. No R-G currents in the depletion regions
		4. Non-degenerate doping (moderate level of impurities, where the dopant concentration is low enough that the Fermi level remains within the forbidden band gap), i.e. Boltzmann approximation is valid
		5. Depletion layer width $\mathrm{\ll}$ Base width
		6. No electric field outside the depletion regions
	3. Solution Approach (Similar to pn-junction analysis)
		1. Calculate carrier densities in quasineutral regions
		2. Calculate current densities at the edges of the depletion regions
2. Model
	1. ![[BJT_Model.png]]

### 4.2.1: Calculate Carrier Densities
1. Approach: Solve steady-state continuity equations in the quasi-neutral regions (no electric field, no carrier generation) of emitter, base, and collector
	1. ![[steady_states_carrierdensities.png]]
	2. ![[Carrier_densities.png]]
2. Carrier Density - Emitter
	1. Continuity Equation: ![[continuity_equation.png | 300]]
		1. General Solution: ![[continuity_equation_soln.png]]
	2. Boundary Conditions (ref [[Chapter 3 - PN-Junctions]]): ![[boundary_conds.png | 300]]
		1. Emitter Solution: ![[boundary_conds_emitter_soln.png | 300]]
3. Carrier Density - Collector
	1. Calculation similar to emitter
	2. Minority carrier distribution in quasi-neutral collector region
		1. ![[carrier_density_collector.png | 300]]
4. Carrier Density - Base
	1. Continuity Equation: ![[continuity_eq_base.png| 300]]
	2. Boundary Conditions: ![[boundary_cond_base.png | 300]]
	3. General Solution: ![[general_soln_base.png | 300]]
	4. Minority carrier distribution in the quasi-neutral base region: ![[carrier_dist_base.png]]

### 4.2.2: Calculate Current Densities (Assume PNP)
1. Approach: Calculate current densities at the edges of the depletion regions from the minority carrier distributions in the quasi-neutral regions, thus considering only carrier diffusion
	1. ![[calculate_current_densities.png| 300]]
2. Current Densities
	1. Electron current -> $\mathrm{J_{En}\ \&\ J_{Cn}}$: From current density equation for electrons, we can solve for the minority carrier (electrons) currents in emitter and collector at the edge of the depletion layer (x' = x" = 0)
		1. ![[current_density_jenjcn.png]]
	2. Hole current -> $\mathrm{J_{Ep}\ \&\ J_{Cp}}$: Calculated from the minority carrier current density in the base region (at the edges of the E-B and B-C depletion regions, x = 0 and x = W), assuming no R-G effects in the depletion region (no current changes across the DRs)
		1. ![[current_density_jepjcp.png]]
	3. BJT Currents
		1. With BJT cross-sectional area A and current densities listed above (the J's) ![[bjt_current.png | 300]]

### 4.2.3: Current Parameters
1. Emitter Efficiency: with $\mathrm{p_{B_{0}}=\frac{n_{i}^2}{N_{B}}}$ and $\mathrm{n_{E0}=\frac{n_{i}^2}{N_{E}}}$![[BJT_emitter_eff.png | 300]]
2. Base Transport Factor: 
	![[base_transport_fact_bjt.png | 300]]
3. Common Base Current Gain: ![[common_base_current_gain_bjt.png]]
4. Common Emitter Current Gain: ![[Common_emitter_currrent_gain_bjt.png]]

### 4.2.4: Small Base W $\mathrm{\ll L_{B}}$ Approx.
1. Minority carrier distribution in the base: with sinh(x) $\mathrm{\approx}$ x and cosh(x) $\mathrm{\approx 1+\frac{1}{2}x^2}$ for small x![[minority_carrier_dist_smallbase.png]]
	1. Minority carrier concentration in active mode decreases linearly across the base from the forward-biased E-B to the reverse-biased B-C junction
	2. Linear decrease in $\mathrm{p_{B}(x)}$ means $\mathrm{I_{Ep}=I_{Cp}}$ (very few minority carriers recombine while diffusing across the base; this is also expressed in a base transport factor close to 1)
2. Emitter Efficiency: $\mathrm{\gamma}$ becomes close to 1 if $\mathrm{N_{E}\gg N_{B}}$ ![[emitter_eff_smallbase.png]]
3. Base Transport Factor: $\mathrm{\alpha_{T}}$ becomes close to 1 if $\mathrm{L_{B}\gg W}$ ![[base_transport_factor_smallbase.png]]
4. Current Gains (neglecting higher order terms): ![[current_gains_smallbase.png]]
5. Currents (Assume Active mode: $\mathrm{V_{EB}>0,V_{CB}<0}$ -> F, R) ![[currents_smallbase_bjt.png]]

---
# 4.3: BJT - Models & Circuit Analysis

![[Chapter43_BJT_Models.pdf]]

### 4.3.1: DC Model: Ebers-Moll Model (Static Model for BJT) - Assume PNP
1. Current Equations
	1. ![[ebersmoll_current.png]]
2. Equivalent Circuit
	1. ![[ebersmoll_ckt.png]]

### 4.3.2: Small Signal Model
1. Generalized Two-Port Model: 
	1. (Working with NPN BJT in common emitter config.) ![[twoportmodel_npn.png]]
	2. DC voltages and currents: $\mathrm{I_{B},I_{C},V_{BE},V_{CE}}$
	3. Superimposed AC voltages and currents: $\mathrm{\overline{i_{b}}, \overline{i_{c}}, \overline{v_{be}}, \overline{v_{ce}}}$
		1. ![[superimposed_voltage_currrent.png]]
	4. Assumption: <span style="color:rgb(255, 0, 0)">Low frequency</span> (carrier distributions can follow the freq. -> no capacitance effects) -> unrealistic assumption; generally not fulfilled
		1. Found using the above superimposed voltage/current![[Assumptions.png]]
		2. Similarly, we solve for $\mathrm{i_{c}}$ ![[assumtpinos.png]]
		3. As a result we get a <span style="color:rgb(255, 0, 0)">general small signal equivalent circuit</span> ![[general_small_signal_circuit.png]]
		4. NPN -> The conductance ($\mathrm{g_{ij}}$) represent the physics behind the two-port model. For the case of the NPN BJT, they must be calculated from appropriate models for $I_{C}$ and $\mathrm{I_{B}}$ ![[conductance.png]] $\mathrm{* I_{C}}$ and $\mathrm{I_{B}}$ from e.g. static analysis of Chapter 4.2 -> [[Chapter 4]] 
		5. PNP -> Same thing as above but different case ![[PNP_twoportmodel.png]]
	5. Assumption: NPN transistor in active mode (F, R) -> How transistor is biased and behaves
		1. From Ebers-Moll model, we find: ![[ebersmoll_active_current.png| 300]]
		2. Using these characteristic equations, the conductance $\mathrm{g_{ij}}$ are calculated: Simplified![[conductance_active_twoportmodel.png]]
2. Hybrid-Pi Model
	1. Definition: Most frequently used model for performing BJT small signal analysis
		1. Hybrid: Combination of resistances and conductance
		2. Pi: $\mathrm{\pi}$-arrangement of elements
		3. Example of Breakdown 
			![[pimodel_breakdown.png | 300]]
		4. Equivalent circuits
			1. Simplified low-frequency
			2. Complete low-frequency
			3. High-frequency
	2. Simplified Hybrid-$\mathrm{\pi}$ Model
		1. Equivalent to two-port model "simplification" for active mode (section above)
			1. ![[simplified_hybridpi_model.png]]
		2. By comparison, one obtains for the input resistance $\mathrm{r_{\pi}}$ and the transconductance $\mathrm{g_{m}}$
			1. Note: $\mathrm{r_{\pi}}$ and $\mathrm{g_{m}}$ depend on the DC operating point: ![[input_resist_transconductance.png]]
	3. Complete Hybrid-$\mathrm{\pi}$ model
		1. Implementing base-width modulation (bwm) and allowing more precise analysis
			1. ![[complete_hybridpi_model.png |400]]
		2. Additional circuit components
			1. Output resistance $\mathrm{r_{0}}$
			2. Feedthrough resistance $\mathrm{r_{\mu}}$
		3. Circuit parameters can be related to two-port parameters
			1. ![[complete_jhybridpi_parameters.png]]
	4. High-Frequency Hybrid-$\mathrm{\pi}$ Model
		1. Model valid for frequencies up to about 500 MHz (at higher freq. delays in signal propagation have to be accounted for)
			1. ![[highfreq_hybridpi_model.png | 400]]
		2. Additional circuit components
			1. Parasitic series resistance: $\mathrm{r_{e}, r_{b}}$, and $\mathrm{r_{c}}$
			2. Junction capacitances: $\mathrm{C_{cb}, C_{eb}}$
				1. Reverse-biased C-B junction: $\mathrm{C_{cb}}$ is primarily junction C
				2. Forward-biased E-B junction: $\mathrm{C_{eb}}$ includes junction and diffusion C

### 4.3.3: DC Model: Transport Model
1. Overview
	1. Goal: Development of (simple) mathematical model describing the BJT I-V characteristic
	2. Assumption: NPN transistor with currents and voltages defined as above
	3. Model construction by superposition of currents ![[bjt_transportmodel.png]]
2. Forward Characteristic ($\mathrm{V_{BC}}=0$)
	1. Base-Emitter voltage $\mathrm{V_{BE}}$ establishes forward-current flow through emitter-base junction with two components:
		1. The larger component, the forward-transport current $\mathrm{I_{F}}$, consists of electrons injected into the base, diffusing across it and swept into the collector; this component constitutes the collector current $\mathrm{I_{C}}$
			1. $\mathrm{I_{C}=I_{F}=I_{S}}[e^{qV_{BE/kT}}-1]$
		2. The smaller current across the emitter base junction forms the base current $\mathrm{I_{B}}$ 
			1. $\mathrm{I_{B}=\frac{I_{F}}{\beta_{F}}=\frac{I_{S}}{\beta_{F}}[e^{qV_{BE}/kT}-1]}$
	
	2. Visual: ![[forward_characteristic_bjt.png| 400]]
	3. Using KCL, we calculate the emitter current $\mathrm{I_{E}=I_{C}+I_{B}}$
		1. $\mathrm{I_{E}=\left( I_{S}+\frac{I_{S}}{\beta _{F}} [e^{qV_{BE}/kT}-1] \right) = I_{S}\left( \frac{\beta_{F}+ 1}{\beta_{F}} [e^{qV_{BE}/kT}-1]\right)}$
			1. With the <span style="color:rgb(255, 0, 0)">forward common-base current gain</span> $\alpha_{F}$ 
				1. (typ. 0.95 $\mathrm{\le} \alpha_{F}$ $\le$ 1.0); $\mathrm{\alpha_{F}=\frac{\beta_{F}+1}{\beta_{F}}}$ ; $\mathrm{\beta_{F}=\frac{\alpha_{F}}{1-\alpha_{F}}}$
				2. Note: $\mathrm{\beta_{F}}$ is our previous common-emitter current gain $\mathrm{\beta_{0}}$; $\mathrm{\alpha_{F}}$ is our previous common-base current gain $\mathrm{\alpha_{0}}$
				3. We also find the following three relations: ![[Current_forwardcharacteristic.png | 400]]
3. Reverse Characteristic ($\mathrm{V_{BE} = 0}$)
	1. Base-collector voltage $\mathrm{V_{BC}}$ establishes forward-current flow through collector-base junction with two components
		1. ![[Visual.png | 400]]
	2. The larger component (reverse-transport current $\mathrm{I_{R}}$), consists of electrons injected into the base from the collector, diffusing across it and swept into the emitter (note: current flow is other way round); this component constitutes now the collector current $\mathrm{I_{E}}$
		1. $\mathrm{I_{E}=-I_{R}=-I_{S}[e^{qV_{BC/kT}}-1]}$
	3. The smaller current across the collector base junction forms again the base current $\mathrm{I_{B}}$
		1. $\mathrm{I_{B}=\frac{I_{R}}{\beta_{R}}=\frac{I_{S}}{\beta_{R}}[e^{qV_{BC/kT}}-1]}$
	4. Using KCL, we calculate the emitter current $\mathrm{I_{C}=I_{E}-I_{B}}$
		1. ![[current_derivation.png]]
	5. Super-positioning the solutions for the forward and reverse characteristics yields the complete Transport Model Equations
4. Transport Model Equations 
	1. for NPN BJT ![[Current_eqs_derivations.png]]
	2. for PNP BJT ![[PNP_transportmodeleqs.png]]
	3. Equivalent Circuit ![[eq_circuit_transportmodel.png]]
	4. Simplified Transport Model
		1. Cutoff Region: $\mathrm{V_{BE} \lt 0V\ and\ V_{BC}<0V}$
			1. ![[cuttoff_transportmodel.png]]
		2. Forward Active Region: $\mathrm{V_{BE} \gt 0V\ and\ V_{BC}\lt0V}$
			1. ![[forwardactive_transportmodel.png]]
		3. Reverse Active Region: $\mathrm{V_{BE} \lt 0V\ and\ V_{BC}\gt0V}$
			1. ![[ReverseAction_transportmodel.png]]
		4. Saturation Region: $\mathrm{V_{BE} \gt 0V\ and\ V_{BC}\gt0V}$
			1. ![[saturation_transportmodel.png]]

### 4.3.4: Single Transistor Amplifier Analysis
1. Overview - Walkthrough with BJT Common-Emitter Amplifier
	1. Goal: Perform AC and DC analysis of single transistor circuit
2. BJT - DC Analysis:
	1. Find equivalent circuit by replacing all capacitors with open circuits and inductors with short circuits
	2. Find the Q-point from the DC equivalent circuit using appropriate large-signal model for the transistor
	3. Circuit to DC for Analysis: Example![[Dc_representation.png | 400]]
	4. DC Analysis Walkthrough ![[dc_analysis.png]]
		1. Base-Bias Thevenin Equivalent
			1. ![[base-bias_thevenin_eq.png]]
		2. DC Analysis Walkthrough (cont.) ![[dc_analysis_calc_bjt.png]]
3. BJT - AC Analysis
	1. Find AC equivalent circuits: 
		1. Replacing all capacitors by short circuits and all inductors by open circuits
		2. Replacing DC voltage sources by ground connections
		3. Replacing DC current sources by open circuits
	2. Replace transistor by its small-signal model (hybrid-pi)
	3. Simplify the resulting AC circuit as much as possible
		1. Use Thevenin or Norton equivalent when necessary
	4. Circuit to AC for Analysis: Example ![[bjt_ac_analysis.png | 400]]
	5. AC Analysis Walkthrough
		1. Base-Bias Thevenin Equivalent ![[basebias_thevenin_bjt_acanalysis.png]]
		2. Transistor Equivalent Circuit 
			1. Part I: ![[transistor_equivalent_circuit_I.png]]
			2. Part II: ![[transistor_equivalent_circuit_II.png]]
			3. Part III: ![[transistor_equivalent_circuit_III.png]]
	6. Physic Component
		1. ![[physics_bjt.png]]