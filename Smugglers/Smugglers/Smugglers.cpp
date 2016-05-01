#include "stdafx.h"
#include "Smugglers.h"
#include <algorithm>

CSmugglersOperator::CSmugglersOperator(Graph && graph)
	: m_graph(std::move(graph))
{
}

void CSmugglersOperator::FindGreatestWay(size_t edge, int64_t &cost)
{
	for (auto way : m_graph.ways.at(edge))
	{
		if (m_graph.ways.find(way.end) != m_graph.ways.end())
		{
			if (cost > way.cost)
			{
				cost = way.cost;
			}
			if (edge != m_graph.graphInfo.start && edge != m_graph.graphInfo.end)
			{
				m_graph.ways.erase(edge);
				FindGreatestWay(way.end, cost);
			}
			return;
		}
	}
}

int64_t CSmugglersOperator::DetermineGreatestLoad()
{
	auto checkedWays = m_graph.ways.at(m_graph.graphInfo.start);

	for (auto way : checkedWays)
	{
		if (m_graph.ways.find(way.end) != m_graph.ways.end())
		{
			int64_t cost = way.cost;
			FindGreatestWay(way.end, cost);
			m_maxCosts.push_back(cost);
		}
	}

	if (m_maxCosts.size() <= 1)
	{
		throw std::exception("No.");
	}

	std::sort(m_maxCosts.begin(), m_maxCosts.end(), [](int64_t n1, int64_t n2) {return n1 < n2; });

	int64_t first = m_maxCosts[m_maxCosts.size() - 1];
	int64_t second = m_maxCosts[m_maxCosts.size() - 2];

	return (first < second) ? first : second;
}
