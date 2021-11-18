#include "core/data_frame.h"
#include <string>
#include <iostream>

using std::string;

int main() {
    std::cout << "print" << std::endl;
    string file_n = "resources/test.csv";
    DataFrame steam_df(file_n, 100);

    std::cout << steam_df.string_values_["url"][0];

    return 0;
}