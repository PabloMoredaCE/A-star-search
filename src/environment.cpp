#include "environment.h"

#include <algorithm>

/**
 * @file environment.cpp
 * @brief Implementacion de la clase Environment
 */
std::ostream& operator<<(std::ostream& os, const Environment& environment) {
    for(std::size_t i = 0; i < environment.GetRows(); i++) {
      for(std::size_t j = 0; j < environment.GetCols(); j++) {
        os << environment.grid_[i][j] << ' ';
      }
      os << '\n';
    }

  return os;
}


void Environment::printPath(std::ostream& os, const std::vector<std::pair<int,int>>& path) const {
  for(std::size_t i = 0; i < grid_.size(); i++) {
    for(std::size_t j = 0; j < grid_[i].size(); j++) {
      std::pair<int,int> current{static_cast<int>(i), static_cast<int>(j)};

      bool is_path = (std::find(path.begin(), path.end(), current)) != path.end();

      if(is_path) {
        os << '*';
      } else {
        os << grid_[i][j];
      }

      if(j + 1 < grid_[i].size()) {
        os << ' ';
      }
    }

    os << '\n';
  }
}