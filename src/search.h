#ifndef SEARCH_H
#define SEARCH_H

#include "node.h"
#include "environment.h"
#include "robot.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>

class Search{
  public:

    bool run(const Node& initial_nd, const Node& final_nd, Robot& robot, 
      const Environment& environment, std::ostream& terminal, std::ostream& file);


    const std::vector<std::pair<int,int>>& getPath() const { return path_;} 
    
    
    /*void addOpen(const Node& nd) {
      open_nodes_.push_back(nd);
    }*/

    /*void addPath(const Node& nd) {
      path_nodes_.push_back(nd);
    }
    */

    int heuristicCal(const Node& actual_nd, const Node& final_nd) const;

    int evaluationCal(const Node& actual_nd, const Node& final_nd) const;

    int getTotalCost() const { return total_cost_; }

  private:
    std::vector<Node> open_nodes_;
    std::vector<Node> closed_nodes_;
    
    std::vector<std::pair<int,int>> path_;
    int total_cost_{0};

    std::size_t getBestOpenIndex(const Node& final_nd) const;

    std::vector<Node> expandNode(const Node& current, const Node& final_nd, Robot& robot, const Environment& environment);

    int findNode(const std::vector<Node>& nodes, const std::pair<int, int>& position) const;

    void sucessorsP(const std::vector<Node>& successors);

    bool reconstructPath(const Node& initial_nd, const Node& final_nd);

    void printIter(std::ostream& os, int iteration) const;
    void printPath(std::ostream& os) const;

};

#endif