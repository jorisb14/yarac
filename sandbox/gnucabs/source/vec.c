
#include <vec.h>

#include <stdio.h>

void Vec_print(
	const struct Vec* const vec)
{
	fprintf(stdout, "vec=[x=%d, y=%d]\n", vec->x, vec->y);
}
