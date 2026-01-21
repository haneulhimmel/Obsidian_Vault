#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double factorial(int n) {
    if (n > 1) {
        return n * factorial(n - 1);
    } else return 1.0;
}

int main() {
    int num_terms;
    cout << "Enter the number of terms to evaluate: ";
    cin >> num_terms;

    // Method 1: x = 1
    double e1_approx = 1.0;
    for (int i = 1; i < num_terms; i++) {
        e1_approx += pow(1.0, i) * (1.0/(factorial(i-1))) * (1.0/i);
    }
    cout << fixed << setprecision(40) << "e is approximately: " << e1_approx << endl;

    // Method 2: x = 2 -> square root
    double e2_approx = 1.0;
    for (int j = 1; j < num_terms; j++) {
        e2_approx += pow(2.0, j) * (1.0/(factorial(j-1))) * (1.0/j);
    }

    cout << fixed << setprecision(40) << "e^2 is approximately: " << e2_approx << endl;
    
    e2_approx = sqrt(e2_approx);
    cout << fixed << setprecision(40) << "which gives e as approximately: " << e2_approx << endl;
}

