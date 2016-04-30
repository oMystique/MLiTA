#include "stdafx.h"
#include "Smugglers.h"

CSmugglersOperator::CSmugglersOperator(Graph && graph)
	: m_graph(std::move(graph))
{
}

int64_t CSmugglersOperator::DetermineGreatestLoad()
{
	int64_t greatestLoad = 0;
	auto checkedWays = m_graph.ways.at(m_graph.graphInfo.start);
	FindGreatestWay(checkedWays);
	return greatestLoad;
}

void CSmugglersOperator::FindGreatestWay(std::set<Target> const &checkedWays)
{
	for (auto way : checkedWays)
	{

	}
}
