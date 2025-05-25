#include <iostream>
#include <string>
#include <limits>
#include <cctype>

#include "../include/read.h"

using namespace std;

namespace read
{
  char yesOrNo(string message)
  {
    string input;
    cout << endl;
    cout << message << " [y/n]: ";
    getline(cin, input);
    return (input.empty() || tolower(input[0]) != 'y') ? 'n' : 'y';
  }
}