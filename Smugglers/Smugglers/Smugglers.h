#pragma once
#include "Graph.h"
#include <vector>

class CSmugglersOperator
{
public:
	CSmugglersOperator(Graph &&graph);
	int64_t DetermineGreatestLoad();
private:
	void FindGreatestWay(size_t edge,  int64_t &cost);
private:
	Graph m_graph;
	std::vector<int64_t> m_maxCosts;
};