#pragma once
#include "signals.h"
#include <deque>

class CLabyrinthController
{
public:
	void OnCellChanged(size_t i, size_t j);
	std::pair<size_t, size_t> GetVisitedCell();
	bool IsNoChanges()const;
private:
	std::deque<std::pair<size_t, size_t>> m_visitedCells;
};