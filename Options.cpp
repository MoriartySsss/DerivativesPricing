//
// Created by MuYao Si on 2021-08-17.
//

#include "Options.h"
#include <cmath>
#include <iostream>

using namespace std;
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>
using namespace boost::math;

Options::Options() {};

Options::Options(const Options& source)
{
    option = source.option;
}

Options::Options(const OptionParameter& source)
{
    option = source;
}

Options::~Options() {};

vector<double> Options::OptionVecCon() const
{
    vector<double> tmp;
    tmp.push_back(option.T);
    tmp.push_back(option.sig);
    tmp.push_back(option.r);
    tmp.push_back(option.S0);
    tmp.push_back(option.b);
    return tmp;
}


void Options::toggle() {
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

double Options::N(double x) {
    normal_distribution<> normalDistribution(0.0, 1.0);
    return cdf(normalDistribution, x);
}

double Options::n(double x) {
    normal_distribution<> normalDistribution(0.0, 1.0);
    return pdf(normalDistribution, x);
}

