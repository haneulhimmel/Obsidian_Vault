[[ECE3025 Intro - Review]]
- Coordinate Systems and Applications
	i. Cartesian Coordinates (x, y, z)
	+ Calculation from Origin to Point (x, y, z) $$\vec{r} = x\hat{a}_{{x}}\ +\ y\hat{a}_{y}\ +\ z\hat{a}_{z}$$
	+ Between 2 Points $$\vec{A} = \vec{r}_{2}\ -\ \vec{r}_{1} = (x_{{2}} - x_{1})\hat{a}_{x}\ +\ (y_{{2}} - y_{1})\hat{a}_{y}\ +\ (z_{{2}} - z_{1})\hat{a}_{z}$$
	+ Length of $\vec{A}$ $$|\vec{A}| = \sqrt{{A_{x}}^2 + {A_{y}}^2 + {A_{z}}^2} = \sqrt{ (x_{2} - x_{{1}})^2 +\ (y_{2} - y_{{1}})^2 +\ (z_{2} - z_{{1}})^2}$$
	+ Unit Vector $$\hat{a}_{A} = \frac{\hat{A}}{|\hat{A}|}$$
	+ Example of Vector Quantities
		1. Velocity: $\overrightarrow{V}$
		2. Electric Field: $\overrightarrow{E}$ 
		3. Magnetic Field: $\overrightarrow{B}$
		
	- Vector Properties (*Dot Product returns a scalar; Cross returns a vector)
		1. Additive
		2. Scalar Multiplication
		3. Dot Product
		4. Vector Projection: $\overrightarrow{A}\cdot{\hat{a}_{{B}}} \rightarrow$ Project of a along b
		5. Orthogonality
		6. Cross Product
		
	ii. Curvilinear
	- General Curvilinear Coordinates -> [Schaun's Outline Mathematical Handbook]
		- 
		- $h_{1}, h_{2}, h_{3}$ are scale factors; $\hat{a_{1}}, \hat{a_{2}}, \hat{a_{3}}$ are unit vectors of the curvilinear coordinate (are orthogonal)$$h_{1}^{2} = (\frac{\partial{x}}{u_{{1}}})^{2} + \frac{\partial{y}}{u_{{1}}})^{2} + \frac{\partial{z}}{u_{{1}}})^{2}$$
		- Differential Elements$$d \overrightarrow{r} = h_{1}u_{1}\hat{a_{1}} + h_{2}u_{2}\hat{a_{2}} + h_{3}u_{3}\hat{a_{3}}$$
		- Gradient $$\nabla \phi = \frac{1}{h_{1}} \frac{\partial{\phi}}{\partial{u_{1}}} + \frac{1}{h_{2}} \frac{\partial{\phi}}{\partial{u_{2}}} + \frac{1}{h_{3}} \frac{\partial{\phi}}{\partial{u_{3}}}$$
		- Divergence $$\nabla \cdot{\overrightarrow{A}} = \frac{1}{h_{1}h_{2}h_{3}} [\frac{\partial}{\partial{u_{1}}}(h_{2}h_{3}A_{1}) + \frac{\partial}{\partial{u_{2}}}(h_{1}h_{3}A_{2}) + \frac{\partial}{\partial{u_{3}}}(h_{2}h_{1}A)3]$$
		- Curl $$\nabla \times {\overrightarrow{A}} = \frac{1}{h_{1}h_{2}h_{3}}\ \begin{vmatrix}
h_{1}\hat{a_{1}} & h_{2}\hat{a_{2}} & h_{3}\hat{a_{3}} \\

\end{vmatrix}$$
			* $\nabla^{2}\phi = 0$ : Laplace's Equation
			
	iii. Cylindrical
	- Example of Cylindrical -> Coaxial Cable ($Inner Radius, Outer Radius, V_{inner}, V_{outer}$)
		- Capacitance per Unit Length $$V(\rho = a) = V^{+}\ \&\ V(\rho = b)$$
	- ($u_{1},u_{2},u_{3}$) -> $(\rho, \phi, z)$
		- $\rho$ is the distance from z
		- z is the axis of the cylinder through the center point of the smallest face
		- $\phi$ represents the angle around the z axis
		- $x = \rho \cos(\theta)$
		- $y = \rho \sin(\theta)$
		- $z=z$
	- Derivations (Based on the Curvilinear Definitions) -> Using above defined X, Y, Z
		- $$h_{\rho} = (\frac{\partial{x}}{\partial{\rho}})^{2} + (\frac{\partial{y}}{\partial{\rho}})^{2} + (\frac{\partial{z}}{\partial{\rho}})^{2} = (\cos\phi)^{2} + (\sin\phi)^{2} = 1$$
		- $$h_{\phi} = (\frac{\partial{x}}{\partial{\phi}})^{2} + (\frac{\partial{y}}{\partial{\phi}})^{2} + (\frac{\partial{z}}{\partial{\phi}})^{2} = (-\rho \sin\phi)^{2} + (\rho\cos\phi)^{2} + 0^2 = \rho^{2}$$
		-  $$h_{z} = (\frac{\partial{x}}{\partial{z}})^{2} + (\frac{\partial{y}}{\partial{z}})^{2} + (\frac{\partial{z}}{\partial{z}})^{2} = 1$$
		- Differential Elements $$d\overrightarrow{r} = \hat{a_{\rho}}d\rho + \rho d\phi \hat{a}_{\phi} + dz \hat{a_{z}} = h_{1}du_{1}\hat{a_{1}} +  h_{2}du_{2}\hat{a_{2}} + h_{3}du_{3}\hat{a_{3}}$$
		- Note on Unit Vectors: 
			1. $\hat{a_{\rho}} = \cos\phi\hat{a_{x}} + \sin\phi\hat{a_{y}}$
			2. $\hat{a_{\phi}} = -\sin \phi \hat{a_{x}} + \cos \phi \hat{a_{y}}$
			3. $\hat{a_{z}} = \hat{a_{z}}$
			
		- Examples
			1. $\overrightarrow{B} = y\hat{a_{x}} - x \hat{a_{y}} + z\hat{a_{z}}$ ; Find $\rho$-component
				- First find x-component: $\overrightarrow{B}\cdot{\hat{a_{x}}} = y$
				- $\therefore \rho$-component = $\overrightarrow{B}\cdot{\hat{a_{\rho}}}$
	
	iii. Spherical
	- General: ($r, \theta, \phi$)
		- $x=r\sin \theta \cos \phi$
		- $y=r\sin \theta \sin \phi$
		- $z = r\cos \theta$ -> A particle between two plates, the z-axis would be defined to be between the plates
		- $h_{r} = 1, h_{\theta} = r, h_{{\phi}} = r\sin \theta$
		- $\hat{a_{r}} = \sin \theta \cos \phi  \hat{a_{x}} + \sin \theta \sin \phi  \hat{a_{y}} + \cos \theta  \hat{a_{z}}$
		- $\hat{{a_{{\theta}}}} = r\cos \theta \cos \phi + r\cos \theta \sin \phi-r\sin \theta$
	- Differential Length Element
		- $d\overrightarrow{l} = dr\hat{a_{r}} + rd\theta + r\sin \theta d\phi$
