#include <ics46/factory/DynamicFactory.hpp>
#include "MyMazeSolver.hpp"
#include "Maze.hpp"
#include <vector>
#include <utility>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MyMazeSolver,
                               "Brian's Maze Solver (Required)");


void MyMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
  visitedCells visited(maze.getHeight(),
                       std::vector<bool>(maze.getWidth(), false));
  
  int x = mazeSolution.getStartingCell().first; // columns
  int y = mazeSolution.getStartingCell().second; // rows

  visited[y][x] = true;

  try { move(visited, maze, mazeSolution, x, y); }
  catch (Complete completeSolution) {}
}
bool MyMazeSolver::checkRightCell(const visitedCells& visited,
                                  const Maze& maze, int x, int y)
{
  return !(x+1 >=  maze.getWidth()
           || visited[y][x+1]
           || maze.wallExists(x,y,Direction::right));
}

bool MyMazeSolver::checkLeftCell(const visitedCells& visited,
                                 const Maze& maze, int x, int y)
{
  return !(x-1 < 0
           || visited[y][x-1]
           || maze.wallExists(x,y,Direction::left));
}

bool MyMazeSolver::checkUpCell(const visitedCells& visited,
                               const Maze& maze, int x, int y)
{
  return !(y-1 < 0
           || visited[y-1][x]
           || maze.wallExists(x,y,Direction::up));
}

bool MyMazeSolver::checkDownCell(const visitedCells& visited,
                                 const Maze& maze, int x, int y)
{
  return !(y+1 >= maze.getHeight()
           || visited[y+1][x]
           || maze.wallExists(x,y,Direction::down));
}

void MyMazeSolver::move(visitedCells& visited, const Maze& maze,
                        MazeSolution& mazeSolution, int x, int y)
{
  while(true)
    {
      if (mazeSolution.isComplete()) throw Complete();
      
      bool canMoveRight = checkRightCell(visited, maze, x, y); 
      bool canMoveLeft = checkLeftCell(visited, maze, x, y);
      bool canMoveUp = checkUpCell(visited, maze, x, y);
      bool canMoveDown = checkDownCell(visited, maze, x, y);

      // if no more unvisited cells adjacent to the current cell
      if (!(canMoveRight || canMoveLeft || canMoveUp || canMoveDown))
        {
          mazeSolution.backUp();
          return;
        }
      
      // else at least one adjacent cell is unvisited
      if (canMoveRight)
        {
          visited[y][x+1] = true;
          mazeSolution.extend(Direction::right);
          move(visited, maze, mazeSolution, x+1, y);
        }
      if (canMoveDown)
        {
          visited[y+1][x] = true;
          mazeSolution.extend(Direction::down);
          move(visited, maze, mazeSolution, x, y+1);
        }
      if (canMoveLeft)
        {
          visited[y][x-1] = true;
          mazeSolution.extend(Direction::left);
          move(visited, maze, mazeSolution, x-1, y);
        }
      if (canMoveUp)
        {
          visited[y-1][x] = true;
          mazeSolution.extend(Direction::up);
          move(visited, maze, mazeSolution, x, y-1);
        }
    }
}
