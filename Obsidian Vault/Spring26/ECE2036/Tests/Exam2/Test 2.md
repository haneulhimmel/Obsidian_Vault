
# Sample Exam Practice

### Question 1: Fill in the blanks

![[exam2_q1.png]]
1. Memory Leak
2. $\mathrm{8 \times 4 = 32}$ bytes
3. friend
4. Overloading
5. Class hierarchy diagram

### Question 2: Pointers

```
#include <iostream>
using namespace std;

/* 
Write a global function here that prompts the user to input non-negative integers one-by-one, and ends the input when a negative integer is entered, your function should return ‘void’ but report the number of integers entered and the sum of the input values back to the calling code using pass by reference implemented with pointers 
*/

void nonNeg(int* numInputs, int* sum) {
	int input;
	cout << "Enter a non-negative number: " << endl;
	cin >> input;
	*numInputs = *numInputs + 1;
	*sum = *sum + input;
	
	while (input >= 0) {
		cout << "Enter a non-negative number: " << endl;
		cin >> input;
		*numInputs = *numInputs + 1;
		*sum = *sum + input;
	}
}

// Alternative with do-while loop

void nonNeg(int* numInputs, int* sum) {
	int input;
	
	do {
		cout << "Enter a non-negative number: " << endl;
		cin >> input;
		*numInputs = *numInputs + 1;
		*sum = *sum + input;
	} 
	while (input >= 0);
}


int main()
{
	int numInputs, sum;
	
// Call your global function here using pointers to pass numInputs and sum by reference
	
	nonNeg(&numInputs, &sum);
	
cout << “The sum of the “ << numInputs << “ numbers entered is “ << sum << endl;

} // end of main()
```

### Question 3: Class Composition w/ Constructors and Destructors

Show the output of the following code, where TimeDate objects contain a Date object:

![[exam2_q3.png]]

### Question 4: Inheritance (ignore)

### Question 5: Operator Overloading

Given a complex number class with the below interface (Complex.h), write functions to overload the ‘=’ and '= =' operators to perform assignment of one complex number to another and to check if two complex numbers are equal. You can implement the functions either as member functions or as non-member functions but you must state which option you are implementing. Note that assignment would work for this class without overloading ‘=’, but you should still implement a full assignment operation where real and imaginary parts are explicitly copied from one complex number to another. Lastly, check for and avoid self assignment in your ‘=’ function, i.e. for the statement ‘c1 = c2;’, if c1 and c2 are equal, do not assign anything to the data members of c1.

```
Class Complex
{
public:
	double getReal() const;
	void setReal(double);
	double getImag() const;
	void setImage(double);
	// add your function prototypes here, if necessary
	
private:
	double real;
	double imag;
};

// add your function implementations here

// overloaded assignment operator
Complex& Complex::operator=(const Complex& other) {

}

// overloaded equal comparison operator
bool Complex::operator==(const Complex& other) {

}
```
