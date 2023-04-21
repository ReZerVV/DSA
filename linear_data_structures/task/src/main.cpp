#include <iostream>
#include <fstream>
#include <string>
#include "algo.hpp"
#include "weather.hpp"

void print_weather(weather_t &weather) {
    std::cout << "DATA: " << weather._date._year << '.' << (int)weather._date._month << '.' << weather._date._day << ' ';
    std::cout << "TEMPERATURE: " << weather._temperature << ' ';
    std::cout << "WIND: " << (int)weather._wind_direction << ':' << weather._wind_force << ' ';
    std::cout << "PRESSURE: " << weather._pressure << ' ';
    std::cout << "RAIN: " << weather._rain << '\n';
}

void weather_array_to_file(const char* file_path_weather, weather_t *weather, const size_t size) {
    std::ofstream file;
    file.open(file_path_weather,  std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cout << "File is not open: " << file_path_weather << std::endl;
        return;
    }
    file.write((char*)&size, sizeof(size));
    for (size_t index = 0; index < size; ++index) {
        file.write((char*)&weather[index], sizeof(weather[index]));
    }
    file.close();
}

weather_t* weather_array_from_file(const char* file_path_weather, size_t &size) {
    std::ifstream file;
    file.open(file_path_weather,  std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cout << "File is not open: " << file_path_weather << std::endl;
        return nullptr;
    }
    file.read((char*)&size, sizeof(size));
    weather_t *weather = new weather_t[size];
    for (size_t index = 0; index < size; ++index) {
        file.read(reinterpret_cast<char*>(&weather[index]), sizeof(weather_t));
    }
    file.close();
    return weather;
}

struct weather_month_t {
    size_t  _rain_count;
    month_t _month;
};
struct compare {
    bool operator()(weather_month_t &first_value, weather_month_t &second_value) {
        return first_value._rain_count > second_value._rain_count;
    }
};

int main(int argc, char** argv) {
    size_t size_weather = 0;
    weather_t *weather = weather_array_from_file("../data/weather_data.bin", size_weather);
    
    std::string year_str;
    std::cin >> year_str;
    size_t year = static_cast<size_t>(std::stoi( year_str ));

    size_t size_weather_month = 12;
    weather_month_t *weather_month = new weather_month_t[size_weather_month];
    for (size_t month_index = 0; month_index < size_weather_month; ++month_index) {
        weather_month[month_index]._month = static_cast<month_t>(month_index);
        weather_month[month_index]._rain_count = 0;
        for (size_t index = 0; index < size_weather; ++index) {
            if (
                weather[index]._date._year == year &&
                static_cast<size_t>(weather[index]._date._month) == month_index &&
                weather[index]._rain
            ) {
                weather_month[month_index]._rain_count += 1;
            }
        }
    }

    heap_sort(weather_month, size_weather_month, compare{ });

    for (size_t month_index = 0; month_index < size_weather_month; ++month_index) {
        std::cout << month_t_to_string(weather_month[month_index]._month) << " : " << weather_month[month_index]._rain_count << std::endl;
    }

    weather_array_to_file("../data/weather_data.bin", weather, size_weather);
    delete weather;
    return 0;
}