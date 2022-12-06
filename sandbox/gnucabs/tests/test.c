
#include <vec.h>

int main(
	void)
{
	const struct Vec vec = { 2, 9 };
	Vec_print((const struct Vec* const)&vec);
	return 0;
}
