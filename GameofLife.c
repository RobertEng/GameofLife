/* File name: GameofLife.c
* This program is the Game of Life by John Horton Conway.
* The game consists of a board with cells where a person can be found.
* The following rules must be followed when generating each board:
* ^ A person with more than three neighbors dies.
* ^ A person with less than two neighbors dies.
* ^ In an empty cell with exactly three neighbors, a person is created.
* This is such an awesome program!
*/

#include<stdio.h>
#include"simpio.h"
#include"genlib.h"
#include"strlib.h"

#define size 10

int getGen();
void getBoard(bool arrBoard[][]);
void displayArray(bool arrBoard[][]);
void setArrFalse(bool arrBoard[][]);
void inputLine(string str, bool arrBoard[][], int row);
void transferBoard(bool Board1[][], bool Board2[][]);
void life(bool currBoard[][], bool newBoard[][], bool visitCell[][], int gens, int currGen);
void clearEdges(bool arrBoard[][]);
void checkSurrounding(bool currBoard[][], int row, int column, bool newBoard[][], bool visitCell[][]);
bool isChange(bool currBoard[][], bool newBoard[][]);

main()
{
      int gens, currGen;
      bool currBoard[size+1][size+1];
      bool newBoard[size+1][size+1];
      bool visitCell[size+1][size+1];
      printf("This is the Game of Life!\n");
      gens=getGen();
      currGen=gens;
      setArrFalse(currBoard);
      setArrFalse(newBoard);
      setArrFalse(visitCell);
      getBoard(currBoard);
      system("cls");
      printf("\nStart!");
      displayArray(currBoard);
      getchar();
      system("cls");
      life(currBoard, newBoard, visitCell, gens, currGen);
      getchar();
}

void life(bool currBoard[][size+1], bool newBoard[][size+1], bool visitCell[][size+1], int gens, int currGen)
{
     int row, column;
     if(currGen<=0){printf("The End!");return;}
     transferBoard(currBoard, newBoard);
     for(row=1; row<=size; row++)
     {    for(column=1; column<=size; column++)
          {    if(currBoard[row][column])
               {    checkSurrounding(currBoard, row, column, newBoard, visitCell);
                    checkSurrounding(currBoard, row+1, column, newBoard, visitCell);
                    checkSurrounding(currBoard, row, column+1, newBoard, visitCell);
                    checkSurrounding(currBoard, row+1, column+1, newBoard, visitCell);
                    checkSurrounding(currBoard, row-1, column, newBoard, visitCell);
                    checkSurrounding(currBoard, row, column-1, newBoard, visitCell);
                    checkSurrounding(currBoard, row-1, column-1, newBoard, visitCell);
                    checkSurrounding(currBoard, row-1, column+1, newBoard, visitCell);
                    checkSurrounding(currBoard, row+1, column-1, newBoard, visitCell);
               }
          }
     }
     
     clearEdges(newBoard);
     clearEdges(currBoard);
     printf("\nGeneration %d of %d:", gens-currGen+1, gens);
     displayArray(newBoard);
     
     setArrFalse(visitCell);
     currGen--;
     if(!isChange(currBoard, newBoard))
     {
          printf("Life has reached equilibrium on your board. All is peaceful.");
          getchar();
          system("cls");
          printf("The End!");
          return;
     }
     else printf("Press Enter to continue.");
     transferBoard(newBoard, currBoard);
     getchar();
     system("cls");
     life(currBoard, newBoard, visitCell, gens, currGen);
}

bool isChange(bool currBoard[][size+1], bool newBoard[][size+1])
{
     int row, column;
     for(row=1; row<=size; row++)
     {    for(column=1; column<=size; column++)
          {     if(currBoard[row][column]!=newBoard[row][column]){return true;}
          }
     }\
     return(false);
}

void checkSurrounding(bool currBoard[][size+1], int row, int column, bool newBoard[][size+1], bool visitCell[][size+1])
{
     int neighbors;
     neighbors=0;
     if(visitCell[row][column]){return;}
     if(currBoard[row+1][column]){neighbors++;}
     if(currBoard[row][column+1]){neighbors++;}
     if(currBoard[row+1][column+1]){neighbors++;}
     if(currBoard[row-1][column]){neighbors++;}
     if(currBoard[row][column-1]){neighbors++;}
     if(currBoard[row-1][column-1]){neighbors++;}
     if(currBoard[row+1][column-1]){neighbors++;}
     if(currBoard[row-1][column+1]){neighbors++;}
     if(neighbors>3){newBoard[row][column]=false;}
     if(neighbors<2){newBoard[row][column]=false;}
     if(neighbors==3){newBoard[row][column]=true;}
     visitCell[row][column]=true;
}

void clearEdges(bool arrBoard[][size+1])
{
     int line;
     for(line=0; line<=size+1; line++)
     {    arrBoard[line][0]=false;
          arrBoard[0][line]=false;
          arrBoard[line][size+1]=false;
          arrBoard[size+1][line]=false;
     }
}

void transferBoard(bool Board1[][size+1], bool Board2[][size+1])
{
     int row, column;
     for(row=0; row<=size+1; row++)
     {    for(column=0; column<=size+1; column++)
          {    Board2[row][column]=Board1[row][column];
          }
     }
}

int getGen()
{
     int gens;
     printf("The game consists of a %d by %d board with cells where people live.\n", size ,size);
     printf("  The following rules must be followed when generating each board:\n");
     printf("  1. A person with more than three neighbors dies.\n");
     printf("  2. A person with less than two neighbors dies.\n");
     printf("  3. In an empty cell with exactly three neighbors, a person is created.\n");
     printf("Each time the people change on the board is called a generation.\n");
     printf("Please enter the number of generations you would like.");
     gens=GetInteger();
     return(gens);
}

void getBoard(bool arrBoard[][size+1])
{
     int dispCol, row, column;
     char ch;
     string str;
     printf("To enter the board, place '*' where you want a person and a space\nwhere you do not.\n");
     printf("Please enter the whole row and then press enter\n ");
     for(dispCol=1; dispCol<=size; dispCol++){printf("%d",dispCol%10);}
     printf("\n");
     for(row=1; row<=size; row++)
     {
          printf("%d",row%10);
          str=GetLine();
          while(StringLength(str)<size)
          {
               printf("Please try again:\n ");
               str=GetLine();
          }
          inputLine(str, arrBoard, row);
     }
}

void inputLine(string str, bool arrBoard[][size+1], int row)
{
     int column;
     for(column=1; column<=size; column++)
     {    if(IthChar(str, column-1)=='*'){arrBoard[row][column]=true;}
     }
}

void displayArray(bool arrBoard[][size+1])
{
     int row, column;
     printf("\n");
     for(row=1;row<=size;row++)
     {
          for(column=1; column<=size; column++)
          {
               if(arrBoard[row][column]){printf(" * ");}
               else{printf(" - ");}
          }
          printf("\n");
     }
}

void setArrFalse(bool arrBoard[][size+1])
{
     int row, column;
     for(row=0;row<=size+1;row++)
     {    for(column=0; column<=size+1; column++){arrBoard[row][column]=false;}
     }
}