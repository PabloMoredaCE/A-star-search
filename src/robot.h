#ifndef ROBOT_H
#define ROBOT_H

#include "environment.h"
#include <utility>


class Robot {
  public:

  Robot(const std::pair<int,int>& pos) 
      : pos_(pos) {}

  void moveUp(const Environment& environment);
  void moveDown(const Environment& environment);
  void moveLeft(const Environment& environment);
  void moveRight(const Environment& environment);

  void setPos(const std::pair<int, int>& pos) { pos_ = pos; }
  std::pair<int, int> getPos() const { return pos_; }

  private:
  //Current position
  std::pair<int,int> pos_;

  bool checkPos(const std::pair<int,int>& pos, const Environment& environment) const;

};

#endif