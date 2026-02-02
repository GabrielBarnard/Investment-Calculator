#include "investment_calculator.h" //Includes the header file

#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

InvestmentCalculator::InvestmentCalculator():m_initialInvestmentAmount(0), m_monthlyDeposit(0), m_annualInterest(0), m_numberOfYears(0) {} //Default values if nothing is inputted

void InvestmentCalculator::requestInput(double& t_variable) { //Void function requestInput. Takes double parameter t_variable. Outputs a cin statement for a specific variable, prevents users from inputting anything other than a integer or a double, or lower than a 0.
    cin >> t_variable; //Takes input for t_variable
    while ((!cin) || (t_variable < 0)) { //Checks if the input was invalid or if it was lower than a 0.
        cin.clear(); //Removes the error state.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Removes faulty input from the input. 

        cout << endl << "Input must be a number that isn't below 0" << endl;
        cout << "Input: ";

        cin >> t_variable;
    }
}

void InvestmentCalculator::displayScreen() { //Void function displayScreen. Displays data input requests in the console for initial investment amount, monthly deposit, annual interest, and number of years. 
    cout << setw(40) << setfill('*') << "" << endl;
    cout << setw(14) << "" << " Data Input " << setw(14) << "" << endl;
    cout << setfill(' ');
    cout << "Initial Investment Amount: $";
    requestInput(m_initialInvestmentAmount); //Calls the function requestInput instead of typing out all of the neccessary code here. Reduces redundant code.
    cout << "Monthly Deposit: $";
    requestInput(m_monthlyDeposit);
    cout << "Annual Interest: %";
    requestInput(m_annualInterest);
    cout << "Number of years: ";
    requestInput(m_numberOfYears);
    system("pause"); //WARNING: ONLY WORKS ON WINDOWS. Waits for the user to press any key.
}

void InvestmentCalculator::calculate() { //Void function calculate. Takes the values that were inputted in the displayScreen function and uses them to calculate various things, which are then stored in the 2D m_data vector. Does not account for monthly deposits.
    m_currentBalance = m_initialInvestmentAmount;
    m_data.resize(m_numberOfYears, vector<double>(3)); //Resizes the array to the user's specified number of years for the rows, and 3 for the columns

    for (int i = 0; i < m_numberOfYears; i++) { //Creates and stores values for a period specified by the user's specified number of years
        m_yearEndInterest = m_currentBalance * (m_annualInterest / 100);
        m_currentBalance += m_yearEndInterest;
        
        m_data[i][0] = (i+1); //i+1, since iteration 0 = year 1
        m_data[i][1] = m_currentBalance;
        m_data[i][2] = m_yearEndInterest;
    }
}

void InvestmentCalculator::calculateWithMonthlyDeposits() { //Void function calculateWithMonthlyDeposits. Takes the values that were inputted in the displayScreen function and uses them to calculate various things, which are then stored in the 2D m_data vector. Accounts for monthly deposits. Compounds MONTHLY.
    m_currentBalance = m_initialInvestmentAmount;
    m_data.resize(m_numberOfYears, vector<double>(3)); //Resizes the array to the user's specified number of years for the rows, and 3 for the columns

    for (int i = 0; i < m_numberOfYears; i++) { //Creates and stores values for a period specified by the user's specified number of years
        for (int j = 0; j < 12; j++) { //Calculates by the month for accuracy
            m_yearEndInterest = (m_currentBalance + (m_monthlyDeposit)) * ((m_annualInterest / 12) / 100);
            m_currentBalance += m_yearEndInterest + (m_monthlyDeposit);
            m_accumulatedInterest += m_yearEndInterest;
        }
        m_data[i][0] = (i+1); //i+1, since iteration 0 = year 1
        m_data[i][1] = m_currentBalance;
        m_data[i][2] = (m_accumulatedInterest);
        m_accumulatedInterest = 0; //Resets accumulated interest back to 0 to prevent the program from calculating the accumulated interest for all years. 
    }
}

void InvestmentCalculator::displayResults(bool t_monthlyDeposits) { //Void function displayResults. Takes the bool parameter t_monthlyDeposits. Displays the results from the calculations in a neat format.
    cout << '\n'; //A newline is added here to give space between the previous cout statements and the results.
    if (!t_monthlyDeposits) { //These if and else statements check if it is displaying the results for something with or without monthly deposits, as specified by the user by inputting 0 (no monthly deposits) or 1 (monthly deposits).
        cout << "\033[1mBalance and Interest Without Additional Monthly Deposits \033[0m" << endl; //033[1m makes the text bold. 033[0m unboldens it.
    } else {
        cout << "\033[1mBalance and Interest With Additional Monthly Deposits \033[0m" << endl; 
    }

    cout << setw(80) << setfill('=') << "" << endl;
    cout << setfill(' ');
    cout << left << setw(25) << "Year" << setw(25) << "Year End Balance" << setw(25) << "Year End Earned Interest" << endl; 
    cout << setw(80) << setfill('-') << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < m_data.size(); i++) { //Outputs all values in the m_data 2D array in the order year, year end balance, and year end earned interest.
        cout << left << setw(25) << m_data[i][0] << setw(25) << fixed << setprecision(2) //setprecision(2) is used to keep the results consistent with real-world currency, since you can't have a fraction of a cent.
        << m_data[i][1] << setw(25) << m_data[i][2] << defaultfloat << endl;
    }
}   