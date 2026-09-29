#ifndef NODE_H
#define NODE_H

#include <utility>

struct Node {
  std::pair<int, int> position; //(r,c)
  int cost; //w(s)
  int accCost; //g(s)
};

#endif