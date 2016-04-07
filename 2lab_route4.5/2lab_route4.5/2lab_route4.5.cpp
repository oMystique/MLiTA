#include "routeFinder.h"

std::ifstream OpenFile(std::string const &fileName)
{
	std::ifstream inputFile;
	inputFile.open(fileName);
	return inputFile;
}

bool FileIsOpened(std::ifstream &inputFile)
{
	return inputFile.is_open();
}

bool CheckCorrectnessTaskOptions(int N, int K)
{
	return (((2 <= N) && (N <= 20) && (1 <= K) && (K <= 20)));
}

vector::Options ParseTaskOptions(std::ifstream &inputFile)
{
	vector::Options taskOptions;

	inputFile >> taskOptions.squareMatrixDimension;
	inputFile >> taskOptions.stepsCount;

	return taskOptions;
}

vector::BinaryInt ParsingFileToRouteArray(std::ifstream &inputFile, vector::Options &taskOptions)
{
	unsigned N = taskOptions.squareMatrixDimension;
	vector::BinaryInt routeArray(N + 1, std::vector<int>(N + 1));

	if (N != 0) 
	{
		for (unsigned i = 1; i <= N; ++i)
		{
			for (unsigned j = 1; j <= N; ++j)
			{
				inputFile >> routeArray[i][j];
			}
		}
	}

	return routeArray;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Invalid args count." << std::endl;
		return 1;
	}

	std::ifstream inputFile = OpenFile(argv[1]);

	if (!FileIsOpened(inputFile))
	{
		std::cout << "Could not open file." << std::endl;
		return 1;
	}

	vector::Options taskOptions = ParseTaskOptions(inputFile);
	if (!CheckCorrectnessTaskOptions(taskOptions.squareMatrixDimension, taskOptions.stepsCount))
	{
		std::cout << "Incorrect task options." << std::endl;
		return 1;
	}

	CRouteFinder routeFinder(taskOptions);
	routeFinder.FindRoute(ParsingFileToRouteArray(inputFile, taskOptions));
	
	std::cout << routeFinder.GetRoute() << std::endl;

    return 0;
}

