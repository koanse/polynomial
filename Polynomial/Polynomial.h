#include <iostream>

using namespace std;

class Polynomial
{
    public:
        //Constructors:
        Polynomial();
        Polynomial(int _n);
        Polynomial(int i_n, int i_k[], double i_ak[]);
        Polynomial(const Polynomial &source);

        //Default functions:
        void read();
		void Polynomial::readFromFile(std::fstream& fs);
        void print();
		void Polynomial::printToFile(std::fstream &fs);
        double valueAt(double x);
        void plot(double xleft, double xright);
        int terms();

        Polynomial derivative();
        Polynomial integral();
        double root(double xleft, double xright);

        Polynomial operator+(Polynomial other);
        Polynomial operator*(Polynomial other);
        Polynomial operator-(Polynomial other);
		Polynomial Polynomial::operator==(Polynomial other);
		bool Polynomial::operator<(Polynomial other);

        void sort();
        void process();

    private:
        int n;
        int *k; double *ak;
        double precision;
};
