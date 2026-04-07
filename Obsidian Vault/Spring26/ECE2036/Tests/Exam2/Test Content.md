# ECE2036: Exam 2 Material

## Neural Networks
1. Lecture notes on Canvas
2. Lab 3: Write-Up and Code
3. ![[neural_nets_notes.pdf]]

---
## Pointers, Built-In Arrays, Dynamic Memory Allocation
1. Sec. 8.2 - 8.9
2. Sec 10.9 (Dynamic Memory)

### Built-In Arrays

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

### Pointers
Simple Syntax 
```
int n = 5;
int* p = &n;   // p holds the address of n

cout << n;     // prints 5       (the value)
cout << &n;    // prints 0x61ff08 (the address)
cout << p;     // prints 0x61ff08 (p stores the address)
cout << *p;    // prints 5       (go to address, get value)

*p = 99;       // go to address and CHANGE the value
cout << n;     // prints 99 — n was changed through the pointer!
```

### Dynamic Memory Allocation
1. Performed with operators **new** and **delete**
	1. The **new** operator can be used to dynamically allocate the exact of memory requirement to hold an object or built-in array at execution time
	2. The obj/built-in array is create in the free store (heap) - a region of memory assigned to each program for storing dynamically allocated objects
	3. The **delete** operator to deallocate (i.e. release) the memory, which can then be reused by future new operations

```
// Obtaining dynamic memory with new: allocates storage of the proper size for an object of type Time, calls a constructor to initialize the object and returns a pointer to the type specified to the right of the new operator (i.e. a Time *).
Time* timePtr{new Time};

// Releasing dynamic memory with delete: first calls the destructor for the obj to which timePtr points, then deallocates the memory associated with the obj, returning the memory to the free store.

delete timePtr;

// Initializing dynamic memory
// This initializes a newly created double to 3.14159 and assigns the returning pointer to ptr

double* ptr{new double{3.14159}};

// The same syntax can be used to specify arguments to an object's constructors
// This initializes a new Time object to 12:45 PM and assigns its pointer to timePtr

Time* timePtr{new Time{12, 45, 0}};

// Dynamically allocating built-in arrays with new[]
// A 10-element integer array can be allocated and assigned to gradesArray: declares int pointer gradesArray and assigns to it a pointer to the first element of a dynamically allocated 10-element array of ints

int* gradesArray{new int[10]{}};

// Releasing dynamically allocated built-in arrays with delete[]
// To dellocate the memory to which gradesArray points, use delete
// If the pointer points to a built-in array of objects, the statement first calls the destructor for every object in the array, then deallocates the memory

delete[] gradesArray;

// If the preceding statement did not include the square brackets ([]) and gradesArray pointed to a built-in array of objects, the result is undefined -> can lead to runtime logic errors
// Using delete or delete[] on a nullptr has no effect

C++11: unique_ptr is a smart pointer for managing dynamically allocated memory
```

---
## Classes - Miscellaneous Topics
1. Sec. 9.4 - 9.8, 9.10 - 9.15
2. Key Concepts
	1. Default constructors
	2. Destructors
	3. When constructors/destructors are called
	4. Class Composition
	5. Friend functions
	6. Static class members

A `friend` declaration lets an **outside function or class** access private and protected members, bypassing normal access rules.
1. Friendship is not inherited: if `main` is a friend of `Base`, it is NOT automatically a friend of `Derived`
2. Friendship is **not mutual** — if A is friends with B, B is not automatically friends with A
3. Breaks encapsulation

```
// Friend Example

class Base {
    friend int main();  // main() can access private/protected members
public:
    void calc(int n) { ... }
protected:
    static int k;
    int m;
};

// Now main() can directly access k and m even though they're protected
int main() {
    Base b;
    b.m = 5;      // normally illegal, but friend allows it
    b.k = 0;      // same here
}
```

A `static` member belongs to the class itself, not to any individual object. Every object shares the exact same copy.

```
class Base {
protected:
    static int k;  // ONE k shared across ALL Base objects
    int m;         // every object has its OWN m
};

int Base::k = 0;  // must be initialized OUTSIDE the class

Base b1, b2, b3;

// Each object has its OWN m:
b1.m = 1;
b2.m = 2;
b3.m = 3;   // all different

// But k is SHARED:
b1 increments k → k = 1
b2 increments k → k = 2
b3 increments k → k = 3  // all see the same k
```

Class Composition is when a class **contains objects of other classes as members** — essentially building complex classes out of simpler ones. It's a "**has-a**" relationship
1. Person does not inherit from Date, but rather has a `Data` object

```
class Date {
public:
    Date(int m, int d, int y) : month{m}, day{d}, year{y} {}
    int getMonth() const { return month; }
    int getDay()   const { return day; }
    int getYear()  const { return year; }
private:
    int month, day, year;
};

class Person {
public:
    Person(string n, int m, int d, int y) 
        : name{n}, birthday{m, d, y} {}  // Date object initialized here
private:
    string name;
    Date birthday;  // Person HAS-A Date
};
```
---
## Operator Overloading
1. Sec. 10.2 - 10.8, 10.10 - 10.11

