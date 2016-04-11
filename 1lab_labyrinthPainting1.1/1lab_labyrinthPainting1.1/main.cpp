#include <iostream>
#include <queue>
#include <fstream>
#include <vector>

//Лабиринт представляет собой квадрат, ?состоящий из N ? N сегментов. Каждый из сегментов 
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

using namespace std;

std::ifstream OpenFile(std::string const &fileName)
{
	std::ifstream inputFile;
	inputFile.open(fileName);
	return inputFile;
}

bool FileIsOpened(std::ifstream &inputFile)
{
	return inputFile.is_open();
}

bool CheckCorrectnessTaskOptions(int N)
{
	return ((3 <= N) && (N <= 30));
}

int ParseMatrixDimension(ifstream &inputFile)
{
	int matrixDimension;
	inputFile >> matrixDimension;
	return matrixDimension;
}

vector<vector<char> > ParsingFileToLabyrinth(ifstream &inputFile, int squareMatrixDimension)
{
	vector<vector<char> > labyrinth(squareMatrixDimension, vector<char>(squareMatrixDimension));

	for (unsigned i = 0; i < squareMatrixDimension; ++i)
	{
		for (unsigned j = 0; j < squareMatrixDimension; ++j)
		{
			inputFile >> labyrinth[i][j];
		}
	}

	return labyrinth;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Invalid args count." << std::endl;
		//return 1;
	}

	std::ifstream inputFile = OpenFile("input.txt");

	if (!FileIsOpened(inputFile))
	{
		std::cout << "Could not open file." << std::endl;
		return 1;
	}

	auto matrixDimension = ParseMatrixDimension(inputFile);

	if (!CheckCorrectnessTaskOptions(matrixDimension))
	{
		std::cout << "Incorrect task options." << std::endl;
		return 1;
	}

	auto labyrinth = ParsingFileToLabyrinth(inputFile, matrixDimension);

	for (int i = 0; i < matrixDimension; ++i)
	{
		for (int j = 0; j < matrixDimension; ++j)
		{
			cout << labyrinth[i][j];
		}
		cout << endl;
	}

	return 0;
}
