#include <iostream>
using namespace std;

void rematch();

static int _ = 2, X = 3, O = 5;
static int Board[9];
static int UserSymbol, ComSymbol;
static int Turn;

void init()
{
	for(int i=0; i<9; i++)
	{
		Board[i] = _;
	}
	UserSymbol = ComSymbol = _;
	Turn = 1;
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
	int j=0, value;
	
	if (symbol == X)
	{
		// Value for user's win
		value = 18;
	}
	else if (symbol == O)
	{
		// Value for computer's win
		value = 50;
	}
	
	if((Turn == 4) && (Board[0] * Board[7] == (value/2))) { return 6; }
	if((Turn == 4) && (Board[2] * Board[7] == (value/2))) { return 8; }
	if((Turn == 4) && (Board[3] * Board[7] == (value/2))) { return 0; }
	if((Turn == 4) && (Board[4] * Board[8] == (value/2))) { return 2; }
	if((Turn == 4) && (Board[5] * Board[7] == (value/2))) { return 2; }
	
	// Diagonal Check - Left to Right
	if(Board[0] * Board[4] * Board[8] == value)
	{
		if(Board[0] == _) return 0;
		if(Board[4] == _) return 4;
		if(Board[8] == _) return 8;
	}
	// Diagonal Check - Right to Left
	if(Board[2] * Board[4] * Board[6] == value)
	{
		if(Board[2] == _) return 2;
		if(Board[4] == _) return 4;
		if(Board[6] == _) return 6;
	}
	
	for(int i=0; i<3; i++)
	{
		j = i*3;
		// Rows Check
		if(Board[j] * Board[j+1] * Board[j+2] == value)
		{
			if(Board[j] == _) return j;
			if(Board[j+1] == _) return j+1;
			if(Board[j+2] == _) return j+2;
		}
		// Columns Check
		if(Board[i] * Board[i+3] * Board[i+6] == value)
		{
			if(Board[i] == _) return i;
			if(Board[i+3] == _) return i+3;
			if(Board[i+6] == _) return i+6;
		}
	}
	
	return -1;
}

int go(int cell)
{
	cout << "In Go: cell: " << cell << endl;
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
	
	go(cell);
	return true;
}

void comPlay()
{
	switch(Turn)
	{
		case 1:
			go(0);
			break;
		case 2:
			if (Board[4] == _)
			{
				go(4);
			}
			else
			{
				go(0);
			}
			break;
		case 3:
			if (Board[8] == _)
			{
				go(8);
			}
			else
			{
				go(2);
			}
			break;
		case 4:
			if (possWin(X) != -1)
			{
				go(possWin(X));
			}
			else
			{
				go(make2());
			}
			break;
		case 5:
			if (possWin(X) != -1)
			{
				go(possWin(X));
				comWins();
			}
			else if (possWin(O) != -1)
			{
				go(possWin(O));
			}
			else if (Board[6] == _)
			{
				go(6);
			}
			else
			{
				go(2);
			}
			break;
		case 6:
			if (possWin(O) != -1)
			{
				go(possWin(O));
				comWins();
			}
			else if (possWin(X) != -1)
			{
				cout << "PossWinX: " << possWin(X) << endl;
				go(possWin(X));
			}
			else if(make2() != -1)
			{
				cout << "Make2: " << make2() << endl;
				go(make2());
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (Board[i] == _)
					{
						go(i);
						break;
					}
				}
			}
			break;
		case 7:
			if (possWin(X) != -1)
			{
				go(possWin(X));
				comWins();
			}
			else if (possWin(O) != -1)
			{
				go(possWin(O));
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (Board[i] == _)
					{
						go(i);
						break;
					}
				}
			}
			break;
		case 8:
			if (possWin(O) != -1)
			{
				go(possWin(O));
				comWins();
			}
			else if (possWin(X) != -1)
			{
				go(possWin(X));
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (Board[i] == _)
					{
						go(i);
						break;
					}
				}
			}
			break;
		case 9:
			if (possWin(X) != -1)
			{
				go(possWin(X));
				comWins();
			}
			else if (possWin(O) != -1)
			{
				go(possWin(O));
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (Board[i] == _)
					{
						go(i);
						break;
					}
				}
			}
			break;
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
}

void startGame()
{
	cout << "TIC - TAC - TOE GAME" << endl << endl;
	
	init();
	
	chooseSymbol();
	
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
