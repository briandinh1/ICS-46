#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>

class MyMazeGenerator : public MazeGenerator 
{
  typedef std::vector<std::vector<bool>> visitedCells;
  std::random_device device;
  
  virtual void generateMaze(Maze& maze);
  
  bool checkRightCell(const visitedCells& visited, int x, int y, int mazeWidth);
  bool checkLeftCell(const visitedCells& visited, int x, int y);
  bool checkUpCell(const visitedCells& visited, int x, int y);
  bool checkDownCell(const visitedCells& visited, int x, int y, int mazeHeight);

  int digRandomSide
  (bool canMoveRight, bool canMoveLeft, bool canMoveUp, bool canMoveDown);

  void dig
  (visitedCells& visited, Maze& maze,  int x, int y);
};


#endif
