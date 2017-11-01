	#include "AItictactoe.cpp"

int main()
{
	TicTacToe object;
	int toss,row,column,totalFilled=0,check;
	bool advance;
	char sign,player1sign,player2sign;
	int choice,DifficultyLevel;
	default_random_engine randomGenerator(time(0));
	uniform_int_distribution<int> boxNumber(1,3),coinToss(1,2);
	SmartMove move;


/*GAME STARTS HERE*/

	cout<<"\n\t1.Multiplayer\n\t2.Play With Computer\n\t";
	cin>>choice;
	if(choice == 1)
	{
		cout<<"\n\t*************************************TOSS*************************************";
		toss = coinToss(randomGenerator);
		if(toss == 1)
		{
			cout<<"\n\tPlayer 1 Won The Toss";
			while(1)
			{
				cout<<"\n\tChoose Your Sign(O or X): ";
				cin>>sign;
				player1sign = sign;
				advance = object.checkPlayerSign(sign);
				if(advance == true)
				{
					object.setPlayerSign(sign,1);
					if(sign == 'O')	
					{
						player2sign = 'X';
						object.setPlayerSign('X',2);
					}
					else
					{
						player2sign = 'O';
						object.setPlayerSign('O',2);
					}
					break;
				}
			}
		}
		else if(toss == 2)
		{
			cout<<"\n\tPlayer 2 Won The Toss";
			while(1)
			{
				cout<<"\n\tChoose Your Sign(O or X): ";
				cin>>sign;
				player2sign = sign;
				advance = object.checkPlayerSign(sign);
				if(advance == true)
				{
					object.setPlayerSign(sign,2);
					if(sign == 'O')	
					{
						player1sign = 'X';
						object.setPlayerSign('X',1);
					}
					else 
					{
						player1sign = 'O';
						object.setPlayerSign('O',1);
					}
					break;
				}
			}	
			object.printMatrix();
			goto PLAYER2WONTOSS;
		}
		object.printMatrix();



		while(totalFilled!=9)
		{
			while(1)
			{
				cout<<"\n\tPlayer 1:\n\tEnter Row: ";
				cin>>row;
				cout<<"\n\tEnter Column: ";
				cin>>column;
				advance = object.insertValue(row-1,column-1,player1sign,1);
				if(advance == true) break;
			}
			totalFilled+=1;
			object.printMatrix();
			check = object.checkWinner();
			if(check == 1)
			{
				cout<<"\n\tPlayer 1 Won The Game!\n";
				break;
			}

			if(totalFilled==9)	break; //WHEN GAME IS DRAWN

			PLAYER2WONTOSS:
			while(1)
			{
				cout<<"\n\tPlayer 2:\n\tEnter Row: ";
				cin>>row;
				cout<<"\n\tEnter Column: ";
				cin>>column;
				advance = object.insertValue(row-1,column-1,player2sign,1);
				if(advance == 1) break;
			}
			totalFilled+=1;
			object.printMatrix();
			check = object.checkWinner();
			if(check == 2)
			{
				cout<<"\n\tPlayer 2 Won The Game!\n";
				break;
			}
		}
		if(check == -1)
			cout<<"\n\tGAME DRAWN!\n";
	}



/*CODE FOR COMPUTER VS HUMAN */
	else if(choice == 2)
	{
		while(1)
		{
			cout<<"\n\tChoose Difficulty Level Of The Game\n\t1.Easy\n\t2.Medium\n\t3.Difficult\n\t";
			cin>>DifficultyLevel;
			if(DifficultyLevel == 1 || DifficultyLevel == 2 || DifficultyLevel == 3)
				break;
			cout<<"\n\tPlease Enter A Valid Choice";
		}

		cout<<"\n\t*************************************TOSS*************************************";
		toss = coinToss(randomGenerator);
		if(toss == 1)
		{
			while(1)
			{
				cout<<"\n\tPlayer Won The Toss\n\tChoose Your Sign(O or X): ";
				cin>>sign;
				player1sign = sign;
				advance = object.checkPlayerSign(sign);
				if(advance == true)
				{
					object.setPlayerSign(sign,1);
					if(sign == 'O')	
					{
						player2sign = 'X';
						object.setPlayerSign('X',2);
					}
					else
					{
						player2sign = 'O';
						object.setPlayerSign('O',2);
					}
					break;
				}
			}
		}
		else if(toss == 2)
		{
			cout<<"\n\tComputer Won The Toss";
			sign = coinToss(randomGenerator);
			if(sign == 1)
			{
				player1sign = 'O';
				object.setPlayerSign(player1sign,1);
				player2sign = 'X';
				object.setPlayerSign(player2sign,2);
			}
			else
			{
				player1sign = 'X';
				object.setPlayerSign(player1sign,1);
				player2sign = 'O';
				object.setPlayerSign(player2sign,2);	
			}
			cout<<"\n\tComputer Chose: "<<player2sign;
			cout<<"\n\tYour Sign: "<<player1sign;
			if(DifficultyLevel == 1)
				goto EASY_COMPUTER_TURN;
			else if(DifficultyLevel == 2)
				goto MEDIUM_COMPUTER_TURN;
			else if(DifficultyLevel == 3)
				goto DIFFICULT_COMPUTER_TURN;
		}
		object.printMatrix();

		if( DifficultyLevel == 1)
		{
			while(totalFilled!=9)
			{
				while(1)
				{
					cout<<"\n\tPlayer 1:\n\tEnter Row: ";
					cin>>row;
					cout<<"\n\tEnter Column: ";
					cin>>column;
					advance = object.insertValue(row-1,column-1,player1sign,1);
					if(advance == true) break;

				}
				totalFilled+=1;
				object.printMatrix();
				check = object.checkWinner();
				if(check == 1)
				{
					cout<<"\n\tPlayer 1 Won The Game!\n";
					break;
				}
				if(totalFilled==9)	break;

				EASY_COMPUTER_TURN:

				cout<<"\n\n\tComputer:\n\t";

				while(1)
				{
					row = boxNumber(randomGenerator);
					column = boxNumber(randomGenerator);
					advance = object.insertValue(row-1,column-1,player2sign,2);
					if(advance == true) break;			
				}
				totalFilled+=1;
				object.printMatrix();
				check = object.checkWinner();
				if(check == 2)
				{
					cout<<"\n\tComputer Won The Game!\n";
					break;
				}
			}
			if(check == -1)
				cout<<"\n\tGAME DRAWN!\n";	
		}

		else if(DifficultyLevel == 2)
		{		
			while(totalFilled!=9)
			{
				while(1)
				{
					cout<<"\n\tPlayer 1:\n\tEnter Row: ";
					cin>>row;
					cout<<"\n\tEnter Column: ";
					cin>>column;
					advance = object.insertValue(row-1,column-1,player1sign,1);
					if(advance == true) break;

				}
				totalFilled+=1;
				object.printMatrix();
				check = object.checkWinner();
				if(check == 1)
				{
					cout<<"\n\tPlayer 1 Won The Game!\n";
					break;
				}
				if(totalFilled==9)	break;

				MEDIUM_COMPUTER_TURN:

				cout<<"\n\n\tComputer:\n\t";

				while(1)
				{
					move = object.checkMove();
					if(move.isCellEmpty == true)
					{
						row = move.row+1;
						column = move.column+1;
						advance = object.insertValue(row-1,column-1,player2sign,2);
					
					}
					else
					{
						row = boxNumber(randomGenerator);
						column = boxNumber(randomGenerator);
						advance = object.insertValue(row-1,column-1,player2sign,2);
					}
					if(advance == true) break;			
				}
				totalFilled+=1;
				object.printMatrix();
				check = object.checkWinner();
				if(check == 2)
				{
					cout<<"\n\tComputer Won The Game!\n";
					break;
				}
			}
			if(check == -1)
				cout<<"\n\tGAME DRAWN!\n";
		}

		else if(DifficultyLevel == 3)
		{
			while(totalFilled!=9)
			{
				while(1)
				{
					cout<<"\n\tPlayer 1:\n\tEnter Row: ";
					cin>>row;
					cout<<"\n\tEnter Column: ";
					cin>>column;
					advance = object.insertValue(row-1,column-1,player1sign,1);
					if(advance == true) break;
				}
				totalFilled+=1;
				object.printMatrix();
				check = object.checkWinner();
				if(check == 1)
				{
					cout<<"\n\tPlayer 1 Won The Game!\n";
					break;
				}
				if(totalFilled==9)	break;

				DIFFICULT_COMPUTER_TURN:

				cout<<"\n\n\tComputer:\n\t";
				move = object.checkAIMove(AI_PLAYER);
				object.insertValue(move.row,move.column,player2sign,2);
				totalFilled+=1;
				object.printMatrix();
				check = object.checkWinner();
				if(check == 2)
				{
					cout<<"\n\tComputer Won The Game!\n";
					break;
				}
			}
			if(check == -1)
				cout<<"\n\tGAME DRAWN!\n";
		}
	}
}