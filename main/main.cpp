#include<iostream>
#include"tset.h"
#include<ctime>

using namespace std;



int main()
{
	const int size = 30;
	TSet a(size), b(size), c(size);
	cout << "a = " << a << endl;
	cout << "MultipleNumber(5) = ";
	a.MultipleNumber(5);
	cout << endl;
	cout << "EvenElem = ";
	a.EvenElem();
	cout << endl;
	cout << "NotEvenElem = ";
	a.NotEvenElem();
	cout << endl;

	a = ~a;
	cout << "a = " << a << endl;
	cout << endl;
	for (int i = 1; i < size; i++)
	{
		cout << "MultipleNumber(" << i << ") = ";
		a.MultipleNumber(i);
		cout << endl;
	}
	cout << endl;
	cout << "EvenElem = ";
	a.EvenElem();
	b = a;
	cout << endl;
	cout << "NotEvenElem = ";
	a.NotEvenElem();
	cout << endl;
	c = a * b;
	cout << "EvenElem || NotEvenElem = " << c;
	return 0;
}