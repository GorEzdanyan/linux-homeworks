#include <iostream>
#include "complex.h"
#include "complex_sort.h"


int main()
{
	Complex arr[5] = {Complex(3,4), Complex(2,8), Complex(2,1), Complex(1,5),Complex(12,3)};
	std::cout << "Absolute values before sorting:" <<std::endl;;
	for(int i = 0;i<5;++i)
		std::cout << arr[i].Absolute() << " ";
	std::cout << std::endl;
	ComplexSort(arr,5);
	std::cout << "Absolute values after sorting:" << std::endl;
	for(int i = 0;i<5;++i)
		std::cout << arr[i].Absolute() << " ";
}
