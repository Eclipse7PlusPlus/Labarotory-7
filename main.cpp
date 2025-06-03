#include <iostream>
#include <climits>
#include <stdexcept>
#include "app_headers.h"

int main() {
    try {
        int32_t size {};
        std::string* strings = FillStringArray(size);
        
        std::string all_dates[MAX_DATES];
        int total_dates = 0;

        for (int32_t i = 0; i < size; ++i) {
            DataFindString(strings[i], all_dates, total_dates);
        }

        SortDates(all_dates, total_dates);

        std::cout << "\nОтсортированные даты:\n";
        for (int i = 0; i < total_dates; ++i) {
            std::cout << all_dates[i] << "\n";
        }
        
        PrintStrings(strings, size);
        DeleteStrings(strings);
        
    } catch (std::bad_alloc& e) {
        std::cerr << "Ошибка выделения памяти: " << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Произошла неизвестная ошибка" << std::endl;
    }
    return 0;
}
