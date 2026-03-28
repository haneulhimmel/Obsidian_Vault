# Tesla - RF Hardware Engineer

![[Pasted image 20260311054717.png]]
![[Interview.png]]
First Principles Thinking is a method of breaking down a problem into its most basic elements and then building up a solution from scratch. Instead of accepting existing knowledge as fact, this method challenges you to ask "why?" repeatedly until you reach foundational truths

### Technical
---
1. Filters
2. Analog Devices
	1. Passive Components
		1. Resistors
		2. Capacitors
		3. Inductors: Store energy in a magentic field
		4. Key concepts
			1. Impedance
			2. Reactance
			3. Frequency Response
		5. Important Equations
			1. $\mathrm{Z_{R}=R}$
			2. $\mathrm{Z_{C}=\frac{1}{j\omega C}}$
			3. $Z_{L}=j\omega L$
	2. Diodes: Essential for rectification
		1. Rectifier: A semiconductor component that converts alternating current (AC) to direct current (DC) by allowing current to flow in only one direction (forward bias) while blocking it in the opposite (reverse bias)
		2. Envelope Detectors: Used in AM radio receivers
		3. RF Mixer: Nonlinear devices enable frequency conversation
	3. Important Parameters:
		1. Forward voltage $\mathrm{V_{on}}$
		2. Reverse breakdown
		3. Junction capacitance (important at RF)
	4. BJT/MOSFET
		1. Common Emitter/Source
		2. Common Collector/Drain
		3. Common Base/Gate
	5. Opamps
		1. Amplifiers
			1. Inverting
			2. Non-inverting
		2. Filters
			1. Active filters
			2. Integrators
			3. Differentiators
3. Communications (Signal Processing)
	1. Fourier Analysis
		1. Any signal can be represented as sum of sinusoids
			1. $\mathrm{x(t)=\sum_{k=1}^{N} A_{k}\cos(\omega_{k}t+\phi_{k})}$
		2. Fourier Series/Transforms
			1. $\mathrm{x(t)\sum_{k=-\infty}^\infty a_{k}e^{j_{2}\pi kf_{0}t}}$
				1. Where kf0 represents integer multiples of fundamental frequency
				2. $\mathrm{\omega_{0}=2\pi f_{0}=\frac{2\pi}{T_{0}};\ T_{0}=\frac{1}{f_{0}}}$
			2. Fourier Series Synthesis
		3. Power Spectral Density
	2. Bandwidth: How much information can be transmitted
		1. B = $\mathrm{f_{high}-f_{low}}$
		2. Higher bandwidth -> Higher Data Rates
	3. Noise: Limits communication performance
		1. Thermal Noise: $\mathrm{P_{n}=kTB}$
			1. k = Boltzmann constant
			2. T = Temperature
			3. B = Bandwidth
		2. Shot Noise: Occurs in semiconductor devices
	4. Signal-to-Noise: Higher SNR (Signal-to-Nose Ratio) is better communication quality
		1. $\mathrm{SNR=\frac{P_{signal}}{P_{{noise}}}}$
4. Modulation Techniques
	1. Amplitude Modulation
		1. Carrier: $\mathrm{c(t)= A_{c}\cos (\omega_{c}t)}$ 
		2. AM Signal: $s(t)=\mathrm{v(t)\cos(\omega_{c}t)}$
			1. Where v(t) -> Modulating signal (voice or music), cos() -> Carrier Signal
	2. Frequency Modulation: Frequency varies with msg signal
		1. Carrier: $\mathrm{c(t)= A_{c}\cos (\omega_{c}t)}$ 
		2. FM Signal: s(t) = $\mathrm{\cos(\omega_{c}t+Hs(t)}$
			1. Where the modulating signal is the s(t), H is the range of frequency variation
	3. Phase Modulation (PM): Information encoded in carrier phase
5. RF Ckt Fundamentals
	1. Transmission Lines: At high frequencies, wires behave like transmission lines
		1. Parameters
			1. Characteristic Impedance $\mathrm{Z_{0}}$
			2. Reflection Coefficient 
			3. Standing Waves
		2. Reflection Coefficient
			1. $\Gamma=\frac{Z_{L}-Z_{0}}{Z_{L}+Z_{0}}$
			2. ![[Pasted image 20260311155706.png]]
	2. Impedance Matching: Mismatches cause reflections and power loss
		1. Definition: the practice of designing or adjusting the input/output impedance of an electrical circuit to equal the source or load impedance, typically to maximize power transfer or minimize signal reflection
		2. Common Technique
			1. L Networks: 
				1. An L-network in RF is a simple, two-element circuit (one inductor and one capacitor) used for impedance matching between a source and a load to maximize power transfer and minimize reflections
			2. Pi Networks: 
				1. An RF Pi network is a 3-element impedance-matching circuit consisting of two shunt (parallel) components and one series component, configured in a shape
			3. Quarter-Wave Transformers
				1. Match a load impedance with a transmission line in order to minimize reflections
		3. Goal: $\mathrm{Z_{L}=Z_{0}}$
	3. Resonant Circuits: Occurs when inductive and capacitive reactance cancel
		1. Resonant Frequency: $\mathrm{f_{0}=\frac{1}{2\pi \sqrt{ LC }}}$
			1. Used in filters, oscillators, and RF tuning circuits
	4. RF Amplifiers: Boost weak signals
		1. Types
			1. Low Noise Amplifier (LNA): First stage of receiver
			2. Power Amplifier: Drives antenna
		2. Important Metrics
			1. Gain 
			2. Noise Figure
			3. Linearity
			4. Efficiency
6. Antennas: Convert electrical signals $\leftrightarrow$ electromagnetic waves
	1. Basic Parameters
		1. Gain: Directional power amplification
		2. Radiation pattern: Spatial signal distribution
		3. Polarization: Orientation of EM waves
	2. Examples
		1. Dipole
		2. Patch antenna
		3. Parabolic dish

![[ECE3043 notes.pdf]]

### Behavioral
1. Why Tesla?
	1. Phone-as-Key (BLE + UWB integration) --> Mechanical Arm implements the same idea
		1. Bluetooth and Ultra-Wideband
			1. Instead of sending narrow radio signals like most wireless systems, UWB sends very short pulses spread across a very wide frequency range
			2. Very short pulses require many frequencies. This comes from a fundamental property of signals called the time–frequency tradeoff
	2. Optimus
	3. Communication with central vehicle computer
		1. Cameras
		2. Radar
		3. Sensors
		4. Driver inputs
		5. Vehicle diagnostics
	4. Wireless subsystems support:
		1. remote unlock
		2. climate control
		3. location tracking
		4. vehicle summon
		5. live status updates