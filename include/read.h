#ifndef READ_H
#define READ_H

#include <iostream>
#include <string>
#include <limits>

#include "./clsString.h"

using namespace std;

namespace read
{
  template <typename inputFlow>
  inline void handleInput(inputFlow &input)
  {
    cin >> input;
    if (cin.good())
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  template <>
  inline void handleInput<string>(string &input)
  {
    do
    {
      getline(cin, input);
      if (clsString::trim(input).empty())
      {
        cout << "Input cannot be empty. Please try again: ";
      }
    } while (clsString::trim(input).empty());
  }

  template <typename inputType>
  inline inputType validatedUserInput(string message)
  {
    inputType input;

    while (true)
    {
      cout << message << endl;
      read::handleInput<inputType>(input);

      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Input. Please try again." << endl;
      }
      else
      {
        return input;
      }
    }
  }

  template <typename typeInRange>
  inline typeInRange numInRange(string message, typeInRange from, typeInRange to)
  {
    typeInRange num;

    while (true)
    {
      cout << message << " (" << from << " to " << to << "): ";
      cin >> num;

      if (cin.fail() || num < from || num > to)
      {
        cout << "Invalid! Please enter between " << from << " and " << to << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      else
      {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return num; // Good input!
      }
    }
  }

  char yesOrNo(string message);
}

#endif // READ_H