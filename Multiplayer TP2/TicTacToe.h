#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class TicTacToe
{
public:
	char mat[3][3], p1, p2;
	void init();
	void display();
	void UpdateMat(char newMat[]);
	void displayInstructions();

	TicTacToe();
	~TicTacToe();



};

