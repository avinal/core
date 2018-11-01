#ifndef BIOGEARS_CMD_UTILS_STRING_HELPER_H
#define BIOGEARS_CMD_UTILS_STRING_HELPER_H

//**********************************************************************************
//Copyright 2015 Applied Research Associates, Inc.
//Licensed under the Apache License, Version 2.0 (the "License"); you may not use
//this file except in compliance with the License.You may obtain a copy of the License
//at :
//http:
//www.apache.org/licenses/LICENSE-2.0
//Unless required by applicable law or agreed to in writing, software distributed under
//the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//CONDITIONS OF ANY KIND, either express or implied.See the License for the
//specific language governing permissions and limitations under the License.
//**************************************************************************************:

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>
#include <regex>
#include <string>

namespace biogears {
inline std::string findAndReplace(std::string& S, const std::string& toReplace, const std::string& replaceWith)
{
  size_t start = 0;
  while (true) {
    size_t pos = S.find(toReplace, start);
    if (pos == std::string::npos) {
      break;
    }
    S.replace(pos, toReplace.length(), replaceWith);
    start = pos + replaceWith.length();
  }
  return S;
}
//-------------------------------------------------------------------------------
inline std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
  str.erase(0, str.find_first_not_of(chars));
  return str;
}
//-------------------------------------------------------------------------------
inline std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}
//-------------------------------------------------------------------------------
inline std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
  return ltrim(rtrim(str, chars), chars);
}
//-------------------------------------------------------------------------------
inline std::vector<std::string> re_split(const std::string& input, const std::string& regex)
{
  // passing -1 as the submatch index parameter performs splitting
  std::regex re(regex);
  std::sregex_token_iterator
    first{ input.begin(), input.end(), re, -1 },
    last;
  return { first, last };
}
//-------------------------------------------------------------------------------
inline std::vector<std::string> split(const std::string& input, const char delimiter)
{
  // passing -1 as the submatch index parameter performs splitting
  auto start = input.begin();
  auto end = input.begin();
  std::string d{ delimiter };

  std::vector<std::string> rValue;
  while (end != input.end()) {
    end = std::find_first_of(start, input.end(), d.begin(), d.end());
    rValue.emplace_back(start, end);
    if (end != input.end()) {
      start = ++end;
    }
  }
  return rValue;
}
//-------------------------------------------------------------------------------
inline std::vector<double> vstod(const std::vector<std::string>& input)
{
  std::vector<double> result(input.size());
  std::transform(input.begin(), input.end(), result.begin(), [](const std::string& val) {
    return std::stod(val);
  });
  return result;
}
}

#endif // BIOGEARS_CMD_UTILS_STRING_HELPER_H
