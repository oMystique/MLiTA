#pragma once
#include <string>
#include <stack>

using OperationsStack = std::stack<std::string>;

class CExpressionConverter
{
public:
	std::string ToSuffixNotation(const std::string &expression);
private:
	static std::istringstream ConvertToElementsStream(std::string const &expression);
	int OperationPriority(std::string const &op)const;
	void AppendOperandsBeforeOpeningBracket();
	void ProceedWithOperands(std::string const &op);
	void PopAllOperands();
private:
	OperationsStack m_operationsStack;
	std::string m_outputExpression;
};