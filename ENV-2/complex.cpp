#include <iostream>
#include "complex.h"

Complex::Complex(): a(0),b(0) {}
Complex::Complex(int n1,int n2): a(n1),b(n2) {}
Complex::Complex(Complex& o)
{
	a = o.a;
	b = o.b;
}
void Complex::Print()
{
	if(b<0)
		std::cout << a << b << "i" << std::endl;
	else
		std::cout << a << "+" << b << "i" <<  std::endl;
}


Complex Complex::operator+(Complex const& o)
    {
       	Complex tmp;
        	tmp.a = a + o.a;
       		tmp.b = a + o.b;
        	return tmp;
    }

Complex Complex::operator-(Complex const& o)
    {
                Complex tmp;
                tmp.a = a - o.a;
                tmp.b = a - o.b;
                return tmp;
    }

Complex Complex::operator*(Complex const& o)
{
	Complex tmp;
	tmp.a = a*o.a+b*o.b;
	tmp.b = a*o.b+b*o.a;
	return tmp;
}

Complex Complex::operator*(int& n)
{
	Complex tmp;
        tmp.a *= n;
        tmp.b *= n;
	return tmp;
}

int Complex::Absolute()
{
	return a*a + b*b;
}



