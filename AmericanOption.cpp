//
// Created by MuYao Si on 2021-08-18.
//

#include "AmericanOption.h"


AmeOption::AmeOption() {}

AmeOption::AmeOption(const AmeOption& source){
    option = source.option;
}

AmeOption::AmeOption(const OptionParameter &source){
    option = source;
}

AmeOption::AmeOption(const Type& optionType) {
    option.optionType = optionType;
}

AmeOption::~AmeOption() {}

AmeOption &AmeOption::operator=(const AmeOption& source) {
    if (this == &source) {
        return *this;
    } else {
        option = source.option;
        return *this;
    }
}

double AmeOption::PricingCall(double Strk) {
    double tmp1 = option.b / pow(option.sig, 2) - 0.5;
    double y1 = -tmp1 + sqrt(pow(tmp1, 2) + 2.0 * option.r / pow(option.sig, 2));
    double tmp2 = ((y1 - 1.0) * option.S0) / (y1 * Strk);
    double c = Strk * pow(tmp2, y1) / (y1 - 1.0);
    return c;
}

double AmeOption::PricingPut(double Strk) {
    double tmp1 = option.b / pow(option.sig, 2) - 0.5;
    double y2 = -tmp1 - sqrt(pow(tmp1, 2) + 2.0 * option.r / pow(option.sig, 2));
    double tmp2 = ((y2 - 1.0) * option.S0) / (y2 * Strk);
    double c = Strk * pow(tmp2, y2) / (1.0 - y2);
    return c;
}

double AmeOption::Price(double Strk) {
    double result;
    switch (option.optionType)
    {
        case 0:
            result = PricingPut(Strk);
            break;
        case 1:
            result = PricingCall(Strk);
            break;
    }
    return result;
}

vector<double> AmeOption::Price(vector<double> Strk) {
    vector<double> result;
    vector<double>::iterator iter;
    for(iter = Strk.begin(); iter != Strk.end(); iter++){
        result.push_back(Price(*iter));
    }
    return result;
}

void AmeOption::toggle() {
    switch(option.optionType)
    {
        case 0:
            option.optionType = Type(1);
            break;
        case 1:
            option.optionType = Type(0);
            break;
    }
}


