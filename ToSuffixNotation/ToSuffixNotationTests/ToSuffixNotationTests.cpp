// ToSuffixNotationTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../ToSuffixNotation/ExpressionConverter.h"

BOOST_AUTO_TEST_SUITE(to_suffix_notation_function_tests)

	struct declare_expression_converter_
	{
		CExpressionConverter exprConverter;
	};


	BOOST_FIXTURE_TEST_SUITE(trivial_tests, declare_expression_converter_)

		BOOST_AUTO_TEST_CASE(trivial_test_1)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("2.4 + 10 * ( 1 + 2 )"), "2.4 10 1 2 + * +");
		}

		BOOST_AUTO_TEST_CASE(trivial_test_2)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("(A + B) * (C + D) - E"), "A B + C D + * E -");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(non_trivial_tests, declare_expression_converter_)

		BOOST_AUTO_TEST_CASE(non_trivial_test_1)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("((2+2) * 2) * 2"), "2 2 + 2 * 2 *");
		}

		BOOST_AUTO_TEST_CASE(non_trivial_test_2)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("2 / (3 - (4 + (5 * 6)))"), "2 3 4 5 6 * + - /");
		}

		BOOST_AUTO_TEST_CASE(non_trivial_test_3_with_more_spaces)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("     8                + (4 / (3 + 2)) *    (3      + 4) / 2     "), "8 4 3 2 + / 3 4 + * 2 / +");
		}

		BOOST_AUTO_TEST_CASE(non_trivial_test_4)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("( 4 + 5 ) * x - (y / 2 + 15)"), "4 5 + x * y 2 / 15 + -");
		}

		BOOST_AUTO_TEST_CASE(operator_precedence_parsed_correct)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("a * d + b * c"), "a d * b c * +");
		}

		BOOST_AUTO_TEST_CASE(association_rules_test)
		{
			BOOST_CHECK_EQUAL(exprConverter.ToSuffixNotation("30 / 5 / 3 / 2"), "30 5 / 3 / 2 /");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

