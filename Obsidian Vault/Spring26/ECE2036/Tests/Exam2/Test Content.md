# ECE2036: Exam 2 Material

## Neural Networks
1. Lecture notes on Canvas
2. Lab 3: Write-Up and Code

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

---
## Operator Overloading
1. Sec. 10.2 - 10.8, 10.10 - 10.11

