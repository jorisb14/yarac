
/**
 * @file cli.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-02
 */

#include <cli.h>
#include <rtm.h>
#include <logger.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @addtogroup cli
 * 
 * @{
 */

/**
 * Display usage banner to the provided stream. Return 0 in case of an error and 1 in case of a
 * success. Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(CLI_usage(stdout, arg0, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char CLI_usage(
	FILE* const stream,
	const char* const arg0,
	signed char* const succeeded);

#define W_CLI_usage(_inmacro_stream, _inmacro_arg0, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!CLI_usage((_inmacro_stream), (_inmacro_arg0), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function CLI_usage(...) returned with internal failure!"); \
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

/**
 * Shift argv array and return the shifted arg.. Return 0 in case of an error and 1 in case of a
 * success. Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     const char* shifted;
 *     assert(CLI_shift(&argc, &argv, &shifted, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char CLI_shift(
	int* const argc,
	const char*** const argv,
	const char** const shifted,
	signed char* const succeeded);

#define W_CLI_shift(_inmacro_argc, _inmacro_argv, _inmacro_shifted, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!CLI_shift((_inmacro_argc), (_inmacro_argv), (_inmacro_shifted), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function CLI_shift(...) returned with internal failure!"); \
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

signed char CLI_Args_create(
	struct CLI_Args** const args,
	signed char* const succeeded)
{
	if (args == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `args` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	W_RTM_malloc((const void** const)args, sizeof(struct CLI_Args), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to allocate memory for cli args block!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*args)->includeDirectories = NULL;

	W_List_create((struct List** const)&((*args)->includeDirectories), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to create include directories list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*args)->sources = NULL;

	W_List_create((struct List** const)&((*args)->sources), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to create surces list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*args)->outputFormat = NULL;
	(*args)->artefactsDirectory = NULL;
	(*args)->optimizationMode = NULL;

	*succeeded = 1;
	return 1;
}

signed char CLI_Args_destroy(
	const struct CLI_Args* const * const args,
	signed char* const succeeded)
{
	if (args == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `args` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	W_List_destroy((const struct List* const * const)&((*args)->includeDirectories), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to create include directories list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_List_destroy((const struct List* const * const)&((*args)->sources), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to create surces list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_RTM_free((const void* const * const)args, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to deallocate memory for cli args block!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char CLI_tryParseArgs(
	signed int* const argc,
	const char*** const argv,
	struct CLI_Args* const * const args,
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

	if (args == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `args` is invalid (null)!");
		return 0;
	}

	if (*args == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `args`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;
	const char* arg0 = NULL;
	
	W_CLI_shift(argc, argv, &arg0, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to shift the argv array!");
		// *succeeded = 0;
		return 1;
	},
	{});

	if (*argc <= 0)
	{
		W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
			"no command-line arguments were provided!");

		W_CLI_usage(stderr, arg0, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to display usage banner!");
			// *succeeded = 0;
			return 1;
		},
		{});

		*succeeded = 0;
		return 1;
	}

	while (*argc > 0)
	{
		const char* flag = NULL;
		
		W_CLI_shift(argc, argv, &flag, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to shift the argv array!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (flag == NULL)
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"encountered flag was invalid (null)!");

			W_CLI_usage(stderr, arg0, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to display usage banner!");
				// *succeeded = 0;
				return 1;
			},
			{});

			*succeeded = 0;
			return 0;
		}

		if (strncmp(flag, "--include-dir", 13) == 0 || strncmp(flag, "-id", 3) == 0)
		{
			if (*argc <= 0)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"no command-line value provided for flag `%s`!",
					flag);

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 1;
			}

			W_CLI_shift(argc, argv, &flag, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to shift the argv array!");
				// *succeeded = 0;
				return 1;
			},
			{});

			if (flag == NULL)
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"encountered flag was invalid (null)!");

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 0;
			}

			W_List_pushLast(&((*args)->includeDirectories), (void*)flag, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add include directory to include directories list!");
				// *succeeded = 0;
				return 0;
			},
			{});
		}
		else if (strncmp(flag, "--output-format", 15) == 0 || strncmp(flag, "-of", 3) == 0)
		{
			if ((*args)->outputFormat != NULL)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
					"repeating --output-format | -of flag!");

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 1;
			}

			if (*argc <= 0)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"no command-line value provided for flag `%s`!",
					flag);

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 1;
			}

			W_CLI_shift(argc, argv, &flag, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to shift the argv array!");
				// *succeeded = 0;
				return 1;
			},
			{});

			if (flag == NULL)
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"encountered flag was invalid (null)!");

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 0;
			}

			(*args)->outputFormat = flag;

			if (strncmp((*args)->outputFormat, "nasm", 4) != 0 && strncmp((*args)->outputFormat, "o", 1) != 0)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"invalid --output-format | -of flag value provided: %s!",
					(*args)->outputFormat);
				*succeeded = 0;
				return 1;
			}
		}
		else if (strncmp(flag, "--artefacts-dir", 16) == 0 || strncmp(flag, "-ad", 3) == 0)
		{
			if ((*args)->artefactsDirectory != NULL)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
					"repeating --artefacts-dir | -ad flag!");

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 1;
			}

			if (*argc <= 0)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"no command-line value provided for flag `%s`!",
					flag);

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 1;
			}

			W_CLI_shift(argc, argv, &flag, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to shift the argv array!");
				// *succeeded = 0;
				return 1;
			},
			{});

			if (flag == NULL)
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"encountered flag was invalid (null)!");

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 0;
			}

			(*args)->artefactsDirectory = flag;
		}
		else if (strncmp(flag, "--optimizations-mode", 16) == 0 || strncmp(flag, "-om", 3) == 0)
		{
			if ((*args)->optimizationMode != NULL)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
					"repeating --optimizations-mode | -om flag!");

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 1;
			}

			if (*argc <= 0)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"no command-line value provided for flag `%s`!",
					flag);

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 1;
			}

			W_CLI_shift(argc, argv, &flag, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to shift the argv array!");
				// *succeeded = 0;
				return 1;
			},
			{});

			if (flag == NULL)
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"encountered flag was invalid (null)!");

				W_CLI_usage(stderr, arg0, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
						"failed to display usage banner!");
					// *succeeded = 0;
					return 1;
				},
				{});

				*succeeded = 0;
				return 0;
			}

			(*args)->optimizationMode = flag;

			if (strncmp((*args)->optimizationMode, "none", 4) != 0 && strncmp((*args)->optimizationMode, "size", 4) != 0 && strncmp((*args)->optimizationMode, "speed", 5) != 0 && strncmp((*args)->optimizationMode, "all", 3) != 0)
			{
				W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
					"invalid --optimizations-mode | -om flag value provided: %s!",
					(*args)->optimizationMode);
				*succeeded = 0;
				return 1;
			}
		}
		else if (strncmp(flag, "--help", 6) == 0 || strncmp(flag, "-h", 2) == 0)
		{
			W_CLI_usage(stdout, arg0, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to display usage banner!");
				// *succeeded = 0;
				return 1;
			},
			{});

			*succeeded = 1;
			return 1;
		}
		else
		{
			W_List_pushLast(&((*args)->sources), (void*)flag, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add source to sources list!");
				// *succeeded = 0;
				return 0;
			},
			{});
		}
	}

	if ((*args)->outputFormat == NULL || ((*args)->outputFormat != NULL && strlen((*args)->outputFormat) <= 0))
	{
		(*args)->outputFormat = "nasm";
	}

	if ((*args)->artefactsDirectory == NULL || ((*args)->artefactsDirectory != NULL && strlen((*args)->artefactsDirectory) <= 0))
	{
		(*args)->artefactsDirectory = "/temp/yarac";
	}

	if ((*args)->optimizationMode == NULL || ((*args)->optimizationMode != NULL && strlen((*args)->optimizationMode) <= 0))
	{
		(*args)->optimizationMode = "none";
	}

	if ((*args)->sources->count <= 0)
	{
		W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
			"no source files were provided!");

		W_CLI_usage(stdout, arg0, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to display usage banner!");
			// *succeeded = 0;
			return 1;
		},
		{});

		*succeeded = 0;
		return 1;
	}

	*succeeded = 1;
	return 1;
}

static signed char CLI_usage(
	FILE* const stream,
	const char* const arg0,
	signed char* const succeeded)
{
	if (stream == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `stream` is invalid (null)!");
		return 0;
	}

	if (arg0 == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `arg0` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	fprintf(stream,
		"  ___    ___ ________  ________  ________  ________      \n"
		" |\\  \\  /  /|\\   __  \\|\\   __  \\|\\   __  \\|\\   ____\\     \n"
		" \\ \\  \\/  / | \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|     \n"
		"  \\ \\    / / \\ \\   __  \\ \\   _  _\\ \\   __  \\ \\  \\        \n"
		"   \\/  /  /   \\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\____   \n"
		" __/  / /      \\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\_______\\ \n"
		"|\\___/ /        \\|__|\\|__|\\|__|\\|__|\\|__|\\|__|\\|_______| \n"
		"\\|___|/                                                  \n"
		"\n"
		"Usage: %s [Options] sources...\n"
		"Options:\n"
		"    [ --include-dir        | -id ] <path>             Add include directory for the target.\n"
		"    [ --output-format      | -of ] <nasm|o>           Set output format to either nasm assembly or .o files. Defaults to nasm assembly.\n"
		"    [ --artifacts-dir      | -ad ] <path>             Set directory for the artifacts.\n"
		"    [ --optimizations-mode | -om ] <mode>             Set optimizations mode to either none, size, speed, or all. Defaults to none.\n"
		"    [ --help               | -h  ]                    Print usage message.\n"
		"\n",
		arg0);

	*succeeded = 1;
	return 1;
}

static signed char CLI_shift(
	int* const argc,
	const char*** const argv,
	const char** const shifted,
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

	if (shifted == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `shifted` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;
	*shifted = NULL;

	if (!(*argc > 0 && *argv != NULL))
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to shift args, since there are no more command-line arguments left!");
		*succeeded = 0;
		return 0;
	}

	*shifted = **argv;
	*argc -= 1;
	*argv += 1;

	*succeeded = 1;
	return 1;
}

/**
 * @}
 */
