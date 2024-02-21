#include "complex.h"
#include "complex_sort.h"
void ComplexSort(Complex *arr,int length)
{
	int i,j;
	bool swapped;
	Complex tmp;
	for(int i = 0;i < length; ++i)
	{
		swapped = false;
		for(int j = i+1; j<length; ++j)
		{
			if(arr[i].Absolute() > arr[j].Absolute())
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				//swapped = true;
			}
		}
	//	if(!swapped)
			//break;
	}
}


