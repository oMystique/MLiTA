#include "stdafx.h"
#include "GraphReader.h"
#include "Smugglers.h"
#include <fstream>

using namespace std;

int main()
{
	std::ifstream strm("input.txt");

	CGraphReader reader;
	try
	{
		auto graph = reader.ReadGraph(strm);

		//cout << graph.graphInfo.settlementsNumber << " "
		//	<< graph.graphInfo.roadNumber << " "
		//	<< graph.graphInfo.start << " "
		//	<< graph.graphInfo.end
		//	<< endl;

		//for (auto i : graph.ways)
		//{
		//	std::cout << i.first;
		//	for (auto j : i.second)
		//	{
		//		std::cout << " {" << j.end << ", " << j.cost << '}';
		//	}
		//	cout << endl;
		//}

		CSmugglersOperator oper(std::move(graph));
		cout << oper.DetermineGreatestLoad() << endl;

	}
	catch (std::exception const &ex)
	{
		cout << ex.what() << endl;
		return 1;
	}

	return 0;
}

