#include "stdafx.h"
#include "GraphReader.h"
#include "Smugglers.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		cout << "Incorrect args count." << endl;
		return 1;
	}

	try
	{
		ifstream strm(argv[1]);

		CGraphReader reader;

		auto graph = reader.ReadGraph(strm);

		CSmugglersOperator oper(std::move(graph));
		cout << oper.DetermineGreatestLoad() << endl;
	}
	catch (std::exception const &ex)
	{
		cout << ex.what() << endl;
		return 1;
	}
	catch (...)
	{
		cout << "Unknow error type." << endl;
		return 1;
	}

	return 0;
}

