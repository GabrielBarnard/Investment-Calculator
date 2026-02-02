#ifndef AIRGEAD_BANKINGAPP_INVESTMENTCALCULATOR_H //Checks if this specific header file has been defined previously. If not, it defines it.
#define AIRGEAD_BANKINGAPP_INVESTMENTCALCULATOR_H

#include <vector>
using namespace std;

class InvestmentCalculator {
    public: //Accessible to everything which includes investment_calculator.h
        InvestmentCalculator(); //Function InvestmentCalculator is used to set InvestmentCalculator's default values
        void displayScreen();
        void requestInput(double& t_variable); 
        void calculate();
        void calculateWithMonthlyDeposits();
        void displayResults(bool t_monthlyDeposits);
    private: //Accessible to just the class
        double m_initialInvestmentAmount;
        double m_monthlyDeposit;
        double m_annualInterest;
        double m_numberOfYears;
        double m_currentBalance;
        double m_accumulatedInterest;
        double m_yearEndInterest; 
        vector<vector<double>> m_data; //2D Vector of doubles
};

#endif