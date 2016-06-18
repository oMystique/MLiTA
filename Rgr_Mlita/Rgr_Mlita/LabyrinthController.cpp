#include "stdafx.h"
#include "LabyrinthController.h"

void CLabyrinthController::OnCellChanged(size_t i, size_t j)
{
	m_visitedCells.push_back({ i, j });
}

std::pair<size_t, size_t> CLabyrinthController::GetVisitedCell()
{
	auto cellCoordinates = m_visitedCells.front();
	m_visitedCells.pop_front();
	return cellCoordinates;
}

bool CLabyrinthController::IsNoChanges()const
{
	return m_visitedCells.empty();
}
