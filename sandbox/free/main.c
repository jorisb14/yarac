
/**
 * @file main.c
 *
 * @copyright This file is a part of the project yaralang and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-11-04
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

struct Vec2
{
	float x, y;
};

int main(
	void)
{
	FILE* file = fopen("./test.txt", "r");
	signed long long length = 0;
	char* line = NULL;

	do
	{
		fprintf(stdout, "+--------------------+\n");
		length = 0;
		signed char isEnd = 0;

		char c = 0;
		do
		{
			c = fgetc(file);
			if (c == '\n') break;
			if (c == EOF) { if (length == 0) { length = -1; break; } isEnd = 1; break; }
			++(length);
		} while (c != EOF);

		if (length == -1)
		{
			continue;
		}

		length = length != 0 ? length + 1 : length;
		fseek(file, -length, SEEK_CUR);
		// fprintf(stdout, "%d\n", (int));

		if (line != NULL)
			free(line);

		line = (char*)malloc((length + 1) * sizeof(char));
		fgets(line, length + 1, file);
		fprintf(stdout, "%s\n", line);
		line[length] = 0;

		fprintf(stdout, "isEnd=%d\nlength=%lld\nstrlen(line)=%lld\n\n", (int)isEnd, length, strlen(line));
		getchar();
	} while (length != -1);
	fprintf(stdout, "+--------------------+\n");
	fprintf(stdout, "END\n");
	free(line);

	/*
	struct Vec2* vec = NULL; // malloc(sizeof(struct Vec2));
	free(vec);

	const char* c = "Hello!";
	void** l = (void**)&c;
	free((void*)*l);
	*/

	/*
	unsigned char data[4] = { 0, 0x02, 1, 0 };
	signed short i = *(signed short*)data;
	fprintf(stdout, "%d\n", i);
	*/

	/*
	signed int i = INT32_MAX - 10;
	signed short s = (signed short)i;
	fprintf(stdout, "%d -> %d (max=%d)\n", i, s, INT16_MAX);
	*/

	/*
	{
		unsigned long long format = 0;
		Lexer_detectNumericLiteralFormat("12345", 5, &format);
		fprintf(stdout, "%llu\n\n", format);
	}

	{
		unsigned long long format = 0;
		Lexer_detectNumericLiteralFormat("0xff00ffu", 9, &format);
		fprintf(stdout, "%llu\n\n", format);
	}

	{
		unsigned long long format = 0;
		Lexer_detectNumericLiteralFormat("3.14e4", 6, &format);
		fprintf(stdout, "%llu\n\n", format);
	}
	*/

#if 0
	// const char* str = "56i labas jeieiei";
	const char* str =
		"3.14e-4";

	float i;
	int n;

	int res = sscanf(str, "%E%n", &i, &n);
	fprintf(stdout, "%d\n", res);

	if (res == 1)
	{
		fprintf(stdout, "i=%f\n", i);
		fprintf(stdout, "n=%d\n", n);
	}



	float var = 1.54334E-34;
	double var2 = 1.54334E-34;

	printf("\n normal:%f\n sci:%e \n or \n sci:%E   \n",var,var,var);
	printf("\n normal:%f\n sci:%e \n or \n sci:%E   \n",var2,var2* 1.0E3 ,var2 * 1.0e3);
#endif

	return 0;
}
