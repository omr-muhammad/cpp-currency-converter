#pragma once

#ifndef _CLSSTRING_H_
#define _CLSSTRING_H_

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class clsString
{
private:
  clsString() {};

public:
  static vector<string> split(const string &text, string delimiter)
  {
    vector<string> words;

    size_t start = 0, end = 0;
    while ((end = text.find(delimiter, start)) != string::npos)
    {
      if (end != start) // Avoid empty substrings for consecutive delimiters
        words.push_back(text.substr(start, end - start));
      start = end + delimiter.length();
    }
    if (start < text.length()) // Add the last word if not empty
      words.push_back(text.substr(start));

    return words;
  }

  static string trim(string text, string direction = "")
  {
    string trim = text;

    if (direction.empty() || direction == "l")
    {
      short firstCharPos = 0;
      while (trim[firstCharPos] == ' ')
      {
        firstCharPos++;
      }

      trim = trim.substr(firstCharPos, trim.length());
      if (direction == "l")
        return trim;
    }

    // If it didn't return from previous if so we need this to work regardless direction
    short lastCharPos = trim.length() - 1;
    while (trim[lastCharPos] == ' ')
    {
      lastCharPos--;
    }

    trim = trim.substr(0, lastCharPos + 1);
    return trim;
  }

  static string lowerStr(string text)
  {
    for (int i = 0; i < text.length(); i++)
      text[i] = tolower(text[i]);

    return text;
  }

  static string upperStr(string text)
  {
    for (int i = 0; i < text.length(); i++)
      text[i] = toupper(text[i]);

    return text;
  }

  static string capitalizeStr(string text)
  {
    text[0] = toupper(text[0]);

    for (int i = 1; i < text.length(); i++)
      text[i] = tolower(text[i]);

    return text;
  }

  static string encryptText(string text)
  {
    string encryptedText = "";
    for (int i = 0; i < text.length(); i++)
    {
      int encryptOperation = int(text[i]) + i * 2;
      encryptedText += char(encryptOperation);
    }

    return encryptedText;
  }

  static string decryptText(string text)
  {
    string decryptedText = "";
    for (int i = 0; i < text.length(); i++)
    {
      int decryptOperation = int(text[i]) - i * 2;
      decryptedText += char(decryptOperation);
    }

    return decryptedText;
  }
};

#endif // _CLSSTRING_H_