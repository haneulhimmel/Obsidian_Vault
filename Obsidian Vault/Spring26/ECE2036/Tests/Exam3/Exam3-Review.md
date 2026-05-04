# Old Content
---
### Exam 1 - [[Exam1-Review|Review]]
1. [[exam1_sample_solution.pdf|Practice Exam Solns.]]


### Exam 2 - [[Exam2-Review|Review]]
1. [[exam2_sample_solution.pdf|Practice Exam Solns.]]

---
# New Content
---
### Labs 4, 5 - Video Game
##### General: Display Object
```
void setup() {
// reset the LCD
pinMode(RESETLINE, OUTPUT);
digitalWrite(RESETLINE, 0);
delay(100);
digitalWrite(RESETLINE, 1);
delay(500);

// communicate with LCD at 9600 baud, using RX and TX pins on ESP32
DisplaySerial.begin(9600, SERIAL_8N1, RX, TX);

// clear LCD screen before starting
Display.gfx_Cls();

// Display initial rectangle
Display.gfx_RectangleFilled(X, Y, X+rectW, Y+rectH, PURPLE);
}
```

### Basic Inheritance - [[C++ How to Program, 10th Edition.pdf#page=540 |Section 11.2 - 11.4]]
##### General:
1. Base classes - more general overview classes
2. Derived classes - more specific classes
3. Inheritance relationships form the basis for a class hierarchy 

### Inheritance with Polymorphism - [[C++ How to Program, 10th Edition.pdf#page=573 |Chapter 12]]
##### General: 
1. Polymorphism operates on base-class pointer handles and base-class reference handles (not off name handlers)
2. Works hand-in-hand with inheritance -> Essentially derived classes (fundamentally dependent on inheritance) share a general function that can be overrode by the derived classes
```
// Base class  
class Animal {  
  public:  
    void animalSound() {  
      cout << "The animal makes a sound \n";  
    }  
};  
  
// Derived class  
class Pig : public Animal {  
  public:  
    void animalSound() {  
      cout << "The pig says: wee wee \n";  
    }  
};  
  
// Derived class  
class Dog : public Animal {  
  public:  
    void animalSound() {  
      cout << "The dog says: bow wow \n";  
    }  
};
```

### Template Functions, Classes - [[C++ How to Program, 10th Edition.pdf#page=825 |Section 18.2 - 18.3]]
##### General:
1. One of the main avenues of [generic programming](https://cplusplus.com/doc/oldtutorial/templates/) - Essentially, special functions that can operate with generic types (not hard locked)

##### Function Implementation
```
// Example finding max of inputed data
template <typename T>
T maximum(const T value1, const T value2, const T value3) {
	T maxVal{value1}; // Assume value1 as max for start
	
	// determine whether value2 is greater than maxVal
	if (value2 > maxVal) {
		maxVal = value2;
	}
	
	if (value3 > maxVal) {
		maxVal = value3;
	}
	
	return maxVal;
}
```

##### Class Implementation - [[C++ How to Program, 10th Edition.pdf#page=827 |Textbook Example]]
1. In-Class Example:
```
#include <string>
#include <iostream>
#include "stack.h"

using namespace std;

template<typename T>
Stack<T>::Stack(int maxElements):maxSize{(maxElements>0)?maxElements:100}
{
	topIndex = -1;
	arrPtr = new T[maxSize];
}

template<typename T>
Stack<T>::~Stack()
{
	delete [] arrPtr;
}
template<typename T>
void Stack<T>::push(const T & value) {
	if (!isFull()) {
		arrPtr[++topIndex] = value;
	}
	else cout << "Error: cannot push value - stack is full.";
}

template<typename T>
T Stack<T>::pop(bool & valid) {
	if (!isEmpty()) {
		valid = true;
		return arrPtr[topIndex--];
	}
	else {
		cout << "\nError: cannot pop value - stack is empty.";
		valid = false;
		T temp;
	return temp;
}

}
template<typename T>
int Stack<T>::getCurrSize() {
	return topIndex+1;
}

template<typename T>
bool Stack<T>::isEmpty() {
	if (topIndex == -1)
		return true;
	else return false;
}

template<typename T>
bool Stack<T>::isFull() {
	if (topIndex == maxSize-1)
		return true;
	else return false;
}
```

### Standard Template Library (STL)
##### Containers and Iterators: [[C++ How to Program, 10th Edition.pdf#page = 697|Chapter 15]]

##### Algorithms: [[C++ How to Program, 10th Edition.pdf#page = 748|Chapter 16]]
###### Lambda Expressions
1. Generally, many STL algorithms can receive function pointers as parameters (On function declaration, the name of the function is implicitly converted into a pointer to the function's body) - However, to implement this, the corresponding function must be declared.
2. Lambda expressions (lambdas) allow you to define anonymous function where they're passed to a function - defined locally inside functions and can use and manipulate the local variables of the enclosing function
3. General Lambda Layout: 
	1. Being with the lambda introducer ([]), followed by a parameter list and function body
	2. The introducer enables the programmer to specify which, if any, local variables the lambda uses - capturing the variables
4. Lambda with an Empty Introducer - empty lambda introducer ([]) indicates that the lambda does not use any of main's local variables
	1. Auto enables the compiler to infer the parameter's type based on the context as which the parameter appears
```
[](auto i) {count << i * 2 << " ";}
```

###### Algorithms to Know - [[C++ How to Program, 10th Edition.pdf#page=753 |Function Implementation]]
1. generate: assigns the result of a successive function calls to every element in a range (function template)
2. generate-n: same as [generate] but to only n elements, not every
3. replace: replaces all values satisfying specific criteria with another value
4. replace-if: replaces all values satisfying specific criteria with another value with a conditional (function template)
5. find: finds the first element satisfying specific criteria (searches for specific value) - (function template)
6. find-if: same as find but instead of specific value; searches for element that satisfies a logical condition (function template)
7. sort: sorts a range into ascending order (function template)
8. is-sorted: checks whether a range into sorted into ascending order (function template)
9. accumulate: sums up or folds a range of elements (function template)
10. transform algorithms: General - Applies a function to a range of elements, storing results in a destination range (function template)
	1. ![[Operations.png]]


---
# Exam 3 Sample

##### Problem 1
1. Implementation, interface, variables, functions, reference, value, data structures, **xxxx**, **xxxx**, **xxxx**
	1. Virtual function -> dynamic (run-time): The function to call is determined at run time. This is slightly slower but much more powerful and flexible for certain problems
		1. You need to write code that doesn't need to know the exact derived type it's operating on (the Open/Closed Principle) -> open for extension/closed for modification
	2. Regular polymorphism determines the function upon compile time
	3. Virtual vs. Template (Dynamic vs Static)
		1. Virtual is better for a list of heterogeneous inheritance class items; while template is better for exact types during compile
```
class Animal { public: void speak() { cout << "Animal sound" << endl; } };
class Dog : public Animal { public: void speak() { cout << "Woof!" << endl; } };

Animal* ptr = new Dog();
ptr->speak(); // Output: "Animal sound"  (NOT "Woof!")

// Virtual
#include <iostream>
#include <vector>

class Shape {
public:
    virtual void draw() const = 0; // Interface
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override { std::cout << "Drawing Circle\n"; }
};

class Square : public Shape {
public:
    void draw() const override { std::cout << "Drawing Square\n"; }
};

int main() {
    // A heterogeneous list: different shapes mixed together
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle());
    shapes.push_back(new Square());
    shapes.push_back(new Circle());

    // Runtime decides which draw() to call
    for (auto s : shapes) {
        s->draw(); // Works perfectly
    }
    
    // Cleanup omitted for brevity
}

// Template
#include <iostream>

class Circle {
public:
    void draw() const { std::cout << "Drawing Circle\n"; }
};

class Square {
public:
    void draw() const { std::cout << "Drawing Square\n"; }
};

// The template magic
template <typename T>
void drawShape(const T& shape) {
    shape.draw(); // Compiler checks that T has a .draw() method
}

int main() {
    Circle c;
    Square s;
    
    // Compiler generates two separate functions:
    // 1. drawShape<Circle>
    // 2. drawShape<Square>
    drawShape(c); 
    drawShape(s);
    
    // BUT: You cannot put Circles and Squares in the same array without a hack (like std::variant)
}
```
^ The compiler looks at the _type of the pointer_ (`Animal*`) and says, "Ah, this is an `Animal` pointer, so I'll call `Animal::speak()`." It doesn't care that the pointer actually points to a `Dog`. This is **not** polymorphic behavior. **Virtual functions solve this problem.**


##### Problem 2
1. F
2. T
3. T
4. T
5. T
6. T
7. T
	1. Iterators are objects that enable sequential traversal through a collection (like lists, sets, or arrays) without exposing its underlying structure
8. T
9. F
10. T

##### Problem 3: Basic Class Creation