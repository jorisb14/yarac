
/**
 * @file main.c
 *
 * @copyright This file is a part of the project yaralang and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-11-01
 */

signed char Vec2_add(
	const int x1,
	const int y1,
	const int x2,
	const int y2,
	int* const x3,
	int* const y3)
{
	if (x3 == (void*)0
	 || y3 == (void*)0)
	{
		return 0;
	}

	*x3 = x1 + x2;
	*y3 = y1 + y2;
	return 1;
}

int _start(
	void)
{
	int x, y;

	if (!Vec2_add(2, 3, 4, 5, &x, &y))
	{
		return 1;
	}

	return 0;
}
