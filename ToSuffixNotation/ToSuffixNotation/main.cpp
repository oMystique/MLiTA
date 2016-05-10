#include "stdafx.h"
#include "ExpressionConverter.h"
#include <iostream>

using namespace std;

int main()
{
	string inputStr;
	getline(cin, inputStr);

	CExpressionConverter exprConverter;
	cout << exprConverter.ToSuffixNotation(inputStr) << endl;

	return 0;
}
