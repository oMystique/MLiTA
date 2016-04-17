#include "Director.h"
#include <iostream>
#include <fstream>

//Лабиринт представляет собой квадрат, состоящий из N x N сегментов. Каждый из сегментов 
//может быть либо пустым, либо заполненным монолитной каменной стеной. Гарантируется, что 
//левый верхний и правый нижний сегменты пусты. Лабиринт обнесён сверху, снизу, слева и справа 
//стенами, оставляющими свободными только левый верхний и правый нижний углы. Директор 
//лабиринта решил покрасить стены лабиринта, видимые изнутри (см. рисунок). Помогите ему 
//рассчитать количество краски, необходимой для этого.

//Ввод из файла INPUT.TXT. В первой строке находится число N, затем идут N строк по N 
//символов: точка обозначает пустой сегмент, решётка - сегмент со стеной.

//Вывод в файл OUTPUT.TXT. Вывести одно число - площадь видимой части внутренних стен 
//лабиринта в квадратных метрах.

//Ограничения: 3 <= N <= 33, размер сегмента 3

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
