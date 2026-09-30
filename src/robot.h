#ifndef ROBOT_H
#define ROBOT_H

#include "environment.h"
#include <utility>


/**
 * @brief Representa el robot que se desplaza por el entorno
 * Guarda su posicion actual y da las cuatro operaciones de movimiento
 */
class Robot {
  public:

  /**
   * @brief Constructor del robot en una posicion dada
   * @param pos Posicion inicial del robot
   */
  Robot(const std::pair<int,int>& pos) 
      : pos_(pos) {}

  /**
   * @brief Movimiento del robot hacia arriba
   * @param environment Entorno por el que se desplaza el robot
   */
  void moveUp(const Environment& environment);

  /**
   * @brief Movimiento del robot hacia abajo
   * @param environment Entorno por el que se desplaza el robot
   */
  void moveDown(const Environment& environment);

  /**
   * @brief Movimiento del robot hacia la izquierda
   * @param environment Entorno por el que se desplaza el robot
   */
  void moveLeft(const Environment& environment);

  /**
   * @brief Movimiento del robot hacia la derecha
   * @param environment Entorno por el que se desplaza el robot
   */
  void moveRight(const Environment& environment);

  /**
   * @brief Altera la posicion actual del robot
   * @param pos Nueva posicion del robot
   */
  void setPos(const std::pair<int, int>& pos) { pos_ = pos; }

  /**
   * @brief Getter de la posicion del robot
   * @return posicion actual del robot
   */
  std::pair<int, int> getPos() const { return pos_; }

  private:
  //Current position
  std::pair<int,int> pos_;

  /**
   * @brief Comprueba si una posicion es valida
   * Es valida cuando se encuentra dentro del entorno y no es un obstáculo
   * @param pos Posicion a comprobar
   * @param environment Entorno donde esta la posicion
   * @return true si es una posicion valida, false si no
   */
  bool checkPos(const std::pair<int,int>& pos, const Environment& environment) const;

};

#endif