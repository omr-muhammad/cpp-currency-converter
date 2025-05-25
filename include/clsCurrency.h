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

    static void _saveCurrenciesToFile()
    {
        ofstream file(_filePath);

        if (!file.is_open())
        {
            cerr << "Error opening file: " << _filePath << endl;
            return;
        }

        for (const auto &currency : _currencies)
        {
            file << _convertObjectToString(currency) << endl;
        }

        file.close();
    }

    void _printCurrency() const
    {
        cout << "----------------------------------------------\n";
        cout << "Country: " << _countryName << endl;
        cout << "Currency Code: " << _curCode << endl;
        cout << "Currency Name: " << _curName << endl;
        cout << "Exchange Rate: " << fixed << setprecision(2) << _curRate << endl;
        cout << "---------------------------------------------\n";
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

    static clsCurrency *findCurrByCode(const string &curCode)
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

    static clsCurrency *findCurrByCountry(const string &countryName)
    {
        auto it = find_if(_currencies.begin(), _currencies.end(),
                          [&countryName](const clsCurrency &currency)
                          {
                              return clsString::lowerStr(currency.getCountryName()) == clsString::lowerStr(countryName);
                          });

        if (it == _currencies.end())
            return nullptr; // Not found

        return &(*it);
    }

    // Methods
    void convertCurrency(string convertToCode, double convertToRate, double amount)
    {
        double convertAmountToUSD = amount / _curRate;
        double convertedAmount = convertAmountToUSD * convertToRate;

        cout << "----------------------------------------------\n";
        cout << "Converting " << _curCode << " to " << convertToCode << endl;
        cout << amount << " " << _curCode << " = " << fixed << setprecision(2) << convertedAmount << " " << convertToCode << endl;
        cout << "----------------------------------------------\n";
    }
};

#endif // CLSCURRENCY_H