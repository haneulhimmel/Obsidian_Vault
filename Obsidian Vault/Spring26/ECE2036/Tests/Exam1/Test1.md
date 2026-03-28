# Topics on Exam 1
### Textbook Sections
1. Basic C++: Section 2.2 - 2.7
2. Basic Classes: Section 3.2 - 3.6, Section 9.21. - 9.2.2. (Separating Interface and Implementation)
3. Control Statements: Section 4.2, 4.4 - 4.13 (if, if/else, while)
					Section 5.2 - 5.5, 5.8 - 5.12 (for, do/while, switch)
4. Functions: Section 6.2 - 6.7, 6.9 - 6.11, 6.13, 6.18 - 6.20 
	(Global functions, cmath functions, argument coercion, variable scope, pass by value reference, recursion, program stack)
	1. Argument coercion: Feature of function prototypes by which the compiler implicitly converts the datatype of the argument passed during the function call to match the datatype in the definition of the function
		1. Argument promotion rules: lower data type maybe converted into a higher data but not vice versa
		2. ![[Pasted image 20260225001902.png]]
	2. Function prototype: Declaration that tells the compiler about a function's name, return type, and parameters before the actual definition -> no body just declaration (like in a header file)
	3. Variable scope
		1. Local scope: variable created inside a function belongs to the local scope that function -> can only be used in that function -> will throw an error if it is attempted to be reached outside the scope
		2. Global scope: variable created outside of a function -> are available from within any scope global and local
	4. Pass by Value: Normal function call where a copy of the variable is made of the one passed through the argument
	5. Pass by Reference: Any operation done to the pass in variable will be reflected in the calling function as well
		1. Syntax: 
		``` 
		void func(int & x) {
		x--;
		}
		```

### Other
1. Numerical errors, Welford's  Algorithm, Approximating e
	1. Numerical
		1. Overflow Error: Number being calculated becomes too large
			1. Could use int, long int, float, double -> but for exponential growth functions, it makes little difference
		2. Ex: recursive-factorial.cc and approximation of e^x
			1. Approximation of e^x in place of factorials, computer 1/n! from the previous term instead of directly using factorial function: $\mathrm{\frac{1}{n!}= \frac{1}{(n-1!)} \times\left( \frac{1}{n} \right)}$
		3. Precision Error
			1. Sometimes can be avoided by being clever about the order that perform operations in
			2. For example, a mean claculation can lose track of small xi values if the divisor is really large because of floating point; therefore,  running avg is better using smth like welford
	2. Welford's Algorithm
		1. Definition: $\mathrm{\mu_{k}=\mu_{k-1} + \frac{x_{k}-\mu_{k-1}}{k}}$ 
			1. Where $\mathrm{\mu_{k}}$ is the updated mean after k data points, $\mathrm{\mu_{k-1}}$ is the mean of the first k-1 data points, $\mathrm{x_{k}}$ is the new data point, and k is the total number of data points processed so far
		2. Calculation of the running average
	3. Approximating e
		1. Using the power series expansion of $\mathrm{e^x}$ : $\mathrm{e^x=1+x+\frac{x^2}{2!}+\frac{x^3}{3!}+\dots}$ $$\mathrm{e^x=\sum^{\infty}_{{n=0}}\frac{x^n}{n!}}$$
2. Complex numbers, Solving quadratic equation, RLC circuit
	1. Complex numbers
		1. Real and imaginary component
	2. Quadratic Equation
		1. Flag for comparison of whether the add/subtract was toggled to find the roots
		2. Case for when discriminant is 0 -> does not matter whether the flag is neg/pos
		3. Then different calculations and assignments based based on flags but incorporated checks for negative and positive discriminant for both
	3. RLC Circuit
		1. Total impedance = Z-Resistor + Z-Load + Z-Capacitor
		2. Omega = $\mathrm{2\pi f}$
		3. ![[Pasted image 20260225000927.png]]
		4. Current of RLC series AC circuit: $\mathrm{\frac{V_{0}}{Z_{total}}}$
3. Divide and conquer, FTF 
	1. Recursion as an Algorithm Design Strat
	2. Breaking down a complex large problem into manage small subproblems to combine solutions in a straightforward way
	3. Fast Fourier Transform -> Break down an O($\mathrm{n^2}$) operation to period functions (one focusing on even samples, the other on odd samples) G(n), H(n)