#pragma once
#include <vector>

struct Cell
{
	char element = '\0';
	bool isVisited = false;
};

using Labyrinth = std::vector<std::vector<Cell> >;

static const int WALLS_COUNT = 4;

class CDirector
{
public:
	CDirector() = delete;
	CDirector(Labyrinth const &labyrinth);
	int GetLabyrinthWallsQuantity();

private:
	void CalculateWallsQuantity(size_t i, size_t j);
	void CheckSpecificCell(size_t i, size_t j, int &emptyCells);

private:
	int m_wallsQuantity;
	Labyrinth m_labyrinth;
};

