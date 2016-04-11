#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace vector
{

typedef std::vector<std::vector<int> > BinaryInt;
typedef std::vector<std::vector<std::string> > BinaryStr;

struct Options
{
	size_t squareMatrixDimension;
	size_t stepsCount;
};

}

class CRouteFinder
{
public:
	CRouteFinder(vector::Options const &arrayOptions);
	void FindRoute(vector::BinaryInt const &inputArray);
	std::string GetRoute()const;
private:
	bool CellParamethersIsCorrect(int counter, int bound, int currentValue, int maxValue);
	void ResizeArrays();
	void SetNewCellParamethers(int &max, std::string &routeStr, size_t i, size_t j);
private:
	vector::BinaryInt m_valueArray;
	vector::BinaryStr m_strArray;
	vector::Options m_arrayOptions;
};