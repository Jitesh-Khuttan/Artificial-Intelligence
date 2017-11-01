	#include "AItictactoe.h"


TicTacToe :: TicTacToe()
{
	register int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			matrix[i][j] = 32;
		}
	}
}

void  TicTacToe :: setPlayerSign(char sign,int player)
{
	if(player == 1)
		player1 = sign;
	else if(player == 2)
		player2 = sign;
	else 
		cout<<"\n\tEnter a valid player";
}

bool TicTacToe :: checkPlayerSign(char sign)
{
	if(sign == 'X' || sign == 'O')
		return true;
	cout<<"\n\tSign is Not Valid! Please Enter \"O\" or \"X\" ";
	return false; 
}

bool TicTacToe :: insertValue(int row,int column,char sign,int type)
{
	if(row>2 || column >2 || row < 0 || column < 0 )
	{
		cout<<"\n\tPlease Enter a Valid Cell Location!";
		return false;
	}
	else if(matrix[row][column] == 32)
	{
		matrix[row][column] = sign;
		return true;
	}
	else if(type == 1)
	{
		cout<<"\n\tThis Cell Is Already Filled!";
		return false;
	}
	return false;
}

void TicTacToe :: printMatrix()
{
	int i,j;
	cout<<"\n\t-------------";
	for(i=0;i<3;i++)
	{
		cout<<"\n\t|";
		for(j=0;j<3;j++)
		{
			cout<<" "<<matrix[i][j]<<" ";
			cout<<"|";
		}
		cout<<"\n\t-------------";
	}
}

// void TicTacToe :: printSigns()
// {
// 	cout<<"\n\tSign Of Player1: "<<player1;
// 	cout<<"\n\tSign Of Player2: "<<player2;
// }

int TicTacToe :: checkWinner()
{
	int i,j,totalFilled=0;
	//Check If Pattern Is Complete In Row
	for(i=0;i<3;i++)
	{
		if(matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2] && matrix[i][0]!=32 )
		{
			if(matrix[i][0] == player1)
				return 1;
			return 2;
		}
	}

	//Check If Pattern Is Complete In Column
	for(i=0;i<3;i++)
	{
		if(matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i] && matrix[0][i]!=32)
		{
			if(matrix[0][i] == player1)
				return 1;
			return 2;
		}
	}

	//Check If Pattern Is Complete In Diaglonal
	if(matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[0][0]!=32)
	{
		if(matrix[0][0] == player1)
			return 1;
		return 2;
	}
	if(matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[0][2]!=32)
	{
		if(matrix[0][2] == player1)
			return 1;
		return 2;
	}

	//Check If There Is a Draw
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(matrix[i][j] != 32)
				totalFilled++;
		}
	}
	if(totalFilled == 9)
		return -1;

	//When None Has Won,Neither The Matrix Is Full
	return 0;
}

SmartMove TicTacToe :: checkMove()
{
	SmartMove move;
	int i;

	//Checking Pattern Diagonally
	{
		if(matrix[0][0] == matrix[1][1] && matrix[0][0] != 32)
		{
			if(matrix[2][2] == 32)
			{
				move.row = 2; move.column = 2;
				move.isCellEmpty = true;
				return move;
			}
		}
		if(matrix[0][0] == matrix[2][2] && matrix[0][0] != 32)
		{
			if(matrix[1][1] == 32)
			{
				move.row = 1; move.column = 1;
				move.isCellEmpty = true;
				return move;
			}
		}
		
		if(matrix[1][1] == matrix[2][2] && matrix[1][1] != 32)
		{
			if(matrix[0][0] == 32)
			{
				move.row = 0; move.column = 0;
				move.isCellEmpty = true;
				return move;
			}
		}
	}


	{
		if(matrix[0][2] == matrix[1][1] && matrix[0][2] != 32)
		{
			if(matrix[2][0] == 32)
			{
				move.row = 2; move.column = 0;
				move.isCellEmpty = true;
				return move;
			}
		}
		if(matrix[0][2] == matrix[2][0] && matrix[0][2] != 32)
		{
			if(matrix[1][1] == 32)
			{
				move.row = 1; move.column = 1;
				move.isCellEmpty = true;
				return move;
			}
		}
		
		if(matrix[1][1] == matrix[2][0] && matrix[1][1] != 32)
		{
			if(matrix[0][2] == 32)
			{
				move.row = 0; move.column = 2;
				move.isCellEmpty = true;
				return move;
			}
		}
	}

	//Check If Pattern Has Count==1(i.e. Two Symbols Are Matching) In Row
	for(i=0;i<3;i++)
	{
		if(matrix[i][0] == matrix[i][1] && matrix[i][0] != 32)
		{
			if(matrix[i][2] == 32)
			{
				move.row = i; move.column = 2;
				move.isCellEmpty = true;
				return move;
			}
		}
		if(matrix[i][0] == matrix[i][2] && matrix[i][0] != 32)
		{
			if(matrix[i][1] == 32)
			{
				move.row = i; move.column = 1;
				move.isCellEmpty = true;
				return move;
			}
		}
		
		if(matrix[i][1] == matrix[i][2] && matrix[i][1] != 32)
		{
			if(matrix[i][0] == 32)
			{
				move.row = i; move.column = 0;
				move.isCellEmpty = true;
				return move;
			}
		}	
	}

	//Check If Pattern Has Count==1(i.e. Two Symbols Are Matching) In Column
	for(i=0;i<3;i++)
	{
		if(matrix[0][i] == matrix[1][i] && matrix[0][i] != 32)
		{
			if(matrix[2][i] == 32)
			{
				move.row = 2; move.column = i;
				move.isCellEmpty = true;
				return move;
			}
		}
		if(matrix[0][i] == matrix[2][i] && matrix[0][i] != 32)
		{
			if(matrix[1][i] == 32)
			{
				move.row = 1; move.column = i;
				move.isCellEmpty = true;
				return move;
			}
		}
		
		if(matrix[1][i] == matrix[2][i] && matrix[1][i] != 32)
		{
			if(matrix[0][i] == 32)
			{
				move.row = 0; move.column = i;
				move.isCellEmpty = true;
				return move;
			}
		}	
	}
	//IF ALL CONDITIONS ARE FALSE(i.e. There Is No Equal Pair)
	move.isCellEmpty = false;
	return move;
}


SmartMove TicTacToe :: checkAIMove(int player)
{

	//BASE CASE
	int result = this->checkWinner();
	if(result == HUMAN_PLAYER)
	{	
		SmartMove tempMove;
		tempMove.score = -10;
		return(tempMove);
	}
	else if(result == AI_PLAYER)
	{
		SmartMove tempMove;
		tempMove.score = 10;
		return(tempMove);
	}
	else if(result == -1) //DRAW
	{
		SmartMove tempMove;
		tempMove.score = 0;
		return(tempMove);
	}


	int i,j;
	std::vector<SmartMove> storeMoves;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(matrix[i][j] == 32)
			{
				SmartMove move;
				move.row = i;
				move.column = j;
				if(player == HUMAN_PLAYER)
				{
					this->insertValue(i,j,player1,2); //2 is a type because Computer is inserting
					move.score = checkAIMove(AI_PLAYER).score;
				}
				else if(player == AI_PLAYER)
				{
					this->insertValue(i,j,player2,2); //2 is a type because Computer is inserting
 					move.score = checkAIMove(HUMAN_PLAYER).score;
				}

				storeMoves.push_back(move);
				matrix[i][j] = 32;	//Clearing The Cell Which Was Used For Virtual Input
			}	
			
		}
	}

	//Finding The Move With Lowest Score(if player is HUMAN) or Highest Score(if player is COMPUTER)
	int bestIndex = 0;
	if(player == AI_PLAYER)
	{
		int highestScore = -99999;
		for(i=0;i<storeMoves.size();i++)
		{
			if(highestScore < storeMoves[i].score)
			{
				highestScore = storeMoves[i].score;
				bestIndex = i;
			}
		}
	}
	else if(player == HUMAN_PLAYER)
	{
		int lowestScore = 99999;
		for(i=0;i<storeMoves.size();i++)
		{
			if(lowestScore > storeMoves[i].score)
			{
				lowestScore = storeMoves[i].score;
				bestIndex = i;
			}
		}
	}
	return storeMoves[bestIndex];
}