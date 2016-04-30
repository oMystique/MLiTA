#pragma once
#include <sstream>
#include "Graph.h"

class CGraphReader
{
public:
	Graph ReadGraph(std::istream &strm);
private:
	bool GraphInfoIsCorrect()const;
	void InsertElement(Target const &target, size_t start);
private:
	Ways m_ways;
	GraphInfo m_graphInfo;
};