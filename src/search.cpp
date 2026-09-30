#include "search.h"

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

/**
 * @file search.cpp
 * @brief Implementacion del algoritmo de busqeuda A*
 */

int Search::heuristicCal(const Node& actual_nd, const Node& final_nd) const {
      if (actual_nd.position == final_nd.position) { return 0; }
      int row = std::abs(final_nd.position.first - actual_nd.position.first);
      int col = std::abs(final_nd.position.second - actual_nd.position.second);
      return 2*(row + col);
    }

int Search::evaluationCal(const Node& actual_nd, const Node& final_nd) const {
  return actual_nd.accCost + heuristicCal(actual_nd, final_nd);
}

/*Node Search::getBestOpen(const Node& final_nd) const {
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
*/


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
    successor.parent_pos = current.position;
    successor.has_parent = true;
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
    successor.parent_pos = current.position;
    successor.has_parent = true;
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
    successor.parent_pos = current.position;
    successor.has_parent = true;
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
    successor.parent_pos = current.position;
    successor.has_parent = true;
    successors.push_back(successor);
  }

  return successors;
}


int Search::findNode(const std::vector<Node>& nodes, const std::pair<int, int>& position) const {
  for (std::size_t i = 0; i < nodes.size(); ++i) {
    if (nodes[i].position == position) {
      return static_cast<int>(i);
    }
  }

  return -1;
}


void Search::sucessorsP(const std::vector<Node>& sucessors) {
  for(const Node& sucessor : sucessors) {

    int open_index = findNode(open_nodes_, sucessor.position);
    int closed_index = findNode(closed_nodes_, sucessor.position);

    if(open_index == -1 && closed_index == -1) {
      open_nodes_.push_back(sucessor);
      continue;
    }

    if(open_index != -1) {
      if(sucessor.accCost < open_nodes_[open_index].accCost) {
        open_nodes_[open_index] = sucessor;
      }
      continue;
    }

    if(closed_index != -1) {
      if(sucessor.accCost < closed_nodes_[closed_index].accCost) {
        open_nodes_.push_back(sucessor);
        
        closed_nodes_.erase(closed_nodes_.begin() + closed_index);
      }
    }
  }
}

bool Search::reconstructPath(const Node& initial_nd, const Node& final_nd) {
  path_.clear();

  std::pair<int,int> current = final_nd.position;
  path_.push_back(current);

  while(current != initial_nd.position) {
    int index = findNode(closed_nodes_, current);
    if(index == -1) { 
      std::cerr << "Error: nodo no encontrado\n";
      return false; 
    }

    const Node& node = closed_nodes_[index];

    if(!node.has_parent) { 
      std::cerr << "Error: nodo sin padre: ("
      << node.position.first + 1
      << ","
      << node.position.second + 1
      << ")\n";
      return false; 
    }

    current = node.parent_pos;
    path_.push_back(current);
  }

  std::reverse(path_.begin(), path_.end());

  return true;
}


void Search::printIter(std::ostream& os, int iteration) const {
  os << "Iteracion " << iteration << '\n';
  os << "---------------------\n";

  os << "Abiertos = ";
  for(std::size_t i = 0; i < open_nodes_.size(); i++) {
    os << '('
       << open_nodes_[i].position.first + 1
       << ','
       << open_nodes_[i].position.second + 1
       << ')';

    if(i + 1 < open_nodes_.size()) {
      os <<", ";
    }
  }

  os << '\n';
  os << "Cerrados = ";
  for(std::size_t i = 0; i < closed_nodes_.size(); i++) {
    os << '('
       << closed_nodes_[i].position.first + 1
       << ','
       << closed_nodes_[i].position.second + 1
       << ')';

    if(i + 1 < closed_nodes_.size()) {
      os <<", ";
    }
  }

  os << '\n';
  os << "---------------------\n";
}

void Search::printPath(std::ostream& os) const {
  os << "Camino: ";
  for(std::size_t i = 0; i < path_.size(); i++) {
    os << '('
       << path_[i].first + 1
       << ','
       << path_[i].second + 1
       << ')';

    if(i + 1 < path_.size()) {
      os << " -> ";
    }
  }
  
  os << '\n';

  os << "Coste: " << total_cost_ << '\n';
}


bool Search::run(const Node& initial_nd, const Node& final_nd, Robot& robot, 
  const Environment& environment, std::ostream& terminal, std::ostream& file) {
  
  open_nodes_.clear();
  closed_nodes_.clear();
  path_.clear();

  total_cost_ = 0;
  
  open_nodes_.push_back(initial_nd);
  int iteration = 0;

  while(!open_nodes_.empty()) {
    printIter(terminal, iteration);
    printIter(file, iteration);

    std::size_t best_index = getBestOpenIndex(final_nd);

    Node current = open_nodes_[best_index];
    open_nodes_.erase(open_nodes_.begin() + best_index);
    
    closed_nodes_.push_back(current);

    if(current.position == final_nd.position) {
      total_cost_ = current.accCost;

      if(!reconstructPath(initial_nd, current)) { return false; }

      printPath(terminal);
      printPath(file);

      return true;
    }

    std::vector<Node> sucessors = expandNode(current, final_nd, robot, environment);
    sucessorsP(sucessors);
    ++iteration;
  }

  terminal << "No se encontro ningun camino\n";
  file << "No se encontro ningun camino\n";

  return false;
      
}