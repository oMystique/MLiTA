#include "stdafx.h"
#include "GraphReader.h"
#include <iostream>

Graph CGraphReader::ReadGraph(std::istream & strm)
{
	strm >> m_graphInfo.settlementsNumber
		>> m_graphInfo.roadNumber
		>> m_graphInfo.start
		>> m_graphInfo.end;

	if (!GraphInfoIsCorrect())
	{
		throw std::exception("Incorrect input data.");
	}

	while (!strm.eof())
	{
		size_t start;
		Target target;
		strm >> start >> target.end >> target.cost;

		InsertElement(target, start);
		std::swap(start, target.end);
		InsertElement(target, start);
	}

	return Graph(std::move(m_graphInfo), std::move(m_ways));
}

bool CGraphReader::GraphInfoIsCorrect()const
{
	return ((3 <= m_graphInfo.settlementsNumber) 
		&& (m_graphInfo.settlementsNumber <= 30)
		&& (m_graphInfo.start != m_graphInfo.end));
}

void CGraphReader::InsertElement(Target const & target, size_t start)
{
	if (start == 0 || target.end == 0)
	{
		return;
	}

	if (m_ways.find(start) != m_ways.end())
	{
		m_ways.at(start).emplace(target);
	}
	else
	{
		Targets targets;
		targets.emplace(target);
		m_ways.emplace(start, targets);
	}
}
