#ifndef NODE_H
#define NODE_H

#include <utility>

struct Node {
  std::pair<int, int> position{0,0}; //(r,c)
  int cost{0}; //w(s)
  int accCost{0}; //g(s)

  std::pair<int,int> parent_pos{0,0};
  bool has_parent{false};
};

#endif