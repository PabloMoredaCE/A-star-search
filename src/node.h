#ifndef NODE_H
#define NODE_H

#include <utility>

struct Node {
  std::pair<int, int> position;
  int cost;
};

#endif