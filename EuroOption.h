//
// Created by MuYao Si on 2021-08-17.
//

#ifndef OPTIONEXACTPRICING_EUROOPTION_H
#define OPTIONEXACTPRICING_EUROOPTION_H

#include "Options.h"
#include <algorithm>

using namespace std;

class EuroOption: public Options{
protected:
    double PricingCall(double Strk);
    double PricingPut(double Strk);

    double DeltaPut(double Strk);
    double DeltaCall(double Strk);

public:
    EuroOption(); // Default constroptiouctor
    EuroOption(const EuroOption& source); // Copy constructor
    EuroOption(const OptionParameter& source);

    EuroOption(const Type& optionType); // Constructor with specific type

    virtual ~EuroOption();

    EuroOption& operator = (const EuroOption& source); // Assignment Operator

    // Option Price member function for computing option prices for a monotonically
    // increasing range of underlying value of  S
    double Price(double Strk);

    // the same but for option delta
    double Delta(double Strk);

    // Put-call parity checking
    //method1: calculate the call (or put) price for a corresponding put (or call) price
    void Parity(double Strk);

    //method2: check if a given set of put/call prices satisfy parity
    void Parity(double Strk, double anotherPrice);

    // Pricing in vector
    vector<double> Price(vector<double> Strk);

    // the same but for option delta
    vector<double> Delta(vector<double> Strk);

    void toggle();

    double payoff(double Strk, double ST){
        double tmp;
        switch(option.optionType){
            case 0:
                tmp = max(Strk - ST, 0.0);
                break;
            case 1:
                tmp = max(ST - Strk, 0.0);
                break;
        }
        return tmp;
    }

    vector<double> payOffVec(double Strk, vector<double> ST);
};


#endif //OPTIONEXACTPRICING_EUROOPTION_H
