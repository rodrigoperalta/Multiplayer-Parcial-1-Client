#include "TicTacToe.h"

TicTacToe::TicTacToe()
{

}

TicTacToe::~TicTacToe()
{

}

void TicTacToe::init()
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			mat[i][j] = '-';
}

void TicTacToe::UpdateMat(char newMat[])
{
	int aux = 0;
	for (int i = 0; i < 9; i++) {
		cout << newMat[i];//Looping 5 times to print out [0],[1],[2],[3],[4]
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{			
			mat[i][j] = newMat[aux];
			aux++;
		}

	aux = 0;
}

void TicTacToe::display()
{

	int i, j;
	system("CLS");
	cout << "\nGrid Co-ordinates : " << endl << endl;

	for (i = 0; i < 3; i++)
	{
		cout << "\t";
		for (j = 0; j < 3; j++)
			cout << i << " " << j << "    ";
		cout << endl;
	}

	cout << "\nThe Tic-Tac-Toe board : " << endl << endl;
	for (i = 0; i < 3; i++)
	{
		cout << "\t";
		for (j = 0; j < 3; j++)
			cout << " " << mat[i][j] << "     ";
		cout << endl;
	}
}

void TicTacToe::displayInstructions()
{

	int i, j;
	//system("CLS");
	cout << "\nGrid Co-ordinates : " << endl << endl;

	for (i = 0; i < 3; i++)
	{
		cout << "\t";
		for (j = 0; j < 3; j++)
			cout << i << " " << j << "    ";
		cout << endl;
	}
}