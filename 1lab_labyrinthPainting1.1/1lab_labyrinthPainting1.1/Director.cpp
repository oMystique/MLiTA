#include "Director.h"

using namespace std;

CDirector::CDirector(Labyrinth const & labyrinth)
	: m_wallsQuantity(0)
	, m_labyrinth(labyrinth)
{
}

int CDirector::GetLabyrinthWallsQuantity()
{
	CalculateWallsQuantity(1, 1);

	if (!m_labyrinth[m_labyrinth.size() - 2][m_labyrinth.size() - 2].isVisited)
	{
		CalculateWallsQuantity(m_labyrinth.size() - 2, m_labyrinth.size() - 2);
	}

	return m_wallsQuantity;
}

void CDirector::CheckSpecificCell(size_t i, size_t j, int &emptyCells)
{
	if (m_labyrinth[i][j].element == '.')
	{
		++emptyCells;
		CalculateWallsQuantity(i, j);
	}
}

void CDirector::CalculateWallsQuantity(size_t i, size_t j)
{
	if (!m_labyrinth[i][j].isVisited)
	{
		m_labyrinth[i][j].isVisited = true;
		int emptyCells = 0;

		if (i > 0)
		{
			CheckSpecificCell(i - 1, j, emptyCells);
		}

		if (i < m_labyrinth.size())
		{
			CheckSpecificCell(i + 1, j, emptyCells);
		}

		if (j > 0)
		{
			CheckSpecificCell(i, j - 1, emptyCells);
		}

		if (j < m_labyrinth.size())
		{
			CheckSpecificCell(i, j + 1, emptyCells);
		}

		m_wallsQuantity += WALLS_COUNT - emptyCells;
	}
}
