#pragma once
#include "LabyrinthModel.h"

class CLabyrinthParser
{
public:
	static Labyrinth<Cell> ParseFileToLabyrinth(std::ifstream &inputFile);
private:
	static void CheckMatrixDimension(size_t matrixDimension);
	static bool IsTheAngleOfLabyrinth(size_t i, size_t j, size_t matrixDimension);
};