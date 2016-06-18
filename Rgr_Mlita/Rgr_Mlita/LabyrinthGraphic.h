#pragma once
#include "LabyrinthModel.h"
#include <deque>

class GraphicCell:
	public sf::Sprite
{
public:
	void VisitCell();
};

class CLabyrinthView : public sf::Drawable
{
	using PullVisitedCell = signal::Signal<std::pair<size_t, size_t>()>;
	using IsNoVisitedCells = signal::Signal<bool()>;
public:
	CLabyrinthView(Labyrinth<Cell> const &labyrinth);
	signal::Connection DoOnVisitedCell(PullVisitedCell::slot_type const &handler);
	signal::Connection NoVisitedCells(IsNoVisitedCells::slot_type const &handler);
	void OnCellChanged(size_t i, size_t j);
	bool SubmissionCompleted()const;
	void NextStep();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	Labyrinth<GraphicCell> m_graphicsLabyrinth;
	std::deque<GraphicCell*> m_visitedCells;
	std::shared_ptr<sf::Texture> m_cellsTexture;
	PullVisitedCell m_pullVisitedCell;
	IsNoVisitedCells m_isNoVisitedCells;
};