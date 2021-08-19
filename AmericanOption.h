//
// Created by MuYao Si on 2021-08-18.
//

#ifndef OPTIONEXACTPRICING_AMERICANOPTION_H
#define OPTIONEXACTPRICING_AMERICANOPTION_H

#include "Options.h"

using namespace std;

class AmeOption: public Options {
public:
    AmeOption();
    AmeOption(const AmeOption& source);
    AmeOption(const OptionParameter& source);
    AmeOption(const Type& optionType);

    virtual ~AmeOption();

    AmeOption& operator = (const AmeOption& source);

    double Price(double Strk);
    double Delta(double Strk) {return 0;}; // will add delta of American option later

    vector<double> Price(vector<double> Strk);
    vector<double> Delta(vector<double> Strk) {
        vector<double> result;
        return result;
    };// will add delta of American option later

    virtual void toggle();

private:
    double PricingCall(double Strk);
    double PricingPut(double Strk);
};


#endif //OPTIONEXACTPRICING_AMERICANOPTION_H
