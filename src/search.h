#ifndef SEARCH_H
#define SEARCH_H

#include "node.h"
#include "environment.h"
#include "robot.h"

#include <cstdlib>
#include <vector>

class Search{
  public:

    void addOpen(const Node& nd) {
      open_nodes_.push_back(nd);
    }

    /*void addPath(const Node& nd) {
      path_nodes_.push_back(nd);
    }
    */

    int heuristicCal(const Node& actual_nd, const Node& final_nd) const;

    int evaluationCal(const Node& actual_nd, const Node& final_nd) const;

    Node getBestOpen(const Node& final_nd) const;

    std::size_t getBestOpenIndex(const Node& final_nd) const;

    std::vector<Node> expandNode(const Node& current, const Node& final_nd, Robot& robot, const Environment& environment);

  private:
    std::vector<Node> open_nodes_;
    std::vector<Node> path_nodes_;

};

#endif