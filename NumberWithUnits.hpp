#include <iostream>
#include <map>
#include <string>
using namespace std;
  
namespace ariel{
    class NumberWithUnits{

    private:
        double val;
        string unit;

    public:
        NumberWithUnits(double value, string type);

        double getValue() const{
            return val;
        };
        std::string getType() const{
            return unit;
        };

        ~NumberWithUnits(){}
        static void read_units(ifstream& units_file);
        static void print();


        /* Overloading the in/out stream operators */
        friend ostream& operator<<(ostream& os, const NumberWithUnits& n);
        friend istream& operator>>(istream& is, NumberWithUnits& n);

        /* Overloading the arithmetic operators */
        NumberWithUnits& operator+=(const NumberWithUnits& num);
        NumberWithUnits& operator-=(const NumberWithUnits& num);
        NumberWithUnits operator+(const NumberWithUnits& n2);
        NumberWithUnits operator-(const NumberWithUnits& n2);
        NumberWithUnits operator+();
        NumberWithUnits operator-();

        /* overlooading ++, -- operators */
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int n);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int n);
       

        /* Multiplication operations overiding */
        friend NumberWithUnits operator*(const NumberWithUnits& n,const double num) ;
        friend NumberWithUnits operator*(const double num, const NumberWithUnits& n) ;
        NumberWithUnits& operator*=(double num);
        
        /* Overloading the comparison operators */
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);
    };
}