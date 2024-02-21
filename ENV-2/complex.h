#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

class Complex
{
	private:
		int a,b;
	public:
		Complex();
		Complex(int,int);
		Complex(Complex&);
		void Print();
		Complex operator+(const Complex&);
		Complex operator-(const Complex&);
		Complex operator*(int& n);
		Complex operator*(const Complex&);
		int Absolute();
};

#endif
