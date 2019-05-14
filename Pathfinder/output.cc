#include <iostream>
#include <fstream>
#include "pathfinder.h"

using namespace std;

ofstream outFile;

bool wallExists(uint8_t maze[][MAX_COLS],int r,int c,int d) {
  return (maze[r][c] & (1 << d)) != 0;
}

bool cellVisited(uint8_t maze[][MAX_COLS],int r,int c) {
  return (maze[r][c] & VISITED) != 0;
}

void drawLine(int r1,int c1,int r2,int c2) {

  outFile << "newpath\n"
       << c1 * 10 + 54 << ' ' << 762 - (r1 * 10 + 54) << " moveto\n"
       << c2 * 10 + 54 << ' ' << 762 - (r2 * 10 + 54) << " lineto\n"
       << "stroke\n";
}

void drawLine2(int r1,int c1,int r2,int c2) {

  outFile << "newpath\n"
       << c1 * 5 + 54 + 5 << ' ' << 762 - (r1 * 5 + 54 + 5) << " moveto\n"
       << c2 * 5 + 54 + 5 << ' ' << 762 - (r2 * 5 + 54 + 5) << " lineto\n"
       << "stroke\n";
}

void drawMaze(uint8_t maze[][MAX_COLS],int nR,int nC,
              bool drawSolution,bool drawDeadEnds) {
  int i,j,d;

  outFile << "newpath\n"
       << "54 " << 762 - (nR * 10 + 54) << " moveto\n"
       << "54 708 lineto\n"
       << nC * 10 + 54 << " 708 lineto\nstroke\n";

  for (i=0;i<nR;i++)
    for (j=0;j<nC;j++) {
      if (maze[i][j] & WALL_RIGHT)
        drawLine(i,j+1,i+1,j+1);
      if (maze[i][j] & WALL_DOWN)
        drawLine(i+1,j,i+1,j+1);
    }

  if (drawDeadEnds) {
    outFile << "1 0 0 setrgbcolor\n";
    for (i=0;i<nR;i++)
      for (j=0;j<nC;j++)
        if ((maze[i][j] & DEAD_END) != 0) {
          if (!wallExists(maze,i,j,0))
            drawLine2(2*i,2*j,2*(i-1),2*j);
          if (!wallExists(maze,i,j,1))
            drawLine2(2*i,2*j,2*i,2*(j+1));
          if (!wallExists(maze,i,j,2))
            drawLine2(2*i,2*j,2*(i+1),2*j);
          if (!wallExists(maze,i,j,3))
            drawLine2(2*i,2*j,2*i,2*(j-1));
        }
  }

  if (drawSolution) {
    outFile << "0 0 1 setrgbcolor gsave currentlinewidth 3 mul setlinewidth "
              " 1 setlinecap\n";
    for (i=0;i<nR;i++)
      for (j=0;j<nC;j++)
        if ((maze[i][j] & (VISITED | DEAD_END)) == VISITED) {
          if (!wallExists(maze,i,j,0) &&
              (maze[i-1][j] & (VISITED | DEAD_END)) == VISITED)
            drawLine2(2*i,2*j,2*(i-1),2*j);
          if (!wallExists(maze,i,j,1) &&
              (maze[i][j+1] & (VISITED | DEAD_END)) == VISITED)
            drawLine2(2*i,2*j,2*i,2*(j+1));
          if (!wallExists(maze,i,j,2) &&
              (maze[i+1][j] & (VISITED | DEAD_END)) == VISITED)
            drawLine2(2*i,2*j,2*(i+1),2*j);
          if (!wallExists(maze,i,j,3) &&
              (maze[i][j-1] & (VISITED | DEAD_END)) == VISITED)
            drawLine2(2*i,2*j,2*i,2*(j-1));
        }
    outFile << "grestore\n";
  }
}

void printMaze(uint8_t maze[][MAX_COLS],int nR,int nC) {
  int i,last,x,y;

  outFile.open("maze.ps");
  if (!outFile) {
    cout << "Error: cannot open maze.ps" << endl;
    return;
  }

  outFile << "%!PS-Adobe-2.0\n\n%%Pages: 3\n%%Page: 1 1\n";

  outFile << "/Arial findfont 20 scalefont setfont\n"
          "54 730 moveto (Random Maze) show\n";

  drawMaze(maze,nR,nC,false,false);

  outFile << "showpage\n";
  outFile << "%%Page: 2 2\n";

  outFile << "/Arial findfont 20 scalefont setfont\n"
          "54 730 moveto (Random Maze With Solution) show\n";

  drawMaze(maze,nR,nC,true,false);

  outFile << "showpage\n";
  outFile << "%%Page: 3 3\n";

  outFile << "/Arial findfont 20 scalefont setfont\n"
          "54 730 moveto (Random Maze With Solution "
          "and Dead Ends) show\n";

  drawMaze(maze,nR,nC,true,true); 

  outFile << "showpage\n"; 
}
