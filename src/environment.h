#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <fstream>
#include <utility>
#include <iostream>


class Environment {
  public:

    Environment(const std::vector<std::vector<int>>& grid) 
      : grid_(grid) {}

    std::size_t GetRows() const { return grid_.size(); }

    std::size_t GetCols() const {
      if (grid_.empty()) {
        return 0;
      } else return grid_[0].size();
    }

    int GetCell(int row, int col) const { return grid_[row][col]; }

    bool checkEnv(const Environment& environment) const;
    friend std::ostream& operator<<(std::ostream& os, 
      const Environment& environment);

    void printPath(std::ostream& os, const std::vector<std::pair<int,int>>& path) const;

  private:

    std::vector<std::vector<int>> grid_;

};

#endif