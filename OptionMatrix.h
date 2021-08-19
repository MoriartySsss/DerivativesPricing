//
// Created by MuYao Si on 2021-08-17.
//

#ifndef OPTIONEXACTPRICING_OPTIONMATRIX_H
#define OPTIONEXACTPRICING_OPTIONMATRIX_H

#include "Options.h"
#include "EuroOption.h"
#include "AmericanOption.h"
#include <string>
#include <cassert>
#include <vector>
#include <variant>
#include <boost/variant.hpp>
using namespace std;

typedef vector<Options*> ParaMatrix;

enum resultType
{
    price = 0,
    delta = 1
};

template <resultType resultType>
class OptionMatrix {
private:
    ParaMatrix Mat;
public:
    OptionMatrix() {};
    OptionMatrix(const ParaMatrix& source):Mat(source) {};
    virtual ~OptionMatrix() {};

    vector<double> calculator(const vector<double>& Strk){
        if (Strk.size() != Mat.size()) {throw "Strike Price and the Parameter Matrix does not have the same length";}
        vector<double> tmp;
        switch(resultType)
        {
            case 0:
                for (int i = 0; i < Strk.size(); i++){
                    tmp.push_back((Mat[i])->Price(Strk[i]));
                }
                break;
            case 1:
                for (int i = 0; i < Strk.size(); i++){
                    tmp.push_back((Mat[i])->Delta(Strk[i]));
                }
                break;
        }
        return tmp;
    }
};


#endif //OPTIONEXACTPRICING_OPTIONMATRIX_H
