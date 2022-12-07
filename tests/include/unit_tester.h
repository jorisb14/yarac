
/**
 * @file unit_tester.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-29
 */

#ifndef _UNIT_TESTER_H_
#define _UNIT_TESTER_H_

#include <stdlib.h>

/**
 * @addtogroup unit_tester
 * 
 * @{
 */

struct UT_Test
{
	const char* name;
	signed char result;
};

void UT_assert(
	const char* expressionString,
	signed char expression,
	struct UT_Test* const test);

#define UT_ASSERT_TRUE(test, expression) \
	{ \
		UT_assert(#expression, (expression), test); \
	}

#define UT_ASSERT_FALSE(test, expression) \
	{ \
		UT_assert(#expression, !(expression), test); \
	}

struct UT_Test* UT_addTest(
	const char* name);

void UT_evalTest(
	struct UT_Test* test);

#define UT_ADD_TEST(name, body) \
	{ \
		struct UT_Test* name = UT_addTest(#name); \
		if (name == NULL) return 1; \
		body \
		UT_evalTest(name); \
	}

#define UT_LOG(...) \
	fprintf(__VA_ARGS__)

signed char UT_evalAll(
	void);

#define UT_EVAL_ALL() \
	UT_evalAll()

/**
 * @}
 */

#endif
