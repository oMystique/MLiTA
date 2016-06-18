#include "stdafx.h"
#include "Canvas.h"
#include "LabyrinthParser.h"

namespace
{
const int FRAME_SWITCH_INTERVAL_MS = 120;
}

std::unique_ptr<CCanvas> CCanvas::Create(std::ifstream & file)
{
	auto canvas = std::make_unique<CCanvas>();

	if (canvas)
	{
		auto labyrinth = CLabyrinthParser::ParseFileToLabyrinth(file);
		canvas->Init(labyrinth);
		return canvas;
	}

	return nullptr;
}	

CLabyrinthView const &CCanvas::GetDrawableObject()const
{
	return *m_view;
}

bool CCanvas::OnUpdate(float &dt)
{
	if (m_view->SubmissionCompleted())
	{
		return false;
	}

	if (dt >= FRAME_SWITCH_INTERVAL_MS)
	{
		m_view->NextStep();
		dt = 0;
	}

	return true;
}

int CCanvas::GetOutput() const
{
	return m_model->GetLabyrinthWallsQuantity();
}

void CCanvas::Init(Labyrinth<Cell> const & labyrinth)
{
	m_model = std::make_unique<CLabyrinthModel>(labyrinth);
	m_view = std::make_unique<CLabyrinthView>(labyrinth);
	m_controller = std::make_unique<CLabyrinthController>();

	m_model->DoOnChangedCell(boost::bind(&CLabyrinthController::OnCellChanged, m_controller.get(), _1, _2));
	m_view->DoOnVisitedCell(boost::bind(&CLabyrinthController::GetVisitedCell, m_controller.get()));
	m_view->NoVisitedCells(boost::bind(&CLabyrinthController::IsNoChanges, m_controller.get()));

	m_model->FillWalls();
}

