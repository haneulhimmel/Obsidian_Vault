### The Bruker Pharmascan 7T features the following:
1. 7T superconducting magnet, with a bore of 160 mm
2. Gradient system (i.d. 90 mm). The maximum Gradient strength is 300 mT/m
3. RF resonator (i.d. 38 mm) optimized for the study of small rodents
4. RF resonator (i.d. 60 mm) for the study of larger objects
5. Several Transmit/Receive Surface coil for the study of small areas on large objects
6. Animal beds and anesthesia unit
7. Animal monitoring system

### Basic Info
1. Tesla is a unit representing the magnetic flux density (1 weber per square meter (Wb/m²))
2. 1T=10,000G (Gauss)
3. Active Shielding -> Extra coils built into the MRI magnet itself (Generate a secondary magnetic field opposite the main field outside the bore)
4. Magnetic Types
	1. Permanent Magnets -> Ferromagnetic Material (natural): No power needed, but weaker induced fields (<= 1T) -> Low-field MRI Scanners
	2. Electromagnets -> Coil of wire with a current passed through producing a magnetic field 
		1. Can reach a few tesla; field can be switched on/off
	3. Superconducting Magnets -> Use superconducting coils cooled with liquid helium to near absolute zero
		1. Can reach 7 T or higher (some research systems go above 10 T)
		2. Strong and stable field
		3. Actively Shielding -> because of higher level fields so it becomes more needed in contrast to electromagnets
	4. Hybrid Magnets -> Combined effort of electromagnets and superconducting magnets
		1. Higher T fields
		2. Mainly research
5. Earth’s field ≈ 0.5 G = 0.00005 T
6. 7 T MRI bore = 70,000 G
7. Field decays quickly — roughly 1/r³, typical for MRI fringe fields
	1. $\mathrm{B\ \alpha\ \frac{1}{r^3}}$
8. Hall Effect
	1. The Hall effect is the production of a voltage difference (Hall voltage) across an electrical conductor, transverse to an electric current and a perpendicular magnetic field. Discovered by Edwin Hall in 1879, it occurs because the magnetic field exerts a Lorentz force on moving charge carriers, deflecting them to one side and creating a measurable charge imbalance.
	2. ![[Hall_Effect.png]]
	3. ![[Hall_lorentz_force.png]]
	4. ![[Hall_Effect_RelationtoMRI.png]]
9. MRI Dipole Behavior
	1. ![[Dipole_Representation.png]]
	2. MRI Magnet -> Long solenoid

---
<div style="page-break-after: always;"></div> 
# Measuring the Shielding Effect Approach

## **Step 1: Prepare Equipment**

2. **Gaussmeter/Teslameter** with a Hall probe.
3. **Tape measure or laser distance meter**.
4. **Notebook or spreadsheet** to log readings.
5. **Safety gear** (if required by lab).

**Calibration:**

- Turn on the gaussmeter.
- Zero it **away from the MRI**, where the field is negligible (~Earth’s field).

---
## **Step 2: Choose Measurement Line**

- Decide a straight line **from the center of the MRI bore outward**.
- Mark distances along this line: e.g., 0.5 m, 1 m, 1.5 m, … until beyond expected 5-Gauss line.

---
## **Step 3: Orient the Probe**

- Hall probes measure the **component of the field along the probe axis**.
- Align the probe with the **main field direction** (usually along bore axis).
- Keep it **steady** during measurement.

---
## **Step 4: Take Measurements**

At each marked distance:
1. Place the probe.
    
2. Read the **B-field value in Gauss or Tesla**.
    
3. Record the value with **distance from bore**.
    
4. Repeat **2–3 times** for consistency.
    

Example log:

|Distance (m)|B (G)|
|---|---|
|0.5|850|
|1.0|220|
|1.5|70|
|2.0|25|
|2.5|10|
|3.0|4|

---
## **Step 5: Plot & Interpret**

1. **Plot B vs distance** to see how the field drops off.
2. **Check the 5-Gauss line**:
    
    - Find distance where **B ≈ 5 G**.
        
    - This is the **safety boundary**.
        
3. **Optional: Log-log plot**:
    
    - Plot `log(B)` vs `log(distance)` to see if decay is roughly ∝ 1/r³.
        
    - Confirms the MRI acts like a **magnetic dipole outside the shield**.
        
4. If the lab has shielding:
    
    - Sudden drops in B indicate **shielding effectiveness**.
        
    - Irregular patterns can show field redirection by steel walls.
        

---
## **Step 6: Document Findings**

- Include **distance, B-field values, plots**.
- Note **probe orientation** and any nearby **ferromagnetic objects**.
- Describe:
    
    - **Fringe field behavior**
        
    - **Distance to 5-Gauss line**
        
    - **Any shielding effects observed**
### **How to measure from the side**

1. Pick a **straight radial line away from the bore**.
    
    - Example: mark distances 0.5 m, 1 m, 1.5 m from the bore wall along the side.
        
2. At each distance, **hold the probe steady**.
    
    - If you have a 3-axis probe → just take the total B-field.
        
    - If not → rotate the probe to find **the maximum reading**.
        
3. Record the field value at each distance.

![[IMG_0200.jpg]]
![[IMG_0201.jpg]]
![[ECE3025- MRI Measurements.pdf]]