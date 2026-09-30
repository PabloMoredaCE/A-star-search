#include "robot.h"

/**
 * @file robot.cpp
 * @brief Implementacion de los movimientos del robot
 */

bool Robot::checkPos(const std::pair<int,int>& pos, const Environment& environment) const {  
  int row = pos.first;
  int col = pos.second;

  if (row < 0 || col < 0) { return false; }

  if (row >= static_cast<int>(environment.GetRows()) || col >= static_cast<int>(environment.GetCols())) {
    return false;
  }

  if (environment.GetCell(row, col) == -1) { return false; }

  return true;
}

void Robot::moveUp(const Environment& environment) {
  std::pair<int,int> new_pos = pos_;
  new_pos.first++;

  if(checkPos(new_pos, environment)) { pos_ = new_pos; }
}
  
void Robot::moveDown(const Environment& environment) {
  std::pair<int,int> new_pos = pos_;
  new_pos.first--;

  if(checkPos(new_pos, environment)) { pos_ = new_pos; }
}

void Robot::moveLeft(const Environment& environment) {
  std::pair<int,int> new_pos = pos_;
  new_pos.second--;

  if(checkPos(new_pos, environment)) { pos_ = new_pos; }
}

void Robot::moveRight(const Environment& environment) {
  std::pair<int,int> new_pos = pos_;
  new_pos.second++;

  if(checkPos(new_pos, environment)) { pos_ = new_pos; }
}