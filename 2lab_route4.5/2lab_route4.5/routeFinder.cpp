#include "routeFinder.h"


CRouteFinder::CRouteFinder(vector::Options const &options)
	: m_arrayOptions(options)
{
}

bool CRouteFinder::CellParamethersIsCorrect(int counter, int bound, int currentValue, int maxValue)
{
	return ((counter <= bound) && (currentValue > maxValue));
}

void CRouteFinder::ResizeArrays()
{
	m_valueArray.resize(m_arrayOptions.squareMatrixDimension + 2,
		std::vector<int>(m_arrayOptions.squareMatrixDimension + 2, 0));

	m_strArray.resize(m_arrayOptions.squareMatrixDimension + 1,
		std::vector<std::string>(m_arrayOptions.squareMatrixDimension + 1, ""));
}

void CRouteFinder::SetNewCellParamethers(int & max, std::string & routeStr, size_t i, size_t j)
{
	max = m_valueArray[i][j];
	routeStr = m_strArray[i][j];
}

void CRouteFinder::FindRoute(const vector::BinaryInt &inputArray)
{
	ResizeArrays();

	m_valueArray[1][1] = inputArray[1][1];
	m_strArray[1][1] = "1 1";

	int max;
	std::string routeStr;

	for (size_t stepsCounter = 1; stepsCounter <= m_arrayOptions.stepsCount; ++stepsCounter)
	{
		for (size_t i = 1; i <= m_arrayOptions.squareMatrixDimension; ++i)
		{
			for (size_t j = 1; j <= m_arrayOptions.squareMatrixDimension; ++j)
			{
				if (((i + j) % 2) != (stepsCounter % 2))
				{
					max = 0;
					routeStr = "";

					if (CellParamethersIsCorrect(i, m_arrayOptions.squareMatrixDimension, m_valueArray[i + 1][j] > max, max))
					{
						SetNewCellParamethers(max, routeStr, i + 1, j);
					}
					if (CellParamethersIsCorrect(1, i, m_valueArray[i - 1][j], max))
					{
						SetNewCellParamethers(max, routeStr, i - 1, j);
					}
					if (CellParamethersIsCorrect(1, j, m_valueArray[i][j - 1], max))
					{
						SetNewCellParamethers(max, routeStr, i, j - 1);
					}
					if (CellParamethersIsCorrect(j, m_arrayOptions.squareMatrixDimension, m_valueArray[i][j + 1], max))
					{
						SetNewCellParamethers(max, routeStr, i, j + 1);
					}
					if (max != 0)
					{
						m_valueArray[i][j] = max + inputArray[i][j];
						m_strArray[i][j] = routeStr + "\n" + std::to_string(i) + " " + std::to_string(j);
					}
				}
			}
		}
	}

}

std::string CRouteFinder::GetRoute()const
{
	int max = 0;
	std::string routeStr;

	for (size_t i = 0; i <= m_arrayOptions.squareMatrixDimension; ++i)
	{
		for (size_t j = 0; j <= m_arrayOptions.squareMatrixDimension; ++j)
		{
			if (m_valueArray[i][j] > max)
			{
				max = m_valueArray[i][j];
				routeStr = m_strArray[i][j];
			}
		}
	}

	routeStr.insert(0, std::to_string(max) + "\n");

	return routeStr;
}
