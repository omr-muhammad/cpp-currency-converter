#pragma once

#ifndef CLSMAINSCREEN_H
#define CLSMAINSCREEN_H

#include <iostream>

using namespace std;

class clsMainScreen
{
private:
    enum options
    {
        enCurrencyList = 1,
        enUpdateRate,
        enCurrencyConverter,
        enExit
    };

    void _displayMenu()
    {
        cout << "Welcome to the Currency Exchange Application!" << endl;
        cout << "Please select an option:" << endl;
        cout << "1. View Currency List" << endl;
        cout << "2. Update Exchange Rates" << endl;
        cout << "3. Currency Converter" << endl;
        cout << "4. Exit" << endl;
    }

    void _showCurrencyList()
    {
        cout << "Displaying available currencies..." << endl;
        // Here you would typically fetch and display the list of currencies.
    }

    void _updateExchangeRates()
    {
        cout << "Updating exchange rates..." << endl;
        // Here you would typically call a service to update the rates.
    }

    void _openCurrencyConverter()
    {
        cout << "Opening currency converter..." << endl;
        // Here you would typically open the currency converter interface.
    }

    void _performUserAction(int action)
    {
        system("clear");

        switch (action)
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
    }

public:
};

#endif // CLSMAINSCREEN_H