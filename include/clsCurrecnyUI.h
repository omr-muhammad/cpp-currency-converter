#pragma once

#ifndef CLSCURRENCYUI_H
#define CLSCURRENCYUI_H

#include <iostream>
#include <iomanip>
#include <vector>

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

public:
    static void displayCurrencyList()
    {
        vector<clsCurrency> &currencies = clsCurrency::getCurrencies();

        _displayCurrencyHeader();
        _displayCurrencyBody(currencies);
        _displayCurrencyFooter();
    }
};

#endif // CLSCURRENCYUI_H