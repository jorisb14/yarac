
/**
 * @file map.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-12-07
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Hash64
{
	unsigned long long value;
};

struct Hash64 hash64(
	const unsigned char* const bytes,
	const unsigned long long length)
{
	assert(bytes != NULL);
	assert(length > 0);

	// Setting up hash blocks
	struct Hash64 hash = {0};
	register unsigned long long state = 0;

	#define PRIMARY1 ((const unsigned char)13)
	#define PRIMARY2 ((const unsigned char)31)

	for (unsigned long long i = 0; i < length; ++i)
	{
		const unsigned char value = *(const unsigned char* const)(bytes + i);
		state += ((value + (state ^ PRIMARY2)) % PRIMARY2) & PRIMARY1;
	}

	hash.value = state;
	return hash;
}

struct Map_Node
{
	const char* key;
	unsigned long long length;
	void* value;
	struct Map_Node* next;
};

struct Map
{
	struct Map_Node** nodes;
	unsigned long long capacity;
	unsigned long long count;
};

signed char Map_create(
	struct Map** const map,
	const unsigned long long capacity)
{
	*map = (struct Map*)malloc(sizeof(struct Map));
	(*map)->nodes = (struct Map_Node**)malloc(capacity * sizeof(struct Map_Node*));
	assert((*map)->nodes != NULL);
	(*map)->capacity = capacity;
	(*map)->count = 0;
	return 1;
}

signed char Map_destroy(
	const struct Map* const * const map)
{
	for (unsigned long long i = 0; i < (*map)->capacity; ++i)
	{
		if ((*map)->nodes[i] == NULL)
		{
			continue;
		}

		for (const struct Map_Node* node = (*map)->nodes[i]; node->next != NULL;)
		{
			const struct Map_Node* current = node;
			node = node->next;
			free((void*)current);
		}
	}

	free((void*)((*map)->nodes));
	free((void*)(*map));
	return 1;
}

signed char Map_push(
	struct Map* const * const map,
	const char* const key,
	void* value)
{
	// Generate index using hash64() function
	const unsigned long long length = strlen(key);
	const struct Hash64 hash = hash64((const unsigned char* const)key, length);
	// fprintf(stdout, "push: index=%llu\n", hash.value);
	// TODO: remove -----------^

	// Check if the index is out of bounds. If so, allocate more memory to the map.
	if (hash.value >= (*map)->capacity)
	{
		const unsigned long long newCapacity = hash.value;
		(*map)->nodes = (struct Map_Node**)realloc((void*)((*map)->nodes), newCapacity);
		assert((*map)->nodes != NULL); // TODO: should be IF, not assert check!
		(*map)->capacity = newCapacity;
	}

	// Check if there are existing nodes that hold provided key
	if ((*map)->nodes[hash.value] != NULL)
	{
		struct Map_Node* current = (*map)->nodes[hash.value];

		for (; current != NULL; current = current->next)
		{
			if (length == current->length && strncmp(key, current->key, length) == 0)
			{
				current->value = value;
				return 1;
			}

			if (current->next == NULL)
			{
				break;
			}
		}

		// Create the new node
		struct Map_Node* node = (struct Map_Node*)malloc(sizeof(struct Map_Node));
		assert(node != NULL); // TODO: should be an IF here, not assert!
		*node = (struct Map_Node) { .key = (const char*)key, .length = length, .value = value, .next = NULL };

		// Insert new node
		current->next = node;
		++((*map)->count);
		return 1;
	}

	// Create the new node
	struct Map_Node* node = (struct Map_Node*)malloc(sizeof(struct Map_Node));
	assert(node != NULL); // TODO: should be an IF here, not assert!
	*node = (struct Map_Node) { .key = (const char*)key, .length = length, .value = value, .next = NULL };

	// Insert new node
	(*map)->nodes[hash.value] = node;
	++((*map)->count);
	return 1;
}

signed char Map_get(
	struct Map* const * const map,
	const char* const key,
	void** value)
{
	const unsigned long long length = strlen(key);
	const struct Hash64 hash = hash64((const unsigned char* const)key, length);
	// fprintf(stdout, "get: index=%llu\n", hash.value);
	// TODO: remove -----------^

	if (hash.value >= (*map)->capacity)
	{
		// Failure
		return 0;
	}

	struct Map_Node* node = (*map)->nodes[hash.value];

	if (node == NULL)
	{
		return 0;
	}

	for (; node != NULL; node = node->next)
	{
		if (length == node->length && strncmp(key, node->key, length) == 0)
		{
			*value = (void*)(node->value);
			return 1;
		}
	}

	*value = NULL;
	return 0;
}

#endif
