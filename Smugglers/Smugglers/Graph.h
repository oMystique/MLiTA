#pragma once
#include <stdint.h>
#include <set>
#include <unordered_map>

struct GraphInfo
{
	size_t settlementsNumber = 0;
	size_t roadNumber = 0;
	size_t start = 0;
	size_t end = 0;
};

struct Target
{
	Target() = default;
	Target(size_t end, int64_t cost)
		: end(end)
		, cost(cost)
	{};

	size_t end = 0;
	int64_t cost = 0;
};

inline bool const operator <(Target const &target1, Target const &target2)
{
	return target2.cost < target1.cost;
}

using Targets = std::multiset<Target> ;
using Ways = std::unordered_map<size_t, Targets>;

struct Graph
{
	Graph(GraphInfo &&graphInfo, Ways &&ways)
		: graphInfo(std::move(graphInfo))
		, ways(std::move(ways))
	{};

	GraphInfo graphInfo;
	Ways ways;
};
