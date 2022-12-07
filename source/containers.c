
/**
 * @file containers.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-14
 */

#include <containers.h>
#include <logger.h>
#include <rtm.h>

#include <stdlib.h>
#include <string.h>

/**
 * @addtogroup containers
 * 
 * @{
 */

struct Hash64
{
	unsigned long long value;
};

static signed char Hash64_hash(
	struct Hash64* const hash,
	const unsigned char* const bytes,
	const unsigned long long length,
	signed char* const succeeded);

#define W_Hash64_hash(_inmacro_hash, _inmacro_bytes, _inmacro_length, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Hash64_hash((_inmacro_hash), (_inmacro_bytes), (_inmacro_length), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Hash64_hash(...) returned with internal failure!"); \
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

signed char Vector_create(
	struct Vector** const vector,
	const unsigned long long capacity,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	W_RTM_malloc((const void** const)vector, sizeof(struct Vector), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"Failed to allocate memory for a vector!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*vector)->data = NULL;

	W_RTM_malloc((const void** const)(&((*vector)->data)), capacity * sizeof(void*), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory block for vector's data!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*vector)->capacity = capacity;
	(*vector)->count = 0;

	*succeeded = 1;
	return 1;
}

signed char Vector_destroy(
	const struct Vector* const * const vector,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	W_RTM_free((const void* const * const)(&((*vector)->data)), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate vector's data!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_RTM_free((const void* const * const)vector, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate vector!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char Vector_getAt(
	struct Vector* const * const vector,
	const unsigned long long index,
	void** const data,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (index >= (*vector)->count)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `index` is out of bounds!");
		*succeeded = 0;
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*data = (*vector)->data[index];
	*succeeded = 1;
	return 1;
}

signed char Vector_setAt(
	struct Vector* const * const vector,
	const unsigned long long index,
	void* const data,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (index >= (*vector)->count)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `index` is out of bounds!");
		*succeeded = 0;
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	(*vector)->data[index] = data;
	*succeeded = 1;
	return 1;
}

signed char Vector_pushLast(
	struct Vector* const * const vector,
	void* const data,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	if ((*vector)->count + 1 > (*vector)->capacity)
	{
		const unsigned long long newCapacity = (*vector)->capacity + ((*vector)->capacity / 2);

		W_RTM_realloc((const void** const)(&((*vector)->data)), newCapacity * sizeof(void*), succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
				"failed to reallocate memory for a vector!");
			// *succeeded = 0;
			return 1;
		},
		{});

		(*vector)->data[(*vector)->count++] = data;
		(*vector)->capacity = newCapacity;
	}
	else
	{
		(*vector)->data[(*vector)->count++] = data;
	}

	*succeeded = 1;
	return 1;
}

signed char List_create(
	struct List** const list,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	W_RTM_malloc((const void** const)list, sizeof(struct List), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"Failed to allocate memory for a list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*list)->head = NULL;
	(*list)->count = 0;
	*succeeded = 1;
	return 1;
}

signed char List_destroy(
	const struct List* const * const list,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	struct List_Node* last = (*list)->head;

	while (last != NULL)
	{
		struct List_Node* current = last;
		last = last->next;

		W_RTM_free((const void* const * const)&current, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
				"failed to deallocate list's node!");
			// *succeeded = 0;
			return 1;
		},
		{});
	}

	W_RTM_free((const void* const * const)list, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char List_pushFirst(
	struct List* const * const list,
	void* const data,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	struct List_Node* node = NULL;

	W_RTM_malloc((const void** const)&node, sizeof(struct List_Node), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory block for list's node!");
		// *succeeded = 0;
		return 1;
	},
	{});

	// Setting up node's 
	node->data = data;

	// Setting up node's 
	node->next = (*list)->head;
	node->previous = NULL;

	if ((*list)->head != NULL)
	{
		(*list)->head->previous = node;
	}

	(*list)->head = node;
	++((*list)->count);
	*succeeded = 1;
	return 1;
}

signed char List_pushLast(
	struct List* const * const list,
	void* const data,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	struct List_Node* node = NULL;

	W_RTM_malloc((const void** const)&node, sizeof(struct List_Node), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory block for list's node!");
		// *succeeded = 0;
		return 1;
	},
	{});

	// Setting up node's 
	node->data = data;

	// Setting up node's 
	node->next = NULL;

	if ((*list)->head == NULL)
	{
		node->previous = NULL;
		(*list)->head = node;

		++((*list)->count);
		*succeeded = 1;
		return 1;
	}

	struct List_Node* last = (*list)->head;

	while (last->next != NULL)
	{
		last = last->next;
	}

	last->next = node;
	node->previous = last;
	++((*list)->count);

	*succeeded = 1;
	return 1;
}

signed char List_popFirst(
	struct List* const * const list,
	void** const popped,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if ((*list)->head == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`s head is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (popped == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `popped` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	struct List_Node* node = (*list)->head;
	(*list)->head = (*list)->head->next;
	*popped = node->data;

	--((*list)->count);
	*succeeded = 1;
	return 1;
}

signed char List_popLast(
	struct List* const * const list,
	void** const popped,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if ((*list)->head == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`s head is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (popped == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `popped` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	struct List_Node* last = (*list)->head;

	while (last->next != NULL)
	{
		last = last->next;
	}

	*popped = last->data;
	--((*list)->count);
	last = NULL;

	*succeeded = 1;
	return 1;
}

signed char List_peekFirst(
	const struct List* const * const list,
	void** const peeked,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (peeked == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `peeked` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*peeked = (*list)->head->data;
	*succeeded = 1;
	return 1;
}

signed char List_peekLast(
	const struct List* const * const list,
	void** const peeked,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (peeked == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `peeked` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	struct List_Node* last = (*list)->head;

	while (last->next != NULL)
	{
		last = last->next;
	}

	*peeked = last->data;
	*succeeded = 1;
	return 1;
}

signed char Map_create(
	struct Map** const map,
	const unsigned long long capacity,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (map == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `map` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	W_RTM_malloc((const void** const)map, sizeof(struct Map), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory for a map!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*map)->nodes = NULL;

	W_RTM_malloc((const void** const)(&((*map)->nodes)), capacity * sizeof(struct Map_Node*), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory block for map's nodes!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*map)->capacity = capacity;
	(*map)->count = 0;

	*succeeded = 1;
	return 1;
}

signed char Map_destroy(
	const struct Map* const * const map,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (map == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `map` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*map == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `map`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

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

			W_RTM_free((const void* const * const)(&current), succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
					"failed to deallocate map's node!");
				// *succeeded = 0;
				return 1;
			},
			{});
		}
	}

	W_RTM_free((const void* const * const)(&((*map)->nodes)), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate map's nodes!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_RTM_free((const void* const * const)map, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate map!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char Map_set(
	struct Map* const * const map,
	const char* const key,
	const unsigned long long length,
	void* value,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (map == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `map` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*map == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `map`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (key == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `key` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (value == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `value` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	struct Hash64 hash = {0};

	W_Hash64_hash(&hash, (const unsigned char* const)key, length, succeeded,
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

	if (hash.value >= (*map)->capacity)
	{
		const unsigned long long newCapacity = hash.value;

		W_RTM_realloc((const void** const)(&((*map)->nodes)), newCapacity, succeeded,
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

		(*map)->capacity = newCapacity;
	}

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

		struct Map_Node* node = NULL;

		W_RTM_malloc((const void** const)(&node), sizeof(struct Map_Node), succeeded,
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

		*node = (struct Map_Node) { .key = (const char*)key, .length = length, .value = value, .next = NULL };

		current->next = node;
		++((*map)->count);
		*succeeded = 1;
		return 1;
	}

	struct Map_Node* node = NULL;

	W_RTM_malloc((const void** const)(&node), sizeof(struct Map_Node), succeeded,
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

	*node = (struct Map_Node) { .key = (const char*)key, .length = length, .value = value, .next = NULL };

	(*map)->nodes[hash.value] = node;
	++((*map)->count);
	*succeeded = 1;
	return 1;
}

signed char Map_get(
	struct Map* const * const map,
	const char* const key,
	const unsigned long long length,
	void** const value,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (map == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `map` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*map == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `map`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (key == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `key` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (value == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `value` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	*value = NULL;

	struct Hash64 hash = {0};

	W_Hash64_hash(&hash, (const unsigned char* const)key, length, succeeded,
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

	if (hash.value >= (*map)->capacity)
	{
		*succeeded = 0;
		return 1;
	}

	struct Map_Node* node = (*map)->nodes[hash.value];

	if (node == NULL)
	{
		*succeeded = 0;
		return 1;
	}

	for (; node != NULL; node = node->next)
	{
		if (length == node->length && strncmp(key, node->key, length) == 0)
		{
			*value = (void*)(node->value);
			*succeeded = 1;
			return 1;
		}
	}

	*value = NULL;
	*succeeded = 0;
	return 1;
}

static signed char Hash64_hash(
	struct Hash64* const hash,
	const unsigned char* const bytes,
	const unsigned long long length,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (hash == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `hash` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	unsigned long long state = 0;

	#define PRIMARY1 ((const unsigned char)13)
	#define PRIMARY2 ((const unsigned char)31)

	for (unsigned long long i = 0; i < length; ++i)
	{
		const unsigned char value = *(const unsigned char* const)(bytes + i);
		state += ((value + (state ^ PRIMARY2)) % PRIMARY2) & PRIMARY1;
	}

	#undef PRIMARY1
	#undef PRIMARY2

	hash->value = state;
	*succeeded = 1;
	return 1;
}

/**
 * @}
 */
