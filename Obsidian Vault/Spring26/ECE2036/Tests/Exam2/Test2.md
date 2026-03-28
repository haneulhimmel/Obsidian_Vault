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

// Explicit initialization of a built-in array
int InitializationArr[5] = {3, -1, 7, 9, -12};

// Passing in C built-in array to a function
processArray(InitializationArr, 5);

// Use of pointer arithmetic on int array
int *arrP = InitializationArr;
cout << *arrP++ << " ";

// Use of pointer arithmetic on double array

```
