
/**
 * @file location.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-10-31
 */

#ifndef _LOCATION_H_
#define _LOCATION_H_

/**
 * @addtogroup types
 * 
 * @{
 */

struct Location
{
	const char* file;
	unsigned long long line;
	unsigned long long column;
};

#ifndef INTERNAL_LOCATION
#	define INTERNAL_LOCATION ((struct Location) { .file = (const char*)__FILE__, .line = (unsigned long long)__LINE__, .column = 0 })
#endif

#ifndef NO_LOCATION
#	define NO_LOCATION ((struct Location) { .file = NULL, .line = 0, .column = 0 })
#endif

#ifndef INVALID_LOCATION
#	define INVALID_LOCATION NO_LOCATION
#endif

/**
 * @}
 */

#endif
