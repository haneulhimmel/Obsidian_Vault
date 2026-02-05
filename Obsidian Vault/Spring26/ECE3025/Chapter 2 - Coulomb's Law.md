
# Conceptual:

| ![[Charges Diagram.png]] | Permittivity of Free Space $=\varepsilon_{0}$ <br>Force on Q2$=\overrightarrow{F}_{2}$<br>$$=\frac{Q_{1}Q_{2}}{4\pi \varepsilon_{0}R_{12}^2} \hat{a}_{21}\ \rightarrow\ where\ \hat{a}_{21}=\frac{\overrightarrow{r}_{2} - \overrightarrow{r}_{1}}{\|\overrightarrow{r}_{2} - \overrightarrow{r}_{1}\|}$$<br>*$\varepsilon_{{0}} = \mathrm{vaccum} \approx 8.85\mathrm{\frac{pF}{\mu}}$*<br><br> |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
- Capacitance between 2 Plates: $C = \frac{\varepsilon_{{0}}A}{d}$, where d is the distance between the 2 plates and air is the medium
- Adheres to the inverse square: a specified physical quantity or intensity (light sound, gravity, or etc.) is inversely proportional to the square of the distance from the source
---
# Point Charge Mathematical Breakdown

### Electric Field Intensity Formula: 
 w/ $Q_{t}=$ the test charge$$\overrightarrow{E}=\frac{\overrightarrow{F_{t}}}{Q_{t}} =\frac{Q_{t}}{4\pi\varepsilon_{0}R_{1t}^2} \hat{a}_{t_{1}}$$
Use spherical b/c $r^2 \rightarrow$ radial distance: hence using cartesian cords. are much more complex
	1. In terms of Q1: $\overrightarrow{F} = \frac{Q_{1}Q_{t}}{4\pi\varepsilon_{0}R_{1t}^2} \hat{a}_{t1} \left.\vphantom{\begin{matrix}a\\b\end{matrix}}\right\}$ Pick the origin: charge location
	2. As a result $\hat{a}_{r}$ is created w/ the set above origin $\rightarrow \overrightarrow{E}=\frac{Q}{4\pi\varepsilon_{0}r^2} \hat{a}_{r}$

### Point Charge Approximation

Taking a charge as a to be a point charge to simplify calculations for forces and fields. The condition being: $|\overrightarrow{r}|$ = distance >> Physical size of charged particles = radius of charge, where >> requires 2 orders of magnitude

Ex: $a=10\mu m\left.\vphantom{\begin{matrix}a\\b\\c\end{matrix}}\right\}\begin{align}E(\overrightarrow{r}&=20\mu m)\neq cannot\ assume\ point\ charge\\E(\overrightarrow{r}&=1mm)= can\ assume\end{align}$

#### 2 Charges:
$$\overrightarrow{E}=\frac{Q_{1}}{4\pi\varepsilon_{0}|\overrightarrow{r}-\overrightarrow{r_{1}}|^2}\hat{a}_{1} + \frac{Q_{2}}{4\pi\varepsilon_{0}|\overrightarrow{r}-\overrightarrow{r_{2}}|^2}\hat{a}_{2}$$
where $\hat{a_{1}},\hat{a_{2}}$ (unit vector from $Q_{n}$ to observation point) are respectively: $\frac{\overrightarrow{r}-\overrightarrow{r_{1}}}{|\overrightarrow{r}-\overrightarrow{r_{1}}|}, \frac{\overrightarrow{r}-\overrightarrow{r_{2}}}{|\overrightarrow{r}-\overrightarrow{r_{2}}|}$

#### Generalized Number of Charges:
$$E(\tau)=\sum^N_{m=1} \frac{Q_{m}}{4\pi\varepsilon_{0} |\overrightarrow{r}-\overrightarrow{r_{m}}|^2}\hat{a_{m}},\ where\ \hat{a_{m} = \frac{\overrightarrow{r}-\overrightarrow{r}_{m}}{|\overrightarrow{r}-\overrightarrow{r}_{m}|}} $$
If linear (meaning far enough from dielectric breakdown), then superposition can be used

Some Assumptions for Equation:
- Field or charge cannot be too big $\rightarrow$ Would lead to dielectric breakdown (lightning) $\therefore$ superposition principle cannot be applied
	- "the total electric force or field acting on a point charge due to a system of multiple charges is the vector sum of the individual forces or fields, calculated as if each charge existed alone"
	- What is the threshold for large 
- Charges are independent of one another
- Coulomb is linear $\rightarrow$ Loops back to first point

#### With enough charges, a summation may not be enough:
$$\sum \rightarrow \int{\frac{Q_{m}}{4\pi\varepsilon_{0} |\overrightarrow{r}-\overrightarrow{r_{m}}|^2}\hat{a_{m}},\ where\ \hat{a_{m} = \frac{\overrightarrow{r}-\overrightarrow{r}_{m}}{|\overrightarrow{r}-\overrightarrow{r}_{m}|}}}$$ For approximation

---
# Line Charge Mathematical Breakdown
### Field Derivation

| Simple Line Diagram                  | What is it?                                                                                                                                                                                 | Simple Capacitor                         |
| ------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------- |
| ![[Pasted image 20260128121104.png]] | i) Bias -> Charge it<br>ii) Capacitor collects charge: Equal and Opposite on terminals<br><br>*For the most part: charge results in an electric field; current results in a magnetic field* | ![[Pasted image 20260128121518.png]]<br> |
The coordinate system for the line wire system is cylindrical since the wire itself is cylinder w/ a radial distance ($\rho$) around the center axis

| ![[Pasted image 20260128124712.png]]                                                                                                                        |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Figure 1. Represents the cylindrical shape of the wire w/ the chosen cylindrical coordinate system (fitting lol) and defined variables that will used later |

The red point indicates the **observation point** in which the calculation for the field is based upon. The value is set arbitrary, and the distance from the wire or the defined center of the wire's axis is known as the **radial distance** ($\rho$). $\rho$ is defined to be any distance away from the center point of the cylindrical wire (its a circle), hence the name radial distance.

### Derivation
$$\begin{gather}
\overrightarrow{E} = \int\frac{dQ}{4\pi\varepsilon_{0}|\vec{r}-\vec{r}'|^2}\hat{a}_{\vec{r}-\vec{r}'} \\  \\
dE_{-} + dE_{+} = dE \hat{a}_{\rho}\cos \theta = dE \hat{a}_{\rho}\frac{\rho}{\sqrt{ \rho^2+z^2 }}
\end{gather}$$
There 2 equations set the stage for solving for the electric field of the infinitely long wire -> requiring a process of simplifying and rearranging to solve the integral. We multiply the initial electric field formula by 2 to account for above and below the X-Y plane as we can see from figure 1. 

| $$\begin{align} \vec{E} = 2\int_{0}^{\infty} \frac{\rho_{L}dz}{4\pi\varepsilon_{0}\|\vec{r}-\vec{r}'\|}\hat{a}_{\rho} \\ \\ = 2 \int_{0}^{\infty} \frac{\rho_{L}\rho dz}{4\pi\varepsilon_{0}(\rho^2+z^2)^{3/2}} &= \frac{2\rho_{L}\rho}{4\pi\varepsilon_{0}} \int_{0}^{\infty} \frac{dz}{(\rho^2 + z^2)^{3/2}} \end{align}$$ | Substitute these values$$\begin{gather} &\|\vec{r}-\vec{r}'\| = \rho^2 + z^2\ \\ &\hat{a}_{\rho} = \frac{\rho}{(\rho^2+z^2)} \frac{1}{\sqrt{ \rho^2 + z^2 }} \end{gather}$$ |
| ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |

We substitute in $\mathrm{\hat{a}_{\rho}}$ with the above definition w/ cosine to get the 2 line of the above equation. From there, we take out the constants that are not the variable that is being integrated: in this case, z. Now, we can compute the integral w/ limits and algebra: getting the ==**final derivation of the electric field**==
$$\int_{0}^{\infty} \frac{dz}{(\rho^2 + z^2)^{3/2}} = \begin{equation} \left. \frac{z}{\rho^2\sqrt{ \rho^2+z^2 }} \right\vert_{0}^{\infty} \end{equation}$$
$$\begin{align} &\rightarrow \lim_{ z \to 0 } \frac{z}{\rho^2\sqrt{ \rho^2+z^2 }} = \lim_{ z \to 0 } \frac{z}{\rho^3}=\frac{0}{\rho^3}=0 \\ \\ &\rightarrow \lim_{ z \to \infty } \frac{z}{\rho^2\sqrt{ \rho^2+z^2 }} = \frac{1}{\rho^{2}} \lim_{ z \to \infty } \frac{z}{z} = \frac{1}{\rho^2} \end{align} \left.\vphantom{\begin{matrix}a\\b\\c\\d\\e\end{matrix}}\right\} \therefore \vec{E} = \frac{\rho_{L}\hat{a}_{\rho}}{2\pi\varepsilon_{0}} \cdot \frac{\rho}{\rho^2}=\frac{\rho_{L}  \hat{a}_{\rho}}{2\pi\varepsilon_{0}\rho}$$

### Assumptions

The main point of contingent is that the wire is assumed to an infinitely long: $L \gg \rho_{max}$
(where L is the length and $\rho$ is the radial distance). 

Based on the 1st assumption, it does not matter where xy-plane is defined; hence, we can pick easier points for solving. Simply, with the infinite length of wire, we can move the xy-plane up or down on the z-axis in this case, and our calculations won't change. 

### Recap

Point Charge: $\vec{E}\ \alpha\ \frac{1}{r^2}\hat{a}_{r}$

Line Charge: $\vec{E}\ \alpha\ \frac{1}{\rho}\hat{a}_{\rho}$

*where $\alpha$ means proportional to*