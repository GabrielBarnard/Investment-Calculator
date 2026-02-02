/*
Created by Gabriel Barnard
Created on the 11th of November 2025
*/

// Code starts here //

#include "investment_calculator.h" //Imports the required header file.

#include <memory>
using namespace std;

int main() {
    auto calc = make_unique<InvestmentCalculator>(); //Creates the object calc
    
    //Neccessary functions to run the program
    calc->displayScreen();
    calc->calculate();
    calc->displayResults(0); //Excluding monthly deposits (0)
    calc->calculateWithMonthlyDeposits();
    calc->displayResults(1); //Including monthly deposits (1)
}