#include "environment.h"
#include "robot.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
  std::ifstream input{"test.txt"};

  if (!input) {
    std::cerr << "No se pudo abrir el archivo\n";
    return 1;
  }

  std::string line;
  std::vector<std::vector<int>> grid;

  while(std::getline(input, line)) {
    std::istringstream row{line};
    std::vector<int> actual_row;
    int value;

    while(row >> value) { 
      actual_row.push_back(value);
    }

    grid.push_back(actual_row);
  }

  Environment environment(grid);

  return 0;
}