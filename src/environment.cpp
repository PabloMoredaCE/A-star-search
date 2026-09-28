#include <environment.h>

std::ostream& operator<<(std::ostream& os, const Environment& environment) {
    for(std::size_t i = 0; i < environment.GetRows(); i++) {
      for(std::size_t j = 0; j < environment.GetCols(); j++) {
        os << environment.grid_[i][j] << ' ';
      }
      os << '\n';
    }

  return os;
}