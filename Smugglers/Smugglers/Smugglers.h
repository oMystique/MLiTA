#pragma once
#include "Graph.h"
#include <vector>

class CSmugglersOperator
{
public:
	CSmugglersOperator(Graph &&graph);
	int64_t DetermineGreatestLoad();
private:
	void FindGreatestWay(std::set<Target> const &checkedWays);
private:
	Graph m_graph;
	std::vector<int64_t> m_visitedVertexs;
	std::vector<int64_t> m_maxCosts;
};