
/**
 * @file containers.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-14
 */

#ifndef _CONTAINERS_H_
#define _CONTAINERS_H_

/**
 * @addtogroup containers
 * 
 * @{
 */

struct Vector
{
	void** data;
	unsigned long long capacity;
	unsigned long long count;
};

/**
 * Create a vector container on the heap, not the stack. Return 0 in case of an internal error and
 * 1 otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector* vector;
 *     signed char succeeded;
 *     assert(Vector_create(&vector, capacity, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Vector_create(
	struct Vector** const vector,
	const unsigned long long capacity,
	signed char* const succeeded);

#define W_Vector_create(_inmacro_vector, _inmacro_capacity, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Vector_create((_inmacro_vector), (_inmacro_capacity), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Vector_create(...) returned with internal failure!"); \
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
 * Destroy vector. All inner elements should be deallocated before-hand! Return 0 in case of an
 * internal error and 1 otherwise. The parameter `succeeded` indicates logic level errors. Should
 * be used as this:
 * 
 * @code{.c}
 *     struct Vector* vector;
 *     signed char succeeded;
 *     // ... 
 *     assert(Vector_destroy(&vector, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Vector_destroy(
	const struct Vector* const * const vector,
	signed char* const succeeded);

#define W_Vector_destroy(_inmacro_vector, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Vector_destroy((_inmacro_vector), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Vector_destroy(...) returned with internal failure!"); \
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
 * Get a value at specified index. Return 0 in case of an internal error and 1 otherwise. The
 * parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector* vector;
 *     void* value = NULL;
 *     signed char succeeded;
 *     assert(Vector_getAt(&vector, index, &value, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Vector_getAt(
	struct Vector* const * const vector,
	const unsigned long long index,
	void** const data,
	signed char* const succeeded);

#define W_Vector_getAt(_inmacro_vector, _inmacro_index, _inmacro_data, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Vector_getAt((_inmacro_vector), (_inmacro_index), (_inmacro_data), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Vector_getAt(...) returned with internal failure!"); \
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
 * Set a value at specified index. Return 0 in case of an internal error and 1 otherwise. The
 * parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector* vector;
 *     signed char succeeded;
 *     assert(Vector_setAt(&vector, index, &value, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Vector_setAt(
	struct Vector* const * const vector,
	const unsigned long long index,
	void* const data,
	signed char* const succeeded);

#define W_Vector_setAt(_inmacro_vector, _inmacro_index, _inmacro_data, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Vector_setAt((_inmacro_vector), (_inmacro_index), (_inmacro_data), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Vector_setAt(...) returned with internal failure!"); \
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
 * Push a value onto the back of the vector container. Return 0 in case of an internal error and 1
 * otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector* vector;
 *     signed char succeeded;
 *     assert(List_pushLast(&vector, value, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Vector_pushLast(
	struct Vector* const * const vector,
	void* const data,
	signed char* const succeeded);

#define W_Vector_pushLast(_inmacro_vector, _inmacro_data, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Vector_pushLast((_inmacro_vector), (_inmacro_data), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Vector_pushLast(...) returned with internal failure!"); \
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
 * The list container's node. It is meant to be used as a dynamic container for the actual items of
 * the list. It is abstracted by the list functions, and should not be used outside of the list.
 * 
 * NOTE: List node does not have constructors and destructors, because it is intended that list is
 * the only owner of the node.
 */
struct List_Node
{
	struct List_Node* next;
	struct List_Node* previous;
	void* data;
};

struct List
{
	struct List_Node* head;
	unsigned long long count;
};

/**
 * Create a list container on the heap, not the stack. Return 0 in case of an internal error and 1
 * otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     assert(List_create(&list, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_create(
	struct List** const list,
	signed char* const succeeded);

#define W_List_create(_inmacro_list, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!List_create((_inmacro_list), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function List_create(...) returned with internal failure!"); \
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
 * Destroy list with it's nodes. All inner elements should be deallocated before-hand! Return 0 in
 * case of an internal error and 1 otherwise. The parameter `succeeded` indicates logic level
 * errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     // ... 
 *     assert(List_destroy(&list, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_destroy(
	const struct List* const * const list,
	signed char* const succeeded);

#define W_List_destroy(_inmacro_list, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!List_destroy((_inmacro_list), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function List_destroy(...) returned with internal failure!"); \
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
 * Push a value into the front of the list container. Return 0 in case of an internal error and 1
 * otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     assert(List_pushFirst(&list, value, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_pushFirst(
	struct List* const * const list,
	void* const data,
	signed char* const succeeded);

#define W_List_pushFirst(_inmacro_list, _inmacro_data, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!List_pushFirst((_inmacro_list), (_inmacro_data), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function List_pushFirst(...) returned with internal failure!"); \
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
 * Push a value onto the back of the list container. Return 0 in case of an internal error and 1
 * otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     assert(List_pushLast(&list, value, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_pushLast(
	struct List* const * const list,
	void* const data,
	signed char* const succeeded);

#define W_List_pushLast(_inmacro_list, _inmacro_data, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!List_pushLast((_inmacro_list), (_inmacro_data), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function List_pushLast(...) returned with internal failure!"); \
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
 * Pop first value from the list container. Return 0 in case of an internal error and 1 otherwise.
 * The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     void* popped;
 *     assert(List_popFirst(&list, &popped, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_popFirst(
	struct List* const * const list,
	void** const popped,
	signed char* const succeeded);

#define W_List_popFirst(_inmacro_list, _inmacro_popped, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!List_popFirst((_inmacro_list), (_inmacro_popped), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function List_popFirst(...) returned with internal failure!"); \
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
 * Pop last value from the list container. Return 0 in case of an internal error and 1 otherwise.
 * The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     void* popped;
 *     assert(List_popLast(&list, &popped, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_popLast(
	struct List* const * const list,
	void** const popped,
	signed char* const succeeded);

#define W_List_popLast(_inmacro_list, _inmacro_popped, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!List_popLast((_inmacro_list), (_inmacro_popped), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function List_popLast(...) returned with internal failure!"); \
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
 * Peek first value from the list container. Return 0 in case of an internal error and 1 otherwise.
 * The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     void* peeked;
 *     assert(List_peekFirst(&list, &peeked, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_peekFirst(
	const struct List* const * const list,
	void** const peeked,
	signed char* const succeeded);

#define W_List_peekFirst(_inmacro_list, _inmacro_peeked, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!List_peekFirst((_inmacro_list), (_inmacro_peeked), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function List_peekFirst(...) returned with internal failure!"); \
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
 * Peek last value from the list container. Return 0 in case of an internal error and 1 otherwise.
 * The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct List* list;
 *     signed char succeeded;
 *     void* peeked;
 *     assert(List_peekLast(&list, &peeked, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char List_peekLast(
	const struct List* const * const list,
	void** const peeked,
	signed char* const succeeded);

/**
 * The map container's node. It is meant to be used as a dynamic container for the actual items of
 * the map. It is abstracted by the map functions, and should not be used outside of the map.
 * 
 * NOTE: Map node does not have constructors and destructors, because it is intended that map is
 * the only owner of the node.
 */
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

/**
 * Create a map container on the heap, not the stack. Return 0 in case of an internal error and
 * 1 otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct Map* map;
 *     signed char succeeded;
 *     assert(Map_create(&map, capacity, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Map_create(
	struct Map** const map,
	const unsigned long long capacity,
	signed char* const succeeded);

#define W_Map_create(_inmacro_map, _inmacro_capacity, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Map_create((_inmacro_map), (_inmacro_capacity), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Map_create(...) returned with internal failure!"); \
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
 * Destroy map. All inner elements should be deallocated before-hand! Return 0 in case of an
 * internal error and 1 otherwise. The parameter `succeeded` indicates logic level errors. Should
 * be used as this:
 * 
 * @code{.c}
 *     struct Map* map;
 *     signed char succeeded;
 *     // ... 
 *     assert(Map_destroy(&map, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Map_destroy(
	const struct Map* const * const map,
	signed char* const succeeded);

#define W_Map_destroy(_inmacro_map, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Map_destroy((_inmacro_map), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Map_destroy(...) returned with internal failure!"); \
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
 * Set a value for the specified key entry in the map. Return 0 in case of an internal error and 1
 * otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct Map* map;
 *     signed char succeeded;
 *     // ... 
 *     assert(Map_set(&map, "key1", 4, value, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Map_set(
	struct Map* const * const map,
	const char* const key,
	const unsigned long long length,
	void* value,
	signed char* const succeeded);

#define W_Map_set(_inmacro_map, _inmacro_key, _inmacro_length, _inmacro_value, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Map_set((_inmacro_map), (_inmacro_key), (_inmacro_length), (_inmacro_value), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Map_set(...) returned with internal failure!"); \
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
 * Get a value for the specified key entry in the map. Return 0 in case of an internal error and 1
 * otherwise. The parameter `succeeded` indicates logic level errors. Should be used as this:
 * 
 * @code{.c}
 *     struct Map* map;
 *     signed char succeeded;
 *     // ... 
 *     assert(Map_get(&map, "key1", 4, &value, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
signed char Map_get(
	struct Map* const * const map,
	const char* const key,
	const unsigned long long length,
	void** const value,
	signed char* const succeeded);

#define W_Map_get(_inmacro_map, _inmacro_key, _inmacro_length, _inmacro_value, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Map_get((_inmacro_map), (_inmacro_key), (_inmacro_length), (_inmacro_value), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function Map_get(...) returned with internal failure!"); \
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
 * @}
 */

#endif
