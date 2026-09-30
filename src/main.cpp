#include "environment.h"
#include "robot.h"
#include "node.h"
#include "search.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

/**
 * @file main.cpp
 * @brief Inicio del programa
 * Lectura del entorno desde un fichero de entrada, 
 * crea los objetos y ejecuta el algoritmo A*
 */

int main(int argc, char* argv[]) {

  if(argc != 4) {
    std::cerr << "Uso: "
              << argv[0]
              << " <fichero_entrada> <salida_mapa> <salida_busqueda>\n"; 
    return 1;
  }

  std::ifstream input{argv[1]};

  if (!input) {
    std::cerr << "No se pudo abrir el archivo\n";
    return 1;
  }

  std::string line;
  std::vector<std::vector<int>> grid;
  std::pair<int,int> rob_pos;
  std::pair<int,int> destination;

  while(std::getline(input, line)) {
    std::istringstream row{line};
    std::vector<int> actual_row;
    int value;

    while(row >> value) { 
      if(value == 0) {
        rob_pos.first = static_cast<int>(grid.size());
        rob_pos.second = static_cast<int>(actual_row.size());
      }

      if(value == 10) {
        destination.first = static_cast<int>(grid.size());
        destination.second = static_cast<int>(actual_row.size());
      }

      actual_row.push_back(value);
    }

    grid.push_back(actual_row);
  }

  Environment environment(grid);
  Robot robot(rob_pos);

  Node initial_nd;
  initial_nd.position = rob_pos;
  initial_nd.cost = 0;
  initial_nd.accCost = 0;
  initial_nd.has_parent = false;

  Node final_nd;
  final_nd.position = destination;
  final_nd.cost = 2;

  std::ofstream search_out{argv[2]};
  std::ofstream path_out{argv[3]};

  if(!search_out) {
    std::cerr << "No se pudo crear el archivo de salida de busqueda\n";
    return 1;
  }

  if(!path_out) {
    std::cerr << "No se pudo crear el archivo de salida del camino\n";
    return 1;
  }

  Search a_star;
  bool found = a_star.run(initial_nd, final_nd, robot, environment, std::cout, search_out);

  if(found) {
    environment.printPath(path_out, a_star.getPath());
  } else {
    path_out << "No se encontro ningun camino\n"; 
  }

  return 0;
}