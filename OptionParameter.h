//
// Created by MuYao Si on 2021-08-18.
//

#ifndef OPTIONEXACTPRICING_OPTIONPARAMETER_H
#define OPTIONEXACTPRICING_OPTIONPARAMETER_H


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum Type
{
    put = 0,
    call= 1
};

struct OptionParameter
{
    double T; // expiry time
    double sig; // volatility
    double r; // risk-free interest rate
    double S0; // current stock price
    double b;
    Type optionType; // Option Type (call or put)
    string assetName; // the underlying asset
    double payoff;

    vector<double> OptionVector ()
    {
        vector<double> v;
        v.push_back(T);
        v.push_back(sig);
        v.push_back(r);
        v.push_back(S0);
        v.push_back(b);
        return v;
    }
};

typedef OptionParameter OptionParameter;



#endif //OPTIONEXACTPRICING_OPTIONPARAMETER_H
