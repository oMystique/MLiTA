#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<int> > BinaryIntVector;
typedef vector<vector<string> > BinaryStrVector;

struct TaskOptions 
{
	int N;
	int K;
};

struct OutputData
{
	BinaryIntVector routeIntArray;
	BinaryStrVector routeStrArray;
};

ifstream OpenFile()
{
	ifstream inputFile;
	inputFile.open("input.txt");
	return inputFile;
}

bool FileIsOpened(ifstream &inputFile)
{
	return inputFile.is_open();
}

bool CheckCorrectnessTaskOptions(int N, int K)
{
	return (((2 <= N) && (N <= 20) && (1 <= K) && (K <= 20)));
}

TaskOptions GetTaskOptions(ifstream &inputFile)
{
	TaskOptions taskOptions;

	inputFile >> taskOptions.N;
	inputFile >> taskOptions.K;

	if (!CheckCorrectnessTaskOptions(taskOptions.N, taskOptions.K)) 
	{
		taskOptions.N = 0;
		taskOptions.K = 0;
	}

	return taskOptions;
}

BinaryIntVector ParsingFileToRouteArray(ifstream &inputFile, TaskOptions &taskOptions)
{
	taskOptions = GetTaskOptions(inputFile);
	unsigned N = taskOptions.N;
	BinaryIntVector routeArray(N + 1, vector<int>(N + 1));

	if (N != 0) {
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

void SetParamethers(int &max, string &tempStr, OutputData const &outputData, int i, int j)
{
	max = outputData.routeIntArray[i][j];
	tempStr = outputData.routeStrArray[i][j];
}

OutputData GetRoute(BinaryIntVector const &inputArray, TaskOptions const &taskOptions)
{
	OutputData outputData;

	outputData.routeIntArray.resize(taskOptions.N + 2, vector<int>(taskOptions.N + 2, 0));
	outputData.routeIntArray[1][1] = inputArray[1][1];

	outputData.routeStrArray.resize(taskOptions.N + 1, vector<string>(taskOptions.N + 1, ""));
	outputData.routeStrArray[1][1] = "1 1";

	int max = 0;
	string tempStr;
	for (int kCounter = 1; kCounter <= taskOptions.K; ++kCounter)
	{
		for (int i = 1; i <= taskOptions.N; ++i)
		{
			for (int j = 1; j <= taskOptions.N; ++j)
			{
				if (((i + j) % 2) != (kCounter % 2)) {
					max = 0;
					tempStr = "";
					if ((i <= taskOptions.N) && (outputData.routeIntArray[i + 1][j] > max))
					{
						SetParamethers(max, tempStr, outputData, i + 1, j);
					}
					if ((i > 0) && (outputData.routeIntArray[i - 1][j] > max))
					{
						SetParamethers(max, tempStr, outputData, i - 1, j);
					}
					if ((j  > 0) && (outputData.routeIntArray[i][j - 1] > max))
					{
						SetParamethers(max, tempStr, outputData, i, j - 1);
					}
					if ((j <= taskOptions.N) && (outputData.routeIntArray[i][j + 1] > max))
					{
						SetParamethers(max, tempStr, outputData, i, j + 1);
					}
					if (max != 0)
					{
						outputData.routeIntArray[i][j] = max + inputArray[i][j];
						outputData.routeStrArray[i][j] = tempStr + "\n" + to_string(i) + " " + to_string(j);
					}
				}
			}
		}
	}
	return outputData;
}

void PrintResults(OutputData const &outputData, TaskOptions const &taskOptions)
{
	int max = 0;
	string tempStr;
	for (int i = 0; i <= taskOptions.N; ++i)
	{
		for (int j = 0; j <= taskOptions.N; ++j)
		{
			if (outputData.routeIntArray[i][j] > max)
			{
				max = outputData.routeIntArray[i][j];
				tempStr = outputData.routeStrArray[i][j];
			}
		}
	}
	cout << max << endl << tempStr << endl;
}

int main()
{
	ifstream inputFile = OpenFile();

	if (!FileIsOpened(inputFile))
	{
		cout << "Could not open file" << endl;
		return 1;
	}

	TaskOptions taskOptions;
	BinaryIntVector inputArray = ParsingFileToRouteArray(inputFile, taskOptions);

	auto outputRoute = GetRoute(inputArray, taskOptions);
	PrintResults(outputRoute, taskOptions);
	
	return 0;
}