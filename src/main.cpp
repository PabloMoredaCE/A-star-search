#include "environment.h"
#include "robot.h"
#include "node.h"
#include "search.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

int main() {
  std::ifstream input{"test.txt"};

  if (!input) {
    std::cerr << "No se pudo abrir el archivo\n";
    return 1;
  }

  std::string line;
  std::vector<std::vector<int>> grid;
  std::pair<int,int> rob_pos;
  std::pair<int,int> destination;

  while(std::getline(input, line)) {
    std::istringstream row{line};
    std::vector<int> actual_row;
    int value;

    while(row >> value) { 
      if(value == 0) {
        rob_pos.first = static_cast<int>(grid.size());
        rob_pos.second = static_cast<int>(actual_row.size());
      }

      if(value == 10) {
        destination.first = static_cast<int>(grid.size());
        destination.second = static_cast<int>(actual_row.size());
      }

      actual_row.push_back(value);
    }

    grid.push_back(actual_row);
  }

  Environment environment(grid);
  Robot robot(rob_pos);

  Node initial_nd{rob_pos, 0};
  Node final_nd{destination, 2};

  Search a_star;
  a_star.addOpen(initial_nd);


  return 0;
}