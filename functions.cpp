#include "app_headers.h"
#include <iostream>
#include <cctype>
#include <stdexcept>

std::string* FillStringArray(int32_t& size) {
    std::cout << "Введите количество строк: ";
    std::cin >> size;
    
    while (std::cin.fail() || size <= 0) {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n'); 
        std::cout << "Ошибка! Введите положительное число: ";
        std::cin >> size;
    }
    std::cin.ignore(INT_MAX, '\n');

    std::string* arr = nullptr;
    try {
        arr = new std::string[size];
    } catch (std::bad_alloc& e) {
        std::cerr << "Ошибка выделения памяти для массива строк: " << e.what() << std::endl;
        throw;
    }

    for (int32_t i = 0; i < size; ++i) {
        try {
            std::cout << "Введите строку " << (i + 1) << ": ";
            std::getline(std::cin, arr[i]);
            if (std::cin.fail()) {
                throw std::runtime_error("Ошибка чтения строки");
            }
        } catch (std::exception& e) {
            std::cerr << "Ошибка при вводе строки " << (i + 1) << ": " << e.what() << std::endl;
            DeleteStrings(arr);
            throw;
        }
    }

    return arr;
}

void PrintStrings(const std::string* strings, int32_t size) {
    std::cout << "\nВведенные строки:\n";
    for (int32_t i = 0; i < size; ++i) {
        std::cout << (i + 1) << ": " << strings[i] << std::endl;
    }
    std::cout << std::endl;
}

void DeleteStrings(std::string* strings) {
    delete[] strings;
}

bool IsValidDate(const std::string& word) {
    if (word.size() != 10) 
        return false;

    if (word[2] != '/' || word[5] != '/') 
        return false;

    for (size_t i = 0; i < word.size(); ++i) {
        if (i == 2 || i == 5) 
            continue;
        if (!std::isdigit(word[i])) 
            return false;
    }

    try {
        int day = std::stoi(word.substr(0, 2));
        int month = std::stoi(word.substr(3, 2));
        int year = std::stoi(word.substr(6, 4));

        if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
            return false;

        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return false;

        if (month == 2) {
            bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            if (day > (isLeap ? 29 : 28))
                return false;
        }
    } catch (...) {
        return false;
    }

    return true;
}

void DataFindString(const std::string& str, std::string* dates, int& count, int max_dates) {
    size_t pos1 = 0;
    size_t pos2 = 0;

    while ((pos1 = str.find_first_not_of(' ', pos1)) != std::string::npos && count < max_dates) {
        pos2 = str.find(' ', pos1);
        std::string word = str.substr(pos1, pos2 - pos1);
        
        if (IsValidDate(word)) {
            dates[count++] = word;
        }
        
        pos1 = (pos2 == std::string::npos) ? pos2 : pos2 + 1;
    }
}

bool IsDateLess(const std::string& date1, const std::string& date2) {
    int day1 = std::stoi(date1.substr(0, 2));
    int month1 = std::stoi(date1.substr(3, 2));
    int year1 = std::stoi(date1.substr(6, 4));

    int day2 = std::stoi(date2.substr(0, 2));
    int month2 = std::stoi(date2.substr(3, 2));
    int year2 = std::stoi(date2.substr(6, 4));

    if (year1 != year2) 
        return year1 < year2;
    if (month1 != month2) 
        return month1 < month2;
    
    return day1 < day2;
}

void SortDates(std::string* dates, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (!IsDateLess(dates[j], dates[j+1])) {
                std::swap(dates[j], dates[j+1]);
            }
        }
    }
}
