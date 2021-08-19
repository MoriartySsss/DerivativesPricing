//
// Created by MuYao Si on 2021-08-17.
//

#ifndef OPTIONEXACTPRICING_OPTIONS_H
#define OPTIONEXACTPRICING_OPTIONS_H

#include "OptionParameter.h"
#include <iostream>
#include <vector>
using namespace std;



class Options {
protected:
    OptionParameter option;
    double N(double x);
    double n(double x);
public:
    Options(); // Constructor
    Options(const Options& source); // Copy Constructor
    Options(const OptionParameter& source); // Copy Constructor

    virtual ~Options(); // Virtual Destructor

    vector<double> OptionVecCon() const; // Convert to vectors

    virtual void toggle(); // Change option type

    virtual double Price(double Strk)=0;
    virtual double Delta(double Strk)=0;

    virtual vector<double> Price(vector<double> Strk)=0;
    virtual vector<double> Delta(vector<double> Strk)=0;
};

#endif //OPTIONEXACTPRICING_OPTIONS_H
