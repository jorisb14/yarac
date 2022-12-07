
/**
 * @file unit_tester.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-29
 */

#include <unit_tester.h>

#include <stdlib.h>
#include <stdio.h>

/**
 * @addtogroup unit_tester
 * 
 * @{
 */

#define RED(str) "\033[0;31m"str"\033[0m"
#define YELLOW(str) "\033[0;33m"str"\033[0m"
#define GREEN(str) "\033[0;32m"str"\033[0m"

static unsigned long long _testsCount = 0;
static struct UT_Test _tests[UT_TESTS_CAP] = {0};

void UT_assert(
	const char* expressionString,
	signed char expression,
	struct UT_Test* const test)
{
	signed char result = expression;

	if (test->result != 0)
	{
		test->result = expression;
	}

#if UT_SUPRESS_LOGS
	(void)expressionString;
	(void)result;
#else
	if (result)
	{
		fprintf(stdout, "   [%s] -> %s\n", expressionString, GREEN("ok"));
	}
	else
	{
		fprintf(stdout, "   [%s] -> %s\n", expressionString, RED("error"));
	}
#endif
}

struct UT_Test* UT_addTest(
	const char* name)
{
	if (_testsCount + 1 > UT_TESTS_CAP)
	{
		fprintf(stdout, "%s", YELLOW("Failed to add new test - reached tests capacity! Try to change UT_TESTS_CAP env variable in the .run.sh script...\n"));
		return NULL;
	}

	fprintf(stdout, "Running %s:\n", name);

	struct UT_Test test = {0};
	test.name = name;
	test.result = -1;
	_tests[_testsCount] = test;
	return &_tests[_testsCount++];
}

void UT_evalTest(
	struct UT_Test* test)
{
	if (test->result)
	{
		fprintf(stdout, " > UT_Test %s %s!\n", test->name, GREEN("passed"));
	}
	else
	{
		fprintf(stdout, " > UT_Test %s %s!\n", test->name, RED("failed"));
	}

	fprintf(stdout, "\n");
}

signed char UT_evalAll(
	void)
{
	unsigned long long good = 0;
	unsigned long long bad = 0;

	for (unsigned long long i = 0; i < _testsCount; ++i)
	{
		if (_tests[i].result) ++good;
		else ++bad;
	}

	fprintf(stdout, "Results: %llu %s and %llu %s...\n", good, GREEN("passed"), bad, RED("failed"));
	return bad == 0;
}

/**
 * @}
 */
