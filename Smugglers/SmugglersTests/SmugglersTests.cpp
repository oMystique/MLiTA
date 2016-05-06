// SmugglersTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Smugglers/GraphReader.h"
#include "../Smugglers/Smugglers.h"
#include <fstream>
#include <memory>

BOOST_AUTO_TEST_SUITE(Smugglers_Tests)

	struct program_components_
	{
		void ProgramProcess(std::string const &fileName, int64_t output)
		{
			auto graph = reader.ReadGraph(std::ifstream(fileName));
			smugglersOperator = std::make_unique<CSmugglersOperator>(std::move(graph));
			BOOST_CHECK_EQUAL(smugglersOperator->DetermineGreatestLoad(), output);
		}

		std::unique_ptr<CSmugglersOperator> smugglersOperator;
		CGraphReader reader;
	};

	BOOST_FIXTURE_TEST_SUITE(trivial_tests, program_components_)
	
		BOOST_AUTO_TEST_CASE(trivial_test_1)
		{
			ProgramProcess("input.txt", 5);
		}

		BOOST_AUTO_TEST_CASE(trivial_test_2)
		{
			ProgramProcess("input1.txt", 4);
		}

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(non_trivial_tests, program_components_)

		BOOST_AUTO_TEST_CASE(non_trivial_test_1)
		{
			ProgramProcess("input5.txt", 6);
		}

		BOOST_AUTO_TEST_CASE(non_trivial_test_2)
		{
			BOOST_CHECK_THROW(ProgramProcess("input2.txt", 0), std::exception);
		}

		BOOST_AUTO_TEST_CASE(non_trivial_test_3)
		{
			BOOST_CHECK_THROW(ProgramProcess("input3.txt", 0), std::exception);
		}

		BOOST_AUTO_TEST_CASE(non_trivial_test_4)
		{
			BOOST_CHECK_THROW(ProgramProcess("input6.txt", 0), std::exception);
		}

		BOOST_AUTO_TEST_CASE(non_trivial_test_5)
		{
			BOOST_CHECK_THROW(ProgramProcess("input7.txt", 0), std::exception);
		}

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(maximum_dimension_tests, program_components_)

		BOOST_AUTO_TEST_CASE(max_dimension_test_1)
		{
			ProgramProcess("input4.txt", 9);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
