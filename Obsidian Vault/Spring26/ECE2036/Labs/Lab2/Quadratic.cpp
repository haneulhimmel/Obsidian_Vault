#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
#include "complex.h"

using namespace std;
int pos = 0;
int neg = 1;

Complex root(double a, double b, double c, int flag) {
    Complex result;
    double discriminant = pow(b, 2.0) - (4.0 * a * c);
    // Error Check
    if (a == 0) {
        cout << "Divide by 0 Error";
        exit;
    }

    if (discriminant == 0) {
        result.setImag(0.0);
        result.setReal(-b / (2.0 * a));
        return result;
    }

    if (flag == pos) {
        if (discriminant < 0) {
            result.setImag(sqrt(-discriminant) / (2.0 * a));
            result.setReal(-b / (2.0 * a));
        } else if (discriminant > 0) {
            result.setImag(0.0);
            result.setReal((-b + sqrt(discriminant)) /  (2.0 * a));
        }
    } else if (flag == neg) {
        if (discriminant < 0) {
            result.setImag(-sqrt(-discriminant) / (2.0 * a));
            result.setReal(-b / (2.0 * a));
        } else if (discriminant > 0) {
            result.setImag(0.0);
            result.setReal((-b - sqrt(discriminant)) /  (2.0 * a));
        }
    }
    return result;
}

int main() {
    
    int a{0};
    int b{0};
    int c{0};

    cout << "Enter a, b, c: ";
    cin >> a >> b >> c;

    Complex posSqRoot = root(a, b, c, pos);
    Complex negSqRoot = root(a, b, c, neg);

    cout << "roots are:\n ";
    posSqRoot.outputAsString();
    cout << endl;
    negSqRoot.outputAsString();
    cout << endl;
    
}