#include <iostream>
using namespace std;

void rematch();

int _ = 2, X = 3, O = 5;
int Board[9] = {_, _, _, _, _, _, _, _, _};
int MagicSquare[9] = {8, 3, 4, 1, 5, 9, 6, 7, 2};
int UserSymbol = _, ComSymbol = _;
int *XMovesList, *OMovesList;
int XMovesListSize = 5, OMovesListSize = 4;
int XListIndex = 0, OListIndex = 0;
int Turn = 1;

void init(char ch)
{
	for(int i=0; i<9; i++)
	{
		Board[i] = _;
	}
	
	Turn = 1;
	
	if(ch == 'X')
	{
		UserSymbol = X;
		ComSymbol = O;
	}
	else
	{
		UserSymbol = O;
		ComSymbol = X;
	}
	
	XMovesList = new int[XMovesListSize];
	OMovesList = new int[OMovesListSize];
	
	XListIndex = 0;
	OListIndex = 0;
	
	for(int i=0; i<XMovesListSize; i++)
	{
		XMovesList[i] = -1;
	}
	
	for(int i=0; i<OMovesListSize; i++)
	{
		OMovesList[i] = -1;
	}
}

int displayBoard()
{
	cout << "Board:";
	for(int i=0; i<9; i++)
	{
		if(i%3 == 0)
		{
			cout << endl;
		}
		if(Board[i] == _)
		{
			cout << "_" << "\t";
		}
		else if(Board[i] == X)
		{
			cout << "X" << "\t";
		}
		else if(Board[i] == O)
		{
			cout << "O" << "\t";
		}
	}
	cout << endl << endl;
}


int make2()
{
	if(Board[4] == _)
	{
		return 4;
	}
	else if(Board[1] == _)
	{
		return 1;
	}
	else if(Board[3] == _)
	{
		return 3;
	}
	else if(Board[5] == _)
	{
		return 5;
	}
	else if(Board[7] == _)
	{
		return 7;
	}
	return -1;
}

int possWin(int symbol)
{
	int result = 0;
	int a = 0, b = 0;
	int *list;
	int listIndex;
	
	if (symbol == X)
	{
		list = XMovesList;
		listIndex = XListIndex;
	}
	else if (symbol == O)
	{
		list = OMovesList;
		listIndex = OListIndex;
	}
	
	if ((Turn == 4) && (list[0] == 0 || list[0] == 7) && (list[1] == 7 || list[1] == 0)) { return 6; }
	if ((Turn == 4) && (list[0] == 2 || list[0] == 7) && (list[1] == 7 || list[1] == 2)) { return 8; }
	if ((Turn == 4) && (list[0] == 3 || list[0] == 7) && (list[1] == 7 || list[1] == 3)) { return 0; }
	if ((Turn == 4) && (list[0] == 4 || list[0] == 8) && (list[1] == 8 || list[1] == 4)) { return 2; }
	if ((Turn == 4) && (list[0] == 5 || list[0] == 7) && (list[1] == 7 || list[1] == 5)) { return 2; }
	
	for(int i=0; i < listIndex-1; i++)
	{
		for(int j=i+1; j < listIndex; j++)
		{
			a = MagicSquare[list[i]];
			b = MagicSquare[list[j]];
			result = 15 - (a + b);
			if(result > 0 && result <= 9)
			{
				for(int k=0; k<9; k++)
				{
					if(MagicSquare[k] == result && Board[k] == _)
					{
						return k;
					}
				}
			}
		}
	}
	
	return -1;
}

int go(int cell)
{
	if (Turn%2 == 0)
	{
		Board[cell] = O;
	}
	else
	{
		Board[cell] = X;
	}
	Turn++;
}

bool checkAvailable(int cell)
{
	if(cell < 0 || cell >= 9)
	{
		cout << "Cell number is invaid." << endl << endl;
		return false;
	}
	
	if(Board[cell] != _)
	{
		cout << "This cell is already occupied. Try another cell." << endl << endl;
		return false;
	}
	return true;
}

void comWins()
{
	displayBoard();
	cout << endl << "CPU Wins..." << endl << endl;
	rematch();
//	getch();
//	exit(1);
}

bool userPlay()
{
	int cell;
	cout << "Enter the cell number to play: ";
	cin >> cell;
	cell--;
	
	if(!checkAvailable(cell))
	{
		return false;
	}
	
	if(UserSymbol == X)
	{
		XMovesList[XListIndex++] = cell;
	}
	else if(UserSymbol == O)
	{
		OMovesList[OListIndex++] = cell;
	}
	
	go(cell);
	return true;
}

void comPlay()
{
	if(ComSymbol == X)
	{
		switch(Turn)
		{
			case 1:
				XMovesList[XListIndex++] = 0;
				go(0);
				break;
//			case 2:
//				if (Board[4] == _)
//				{
//					XMovesList[XListIndex++] = 4;
//					go(4);
//				}
//				else
//				{
//					XMovesList[XListIndex++] = 0;
//					go(0);
//				}
//				break;
			case 3:
				if (Board[8] == _)
				{
					XMovesList[XListIndex++] = 8;
					go(8);
				}
				else
				{
					XMovesList[XListIndex++] = 2;
					go(2);
				}
				break;
//			case 4:
//				if (possWin(X) != -1)
//				{
//					XMovesList[XListIndex++] = possWin(X);
//					go(possWin(X));
//				}
//				else
//				{
//					XMovesList[XListIndex++] = make2();
//					go(make2());
//				}
//				break;
			case 5:
				if (possWin(X) != -1)
				{
					XMovesList[XListIndex++] = possWin(X);
					go(possWin(X));
					comWins();
				}
				else if (possWin(O) != -1)
				{
					XMovesList[XListIndex++] = possWin(O);
					go(possWin(O));
				}
				else if (Board[6] == _)
				{
					XMovesList[XListIndex++] = 6;
					go(6);
				}
				else
				{
					XMovesList[XListIndex++] = 2;
					go(2);
				}
				break;
//			case 6:
//				if (possWin(O) != -1)
//				{
//					XMovesList[XListIndex++] = possWin(O);
//					go(possWin(O));
//					comWins();
//				}
//				else if (possWin(X) != -1)
//				{
//					XMovesList[XListIndex++] = possWin(X);
//					go(possWin(X));
//				}
//				else if(make2() != -1)
//				{
//					cout << make2();
//					XMovesList[XListIndex++] = make2();
//					go(make2());
//				}
//				else
//				{
//					for (int i = 0; i < 9; i++)
//					{
//						if (Board[i] == _)
//						{
//							XMovesList[XListIndex++] = i;
//							go(i);
//							break;
//						}
//					}
//				}
//				break;
			case 7:
				if (possWin(X) != -1)
				{
					XMovesList[XListIndex++] = possWin(X);
					go(possWin(X));
					comWins();
				}
				else if (possWin(O) != -1)
				{
					XMovesList[XListIndex++] = possWin(O);
					go(possWin(O));
				}
				else
				{
					for (int i = 0; i < 9; i++)
					{
						if (Board[i] == _)
						{
							XMovesList[XListIndex++] = i;
							go(i);
							break;
						}
					}
				}
				break;
//			case 8:
//				if (possWin(O) != -1)
//				{
//					XMovesList[XListIndex++] = possWin(O);
//					go(possWin(O));
//					comWins();
//				}
//				else if (possWin(X) != -1)
//				{
//					XMovesList[XListIndex++] = possWin(X);
//					go(possWin(X));
//				}
//				else
//				{
//					for (int i = 0; i < 9; i++)
//					{
//						if (Board[i] == _)
//						{
//							XMovesList[XListIndex++] = i;
//							go(i);
//							break;
//						}
//					}
//				}
//				break;
			case 9:
				if (possWin(X) != -1)
				{
					XMovesList[XListIndex++] = possWin(X);
					go(possWin(X));
					comWins();
				}
				else if (possWin(O) != -1)
				{
					XMovesList[XListIndex++] = possWin(O);
					go(possWin(O));
				}
				else
				{
					for (int i = 0; i < 9; i++)
					{
						if (Board[i] == _)
						{
							XMovesList[XListIndex++] = i;
							go(i);
							break;
						}
					}
				}
				break;
		}
	}
	else if(ComSymbol == O)
	{
		switch(Turn)
		{
//			case 1:
//				OMovesList[OListIndex++] = 0;
//				go(0);
//				break;
			case 2:
				if (Board[4] == _)
				{
					OMovesList[OListIndex++] = 4;
					go(4);
				}
				else
				{
					OMovesList[OListIndex++] = 0;
					go(0);
				}
				break;
//			case 3:
//				if (Board[8] == _)
//				{
//					OMovesList[OListIndex++] = 8;
//					go(8);
//				}
//				else
//				{
//					OMovesList[OListIndex++] = 2;
//					go(2);
//				}
//				break;
			case 4:
				if (possWin(X) != -1)
				{
					OMovesList[OListIndex++] = possWin(X);
					go(possWin(X));
				}
				else
				{
					OMovesList[OListIndex++] = make2();
					go(make2());
				}
				break;
//			case 5:
//				if (possWin(X) != -1)
//				{
//					OMovesList[OListIndex++] = possWin(X);
//					go(possWin(X));
//					comWins();
//				}
//				else if (possWin(O) != -1)
//				{
//					OMovesList[OListIndex++] = possWin(O);
//					go(possWin(O));
//				}
//				else if (Board[6] == _)
//				{
//					OMovesList[OListIndex++] = 6;
//					go(6);
//				}
//				else
//				{
//					OMovesList[OListIndex++] = 2;
//					go(2);
//				}
//				break;
			case 6:
				if (possWin(O) != -1)
				{
					OMovesList[OListIndex++] = possWin(O);
					go(possWin(O));
					comWins();
				}
				else if (possWin(X) != -1)
				{
					OMovesList[OListIndex++] = possWin(X);
					go(possWin(X));
				}
				else if(make2() != -1)
				{
					OMovesList[OListIndex++] = make2();
					go(make2());
				}
				else
				{
					for (int i = 0; i < 9; i++)
					{
						if (Board[i] == _)
						{
							OMovesList[OListIndex++] = i;
							go(i);
							break;
						}
					}
				}
				break;
//			case 7:
//				if (possWin(X) != -1)
//				{
//					OMovesList[OListIndex++] = possWin(X);
//					go(possWin(X));
//					comWins();
//				}
//				else if (possWin(O) != -1)
//				{
//					OMovesList[OListIndex++] = possWin(O);
//					go(possWin(O));
//				}
//				else
//				{
//					for (int i = 0; i < 9; i++)
//					{
//						if (Board[i] == _)
//						{
//							OMovesList[OListIndex++] = i;
//							go(i);
//							break;
//						}
//					}
//				}
//				break;
			case 8:
				if (possWin(O) != -1)
				{
					cout << "PossWinO: " << possWin(O);
					OMovesList[OListIndex++] = possWin(O);
					go(possWin(O));
					comWins();
				}
				else if (possWin(X) != -1)
				{
					OMovesList[OListIndex++] = possWin(X);
					go(possWin(X));
				}
				else
				{
					for (int i = 0; i < 9; i++)
					{
						if (Board[i] == _)
						{
							OMovesList[OListIndex++] = i;
							go(i);
							break;
						}
					}
				}
				break;
//			case 9:
//				if (possWin(X) != -1)
//				{
//					OMovesList[OListIndex++] = possWin(X);
//					go(possWin(X));
//					comWins();
//				}
//				else if (possWin(O) != -1)
//				{
//					OMovesList[OListIndex++] = possWin(O);
//					go(possWin(O));
//				}
//				else
//				{
//					for (int i = 0; i < 9; i++)
//					{
//						if (Board[i] == _)
//						{
//							OMovesList[OListIndex++] = i;
//							go(i);
//							break;
//						}
//					}
//				}
//				break;
		}
	}
}

bool checkUserWin()
{
	int j;

	if(Board[0] * Board[4] * Board[8] == 27) {
		return true;
	}
	// Diagonal Check - Right to Left
	if(Board[2] * Board[4] * Board[6] == 27) {
		return true;
	}
	for(int i=0; i<3; i++) {
		j = i*3;
		// Rows Check
		if(Board[j] * Board[j+1] * Board[j+2] == 27) {
			return true;
		}
		// Columns Check
		if(Board[i] * Board[i+3] * Board[i+6] == 27) {
			return true;
		}
	}

	return false;
}

void play()
{
	bool flag;

	if (ComSymbol == X)
	{
		cout << "Computer's Turn:" << endl;
		comPlay();
		displayBoard();
	}

	while(Turn <= 9)
	{
		flag = userPlay();
		if(!flag) continue;
		displayBoard();
		if(Turn >= 4 && checkUserWin())
		{
			cout << "You Won..." << endl << endl;
			rematch();
		}

		if (Turn > 9) break;

		cout << "Computer's Turn:" << endl;
		comPlay();
		displayBoard();
	}
}

void chooseSymbol()
{
	char ch;
	
	while(true)
	{
		cout << "X: First Turn\tO: Second Turn" << endl;
		cout << "Choose your symbol (X/O): ";
		cin >> ch;
		
		ch = toupper(ch);
		
		if(ch == 'X' || ch == 'O')
		{
			break;
		}
		cout << "Enter valid character." << endl << endl;
	}
	init(ch);
}

void startGame()
{
	cout << "TIC - TAC - TOE GAME" << endl << endl;
	
	chooseSymbol();
	
//	init();
	
	cout << endl;
	displayBoard();
	
	play();
	
	cout << "It's a Tie..." << endl << endl;

	rematch();
}

void rematch()
{
	char rematch;
	cout << "Rematch?(y/n): ";
	cin >> rematch;
	
	rematch = toupper(rematch);
	
	if(rematch == 'Y')
	{
		startGame();
	}
	else if(rematch == 'N')
	{
		cout << endl << "Exiting..." << endl;
	}
}

int main()
{
	startGame();
	return 0;
}
