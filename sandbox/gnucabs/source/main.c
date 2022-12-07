
#include <vec.h>

int main(
	void)
{
	struct Vec vec = { 5, 7 };
	Vec_print((const struct Vec* const)&vec);

#if YARAC_DEBUG
	vec.x = 69; vec.y = 420;
	Vec_print((const struct Vec* const)&vec);
#endif

	return 0;
}
