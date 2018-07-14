#include <ics46/factory/DynamicFactory.hpp>
#include "MyMazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
#include <vector>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyMazeGenerator,
                               "Brian's Maze Generator (Required)");


void MyMazeGenerator::generateMaze(Maze& maze)
{
  maze.addAllWalls();

  visitedCells visited(maze.getHeight(),
                       std::vector<bool>(maze.getWidth(), false));

  int x = 0; // columns
  int y = 0; // rows

  visited[y][x]= true;

  dig (visited, maze, x, y);
}

bool MyMazeGenerator::checkRightCell(const visitedCells& visited, int x, int y, int mazeWidth)
{
  return !(x+1 >= mazeWidth || visited[y][x+1]);
}

bool MyMazeGenerator::checkLeftCell(const visitedCells& visited, int x, int y)
{
  return !(x-1 < 0 || visited[y][x-1]);
}

bool MyMazeGenerator::checkUpCell(const visitedCells& visited, int x, int y)
{
  return !(y-1 < 0 || visited[y-1][x]);
}

bool MyMazeGenerator::checkDownCell(const visitedCells& visited, int x, int y, int mazeHeight)
{
  return !(y+1 >= mazeHeight || visited[y+1][x]);
}


int MyMazeGenerator::digRandomSide(bool canMoveRight, bool canMoveLeft,
                                   bool canMoveUp, bool canMoveDown)
{
  std::default_random_engine engine(device());
  std::uniform_int_distribution<int> distribution(1,4);
  // 1 = right, 2 = left, 3 = up, 4 = down
  
  int side = distribution(engine);

  if ((side == 1 && !canMoveRight) || (side == 2 && !canMoveLeft)
      || (side == 3 && !canMoveUp) || (side == 4 && !canMoveDown))
    return digRandomSide(canMoveRight, canMoveLeft, canMoveUp, canMoveDown);
  
  return side;
}

void MyMazeGenerator::dig(visitedCells& visited, Maze& maze, int x, int y)
{
  while(true)
    { 
      bool canMoveRight = checkRightCell(visited, x, y, maze.getWidth()); 
      bool canMoveLeft = checkLeftCell(visited, x, y);
      bool canMoveUp = checkUpCell(visited, x, y);
      bool canMoveDown = checkDownCell(visited, x, y, maze.getHeight());

      // if no more unvisited cells adjacent to the current cell
      if (!(canMoveRight || canMoveLeft || canMoveUp || canMoveDown)) return;
      
      // else at least one adjacent cell is unvisited
      int directionToDig = digRandomSide
        (canMoveRight, canMoveLeft, canMoveUp, canMoveDown);

      // 1 = right, 2 = left, 3 = up, 4 = down
      switch(directionToDig)
        {
        case 1:
          maze.removeWall(x++, y, Direction::right); break;
        case 2:
          maze.removeWall(x--, y, Direction::left); break;
        case 3:
          maze.removeWall(x, y--, Direction::up); break;
        case 4:
          maze.removeWall(x, y++, Direction::down); break;
        }

      visited[y][x] = true;
      dig(visited, maze, x, y);     
    }
}
