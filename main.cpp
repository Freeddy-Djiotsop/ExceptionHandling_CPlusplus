#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <exception>


class DimensionException: public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "\nFehler: Vektoren unterschiedlicher Dimension!\n";
    }
};


class DivisionException: public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "\nFehler: Division durch Null!\n";
    }
};

using namespace std;

class Vektor
{
	private:
		double* d;
		int n;

	public:
		Vektor(int i) : n(i) {
			d = new double[i];
			for(int i=0 ; i<n ; i++)
				d[i] = rand() % 100 / 10.0;
		}

		~Vektor() {
			delete[] d;
		}

		//Vektoren elementweise addieren
		Vektor& operator+=(const Vektor& v) {
			if(v.n != n)
                throw(DimensionException());

			for(int i=0 ; i<n ; i++)
				d[i] += v.d[i];

			return *this;
		}

		//Jedes Element des Vektors durch z teilen
		Vektor& operator/=(double z) {
			if(z == 0)
                throw(DivisionException());

			for(int i=0 ; i<n ; i++)
				d[i] /= z;

			return *this;
		}

	friend ostream& operator<<(ostream& os, const Vektor& v) {
		os << setprecision(1) << fixed;
		os << "(";
		for(int i=0; i<v.n; ++i) {
			os << v.d[i];
			if(i<v.n-1)
				os << ",  ";
		}
		os << ")";
		return os;
	}
};

int main() {
	srand(time(nullptr));
	Vektor v1(5);
	Vektor v2(5);
	Vektor v3(6);
	cout << "       v1: " << v1 << endl;
	cout << "       v2: " << v2 << endl;
	cout << "       v3: " << v3 << endl;


	try
	{
        v1 += v2;
        cout << " v1 += v2: " << v1 << endl;
	}catch(DimensionException e){cout<<e.what();}


	try
	{
        v3 /= 2.5;
        cout << "v3 /= 2.5: " << v3 << endl;
	}catch(DivisionException e){cout<<e.what();}


	try
	{
        v1 += v3;
        cout << " v1 += v3: " << v1 << endl;
	}catch(DimensionException e){cout<<e.what();}


	try
	{
        v3 /= 0.0;
        cout << "v3 /= 0.0: " << v3 << endl;
	}catch(DivisionException e){cout<<e.what();}




	return 0;
}
