#pragma once
#include "LabyrinthController.h"
#include "LabyrinthGraphic.h"

class CCanvas
{
public:
	static std::unique_ptr<CCanvas> Create(std::ifstream &file);

	CLabyrinthView const &GetDrawableObject()const;
	bool OnUpdate(float &dt);
	int GetOutput()const;
private:
	void Init(Labyrinth<Cell> const &labyrinth);
private:
	std::unique_ptr<CLabyrinthController> m_controller = nullptr;
	std::unique_ptr<CLabyrinthModel> m_model = nullptr;
	std::unique_ptr<CLabyrinthView> m_view = nullptr;
};