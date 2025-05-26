#pragma once

#ifndef CLSCURRENCYUI_H
#define CLSCURRENCYUI_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "read.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyUI
{
private:
    static void _displayCurrencyHeader()
    {
        cout << setw(15) << left << "Currency Code" << " | "
             << setw(30) << left << "Country Name" << " | "
             << setw(30) << left << "Currency Name" << " | "
             << setw(15) << left << "Exchange Rate" << endl;
        cout << string(15, '-') << "-+-"
             << string(30, '-') << "-+-"
             << string(30, '-') << "-+-"
             << string(15, '-') << endl;
    }

    static void _displayCurrencyRow(const clsCurrency &currency)
    {
        cout << setw(15) << left << currency.getCurCode() << " | "
             << setw(30) << left << currency.getCountryName() << " | "
             << setw(30) << left << currency.getCurName() << " | "
             << setw(15) << left << fixed << setprecision(2) << currency.getCurRate() << endl;
    }

    static void _displayCurrencyBody(vector<clsCurrency> &currencies)
    {

        if (currencies.empty())
        {
            _displayCurrencyHeader();
            string msg = "NO CURRENCIES AVAILABLE!";
            int width = 95; // Adjusted to match header width
            int padding = (width - msg.length()) / 2;

            cout << string(padding, ' ') << msg << endl;
            _displayCurrencyFooter();
            return;
        }

        for (const auto &currency : currencies)
            _displayCurrencyRow(currency);
    }

    static void _displayCurrencyFooter()
    {
        cout << string(95, '-') << endl;
    }

    static bool _getNewRate(double &newRate)
    {
        newRate = read::validatedUserInput<double>("Enter New Exchange Rate or '0' to cancel: ");

        if (newRate <= 0)
        {
            cout << "Update cancelled.\n";
            return false;
        }

        return true;
    }

public:
    static void displayCurrencyList()
    {
        vector<clsCurrency> &currencies = clsCurrency::getCurrencies();

        _displayCurrencyHeader();
        _displayCurrencyBody(currencies);
        _displayCurrencyFooter();
    }

    static void updateCurrencyRateUI()
    {
        while (true)
        {
            system("clear");
            string curCode = read::validatedUserInput<string>("Enter Currency Code: ");

            clsCurrency *currency = clsCurrency::findCurrByCode(curCode);

            if (!currency)
            {
                cout << "Currency with code '" << curCode << "' not found.\n";

                if (read::yesOrNo("Do you want to try again?") == 'y')
                    continue;

                break;
            }

            cout << "\nCurrent Currency Details:\n";
            currency->printCurrency();

            if (read::yesOrNo("Do you want to update this currency?") != 'y')
            {
                cout << "Update cancelled.\n";
                return;
            }

            double newRate;

            if (!_getNewRate(newRate))
                break;

            if (currency->updateRate(newRate))
            {
                cout << "\nNew Currency Details:\n";
                currency->printCurrency();
                return;
            }

            cout << "Failed to update the exchange rate. Please try again later.\n";
            return;
        }
    }
};

#endif // CLSCURRENCYUI_H