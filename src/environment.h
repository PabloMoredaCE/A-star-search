#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <fstream>
#include <utility>
#include <iostream>



/**
 * @brief Representa el entorno bidimensional
 * El entorno se almacena como una matriz de valores enteros 
 * donde cada valor representa el coste de atravesar una celda
 * (o un valor especial)
 * 
 */
class Environment {
  public:


    /**
     * @brief Construcción de un entorno a partir de una matriz
     * @param grid Matriz con la información del entorno
     */
    Environment(const std::vector<std::vector<int>>& grid) 
      : grid_(grid) {}


    /**
     * @brief Getter para filas del entorno
     * @return Numero de filas
     */
    std::size_t GetRows() const { return grid_.size(); }

    /**
     * @brief Getter para columnas del entorno
     * @return Numero de columnas, 0 si la matriz esta vacia
     */
    std::size_t GetCols() const {
      if (grid_.empty()) {
        return 0;
      } else return grid_[0].size();
    }

    /**
     * @brief Obtiene el valor de una celda
     * @param row Fila de la celda
     * @param col Columna de la celda
     * @return Valor almacenado en la posicion dada
     */
    int GetCell(int row, int col) const { return grid_[row][col]; }

    
    //bool checkEnv(const Environment& environment) const;

    /**
     * @brief Escribe el entorno en un flujo de salida
     * @param os Flujo de salida
     * @param environment Entorno a imprimir
     * @return Referencia al flujo de salida
     */
    friend std::ostream& operator<<(std::ostream& os, 
      const Environment& environment);

    /**
     * @brief Imprime el entorno marcando el camino solucion con '*'
     * @param os Flujo de salida donde se escribe el entorno
     * @param path Secuencia que forma el camino solucion
     */
    void printPath(std::ostream& os, const std::vector<std::pair<int,int>>& path) const;

  private:

    std::vector<std::vector<int>> grid_;

};

#endif