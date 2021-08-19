//
// Created by MuYao Si on 2021-08-17.
//

#include "EuroOption.h"
#include "Options.h"
#include <cmath>
#include <iostream>

using namespace std;
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>
using namespace boost::math;




EuroOption::EuroOption() {}

EuroOption::EuroOption(const EuroOption &source) {
    option = source.option;
}

EuroOption::EuroOption(const OptionParameter &source){
    option = source;
}

EuroOption::EuroOption(const Type &optionType) {
    option.optionType = optionType;
}

EuroOption::~EuroOption() {}

EuroOption& EuroOption::operator=(const EuroOption &source){
    if (this == &source){
        return *this;
    } else {
        option = source.option;
        return *this;
    }
}


double EuroOption::PricingCall(double Strk) {
    double K = Strk;
    double d1;
    double d2;
    d1 = (log(option.S0/K) + (option.b + option.sig * option.sig /2) * option.T)/(option.sig * sqrt(option.T));
    d2 = (log(option.S0/K) + (option.b - option.sig * option.sig /2) * option.T)/(option.sig * sqrt(option.T));
    double tmpPrice;
    tmpPrice = option.S0 * exp((option.b - option.r) * option.T) * N(d1) - K * exp((-1) * option.r * option.T) * N(d2);
    return tmpPrice;
}

double EuroOption::PricingPut(double Strk) {
    double K = Strk;
    double d1;
    double d2;
    d1 = (log(option.S0/K) + (option.b + option.sig * option.sig /2) * option.T)/(option.sig * sqrt(option.T));
    d2 = (log(option.S0/K) + (option.b - option.sig * option.sig /2) * option.T)/(option.sig * sqrt(option.T));
    double tmpPrice;
    tmpPrice = K * exp((-1) * option.r * option.T) * N((-1) * d2) - option.S0 * exp((option.b - option.r) * option.T) * N((-1) * d1);
    return tmpPrice;
}

double EuroOption::Price(double Strk) {
    double tmpResult;
    if (option.optionType == 1)
    {
        tmpResult = PricingCall(Strk);
    } else {
        tmpResult = PricingPut(Strk);
    }
    return tmpResult;
}

double EuroOption::DeltaPut(double Strk) {
    double K = Strk;
    double d1;
    d1 = (log(option.S0/K) + (option.b + option.sig * option.sig /2) * option.T)/(option.sig * sqrt(option.T));
    return exp((option.b-option.r) * option.T) * (1 - N(d1));
}

double EuroOption::DeltaCall(double Strk) {
    double K = Strk;
    double d1;
    d1 = (log(option.S0/K) + (option.b + option.sig * option.sig /2) * option.T)/(option.sig * sqrt(option.T));
    return exp((option.b-option.r) * option.T) * N(d1);
}

double EuroOption::Delta(double Strk) {
    double tmpResult;
    if (option.optionType == 1)
    {
        tmpResult = DeltaCall(Strk);
    } else {
        tmpResult = DeltaPut(Strk);
    }
    return tmpResult;
}

void EuroOption::Parity(double Strk) {
    double K = Strk;
    double tmpResult;
    double result;
    if (option.optionType == 1)
    {
        tmpResult = PricingCall(Strk);
        result = tmpResult + K * exp((-1) * option.r * option.T) - option.S0;
        cout << "The price of a European put option is " << result << " by put-call parity." << endl;
    } else {
        tmpResult = PricingPut(Strk);
        result = tmpResult + option.S0 - K * exp((-1) * option.r * option.T);
        cout << "The price of a European call option is " << result << " by put-call parity." << endl;
    }
}

void EuroOption::Parity(double Strk, double anotherPrice) {
    double K = Strk;
    double tmpResult;
    double result;
    if (option.optionType == 1)
    {
        tmpResult = PricingCall(Strk);
        result = tmpResult + K * exp((-1) * option.r * option.T) - option.S0;
        cout << "The price of a European put option is " << result << " by put-call parity." << endl;
    } else {
        tmpResult = PricingPut(Strk);
        result = tmpResult + option.S0 - K * exp((-1) * option.r * option.T);
        cout << "The price of a European call option is " << result << " by put-call parity." << endl;
    }

    if (abs(result - anotherPrice) < 0.001) {
        cout << "Your answer satisfies the put-call parity." << endl;
    } else {
        cout << "Your answer does not satisfy the put-call parity." << endl;
    }
}

vector<double> EuroOption::Price(vector<double> Strk) {
    vector<double>::iterator iter;
    vector<double> result;
    for (iter = Strk.begin(); iter != Strk.end(); iter++){
        result.push_back(Price(*(iter)));
    }
    return result;
}

vector<double> EuroOption::Delta(vector<double> Strk) {
    vector<double>::iterator iter;
    vector<double> result;
    for (iter = Strk.begin(); iter != Strk.end(); iter++){
        result.push_back(Delta(*(iter)));
    }
    return result;
}

void EuroOption::toggle() {
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

vector<double> EuroOption::payOffVec(double Strk, vector<double> ST) {
    vector<double>::iterator iter;
    vector<double> result;
    for(iter = ST.begin(); iter != ST.end(); iter++){
        result.push_back(payoff(Strk, (*iter)));
    }
    return result;
}

