#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"

class MyMazeSolver : public MazeSolver
{
  class Complete{};
  typedef std::vector<std::vector<bool>> visitedCells;
  
  virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);

  bool checkRightCell(const visitedCells& visited, const Maze& maze, int x, int y);
  bool checkLeftCell(const visitedCells& visited, const Maze& maze, int x, int y);
  bool checkUpCell(const visitedCells& visited, const Maze& maze, int x, int y);
  bool checkDownCell(const visitedCells& visited, const Maze& maze, int x, int y);

  void move(visitedCells& visited, const Maze& maze,
            MazeSolution& mazeSolution, int x, int y);
};

#endif
