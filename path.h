//
// Created by MuYao Si on 2021-08-18.
//

#ifndef OPTIONEXACTPRICINGMONTECARLOPRICING_PATH_H
#define OPTIONEXACTPRICINGMONTECARLOPRICING_PATH_H

#include "Options.h"
#include "NormalDistribution.h"

class path{
protected:
    OptionParameter option;
public:
    vector<double> pathVec;
    path(const path& source):pathVec(source.pathVec), option(source.option){};
    path(const OptionParameter& source):option(source){};
    vector<vector<double>> pathSimulation(int NumOfSteps, int times);

private:
    double drift(double X) const;
    double diffusion(double X) const;
    double diffusionDerivative(double X) const;

};


#endif //OPTIONEXACTPRICINGMONTECARLOPRICING_PATH_H
