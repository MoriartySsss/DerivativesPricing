//
// Created by MuYao Si on 2021-08-18.
//

#include "path.h"
#include <cmath>


double path::drift(double X) const {
    return (option.r) * X;
}

double path::diffusion(double X) const {
    double betaCEV = 1.0;
    return (option.sig) * pow(X, betaCEV);
}

double path::diffusionDerivative(double X) const {
    double betaCEV = 1.0;
    return 0.5 * (option.sig) * (betaCEV)*pow(X, 2.0 * betaCEV - 1.0);
}

vector<vector<double>> path::pathSimulation(int NumOfSteps, int times) {
    double deltaT = option.T / double(NumOfSteps);
    double sqrtDeltaT = sqrt(deltaT);
    NormalGenerator* normal = new BoostNormal();
    vector<vector<double>> history;
    vector<double> historyVec;
    vector<double> results;
    double dW;
    double VOld, VNew;
    for (long i = 1; i <= times; ++i)
    { // Calculate a path at each iteration

        if ((i / 10000) * 10000 == i)
        {// Give status after each 1000th iteration

            std::cout << (double(i)/double(times)) * 100 << "%" << std::endl;
        }

        VOld = option.S0;
        historyVec.clear();
        historyVec.push_back(VOld);
        for (unsigned long index = 1; index < NumOfSteps; ++index)
        {

            // Create a random number
            dW = normal->getNormal();

            // The FDM (in this case explicit Euler)
            VNew = VOld + (deltaT * drift(VOld))
                   + (sqrtDeltaT * diffusion(VOld) * dW);
            historyVec.push_back(VNew);
            VOld = VNew;
        }
        results.push_back(historyVec.back());
        history.push_back(historyVec);
        historyVec.clear();
    }
    pathVec = results;
    return history;
}




