
/**
 * @file main.c
 *
 * @copyright This file is a part of the project yarac and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-11-29
 */

#include <unit_tester.h>

#include <location.h>
#include <logger.h>
#include <rtm.h>
#include <containers.h>
#include <types.h>
#include <cli.h>
#include <lexer.h>

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

#define SAMPLES_DIR "./include/samples"

int main(
	void)
{
	// Intrinsics tokens test
	#include <samples/intrinsics.uth>

	// Keywords tokens test
	#include <samples/keywords.uth>

	// Decorators tokens test
	#include <samples/decorators.uth>

	// Literals tokens test
	#include <samples/literals.uth>

	// Invalid tokens test
	#include <samples/invalids.uth>

	// Identifiers tokens test
	#include <samples/identifiers.uth>

	// Comments tokens test
	#include <samples/comments.uth>

	// Lexer benchmarks
	#include <samples/lexer_benchmark.uth>

	// Final touches
	return !UT_EVAL_ALL();
}
