#include <iostream>
#include <fstream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

const double EPS = 0.001;

namespace ariel{
    
    static map<string, map<string, double> > conversionMap;

    NumberWithUnits :: NumberWithUnits(double value, const string& type){
        conversionMap.at(type); // check if type found in the map.
        this->val=value;
        this->unit=type;
    }

    double conversion(double value, const string& from, const string& to){
        if(from == to) {return value;}
        if(conversionMap[from][to] == 0){
            throw invalid_argument{"Units do not match - ["+from+"] cannot be converted to ["+to+"]"};
        }
        return value * conversionMap[from][to];
    };


    void NumberWithUnits ::read_units(ifstream& units_file){
        double num1=0; 
        double num2=0;
        string unit1, unit2, eq;
        while(units_file >> num1 >> unit1 >> eq >> num2 >> unit2){

            conversionMap[unit1][unit2] = num2;
            conversionMap[unit2][unit1]= num1/num2;
            
            /* Update unit1 adjencies */
            for(auto &pair : conversionMap[unit1]) {
                double v = conversionMap[unit2][unit1] * pair.second;
                conversionMap[unit2][pair.first] = v;
                conversionMap[pair.first][unit2] = 1/v;
            }
            /* Update unit2 adjencies */
            for(auto &pair : conversionMap[unit2]) {
                double v = conversionMap[unit1][unit2] * pair.second;
                conversionMap[unit1][pair.first] = v;
                conversionMap[pair.first][unit1] = 1/v;
            }
        }
    }

     void NumberWithUnits :: print(){
        for(auto& unit1 : conversionMap){
            for (auto& unit2 : unit1.second){
               cout<< unit1.first << " " << unit2.first << " "<<unit2.second<< endl;
            }
        }
    }


    //-------------in\out stream operator-------------//
    ostream& operator<<(ostream& os, const NumberWithUnits& n){
        os << n.val << "[" << n.unit << "]";
        return os;
    }

    std::istream &operator>>(std::istream &is, NumberWithUnits &n) {
        double val=0;
        string type;
        char c='0';
        is >> val;
        is >> c ;
        while(c!=']'){
            if(c!='['){
                type.insert(type.end(),c);
            }
            is>>c;
        }
       if(conversionMap[type].empty()){throw invalid_argument{"unit doesnt exist"};};
        n.val=val;
        n.unit=type;
        return is;
    }

        
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &n) {
    this->val+= conversion(n.val, n.unit, this->unit);
    return *this;
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &n) {
    this->val-= conversion(n.val, n.unit, this->unit);
    return *this;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n2) {
        double convert = conversion(n2.val, n2.unit, this->unit);
        NumberWithUnits ans(this->val+convert, this->unit);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n2) {
        double convert = conversion(n2.val, n2.unit, this->unit);
        NumberWithUnits ans(this->val-convert, this->unit);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator+(){
        NumberWithUnits ans(+this->val , this->unit);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator-(){
         NumberWithUnits ans(-this->val, this->unit);
        return ans;
    }

    //------------Increament\Decreament operators-------//

    NumberWithUnits& NumberWithUnits::operator++(){
        ++(this->val);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int n){
        return NumberWithUnits((this->val)++, this->unit);
  
    }

    NumberWithUnits& NumberWithUnits::operator--(){
        --(this->val);
        return *this;
    }
    
    NumberWithUnits NumberWithUnits::operator--(int n){
        return NumberWithUnits((this->val)--, this->unit);
    }


    //----------Multiplication operators----------//

    NumberWithUnits operator*(const NumberWithUnits& n, const double num)  {
        return NumberWithUnits(n.val*num, n.unit);
    }
    NumberWithUnits operator*(const double num, const NumberWithUnits& n)  {
        return NumberWithUnits(n.val*num, n.unit);
    }
    NumberWithUnits& NumberWithUnits::operator*=(double num) {
        this->val*=num;
        return *this;
    }

    //------------boolean operators---------------//

    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return (n1.val > conversion(n2.val, n2.unit, n1.unit));
    }
    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return ((n1>n2) || (n1 == n2));
    }
    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return (n1.val < conversion(n2.val, n2.unit, n1.unit));
    }
    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return ((n1<n2) || (n1==n2));
    }
    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return (abs(n1.val- conversion(n2.val, n2.unit, n1.unit)) <= EPS);
    }
    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return !(n1==n2);
    }
}

