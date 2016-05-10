#include "stdafx.h"
#include "ExpressionConverter.h"
#include <sstream>
#include <boost/algorithm/string/replace.hpp>

using namespace std;
using boost::replace_all;

string CExpressionConverter::ToSuffixNotation(string const &expression)
{
	auto exprStrm = ConvertToElementsStream(expression);
	string element;

	while (exprStrm >> element)
	{
		if (element == ")")
		{
			AppendOperandsBeforeOpeningBracket();
			m_operationsStack.pop();
		}
		else if (element == "(")
		{
			m_operationsStack.push(element);
		}
		else if (element == "+" || element == "-" || element == "/" || element == "*")
		{
			ProceedWithOperands(element);
		}
		else
		{
			m_outputExpression += element + " ";
		}
	}

	PopAllOperands();

	return m_outputExpression.substr(0, m_outputExpression.size() - 1);
}

istringstream CExpressionConverter::ConvertToElementsStream(string const & expression)
{
	string tempStr(expression);

	replace_all(tempStr, "(", " ( ");
	replace_all(tempStr, ")", " ) ");

	return istringstream(tempStr);
}

int CExpressionConverter::GetOperandPriority(string const &op)
{
	switch (op[0])
	{
	case '*':
		return 3;
	case '/':
		return 3;
	case '+':
		return 2;
	case '-':
		return 2;
	case '(':
		return 1;
	}

	return 0;
}

void CExpressionConverter::AppendOperandsBeforeOpeningBracket()
{
	while (m_operationsStack.top() != "(")
	{
		m_outputExpression += m_operationsStack.top() + " ";
		m_operationsStack.pop();
	}
}

void CExpressionConverter::ProceedWithOperands(string const & op)
{
	if (m_operationsStack.empty())
	{
		m_operationsStack.push(op);
	}
	else
	{
		if (GetOperandPriority(m_operationsStack.top()) < GetOperandPriority(op))
		{
			m_operationsStack.push(op);
		}
		else
		{
			while (!m_operationsStack.empty() && GetOperandPriority(m_operationsStack.top()) >= GetOperandPriority(op))
			{
				m_outputExpression += m_operationsStack.top() + " ";
				m_operationsStack.pop();
			}
			m_operationsStack.push(op);
		}
	}
}

void CExpressionConverter::PopAllOperands()
{
	while (!m_operationsStack.empty())
	{
		m_outputExpression += m_operationsStack.top() + " ";
		m_operationsStack.pop();
	}
}
