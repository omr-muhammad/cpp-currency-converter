#pragma once

#ifndef CLSCURRENCY_H
#define CLSCURRENCY_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
    string _countryName, _curCode, _curName;
    double _curRate;
    inline static vector<clsCurrency> _currencies;
    inline static const string _filePath = "currencies.txt";

    static string _convertObjectToString(const clsCurrency &currency, string delimiter = "#//#")
    {
        return currency._countryName + delimiter +
               currency._curCode + delimiter +
               currency._curName + delimiter +
               to_string(currency._curRate);
    }

    static clsCurrency _convertLineToObject(const string &line, string delimiter = "#//#")
    {
        vector<string> parts = clsString::split(line, delimiter);

        if (parts.size() < 4)
        {
            throw invalid_argument("Invalid line format: " + line);
        }

        string countryName = clsString::trim(parts[0]);
        string curCode = clsString::trim(parts[1]);
        string curName = clsString::trim(parts[2]);
        double curRate = stod(clsString::trim(parts[3]));

        return clsCurrency(countryName, curCode, curName, curRate);
    }

    static bool _saveCurrenciesToFile()
    {
        ofstream file(_filePath);

        if (!file.is_open())
            return false;

        for (const auto &currency : _currencies)
            file << _convertObjectToString(currency) << endl;

        file.close();
        return true;
    }

public:
    // Constructor
    clsCurrency(string countryName, string curCode, string curName, double curRate) : _countryName(countryName), _curCode(curCode), _curName(curName), _curRate(curRate) {}

    // Getters
    string getCountryName() const { return _countryName; }
    string getCurCode() const { return _curCode; }
    string getCurName() const { return _curName; }
    double getCurRate() const { return _curRate; }
    static vector<clsCurrency> &getCurrencies() { return _currencies; }

    // Setters
    void setCurRate(double curRate)
    {
        _curRate = curRate;
        _saveCurrenciesToFile(); // Save changes to file
    }

    // Static methods
    static void loadCurrenciesFromFile()
    {
        ifstream file(_filePath);

        if (!file.is_open())
        {
            cerr << "Error opening file: " << _filePath << endl;
            return;
        }

        _currencies.clear();

        string line;
        while (getline(file, line))
        {
            try
            {
                clsCurrency currency = _convertLineToObject(line);
                _currencies.push_back(currency);
            }
            catch (const invalid_argument &e)
            {
                cerr << "Skipping invalid line: " << line << " - " << e.what() << endl;
            }
        }

        file.close();
    }

    static clsCurrency *findCurr(const string &curCode)
    {
        auto it = find_if(_currencies.begin(), _currencies.end(),
                          [&curCode](const clsCurrency &currency)
                          {
                              return clsString::lowerStr(currency.getCurCode()) == clsString::lowerStr(curCode);
                          });

        if (it == _currencies.end())
            return nullptr; // Not found

        return &(*it);
    }

    static clsCurrency *findCurr(const string &curCode, const string &countryName)
    {
        auto it = find_if(_currencies.begin(), _currencies.end(),
                          [&curCode, &countryName](const clsCurrency &currency)
                          {
                              bool matchCode = clsString::lowerStr(currency.getCurCode()) == clsString::lowerStr(curCode);
                              bool matchCountry = clsString::lowerStr(currency.getCountryName()) == clsString::lowerStr(countryName);

                              return matchCode && matchCountry;
                          });

        if (it == _currencies.end())
            return nullptr; // Not found

        return &(*it);
    }

    // Methods
    void printCurrency() const
    {
        cout << "\nCurrency Details:\n";
        cout << "----------------------------------------------\n";
        cout << "Country: " << _countryName << endl;
        cout << "Currency Code: " << _curCode << endl;
        cout << "Currency Name: " << _curName << endl;
        cout << "Exchange Rate: " << fixed << setprecision(2) << _curRate << endl;
        cout << "---------------------------------------------\n";
    }

    double convertCurrency(double curRate, double amount)
    {
        double convertAmountToUSD = amount / _curRate;
        double convertedAmount = convertAmountToUSD * curRate;

        return convertedAmount;
    }

    bool updateRate(double newRate)
    {
        setCurRate(newRate);
        return _saveCurrenciesToFile();
    }
};

#endif // CLSCURRENCY_H