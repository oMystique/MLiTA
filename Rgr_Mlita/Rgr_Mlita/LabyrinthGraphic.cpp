#include "stdafx.h"
#include "LabyrinthGraphic.h"

using namespace sf;

const int CELL_WIDTH = 20;

IntRect GetElementTextureRect(char ch)
{
	switch (ch)
	{
	case '#':
		return IntRect(0, 0, CELL_WIDTH, CELL_WIDTH);
	case '\0':
		return IntRect(CELL_WIDTH * 2, 0, CELL_WIDTH, CELL_WIDTH);
	case '.':
		return IntRect(CELL_WIDTH, 0, CELL_WIDTH, CELL_WIDTH);
	}
	return IntRect();
}

CLabyrinthView::CLabyrinthView(Labyrinth<Cell> const &labyrinth)
{
	m_cellsTexture = std::make_shared<sf::Texture>();
	m_cellsTexture->loadFromFile("res/cells_1.png");
	m_graphicsLabyrinth.resize(labyrinth.size(), std::vector<GraphicCell>(labyrinth.size()));
	auto centralizePos = Vector2f(400, 375) - Vector2f(static_cast<float>(m_graphicsLabyrinth.size()) / 2.f * CELL_WIDTH
		, static_cast<float>(m_graphicsLabyrinth.size()) / 2.f * CELL_WIDTH);
	for (size_t i = 0; i != labyrinth.size(); ++i)
	{
		for (size_t j = 0; j != labyrinth.size(); ++j)
		{
			m_graphicsLabyrinth[i][j].setTexture(*m_cellsTexture);
			m_graphicsLabyrinth[i][j].setTextureRect(GetElementTextureRect(labyrinth[i][j].element));
			m_graphicsLabyrinth[i][j].setPosition(centralizePos
				+ Vector2f(20.f * static_cast<float>(j), 20.f * static_cast<float>(i)));
		}
	}
}

signal::Connection CLabyrinthView::DoOnVisitedCell(PullVisitedCell::slot_type const & handler)
{
	return m_pullVisitedCell.connect(handler);
}

signal::Connection CLabyrinthView::NoVisitedCells(IsNoVisitedCells::slot_type const & handler)
{
	return m_isNoVisitedCells.connect(handler);
}

void CLabyrinthView::OnCellChanged(size_t i, size_t j)
{
	m_visitedCells.push_back(&m_graphicsLabyrinth[i][j]);
}

bool CLabyrinthView::SubmissionCompleted()const
{
	return m_isNoVisitedCells().get();
}

void CLabyrinthView::NextStep()
{
	auto cellCordinates = m_pullVisitedCell().get();
	m_graphicsLabyrinth[cellCordinates.first][cellCordinates.second].VisitCell();
}

void CLabyrinthView::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	for (size_t i = 0; i != m_graphicsLabyrinth.size(); ++i)
	{
		for (size_t j = 0; j != m_graphicsLabyrinth.size(); ++j)
		{
			target.draw(m_graphicsLabyrinth[i][j], states);
		}
	}
}

void GraphicCell::VisitCell()
{
	if (getTextureRect().top == 0)
	{
		setTextureRect(IntRect(getTextureRect().left, getTextureRect().height, getTextureRect().width, getTextureRect().height));
	}
}
