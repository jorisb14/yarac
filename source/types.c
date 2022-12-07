
/**
 * @file types.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-10-30
 */

#include <types.h>
#include <logger.h>
#include <rtm.h>

/**
 * @addtogroup types
 * 
 * @{
 */

signed char Token_create(
	struct Token** const token,
	const unsigned long long id,
	const signed long long kind,
	const struct Location* const location,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (token == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `token` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*token != NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `token`'s deref was not NULL!");
		*succeeded = 0;
		return 0;
	}

	if (location == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `location` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	*token = NULL;

	W_RTM_malloc((const void** const)token, sizeof(struct Token), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory for a token!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*token)->id = id;
	(*token)->kind = kind;
	(*token)->location = *location;
	*succeeded = 1;
	return 1;
}

signed char Token_destroy(
	const struct Token* const * const token,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (token == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `token` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*token == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `token`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	switch ((*token)->kind)
	{
		case TOKEN_KIND_LITERAL_STRING:
		{
			W_RTM_free((const void* const * const)(&((*token)->value.string.bytes)), succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
					"failed to deallocate memory for a token's source!");
				// *succeeded = 0;
				return 1;
			},
			{});
		} break;

		default:
		{
		} break;
	}

	W_RTM_free((const void* const * const)(&((*token)->source.buffer)), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate memory for a token's source!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_RTM_free((const void* const * const)token, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate memory for a token!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char Block_create(
	struct Block** const block,
	const signed long long kind,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*block != NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `block`'s deref was not NULL!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	*block = NULL;

	W_RTM_malloc((const void** const)block, sizeof(struct Block), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory for a block!");
		// *succeeded = 0;
		return 1;
	},
	{});

	(*block)->kind = kind;
	*succeeded = 1;
	return 1;
}

signed char Block_destroy(
	const struct Block* const * const block,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	switch ((*block)->kind)
	{
		case BLOCK_KIND_OPERATION:
		{
		} break;

		case BLOCK_KIND_IDENTIFIER:
		{
		} break;

		case BLOCK_KIND_COMPOUND:
		{
			switch ((*block)->inner.compoundBlock.kind)
			{
				case COMPOUND_BLOCK_KIND_IF:
				{
					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.ifBlock.conditionBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for an if condition block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.ifBlock.conditionBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a if condition blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});

					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.ifBlock.bodyBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for an if body block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.ifBlock.bodyBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a if body blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});
				} break;

				case COMPOUND_BLOCK_KIND_WHILE:
				{
					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.whileBlock.conditionBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for a while condition block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.whileBlock.conditionBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a while condition blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});

					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.whileBlock.bodyBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for a while body block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.whileBlock.bodyBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a while body blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});
				} break;

				case COMPOUND_BLOCK_KIND_WITH:
				{
					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.withBlock.identifierBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for a with identifiers block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.withBlock.identifierBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a with identifiers blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});

					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.withBlock.bodyBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for a with body block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.withBlock.bodyBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a with body blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});
				} break;

				case COMPOUND_BLOCK_KIND_PROCEDURE:
				{
					W_Block_destroy((const struct Block* const * const)&((*block)->inner.compoundBlock.inner.procedureBlock.identifierBlock), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a procedure identifier block!");
						// *succeeded = 0;
						return 1;
					},
					{});

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.procedureBlock.inTypesTokens), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a procedure in types tokens list!");
						// *succeeded = 0;
						return 1;
					},
					{});

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.procedureBlock.outTypesTokens), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a procedure out types tokens list!");
						// *succeeded = 0;
						return 1;
					},
					{});

					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.procedureBlock.bodyBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for a procedure body block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.procedureBlock.bodyBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a procedure body blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});
				} break;

				case COMPOUND_BLOCK_KIND_MODULE:
				{
					W_Block_destroy((const struct Block* const * const)&((*block)->inner.compoundBlock.inner.moduleBlock.identifierBlock), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a module identifier block!");
						// *succeeded = 0;
						return 1;
					},
					{});

					for (struct List_Node* iterator = (*block)->inner.compoundBlock.inner.moduleBlock.bodyBlocks->head; iterator != NULL; iterator = iterator->next)
					{
						const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

						W_Block_destroy(innerBlock, succeeded,
						{
							*succeeded = 0;
							return 0;
						},
						{
							W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
								"failed to deallocate memory for a module body block!");
							// *succeeded = 0;
							return 1;
						},
						{});
					}

					W_List_destroy((const struct List* const * const)&((*block)->inner.compoundBlock.inner.moduleBlock.bodyBlocks), succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
							"failed to deallocate memory for a module body blocks list!");
						// *succeeded = 0;
						return 1;
					},
					{});
				} break;
			
				default:
				{
				} break;
			}
		} break;

		case BLOCK_KIND_IMPORT:
		{
			for (struct List_Node* iterator = (*block)->inner.importBlock.identifierBlocks->head; iterator != NULL; iterator = iterator->next)
			{
				const struct Block* const * const innerBlock = (const struct Block* const * const)(&(iterator->data));

				W_Block_destroy(innerBlock, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
						"failed to deallocate memory for an import identifiers block!");
					// *succeeded = 0;
					return 1;
				},
				{});
			}

			W_List_destroy((const struct List* const * const)&((*block)->inner.importBlock.identifierBlocks), succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
					"failed to deallocate memory for an import identifiers blocks list!");
				// *succeeded = 0;
				return 1;
			},
			{});
		} break;

		default:
		{
		} break;
	}

	W_RTM_free((const void* const * const)block, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate memory for a block!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char Frame_create(
	struct Frame** const frame,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (frame == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `frame` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*frame != NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `frame`'s deref was not NULL!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	*frame = NULL;

	W_RTM_malloc((const void** const)frame, sizeof(struct Frame), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to allocate memory for a frame!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_List_create(&(*frame)->bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to create a gmm list for frame's blocks!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

signed char Frame_destroy(
	const struct Frame* const * const frame,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (frame == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `frame` is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	if (*frame == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"provided function parameter `frame`'s deref is invalid (null)!");
		*succeeded = 0;
		return 0;
	}

	*succeeded = 0;

	for (struct List_Node* blocksIterator = (*frame)->bodyBlocks->head; blocksIterator != NULL; blocksIterator = blocksIterator->next)
	{
		const struct Block* const * const block = (const struct Block* const * const)(&(blocksIterator->data));

		W_Block_destroy(block, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
				"failed to deallocate memory for a block!");
			// *succeeded = 0;
			return 1;
		},
		{});
	}

	W_List_destroy((const struct List* const * const)&((*frame)->bodyBlocks), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate memory for a frame body blocks list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_RTM_free((const void* const * const)frame, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s",
			"failed to deallocate memory for a frame!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

/**
 * @}
 */
