#include "stdafx.h"
#include "LabyrinthParser.h"

using namespace std;

Labyrinth<Cell> CLabyrinthParser::ParseFileToLabyrinth(ifstream & inputFile)
{
	size_t squareMatrixDimension;
	inputFile >> squareMatrixDimension;

	CheckMatrixDimension(squareMatrixDimension);

	Labyrinth<Cell> labyrinth(squareMatrixDimension + 2, vector<Cell>(squareMatrixDimension + 2)); //+2 for addition walls

	for (size_t i = 0; i < squareMatrixDimension + 2; ++i)
	{
		for (size_t j = 0; j < squareMatrixDimension + 2; ++j)
		{
			if (IsTheAngleOfLabyrinth(i, j, squareMatrixDimension))
			{
				labyrinth[i][j].element = '\0';
			}
			else if (((i == 0) || (i == squareMatrixDimension + 1)
				|| (j == 0) || (j == squareMatrixDimension + 1)))
			{
				labyrinth[i][j].element = '#';
			}
			else
			{
				inputFile >> labyrinth[i][j].element;
			}
		}
	}

	return labyrinth;
}

void CLabyrinthParser::CheckMatrixDimension(size_t matrixDimension)
{
	if (!((3 <= matrixDimension) && (matrixDimension <= 33)))
	{
		throw invalid_argument("Invalid matrix dimension. 3 <= N <= 33");
	}
}

bool CLabyrinthParser::IsTheAngleOfLabyrinth(size_t i, size_t j, size_t matrixDimension)
{
	return ((i == 0 && j == 0) || (i == matrixDimension + 1 && j == matrixDimension + 1)
		|| (i == 0 && j == 1) || (i == 1 && j == 0)
		|| (i == matrixDimension && j == matrixDimension + 1)
		|| (i == matrixDimension + 1 && j == matrixDimension));
}
