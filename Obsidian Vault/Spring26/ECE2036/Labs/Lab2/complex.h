class Complex
{
    public:
        Complex(); // default constructor, initialize to 0.0 + 0.0i
        Complex(double, double);
        double getReal() const;
        void setReal(double);
        double getImag() const;
        void setImag(double);
        Complex add(Complex) const; // add this complex num to complex parameter, return result
        Complex subtract(Complex) const; // this complex num minus complex parameter, return result
        Complex multiply(Complex) const; // multiply this complex num times complex parameter, return result
        Complex divide(Complex) const; // this complex num divided by complex parameter, return result
        Complex conjugate() const; // conjugate of a + bi is a - bi
        double norm() const; // a^2 + b^2
        double magnitude() const; // sqrt(a^2 + b^2)
        void outputAsString() const;
    private:
        double real;
        double imag;
    };