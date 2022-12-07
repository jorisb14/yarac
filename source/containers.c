
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

/**
 * @addtogroup containers
 * 
 * @{
 */

signed char List_create(
	struct List** const list,
	signed char* const succeeded)
{
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	W_RTM_malloc((const void** const)list, sizeof(struct List), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
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
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to deallocate list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char List_getCount(
	const struct List* const * const list,
	unsigned long long* const count,
	signed char* const succeeded)
{
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if (count == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `count` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*count = (*list)->count;
	*succeeded = 1;
	return 1;
}

signed char List_pushFirst(
	struct List* const * const list,
	void* const data,
	signed char* const succeeded)
{
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
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
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
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
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if ((*list)->head == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`s head is invalid (null)!");
		return 0;
	}

	if (popped == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `popped` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
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
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if ((*list)->head == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`s head is invalid (null)!");
		return 0;
	}

	if (popped == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `popped` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

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
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if (peeked == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `peeked` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
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
	if (list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list` is invalid (null)!");
		return 0;
	}

	if (*list == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `list`'s deref is invalid (null)!");
		return 0;
	}

	if (peeked == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `peeked` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	struct List_Node* last = (*list)->head;

	while (last->next != NULL)
	{
		last = last->next;
	}

	*peeked = last->data;
	*succeeded = 1;
	return 1;
}

signed char Vector_create(
	struct Vector** const vector,
	const unsigned long long capacity,
	signed char* const succeeded)
{
	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	W_RTM_malloc((const void** const)vector, sizeof(struct Vector), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	W_RTM_free((const void* const * const)(&((*vector)->data)), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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
	void** const gotten,
	signed char* const succeeded)
{
	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		return 0;
	}

	if (index >= (*vector)->count)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `index` is out of bounds!");
		return 0;
	}

	if (gotten == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `gotten` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*gotten = (*vector)->data[index];
	*succeeded = 1;
	return 1;
}

signed char Vector_setAt(
	struct Vector* const * const vector,
	const unsigned long long index,
	void* const gotten,
	signed char* const succeeded)
{
	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		return 0;
	}

	if (index >= (*vector)->count)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `index` is out of bounds!");
		return 0;
	}

	if (gotten == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `gotten` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	(*vector)->data[index] = gotten;
	*succeeded = 1;
	return 1;
}

signed char Vector_pushLast(
	struct Vector* const * const vector,
	void* const data,
	signed char* const succeeded)
{
	if (vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector` is invalid (null)!");
		return 0;
	}

	if (*vector == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `vector`'s deref is invalid (null)!");
		return 0;
	}

	if (data == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `data` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if ((*vector)->count + 1 > (*vector)->capacity)
	{
		unsigned long long newCapacity = (*vector)->capacity + ((*vector)->capacity / 2);

		W_RTM_realloc((const void** const)(&((*vector)->data)), newCapacity * sizeof(void*), succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
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

/**
 * @}
 */
