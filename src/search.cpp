#include "search.h"

#include <cstdlib>
#include <vector>
#include <stdexcept>

int Search::heuristicCal(const Node& actual_nd, const Node& final_nd) const {
      if (actual_nd.position == final_nd.position) { return 0; }
      int row = std::abs(final_nd.position.first - actual_nd.position.first);
      int col = std::abs(final_nd.position.second - actual_nd.position.second);
      return 2*(row + col);
    }

int Search::evaluationCal(const Node& actual_nd, const Node& final_nd) const {
  return actual_nd.accCost + heuristicCal(actual_nd, final_nd);
}

Node Search::getBestOpen(const Node& final_nd) const {
  if (open_nodes_.empty()) {
    throw std::runtime_error("No open nodes available");
  }

  std::size_t best_index = 0;
  int best_eval = evaluationCal(open_nodes_[0], final_nd);

  for (std::size_t i = 1; i < open_nodes_.size(); ++i) {
    int current_eval = evaluationCal(open_nodes_[i], final_nd);

    if (current_eval < best_eval) {
      best_eval = current_eval;
      best_index = i;
    }
  }

  return open_nodes_[best_index];
}

std::size_t Search::getBestOpenIndex(const Node& final_nd) const {
  std::size_t best_index = 0;
  int best_f = evaluationCal(open_nodes_[0], final_nd);

  for (std::size_t i = 1; i < open_nodes_.size(); ++i) {
    int current_f = evaluationCal(open_nodes_[i], final_nd);

    if (current_f < best_f) {
      best_f = current_f;
      best_index = i;
    }
  }

  return best_index;
}

std::vector<Node> Search::expandNode(const Node& current, const Node& final_nd, Robot& robot, const Environment& environment) {
  std::vector<Node> successors;

  //Move up
  robot.setPos(current.position);
  robot.moveUp(environment);

  std::pair<int, int> new_pos = robot.getPos();

  if (new_pos != current.position) {
    Node successor;
    successor.position = new_pos;
    if (new_pos == final_nd.position) {
      successor.cost = 2;
    } else {
      successor.cost = environment.GetCell(new_pos.first, new_pos.second);
    }

    successor.accCost = current.accCost + successor.cost;
    successors.push_back(successor);
  }

  // Move down
  robot.setPos(current.position);
  robot.moveDown(environment);

  new_pos = robot.getPos();

  if (new_pos != current.position) {
    Node successor;
    successor.position = new_pos;
    if (new_pos == final_nd.position) {
      successor.cost = 2;
    } else {
      successor.cost = environment.GetCell(new_pos.first, new_pos.second);
    }

    successor.accCost = current.accCost + successor.cost;
    successors.push_back(successor);
  }

  // Move left
  robot.setPos(current.position);
  robot.moveLeft(environment);

  new_pos = robot.getPos();

  if (new_pos != current.position) {
    Node successor;
    successor.position = new_pos;
    if (new_pos == final_nd.position) {
      successor.cost = 2;
    } else {
      successor.cost = environment.GetCell(new_pos.first, new_pos.second);
    }

    successor.accCost = current.accCost + successor.cost;
    successors.push_back(successor);
  }

  // Move right
  robot.setPos(current.position);
  robot.moveRight(environment);

  new_pos = robot.getPos();

  if (new_pos != current.position) {
    Node successor;
    successor.position = new_pos;
    if (new_pos == final_nd.position) {
      successor.cost = 2;
    } else {
      successor.cost = environment.GetCell(new_pos.first, new_pos.second);
    }

    successor.accCost = current.accCost + successor.cost;
    successors.push_back(successor);
  }

  return successors;
}
