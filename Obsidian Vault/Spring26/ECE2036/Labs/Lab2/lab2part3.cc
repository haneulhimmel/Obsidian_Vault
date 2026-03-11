#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
#include <numbers>
#include "complex.h"

using namespace std;

int main() {
    
    double R{0};
    double L{0};
    double C{0};
    double V{0};
    double f{0};

    cout << "Enter R, L, C, V, f: ";
    cin >> R >> L >> C >> V >> f;

    // Current = V/Z0 ; where Z0 = ZR + ZL + ZC
    Complex ZR;
    Complex ZL;
    Complex ZC;
    Complex Z;
    Complex V0;
    Complex current;
    const double PI = 3.14159265358979323846;
    double omega = 2.0 * PI * f;
    if (omega == 0) {
        cout << "Divide by 0 Error";
        exit;
    }
    double circuitCurrent;

    ZR.setReal(R);
    ZL.setImag((omega * L));
    ZC.setImag((-1 / (omega * C)));
    V0.setReal(V);

    Z = ZL.add(ZC);
    Z = Z.add(ZR);
    current = V0.divide(Z);
    circuitCurrent = current.magnitude();

    cout << fixed << setprecision(5) << "current is " << circuitCurrent << endl;

}