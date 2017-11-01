#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random>
#include<vector>
#include<string.h>
#define HUMAN_PLAYER 1
#define AI_PLAYER 2
using namespace std;

typedef struct
{
	int row,column,score;
	bool isCellEmpty;
}SmartMove;

class TicTacToe
{
	private:
		char matrix[3][3];
		char player1,player2;
	public:
		TicTacToe();
		bool checkPlayerSign(char);
		void setPlayerSign(char,int);
		bool insertValue(int,int,char,int);
		int checkWinner();
		void printMatrix();
		SmartMove checkMove();
		void printSigns();
		SmartMove checkAIMove(int);
};