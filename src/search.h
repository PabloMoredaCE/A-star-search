#ifndef SEARCH_H
#define SEARCH_H

#include "node.h"

#include <cstdlib>
#include <vector>

class Search{
  public:

    void addOpen(const Node& nd) {
      open_nodes_.push_back(nd);
    }

    void addPath(const Node& nd) {
      path_nodes_.push_back(nd);
    }

    int heuristicCal(const Node& actual_nd, const Node& final_nd) const {
      if (actual_nd.position == final_nd.position) { return 0; }
      int row = std::abs(final_nd.position.first - actual_nd.position.first);
      int col = std::abs(final_nd.position.second - actual_nd.position.second);
      return 2*(row + col);
    }

  private:
    std::vector<Node> open_nodes_;
    std::vector<Node> path_nodes_;

};

#endif