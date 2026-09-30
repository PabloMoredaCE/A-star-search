#ifndef SEARCH_H
#define SEARCH_H

#include "node.h"
#include "environment.h"
#include "robot.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <random>

/**
 * @brief Implementacion del algoritmo de busqueda A*
 * La clase gestiona listas de nodos abiertos y cerrados,
 * evalua los nodos mediante la funcion dada y reconstruye 
 * el camino de coste minimo al alcanzar el destino
 */
class Search{
  public:

    /**
     * @brief Ejecucion de la busqueda A*
     * 
     * @param initial_nd Nodo inicial
     * @param final_nd Nodo final
     * @param robot Robot que genera las posiciones sucesoras
     * @param environment Entorno donde se hace la busqueda
     * @param temrinal Flujo utilizado para mostrar la info por pantalla
     * @param file Flujo utilizado para guardar la info de busqueda
     * 
     * @return true si se encuentra un camino, false si no
     */
    bool run(const Node& initial_nd, const Node& final_nd, Robot& robot, 
      const Environment& environment, std::ostream& terminal, std::ostream& file);

    /**
     * @brief Devuelve el camino solucion
     * @return Referencia a la secuencia del camino solucion
     */
    const std::vector<std::pair<int,int>>& getPath() const { return path_;} 
    
    
    /*void addOpen(const Node& nd) {
      open_nodes_.push_back(nd);
    }*/

    /*void addPath(const Node& nd) {
      path_nodes_.push_back(nd);
    }
    */

    /**
     * @brief Calcula el valor de la funcion heuristica h(n)
     * 
     * @param actual_nd Nodo evaluado
     * @param final_nd Nodo destino
     * @return Valor de la funcion heuristica
     */
    int heuristicCal(const Node& actual_nd, const Node& final_nd) const;

    /**
     * @brief Calcula el valor de la funcion de evaluacion A*
     * f(n) = g(n) + h(n)
     * @param actual_nd Nodo evaluado
     * @param final_nd Nodo destino
     * @return Valor de la funcion evaluacion f(n)
     */
    int evaluationCal(const Node& actual_nd, const Node& final_nd) const;


    /**
     * @brief Devuelve el coste total de la solucion
     * @return Coste acumulado total del camino
     */
    int getTotalCost() const { return total_cost_; }

  private:
    std::vector<Node> open_nodes_;
    std::vector<Node> closed_nodes_;
    
    std::vector<std::pair<int,int>> path_;
    int total_cost_{0};

    //Random generator
    std::mt19937 generator_{std::random_device{}()};

    /**
    * @brief Selecciona aleatoriamente uno de los dos mejores nodos abiertos.
    *
    * Se buscan los dos nodos de la lista de abiertos con menor valor
    * de f(n) y se selecciona uno de ellos al azar.
    * Si solo existe un nodo abierto, se selecciona dicho nodo.
    *
    * @param final_nd Nodo destino utilizado para calcular la heuristica.
    * @return Indice del nodo seleccionado en la lista de abiertos.
    */
    std::size_t getRandomBestOpenIndex(const Node& final_nd);
    /**
     * @brief Genera los sucesores de un nodo
     * 
     * @param current Nodo actual
     * @param final_nd Nodo destino
     * @param robot Robot utilizado para realizar los movimientos
     * @param environment Entorno que contiene la informacion del mapa
     * 
     * @return Vector que contiene todos los nodos sucesores validos
     */
    std::vector<Node> expandNode(const Node& current, const Node& final_nd, Robot& robot, const Environment& environment);

    /**
     * @brief Busca una posicion en el vector de nodos
     * @param nodes Vector de nodos
     * @param position Posicion a buscar
     * @return Indice del nodo si se encuentra, -1 si no
     */
    int findNode(const std::vector<Node>& nodes, const std::pair<int, int>& position) const;


    /**
     * @brief Procesado de los sucesores
     * @param sucessors Nodos sucesores
     */
    void sucessorsP(const std::vector<Node>& successors);

    /**
     * @brief Reconstruccion del camino de destino a origen
     * @param initial_nd Nodo inicial
     * @param final_nd Nodo destino
     * 
     * @return true si el camino se reconstruye, false si no
     */
    bool reconstructPath(const Node& initial_nd, const Node& final_nd);

    /**
     * @brief Imprime las listas de nodos abiertos y cerrados
     * @param os Flujo de salida
     * @param iteration Iteracion actual
     */
    void printIter(std::ostream& os, int iteration) const;

    /**
     * @brief Imprime el camino solucion y su coste total
     * @param os Flujo de salida
     */
    void printPath(std::ostream& os) const;

};

#endif