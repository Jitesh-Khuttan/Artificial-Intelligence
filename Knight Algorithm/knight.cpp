#include <bits/stdc++.h>
using namespace std;

const int PLACEATTACK = 5;
const int PLACEKNIGHT = 10;
static int boardNumber = 0;
int rows,columns;

void initialiseBoard(int** board)
{
	int row,column;
	for(row=0;row<rows;row++)
	{
		for(column=0;column<columns;column++)
		{
			board[row][column] = 0;
		}
	}
}

void cleanUp(int** board)
{
	delete board;
}


int** allocateMemory()
{
//	cout<<"\n\t";
	int** board;
	board = new int*[rows];
	for(int counter=0;counter<rows;counter++)
	{
		board[counter] = new int[columns];
	}
	initialiseBoard(board);
	return board;
}



void printBoard(int** board)
{
	int row,column;
	boardNumber++;
	cout<<"\n\tBoard "<<boardNumber;
	for(row=0;row<rows;row++)
	{
		cout<<"\n\t";
		for(column=0;column<columns;column++)
		{
			cout<<board[row][column]<<"\t";
		}	
	}
}


bool isPlaced(int** board,int i, int j)
{
	if(board[i][j] == 0)
		return true;
	return false;
}

void placeAttacks(int** board,int i,int j)
{
	if((i-2) >= 0 && (j-1) >= 0)
		board[i-2][j-1] = PLACEATTACK;
	
	if((i-2) >= 0 && (j+1) < columns)
		board[i-2][j+1] = PLACEATTACK;
		
	if((i-1) >= 0 && (j-2) >= 0)
		board[i-1][j-2] = PLACEATTACK;
	if((i-1) >= 0 && (j+2) < columns)
		board[i-1][j+2] = PLACEATTACK;
		
	if((i+1) < rows && (j-2) >= 0)
		board[i+1][j-2] = PLACEATTACK;
	if((i+1) < rows && (j+2) < columns)
		board[i+1][j+2] = PLACEATTACK;
		
	if((i+2) < rows && (j-1) >= 0)
		board[i+2][j-1] = PLACEATTACK;
	if((i+2) < rows && (j+1) < columns)
		board[i+2][j+1] = PLACEATTACK;

}

void placeKnight(int** board,int start_i,int start_j,int remainingKnights)
{
	if(remainingKnights == 0)
	{
	//	cout<<"\n\tKnights are zero";
		printBoard(board);
		return;
	}
	
	int i,j;
	for(i=start_i;i<rows;i++)
	{
		for(j = start_j;j<columns;j++)
		{
			//cout<<"(i,j): ("<<i<<","<<j<<")"<<endl;
			if(isPlaced(board,i,j))
			{
				int** newBoard;
				newBoard = allocateMemory();
				//cout<<"\n\tMemory Allocated!";
				//Copying Previous Board Into New Board
				for(int counter=0;counter<rows;counter++)
				{
					for(int offset=0;offset<columns;offset++)
					{
						newBoard[counter][offset] = board[counter][offset];
					}
				}
				//cout<<"\n\tBoard Copied!";
				newBoard[i][j] = PLACEKNIGHT;
				//cout<<"\n\tKnight Placed!";
				placeAttacks(newBoard,i,j);
				//cout<<"\n\tAttacks Placed!";
				//printBoard(newBoard);
				placeKnight(newBoard,i,j,remainingKnights - 1);
				cleanUp(newBoard);
			}
		}
		start_j = 0;
	}
}


int main()
{
	int** board;
	int counter,totalKnights;
	cout<<"\n\tEnter number of rows: ";
	cin>>rows;
	cout<<"\n\tEnter number of columns: ";
	cin>>columns;
	cout<<"\n\tEnter number of knights to be placed";
	cin>>totalKnights;
	board = new int*[rows];
	for(counter=0;counter<rows;counter++)
	{
		board[counter] = new int[columns];
	}
	
	initialiseBoard(board);
//	printBoard(board);
	placeKnight(board,0,0,totalKnights);	
	return 0;
}
