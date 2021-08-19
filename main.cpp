#include <iostream>
#include "Options.h"
#include "EuroOption.h"
#include "OptionMatrix.h"
#include "AmericanOption.h"
#include "path.h"
#include "OptionParameter.h"
#include "NormalDistribution.h"


using namespace std;

// Average Of A Vector (For Monte Carlo Simulation)
double ave(const vector<double>& source){
    int size = source.size();
    double tmp = 0;
    for (int i = 0; i < size; ++i){
        tmp = tmp + ((source[i])/size);
    }
    return tmp;
}


// Print Function for Options
void print(OptionParameter& source)
{
    vector<double> myList;
    myList = source.OptionVector();
    typename vector<double>::const_iterator i;
    cout << "T  , sig  , r  , S  , b  , type" << endl;
    cout << "[";
    for (i = myList.begin(); i != myList.end(); ++i)
    {
        std::cout << *i << " , ";
    }
    switch (source.optionType){
        case 1:
            cout << "Call Option";
        case 0:
            cout << "Put Option";
    }
    std::cout << "]\n";
}


void sampleTest(){
    //
    // Load Test Data
    //
    vector<double> strike({ 65, 100, 10, 100 });
    OptionParameter test1 = {0.25, 0.3, 0.08, 60, 0.08, call};
    print(test1);
    EuroOption T1(test1);
    EuroOption *Batch1 = &T1;
    OptionParameter test2 = {1, 0.2, 0.0, 100, 0, call};
    print(test2);
    EuroOption T2(test2);
    EuroOption *Batch2 = &T2;
    OptionParameter test3 = {1, 0.5, 0.12, 5, 0.12, call};
    print(test3);
    EuroOption T3(test3);
    EuroOption *Batch3 = &T3;
    OptionParameter test4 = {30, 0.3, 0.08, 100, 0.08, call};
    print(test4);
    EuroOption T4(test4);
    EuroOption *Batch4 = &T4;

    //
    // Matrix 1 for prices of the options
    //

    // ParaMatrix is a vector of pointers of options
    ParaMatrix matrix({Batch1, Batch2, Batch3, Batch4});
    // Construct the class to compute the prices, specify the result we want (we want price in this case)
    OptionMatrix<price> sampleResult1(matrix);
    vector<double> sampleTmp1 = sampleResult1.calculator(strike);
    // print the prices of the options
    cout << "The prices of the European call options we listed above:" << endl;
    for(int i=0; i<sampleTmp1.size(); ++i){
        cout << sampleTmp1[i] << " , ";
    }
    // Also, we can compute the delta of the sample options

    cout << "\n##########################" << endl;
    // Convert the option type e.g. call => put
    Batch1->toggle();
    Batch2->toggle();
    Batch3->toggle();
    Batch4->toggle();

    // Matrix 2 for prices of the options
    ParaMatrix matrix2({Batch1, Batch2, Batch3, Batch4});
    OptionMatrix<price> sampleResult2(matrix2);
    vector<double> sampleTmp2 = sampleResult2.calculator(strike);
    // print the prices of the options
    cout << "The prices of the European put options we listed above:" << endl;
    for(int i=0; i<sampleTmp2.size(); ++i){
        cout << sampleTmp2[i] << " , ";
    }


    cout << "\n##########################" << endl;
    OptionParameter test5 = {0, 0.1, 0.1, 110, 0.02, call};
    AmeOption T5(test5);
    cout << T5.Price(100) << endl;


    cout << "##########################" << endl;
    path MC1(test1);
    cout << "lets price a put European option" << endl;
    print(test1);
    cout << "The Strike price is " << 65 << endl;
    int NOS;
    cout << "the number of steps?" << endl;
    cin >> NOS;
    int NOSim;
    cout << "the number of simulations?" << endl;
    cin >> NOSim;
    MC1.pathSimulation(NOS, NOSim);
    vector<double> MCResVec = T1.payOffVec(65,MC1.pathVec);
    double MCResult = ave(MCResVec);
    cout << MCResult << endl;

};


int main() {
    sampleTest();
    return 0;
}

