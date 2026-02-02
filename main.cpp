/*
Created by Gabriel Barnard
Updated on the 2nd of February 2026
*/

// Code starts here //

#include "investment_calculator.h" 

#include <memory>
using namespace std;

int main() {
    auto calc = make_unique<InvestmentCalculator>(); //Creates the object calc
    
    calc->initiateInvestmentCalculator();
}
