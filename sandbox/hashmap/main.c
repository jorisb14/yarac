
/**
 * @file main.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-12-07
 */

#include "map.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_SAMPLE_TEST(input) \
	{ \
		const unsigned long long length = strlen(input); \
		 \
		for (int i = 0; i < 3; ++i) \
		{ \
			struct Hash64 h = hash64((const unsigned char*)input, length); \
			fprintf(stdout, "%llu ", h.value); \
		} \
		fprintf(stdout, "\n"); \
	}

int main(
	void)
{
	struct Map* map = NULL;

	assert(Map_create(&map, 100));
	assert(Map_push(&map, "main", "A main function"));
	assert(Map_push(&map, "fprintf", "A fprintf function"));
	assert(Map_push(&map, "stdout", "A stdout function"));
	assert(Map_push(&map, "stderr", "A stderr function"));
	assert(Map_push(&map, "stdin", "A stdin function"));
	assert(Map_push(&map, "putp64", "A putp64 function"));
	assert(Map_push(&map, "puti64", "A puti64 function"));
	assert(Map_push(&map, "putf64", "A putf64 function"));
	assert(Map_push(&map, "sqrt", "A sqrt function"));
	assert(Map_push(&map, "sqrt", "A sqrt funcstion"));
	assert(Map_push(&map, "sqrt", "A sqrt funcsgtdgsion"));
	assert(Map_push(&map, "sqrt", "A sqrt funcasfgtion"));
	assert(Map_push(&map, "sqrt", "A sqrt fungsgsction"));
	assert(Map_push(&map, "sqrt", "A sqrt sdas"));

	{
		const char* val = NULL;
		fprintf(stdout, "%d ", Map_get(&map, "main", (void**)&val));
		fprintf(stdout, "val = %s\n", val);
	}

	{
		const char* val = NULL;
		fprintf(stdout, "%d ", Map_get(&map, "stderr", (void**)&val));
		fprintf(stdout, "val = %s\n", val);
	}

	{
		const char* val = NULL;
		fprintf(stdout, "%d ", Map_get(&map, "putf64", (void**)&val));
		fprintf(stdout, "val = %s\n", val);
	}

	return 0;
}
