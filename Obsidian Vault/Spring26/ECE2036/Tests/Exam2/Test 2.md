
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

---
# Built-In Arrays and Pointers

Function with array as a input parameter
```
void processArray(int *arr, const int numItems) {
	for(int i = 0; i < numItems; i++)
		arr[i] = arr[i] + 1;
		
		// Example of a print statement within for lowithout 	cout << " arrStatic[" << i << "] = " << arrStatic[i] << end
} 
```

Basic Array Knowledge
```
// built-in array w/o initialization
int noInitializationArr[5];

// Passing in C built-in array to a function
processArray(InitializationArr, 5);

// Use of pointer arithmetic on int array
// Explicit initialization of a built-in array
int InitializationArr[5] = {3, -1, 7, 9, -12};
int *arrP = InitializationArr;
cout << *arrP++ << " ";

// Use of pointer arithmetic on double array
double arrStaticDouble[] = {3.14159, 2.71828, 1.6180, -1.234, 632.9976};
double *darrP = arrStaticDouble;
cout << *darrP++ << " ";

// string as a built-in array of characters
char color[50] = "blue";
cout << "Outputting array color[], first as an array of char's and then as a
string\n";

// outputting string character by character
{
	int i=0;
	cout << " ";
	while (color[i] != '\0') {
		cout << color[i];
		i++;
	}
cout << endl;
}

//outputting string as a string
cout << " " << color << endl << endl;

// dynamic C built-in array with variable size and new to
// allocate space for the array
int size{7};
int * arrDynamic{new int[size]};
cout << "arrDynamic[] before calling processArray() function (no initialization):
\n";

for (int i=0; i < size; i++)
	cout << " arrDynamic[" << i << "] = " << arrDynamic[i] << endl;
cout << endl;

processArray(arrDynamic, size);

cout << "arrDynamic[] after calling processArray() function:\n";
for (int i=0; i < size; i++)
	cout << " arrDynamic[" << i << "] = " << arrDynamic[i] << endl;
cout << endl;

// free up space allocated for arrDynamic
delete [] arrDynamic;
```

# Constructor, Destructor Execution Timing and Order

# Class w/ Composition

# Operator Overloading