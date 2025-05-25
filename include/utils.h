#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class utils
{
private:
    static string _txtOnesNumbers(short num)
    {
        switch (num)
        {
        case 1:
            return "One ";
        case 2:
            return "Two ";
        case 3:
            return "Three ";
        case 4:
            return "Four ";
        case 5:
            return "Five ";
        case 6:
            return "Six ";
        case 7:
            return "Seven ";
        case 8:
            return "Eight ";
        case 9:
            return "Nine ";
        case 10:
            return "Ten ";
        case 11:
            return "Eleven ";
        case 12:
            return "Twelve ";
        case 13:
            return "Thirteen ";
        case 14:
            return "Fourteen ";
        case 15:
            return "Fifteen ";
        case 16:
            return "Sixteen ";
        case 17:
            return "Seventeen ";
        case 18:
            return "Eighteen ";
        case 19:
            return "Nineteen ";
        default:
            return "";
        }
    }

    static string _txtTensNumbers(short num)
    {
        switch (num)
        {
        case 2:
            return "Twenty ";
        case 3:
            return "Thirty ";
        case 4:
            return "Forty ";
        case 5:
            return "Fifty ";
        case 6:
            return "Sixty ";
        case 7:
            return "Seventy ";
        case 8:
            return "Eighty ";
        case 9:
            return "Ninety ";
        default:
            return "";
        }
    }

    static long long _readNum()
    {
        long long num = 0;

        do
        {
            cout << "Enter A Number Below One Trillion To Convert: ";
            cin >> num;
        } while (num >= 1000000000000);

        return num;
    }

    static string _chunkToTxt(short chunk)
    {
        string txt;
        if (chunk >= 100)
        {
            txt = _txtOnesNumbers(chunk / 100) + "Hundred ";
            chunk %= 100;
        }

        if (chunk >= 20)
        {
            txt += _txtTensNumbers(chunk / 10);
            chunk %= 10;
        }

        if (chunk > 0)
            txt += _txtOnesNumbers(chunk);

        return txt;
    }

public:
    static string convertNumToReadableTxt(long long num)
    {
        if (num == 0)
            return "Zero";

        string txt;
        vector<string> units = {"", "Thousand ", "Million ", "Billion "};
        short unitIdx = 0;

        while (num > 0)
        {
            int chunk = num % 1000;

            if (chunk != 0)
                txt = _chunkToTxt(chunk) + units[unitIdx] + txt;

            num /= 1000;
            unitIdx++;
        }

        return txt;
    }
};

#endif