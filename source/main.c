
/**
 * @file main.c
 *
 * @copyright This file is a part of the project yarac and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-10-30
 */

#include <location.h>
#include <logger.h>
#include <rtm.h>
#include <containers.h>
#include <types.h>
#include <cli.h>
#include <lexer.h>
#include <parser.h> // TODO: implement parser!
#include <linker.h> // TODO: implement linker!

// TODO: make debug-only!
#include <debug/utils.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static signed char Yarac_main(
	signed int* const argc,
	const char*** const argv,
	signed char* const succeeded);

#define W_Yarac_main(_inmacro_argc, _inmacro_argv, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Yarac_main((_inmacro_argc), (_inmacro_argv), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Yarac_main(...) returned with internal failure!"); \
			_inmacro_internalFailCallback \
		} \
		else \
		{ \
			if (!(*(_inmacro_succeeded))) \
			{ \
				_inmacro_logicalFailCallback \
			} \
			else \
			{ \
				_inmacro_successCallback \
			} \
		} \
	}

int main(
	signed int argc,
	const char** argv)
{
	signed char succeeded = 0;

	W_Yarac_main(&argc, (const char*** const)&argv, &succeeded,
	{
		succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to run the yarac compiler!!");
		// succeeded = 0;
		return 0;
	},
	{});

	succeeded = 1;
	return !(succeeded == 1);
}

static signed char Yarac_main(
	signed int* const argc,
	const char*** const argv,
	signed char* const succeeded)
{
	if (argc == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `argc` is invalid (null)!");
		return 0;
	}

	if (argv == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `argv` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	// Parsing command-line arguments
	struct CLI_Args* args = NULL;

	W_CLI_Args_create((struct CLI_Args** const)&args, succeeded,
	{
		*succeeded = 0;
		goto global_cleanup;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
			"failed to create cli arguments container!");
		// *succeeded = 0;
		goto global_cleanup;
	},
	{});

	W_CLI_tryParseArgs(argc, argv, &args, succeeded,
	{
		*succeeded = 0;
		goto global_cleanup;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
			"failed to parse command-line arguments!");
		// *succeeded = 0;
		goto global_cleanup;
	},
	{});

	// Compile everything
	struct Vector* tokens = NULL;

	W_Vector_create((struct Vector** const)&tokens, 4, succeeded,
	{
		*succeeded = 0;
		goto global_cleanup;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to create vector container!");
		// *succeeded = 0;
		goto global_cleanup;
	},
	{});

	for (struct List_Node* sourcesIterator = args->sources->head; sourcesIterator != NULL; sourcesIterator = sourcesIterator->next)
	{
		const char* source = (const char*)sourcesIterator->data;
		const unsigned long long sourceLength = strlen(source);
		(void)sourceLength;

		W_Lexer_lexFile(source, &tokens, succeeded,
		{
			goto local_tokens_cleanup;
		},
		{
			W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
				"failed to lex file: %s!",
				source);
			goto local_tokens_cleanup;
		},
		{
			W_Lexer_validateTokens(source, (const struct Vector* const * const)&tokens, succeeded,
			{
				*succeeded = 0;
				goto local_tokens_cleanup;
			},
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"failed to validate file: %s!",
					source);
				// *succeeded = 0;
				goto local_tokens_cleanup;
			},
			{});
		});

#if YARAC_DEBUG
		for (unsigned long long index = 0; index < tokens->count; ++index)
		{
			signed char temp = 0;
			struct Token* token = NULL;

			W_Vector_getAt((struct Vector* const * const)&tokens, index, (void** const)&token, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				// TODO: log!
				// *succeeded = 0;
				return 1;
			},
			{});

			Token_print(stdout, (const struct Token* const * const)&token, 0, &temp);
		}
#endif

#if 0
		struct Frame* frame = NULL;

		W_Parser_parseFrame(&tokens, &frame, succeeded,
		{
			*succeeded = 0;
			goto local_frame_cleanup;
		},
		{
			W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
				"failed to parse frame for file: %s!",
				(const char*)source);
			// *succeeded = 0;
			goto local_frame_cleanup;
		},
		{
			FILE* file = fopen("./frame.txt", "w");

			W_Frame_serialize((const struct Frame* const * const)&frame, file, succeeded,
			{},
			{},
			{});

			/*
			// TODO: Save meta data!
			// TODO: rework this:
			signed char temp = 0;
			FILE* file = fopen("meta.out", "w");
			assert(file != NULL);
			Frame_print(file, (const struct Frame* const * const)&frame, 0, &temp);
			fclose(file);
			*/
		});

local_frame_cleanup:
		W_Frame_destroy(&frame, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to destroy include directories list!");
			// *succeeded = 0;
			goto global_cleanup;
		},
		{});
#endif

local_tokens_cleanup:
		for (unsigned long long index = 0; index < tokens->count; ++index)
		{
			struct Token* token = NULL;

			W_Vector_getAt((struct Vector* const * const)&tokens, index, (void** const)&token, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				// TODO: log!
				// *succeeded = 0;
				return 1;
			},
			{});

			W_Token_destroy((const struct Token* const * const)&token, succeeded,
			{
				*succeeded = 0;
			},
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"failed to destroy a token!",
					(const char*)source);
				// *succeeded = 0;
			},
			{});
		}

		// W_Vector_destroy((const struct Vector* const * const)&tokens, succeeded,
		// {
		// 	*succeeded = 0;
		// },
		// {
		// 	W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
		// 		"failed to destroy tokens list!");
		// 	// *succeeded = 0;
		// },
		// {});

		// Restart setting the tokens without modifying vector's buffer:
		tokens->count = 0;
	}

	W_Vector_destroy((const struct Vector* const * const)&tokens, succeeded,
	{
		*succeeded = 0;
		goto global_cleanup;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to destroy vector container!");
		// *succeeded = 0;
		goto global_cleanup;
	},
	{});

global_cleanup:
	W_CLI_Args_destroy((const struct CLI_Args* const * const)&args, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to destroy cli args!");
		*succeeded = 0;
		return 1;
	},
	{});

	// *succeeded = ?;
	return 1;
}
