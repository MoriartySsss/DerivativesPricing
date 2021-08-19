#include <iostream>
#include "Options.h"
#include "EuroOption.h"
#include "OptionMatrix.h"
#include "AmericanOption.h"
#include "path.h"
#include "OptionParameter.h"
#include "NormalDistribution.h"


using namespace std;

double ave(const vector<double>& source){
    int size = source.size();
    double tmp = 0;
    for (int i = 0; i < size; ++i){
        tmp = tmp + ((source[i])/size);
    }
    return tmp;
}


int main() {
    // Test Data
    vector<double> strike({ 65, 100, 10, 100 });
    OptionParameter test1 = {0.25, 0.3, 0.08, 60, 0.08, call};
    EuroOption T1(test1);
    EuroOption *Batch1 = &T1;
    OptionParameter test2 = {1, 0.2, 0.0, 100, 0, call};
    EuroOption T2(test2);
    EuroOption *Batch2 = &T2;
    OptionParameter test3 = {1, 0.5, 0.12, 5, 0.12, call};
    EuroOption T3(test3);
    EuroOption *Batch3 = &T3;
    OptionParameter test4 = {30, 0.3, 0.08, 100, 0.08, call};
    EuroOption T4(test4);
    EuroOption *Batch4 = &T4;

    /*
    // Matrix 1 for prices of the options
    ParaMatrix matrix({Batch1, Batch2, Batch3, Batch4});
    OptionMatrix<price> result(matrix);
    vector<double> tmp = result.calculator(strike);
    for(int i=0; i<tmp.size(); ++i){
        cout << tmp[i] << endl;
    }

    cout << "##########################" << endl;
    // Convert the option type e.g. call => put
    Batch1->toggle();
    Batch2->toggle();
    Batch3->toggle();
    Batch4->toggle();

    // Matrix 2 for prices of the options
    ParaMatrix matrix2({Batch1, Batch2, Batch3, Batch4});
    OptionMatrix<price> result2(matrix2);
    vector<double> tmp2 = result2.calculator(strike);
    for(int i=0; i<tmp2.size(); ++i){
        cout << tmp2[i] << endl;
    }


    cout << "##########################" << endl;
    OptionParameter test5 = {0, 0.1, 0.1, 110, 0.02, call};
    AmeOption T5(test5);
    cout << T5.Price(100) << endl;
    AmeOption *Batch5 = &T5;
    vector<double> AmeStrike({100});
    ParaMatrix matrix3({Batch5});
    OptionMatrix<price> result3(matrix3);
    vector<double> tmp3 = result3.calculator(AmeStrike);
    for(int i=0; i<tmp3.size(); ++i){
        cout << tmp3[i] << endl;
    }
    print(tmp3);

     */
    cout << "##########################" << endl;
    path MC1(test1);
    MC1.pathSimulation(50, 20000);
    EuroOption EO;
    vector<double> tmpVec = EO.payOffVec(65,MC1.pathVec);
    double c = ave(tmpVec);
    cout << c << endl;

    return 0;
}

