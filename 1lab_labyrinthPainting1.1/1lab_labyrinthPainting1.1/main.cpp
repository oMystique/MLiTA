#include "Director.h"
#include <iostream>
#include <fstream>

const int WALL_AREA = 9;

using namespace std;

ifstream OpenFile(string const &fileName)
{
	ifstream inputFile;
	inputFile.open(fileName);
	return inputFile;
}

bool FileIsOpened(ifstream &inputFile)
{
	return inputFile.is_open();
}

bool CheckCorrectnessTaskOptions(int N)
{
	return ((3 <= N) && (N <= 33));
}

int ParseMatrixDimension(ifstream &inputFile)
{
	int matrixDimension;
	inputFile >> matrixDimension;

	return matrixDimension;
}

Labyrinth ParsingFileToLabyrinth(ifstream &inputFile, size_t squareMatrixDimension)
{
	Labyrinth labyrinth(squareMatrixDimension + 2, vector<char>(squareMatrixDimension + 2));

	for (size_t i = 0; i < squareMatrixDimension + 2; ++i)
	{
		for (size_t j = 0; j < squareMatrixDimension + 2; ++j)
		{

			if ((i == 0) || (i == squareMatrixDimension + 1) 
				|| (j == 0) || (j == squareMatrixDimension + 1)) 
			{
				labyrinth[i][j] = '#';
			}
			else
			{
				inputFile >> labyrinth[i][j];
			}

		}
	}

	return labyrinth;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Invalid args count." << endl;
		return 1;
	}

	auto inputFile = OpenFile(argv[1]);

	if (!FileIsOpened(inputFile))
	{
		cout << "Could not open file." << endl;
		return 1;
	}

	auto matrixDimension = ParseMatrixDimension(inputFile);

	if (!CheckCorrectnessTaskOptions(matrixDimension))
	{
		cout << "Incorrect task options." << endl;
		return 1;
	}

	auto labyrinth = ParsingFileToLabyrinth(inputFile, matrixDimension);

	CDirector director(labyrinth);
	cout << (director.GetLabyrinthWallsQuantity() - WALLS_COUNT) * WALL_AREA << endl;

	return 0;
}
