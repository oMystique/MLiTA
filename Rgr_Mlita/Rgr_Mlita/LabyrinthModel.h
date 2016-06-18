#pragma once
#include <fstream>
#include "signals.h"
#include "Definitions.h"

static const int WALLS_COUNT = 4;
static const int WALL_AREA = 9;

struct Cell
{
	char element;
	bool isVisited;
};

class CLabyrinthModel
{
	using OnVisitedCell = signal::Signal<void(size_t i, size_t j)>;
public:
	CLabyrinthModel() = delete;
	CLabyrinthModel &operator=(CLabyrinthModel const &director) = delete;
	CLabyrinthModel &operator=(CLabyrinthModel &&director) = delete;

	CLabyrinthModel(Labyrinth<Cell> const &labyrinth);
	int GetLabyrinthWallsQuantity()const;
	void FillWalls();
	signal::Connection DoOnChangedCell(OnVisitedCell::slot_type const &handler);
private:
	void CalculateWallsQuantity(size_t i, size_t j);
	void CheckSpecificCell(size_t i, size_t j, int &emptyCells);
private:
	int m_wallsQuantity;
	Labyrinth<Cell> m_labyrinth;
	OnVisitedCell m_onChangedCell;
};

