#pragma once

#ifndef CLSMAINSCREEN_H
#define CLSMAINSCREEN_H

#include <iostream>
#include <string>
#include <cstdlib> // For system("clear")

#include "clsCurrecnyUI.h"
#include "clsCurrency.h"
#include "read.h"

using namespace std;

class clsMainScreen
{
private:
    enum _options
    {
        enCurrencyList = 1,
        enUpdateRate,
        enCurrencyConverter,
        enExit
    };

    static void _backMainMenu()
    {
        cout << "Press any key to return to the main menu..." << endl;
        system("pause > nul");
    }

    static void _displayMenu()
    {
        cout << "            Currency Exchange Application!            \n";
        cout << "---------------------------------------------\n";
        cout << "Please select an option:" << endl;
        cout << "1. View Currency List" << endl;
        cout << "2. Update Exchange Rates" << endl;
        cout << "3. Currency Converter" << endl;
        cout << "4. Exit" << endl;
        cout << "---------------------------------------------\n";
    }

    static void _showCurrencyList()
    {
        clsCurrencyUI::displayCurrencyList();
    }

    static void _updateExchangeRates()
    {
        clsCurrencyUI::updateCurrencyRateUI();
    }

    static void _openCurrencyConverter()
    {
        clsCurrencyUI::convertCurrencyUI();
    }

    static void _performUserAction(int action)
    {
        system("clear");

        switch (_options(action))
        {
        case enCurrencyList:
            _showCurrencyList();
            break;
        case enUpdateRate:
            _updateExchangeRates();
            break;
        case enCurrencyConverter:
            _openCurrencyConverter();
            break;
        case enExit:
            return; // Exit the application
        default:
            cout << "Invalid option selected." << endl;
        }

        _backMainMenu();
    }

public:
    static void run()
    {
        clsCurrency::loadCurrenciesFromFile(); // Load currencies from file at the start
        int userChoice = 0;

        while (true)
        {
            system("clear");
            _displayMenu();

            userChoice = read::numInRange<int>("\n\nPlease Enter Your Choice", 1, 4);

            if (userChoice == enExit)
            {
                cout << "Exiting the application. Goodbye!" << endl;
                break; // Exit the loop and end the program
            }

            _performUserAction(userChoice);
        }
    }
};

#endif // CLSMAINSCREEN_H