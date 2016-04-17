#pragma once
#include <vector>

using Labyrinth = std::vector<std::vector<char> >;
using ArrayOfVisits = std::vector<std::vector<bool> >;

static const int WALLS_COUNT = 4;

class CDirector
{
public:
	CDirector(Labyrinth const &labyrinth);
	int GetLabyrinthWallsQuantity();

private:
	void CalculateWallsQuantity(size_t i, size_t j);
	void CheckSpecificCell(size_t i, size_t j, int &emptyCells);

private:
	int m_wallsQuantity;
	ArrayOfVisits m_visitedCells;
	const Labyrinth &m_labyrinth;
};

