#include "investment_calculator.h" 

#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

InvestmentCalculator::InvestmentCalculator():m_initialInvestmentAmount(0), m_monthlyDeposit(0), m_annualInterest(0), m_numberOfYears(0) {} 

//Initiates the investment calculator. No other functions are needed if this one is used.
void InvestmentCalculator::initiateInvestmentCalculator() {
    displayScreen();
    
    calculate();
    displayResults(false);
    calculateWithMonthlyDeposits();
    displayResults(true);
}

//Requests user input. Reduces redundant code caused by multiple questions.
void InvestmentCalculator::requestInput(double& t_inputVariable) { 
    cin >> t_inputVariable;
    if ((!cin) || (t_inputVariable < 0)) { 
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        cout << endl << "Input must be a number that isn't below 0" << endl;
        cout << "Input: ";

	requestInput(t_inputVariable);
    }
}

//Displays info to user
void InvestmentCalculator::displayScreen() { 
    cout << setw(40) << setfill('*') << "" << endl;
    cout << setw(14) << "" << " Data Input " << setw(14) << "" << endl;
    cout << setfill(' ');
    cout << "Initial Investment Amount: $";
    requestInput(m_initialInvestmentAmount); 
    cout << "Monthly Deposit: $";
    requestInput(m_monthlyDeposit);
    cout << "Annual Interest: %";
    requestInput(m_annualInterest);
    cout << "Number of years: ";
    requestInput(m_numberOfYears);

    char i;
    cout << "Press ENTER to continue" << endl;
    cin.get(i);
}

//Calculates investments without monthly deposits
void InvestmentCalculator::calculate() { 
    m_currentBalance = m_initialInvestmentAmount;
    m_data.resize(m_numberOfYears, vector<double>(3)); 

    //Compounds / Contributes each year 
    for (int i = 0; i < m_numberOfYears; i++) { 
        m_yearEndInterest = m_currentBalance * (m_annualInterest / 100);
        m_currentBalance += m_yearEndInterest;
        
        m_data[i][0] = (i+1); //i+1, since iteration 0 = year 1
        m_data[i][1] = m_currentBalance;
        m_data[i][2] = m_yearEndInterest;
    }
}

//Calculates investments with monthly deposits
void InvestmentCalculator::calculateWithMonthlyDeposits() { 
    m_currentBalance = m_initialInvestmentAmount;
    m_data.resize(m_numberOfYears, vector<double>(3)); 
	
    //Compounds / Contributes at the beginning of each month
    for (int i = 0; i < m_numberOfYears; i++) { 
        for (int j = 0; j < 12; j++) { 
            m_yearEndInterest = (m_currentBalance + (m_monthlyDeposit)) * ((m_annualInterest / 12) / 100);
            m_currentBalance += m_yearEndInterest + (m_monthlyDeposit);
            m_accumulatedInterest += m_yearEndInterest;
        }
        m_data[i][0] = (i+1); 
        m_data[i][1] = m_currentBalance;
        m_data[i][2] = (m_accumulatedInterest);
        m_accumulatedInterest = 0; 
    }
}

//Displays the results of calculations to the user
void InvestmentCalculator::displayResults(bool t_monthlyDeposits) {
    cout << '\n'; 
    if (!t_monthlyDeposits) { 
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
        cout << left << setw(25) << m_data[i][0] << setw(25) << fixed << setprecision(2) //setprecision(2) is used to keep the results consistent with real-world currenc
        << m_data[i][1] << setw(25) << m_data[i][2] << defaultfloat << endl;
    }
}   
