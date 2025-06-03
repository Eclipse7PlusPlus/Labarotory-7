#ifndef APP_HEADERS_H
#define APP_HEADERS_H

#include <string>
#include <cstdint>

constexpr int MAX_DATES = 100;

void PrintStrings(const std::string* strings, int32_t size);
void DeleteStrings(std::string* strings);
std::string* FillStringArray(int32_t& size);

bool IsValidDate(const std::string& word);
void DataFindString(const std::string& str, std::string* dates, int& count, int max_dates = MAX_DATES);
bool IsDateLess(const std::string& date1, const std::string& date2);
void SortDates(std::string* dates, int count);

#endif 
