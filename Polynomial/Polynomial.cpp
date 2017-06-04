#include "stdafx.h"
#include "polynomial.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>


vector<Polynomial> polyVector;


typedef std::pair<int, int> ipair;
std::list<ipair> thelist;



void loadListFromFile()
{
	thelist.sort([](const ipair & a, const ipair & b) { return a.first < b.first; });
	std::fstream fs;
	fs.open("import.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	
	int n;
	fs >> n;
	for (int i = 0; i < n; i++)
	{
		Polynomial p;
		p.readFromFile(fs);
		polyVector.push_back(p);
		p.print();
	}

	fs.close();
}

void saveListToFile()
{
	std::fstream fs;
	fs.open("list.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	for each (Polynomial p in polyVector)
	{
		p.printToFile(fs);
	}

	fs.close();
}


int main()
{
	Polynomial p1, p2, p3;
	std::string in;
	unsigned int i, index;
	double x, f;

	do
	{
		std::cout << "Available commands: exit, add, subtract, multiply, value, print, printall, push, remove, edit, sort, savetofile, readfromfile\n";
		std::cin >> in;

		if (in == "add")
		{
			std::cout << "A:\n";
			p1.read();
			p1.print();
			
			std::cout << "B:\n";
			p2.read();
			p2.print();

			p3 = p1 + p2;
			std::cout << "Result:\n";
			p3.print();
		}
		else if (in == "subtract")
		{
			std::cout << "A:\n";
			p1.read();
			p1.print();

			std::cout << "B:\n";
			p2.read();
			p2.print();

			p3 = p1 - p2;
			std::cout << "Result:\n";
			p3.print();
		}
		else if (in == "multiply")
		{
			std::cout << "A:\n";
			p1.read();
			p1.print();

			std::cout << "B:\n";
			p2.read();
			p2.print();

			p3 = p1 * p2;
			std::cout << "Result:\n";
			p3.print();
		}
		else if (in == "value")
		{
			std::cout << "A:\n";
			p1.read();
			p1.print();

			std::cout << "x:\n";
			std::cin >> x;
			f = p1.valueAt(x);
			std::cout << "f = " << f << ":\n";
		}
		else if (in == "print")
		{
			std::cout << "Index:\n";
			cin >> index;

			if (index < polyVector.size() && index >= 0)
			{
				polyVector[index].print();
			}
		}
		else if (in == "printall")
		{
			for (i = 0; i < polyVector.size(); i++)
			{
				std::cout << "i = " << i << ":\n";
				polyVector[i].print();
			}
		}
		else if (in == "push")
		{
			std::cout << "A:\n";
			p1.read();
			p1.print();

			std::cout << "A added\n";
			polyVector.push_back(p1);			
		}
		else if (in == "remove")
		{
			std::cout << "Index:\n";
			cin >> index;

			if (index < polyVector.size() && index >= 0)
			{
				std::cout << "Remove:\n";
				polyVector[index].print();
				polyVector.erase(polyVector.begin() + index);
			}
		}
		else if (in == "edit")
		{
			std::cout << "Index:\n";
			cin >> index;

			if (index < polyVector.size() && index >= 0)
			{
				polyVector[index].print();

				std::cout << "A:\n";
				p1.read();
				p1.print();
								
				polyVector[index] = p1;
				std::cout << "Edited\n";
			}
		}
		else if (in == "sort")
		{
			sort(polyVector.begin(), polyVector.end());
			std::cout << "Sorted:\n";
			
			for (i = 0; i < polyVector.size(); i++)
			{
				std::cout << "i = " << i << ":\n";
				polyVector[i].print();
			}
		}
		else if (in == "savetofile")
		{
			saveListToFile();
			std::cout << "Saved to list.txt\n";
		}
		else if (in == "readfromfile")
		{
			loadListFromFile();
			std::cout << "Loaded from import.txt\n";
		}


	} while (in != "exit");
	
    return 0;
}


Polynomial::Polynomial()
{
	n = 1;
}

Polynomial::Polynomial(int _n)
{
	n = _n;
	k = new int[n];
	ak = new double[n];
}

//Copy constructor
Polynomial::Polynomial(const Polynomial &source)
{
	n = source.n;
	ak = source.ak;
	k = source.k;
}

void Polynomial::read()
{
	std::cout << "n:\n";
	std::cin >> n;
	k = new int[n];
	ak = new double[n];

	for (int j = 0; j < n; j++)
	{
		std::cout << "k" << j << ", a" << j << ":\n";
		cin >> k[j] >> ak[j];
	}

}

void Polynomial::readFromFile(std::fstream& fs)
{
	fs >> n;
	k = new int[n];
	ak = new double[n];

	for (int j = 0; j < n; j++)
	{
		fs >> k[j] >> ak[j];
	}

}

int Polynomial::terms() { return n; }

Polynomial::Polynomial(int i_n, int i_k[], double i_ak[])
{
	n = i_n; k = i_k; ak = i_ak;
}

// Properly formatted print() function
void Polynomial::print()
{
	process();
	if (ak[0] != 0 && k[0] == 0) cout << ak[0];
	else if (ak[0] == 1 && k[0] != 0) cout << "x^" << k[0];
	else if (ak[0] == -1 && k[0] != 0) cout << "-x^" << k[0];
	else if (ak[0] == 0) { /*Do nothing*/ }
	else cout << ak[0] << "x^" << k[0];
	for (int q = 1; q < n; q++)
	{
		double _ak = (ak[q]);
		int _k = (k[q]);
		if (_ak != 1 && _ak != -1)
		{
			if (_ak > 0)
			{
				if (_k != 1) cout << " + " << _ak << "x^" << _k;
				else cout << " + " << _ak << "x";
			}
			else if (_ak == 0) {}
			else {
				if (_k != 1) cout << _ak << "x^" << _k;
				else cout << _ak << "x";
			}
		}
		else
		{
			if (_ak > 0) {
				if (_k != 1) cout << " + " << "x^" << _k;
				else cout << " + " << "x";
			}
			else {
				if (_k != 1) cout << " - " << "x^" << _k;
				else cout << " - " << "x";
			}
		}

	}
	cout << endl;
}

// Properly formatted print() function
void Polynomial::printToFile(std::fstream& fs)
{
	process();
	if (ak[0] != 0 && k[0] == 0) fs << ak[0];
	else if (ak[0] == 1 && k[0] != 0) fs << "x^" << k[0];
	else if (ak[0] == -1 && k[0] != 0) fs << "-x^" << k[0];
	else if (ak[0] == 0) { /*Do nothing*/ }
	else fs << ak[0] << "x^" << k[0];
	for (int q = 1; q < n; q++)
	{
		double _ak = (ak[q]);
		int _k = (k[q]);
		if (_ak != 1 && _ak != -1)
		{
			if (_ak > 0)
			{
				if (_k != 1) fs << " + " << _ak << "x^" << _k;
				else fs << " + " << _ak << "x";
			}
			else if (_ak == 0) {}
			else {
				if (_k != 1) fs << _ak << "x^" << _k;
				else fs << _ak << "x";
			}
		}
		else
		{
			if (_ak > 0) {
				if (_k != 1) fs << " + " << "x^" << _k;
				else fs << " + " << "x";
			}
			else {
				if (_k != 1) fs << " - " << "x^" << _k;
				else fs << " - " << "x";
			}
		}

	}
	fs << endl;
}

double Polynomial::valueAt(double x)
{
	double sum = 0;
	for (int j = 0; j < n; j++)
	{
		sum = sum + ((ak[j]) * pow(x, k[j]));
	}

	return sum;
}

Polynomial Polynomial::operator+(Polynomial other)
{
	int *new_k = new int[n + other.n];
	double *new_ak = new double[n + other.n];


	for (int j = 0; j < other.terms(); j++)
	{
		new_k[j] = other.k[j];
		new_ak[j] = other.ak[j];
	}

	for (int j = 0; j < n; j++)
	{
		new_k[j + other.n] = k[j];
		new_ak[j + other.n] = ak[j];
	}

	Polynomial tr(n + other.n);
	tr.ak = new_ak;
	tr.k = new_k;
	tr.process();
	return tr;
}

Polynomial Polynomial::operator-(Polynomial other)
{
	int *new_k = new int[n + other.n];
	double *new_ak = new double[n + other.n];


	for (int j = 0; j < other.terms(); j++)
	{
		new_k[j] = other.k[j];
		new_ak[j] = (-1) * other.ak[j];
	}

	for (int j = 0; j < n; j++)
	{
		new_k[j + other.n] = k[j];
		new_ak[j + other.n] = ak[j];
	}

	Polynomial tr(n + other.n);
	tr.ak = new_ak;
	tr.k = new_k;
	tr.process();
	return tr;
}

//SORTING ALGORITHM
void Polynomial::sort()
{
	int temp;
	double dtemp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (k[i] > k[j])
			{
				temp = k[i];
				k[i] = k[j];
				k[j] = temp;
				dtemp = ak[i];
				ak[i] = ak[j];
				ak[j] = dtemp;
			}
		}
	}
}

void Polynomial::process()
{
	sort();
	double zeroes = 0, duplicates = 0;
	int temp, p = 0, nold = n;
	int *kt = new int[nold];
	double *akt = new double[nold];

	for (int i1 = 0; i1 < n - 1; i1++)
	{
		temp = k[i1];
		if (ak[i1] == 0) { zeroes++; continue; }
		for (int j1 = i1 + 1; j1 < n; j1++)
		{
			if (k[j1] == k[i1])
			{
				duplicates++; i1++;
			}
		}
	}	

	if ((duplicates) > 0)
	{

		kt = k; akt = ak;
		n = n - duplicates - zeroes;

		k = new int[n];
		ak = new double[n];

		for (int i1 = 0; i1 < nold; i1++)
		{
			temp = kt[i1];
			if (akt[i1] == 0) { i1++; }
			k[p] = kt[i1];
			ak[p] = akt[i1];
			for (int j1 = i1 + 1; j1 < nold; j1++)
			{
				if (kt[j1] == kt[i1]) { i1++; ak[p] += akt[i1]; }
			}
			p++;
		}
	}
}


Polynomial Polynomial::operator*(Polynomial other)
{
	int *new_k = new int[n * other.n];
	double *new_ak = new double[n * other.n];
	int p = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < other.n; j++)
		{
			new_k[p] = k[i] + other.k[j];
			new_ak[p] = ak[i] * other.ak[j];
			p++;
		}
	}

	Polynomial tr(n * other.n);
	tr.ak = new_ak;
	tr.k = new_k;
	return tr;
}

Polynomial Polynomial::operator==(Polynomial other)
{
	if (n != other.n)
	{
		return n - other.n;
	}
	
	for (int i = 0; i < n; i++)
	{
		if (k[i] != other.k[i] || ak[i] != other.ak[i])
		{
			return k[i] + ak[i] - k[i] - ak[i];
		}
	}
}

bool Polynomial::operator<(Polynomial other)
{
	return n < other.n;
}