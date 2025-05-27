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

    static clsCurrency *_getCurrency(string message = "Enter Currency Code or 0 to cancel: ")
    {
        while (true)
        {
            string curCode = read::validatedUserInput<string>(message);

            if (curCode == "0")
                return nullptr;

            string countryName = read::validatedUserInput<string>("Enter Country Name or 0 to cancel: ");

            if (countryName == "0")
                return nullptr;

            clsCurrency *currency = clsCurrency::findCurr(curCode, countryName);

            if (currency)
                return currency;

            // If we reach here, the currency was not found
            if (read::yesOrNo("Currency not found. Do you want to try again?") != 'y')
                return nullptr;
        }
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

    static void _printConversionResult(double result, const clsCurrency &fromCurrency, const clsCurrency &toCurrency, double amount)
    {
        cout << "\nConversion Result:\n";
        cout << "----------------------------------------------\n";
        cout << "Converted " << amount << " " << fromCurrency.getCurCode() << " to "
             << fixed << setprecision(2) << result << " " << toCurrency.getCurCode() << endl;
        cout << "---------------------------------------------\n";
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

            clsCurrency *currency = _getCurrency();
            if (!currency)
                return;

            currency->printCurrency();

            if (read::yesOrNo("Do you want to update this currency?") != 'y')
            {
                cout << "Update cancelled.\n";
                return;
            }

            double newRate;

            if (!_getNewRate(newRate))
                return;

            if (currency->updateRate(newRate))
            {
                currency->printCurrency();
                return;
            }

            cout << "Failed to update the exchange rate. Please try again later.\n";
            return;
        }
    }

    static void convertCurrencyUI()
    {
        while (true)
        {
            system("clear");

            clsCurrency *fromCurrency = _getCurrency("Enter From Currency Code or 0 to cancel: ");

            if (!fromCurrency)
                return;

            fromCurrency->printCurrency();

            clsCurrency *toCurrency = _getCurrency("Enter To Currency Code or 0 to cancel: ");

            if (!toCurrency)
                return;

            if (toCurrency == fromCurrency)
            {
                cout << "You cannot convert a currency to itself. Please try again.\n";
                continue;
            }

            double amount = read::validatedUserInput<double>("Enter Amount to Convert or '0' to cancel: ");

            if (amount <= 0)
            {
                cout << "\nConversion cancelled.\n";
                return;
            }

            double result = fromCurrency->convertCurrency(toCurrency->getCurRate(), amount);

            _printConversionResult(result, *fromCurrency, *toCurrency, amount);

            if (read::yesOrNo("Do you want to convert another currency?") != 'y')
                return;
        }
    }
};
#endif // CLSCURRENCYUI_H