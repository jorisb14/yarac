
/**
 * @file parser.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-01
 */

#include <parser.h>
#include <logger.h>
#include <rtm.h>
#include <types.h>

#include <assert.h>

/**
 * @addtogroup parser
 * 
 * @{
 */

// TODO: implement the parser module!
static_assert(1, "Parser module is not implement yet"); // NOTE: hack to suppress occasional GCC error for empty C file.

signed char Parser_parseFrame(
	struct Frame** const frame,
	const struct List* const * const tokens,
	signed char* const succeeded)
{
	if (frame == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `frame` is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	// TODO: implement!

	*succeeded = 1;
	return 1;
}

#if 0

static struct List_Node* _parser_current;

// NEXT STEPS:
// TODO: rework all the logs and messages in the parser! (1) [+]
// TODO: implement a validator function for the frame (here validation must be local to the frame and global validation will happen later)! (2) [-]
//     > Submodules can only exist in modules, not in other blocks
//     > Nested procedures cannot be marked `export`
//     > Imports cannot be places inside the modules, procedures and other blocks. Thay must be globally scoped (relative to the frame)
// TODO: think about making return a block and not just a keyword (3) [-]

/**
 * Try to parse TOP LAYER blocks and must not be used in other parts of the parser, apart the frame
 * parsing function! Return 0 in case of an error and 1 in case of a success. Should be used like
 * this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(Parser_tryParseBlocks(&blocks, &result) == 1);
 * @endcode
 */
static signed char Parser_tryParseBlocks(
	struct List* const blocks,
	signed char* const succeeded);

#define W_Parser_tryParseBlocks(_inmacro_blocks, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseBlocks((_inmacro_blocks), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseBlocks(...) returned with internal failure!"); \
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

static signed char Parser_tryParseOperationBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseOperationBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseOperationBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseOperationBlock(...) returned with internal failure!"); \
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

static signed char Parser_tryParseIdentifierBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseIdentifierBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseIdentifierBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseIdentifierBlock(...) returned with internal failure!"); \
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

static signed char Parser_tryParseIfBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseIfBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseIfBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseIfBlock(...) returned with internal failure!"); \
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

static signed char Parser_tryParseWhileBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseWhileBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseWhileBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseWhileBlock(...) returned with internal failure!"); \
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

static signed char Parser_tryParseWithBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseWithBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseWithBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseWithBlock(...) returned with internal failure!"); \
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

static signed char Parser_tryParseProcedureBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseProcedureBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseProcedureBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseProcedureBlock(...) returned with internal failure!"); \
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

static signed char Parser_tryParseModuleBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseModuleBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseModuleBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseModuleBlock(...) returned with internal failure!"); \
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

static signed char Parser_tryParseImportBlock(
	struct Block** const block,
	signed char* const succeeded);

#define W_Parser_tryParseImportBlock(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_tryParseImportBlock((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_tryParseImportBlock(...) returned with internal failure!"); \
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

/*
signed char Parser_validateFrame(
	const struct Frame* const * const frame,
	signed char* const validated)
{
	if (frame == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `frame` is invalid (null)!");
		return 0;
	}

	if (*frame == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `frame`'s deref is invalid (null)!");
		return 0;
	}

	if (validated == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `validated` is invalid (null)!");
		return 0;
	}

	*validated = 0;



	// TODO: implement!



	*validated = 1;
	return 1;
}
*/

signed char Parser_parseFrame(
	const struct List* const tokens,
	struct Frame** const frame,
	signed char* const succeeded)
{
	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (frame == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `frame` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;
	_parser_current = tokens->head;
	*frame = NULL;

	W_Frame_create(frame, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to create a frame!");
		// *succeeded = 0;
		return 1;
	},
	{});

	W_Parser_tryParseBlocks(&(*frame)->bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, NO_LOCATION, "%s",
			"failed to parse blocks!");
		// *succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Parser_tryParseBlocks(
	struct List* const blocks,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (blocks == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `blocks` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	for (; _parser_current != NULL; _parser_current = _parser_current->next)
	{
		struct Token* token = (struct Token*)_parser_current->data;

		switch (token->kind)
		{
			case TOKEN_KIND_KEYWORD_RETURN:
			case TOKEN_KIND_INTRINSIC_ADD:
			case TOKEN_KIND_INTRINSIC_SUBTRACT:
			case TOKEN_KIND_INTRINSIC_MULTIPLY:
			case TOKEN_KIND_INTRINSIC_DIVIDE:
			case TOKEN_KIND_INTRINSIC_MODULUS:
			case TOKEN_KIND_INTRINSIC_EQUAL:
			case TOKEN_KIND_INTRINSIC_NEQUAL:
			case TOKEN_KIND_INTRINSIC_GREATER:
			case TOKEN_KIND_INTRINSIC_LESS:
			case TOKEN_KIND_INTRINSIC_BAND:
			case TOKEN_KIND_INTRINSIC_BOR:
			case TOKEN_KIND_INTRINSIC_BNOT:
			case TOKEN_KIND_INTRINSIC_SHIFTL:
			case TOKEN_KIND_INTRINSIC_SHIFTR:
			case TOKEN_KIND_INTRINSIC_SYSCALL0:
			case TOKEN_KIND_INTRINSIC_SYSCALL1:
			case TOKEN_KIND_INTRINSIC_SYSCALL2:
			case TOKEN_KIND_INTRINSIC_SYSCALL3:
			case TOKEN_KIND_INTRINSIC_SYSCALL4:
			case TOKEN_KIND_INTRINSIC_SYSCALL5:
			case TOKEN_KIND_INTRINSIC_SYSCALL6:
			case TOKEN_KIND_INTRINSIC_CLONE:
			case TOKEN_KIND_INTRINSIC_DROP:
			case TOKEN_KIND_INTRINSIC_OVER:
			case TOKEN_KIND_INTRINSIC_SWAP:
			case TOKEN_KIND_LITERAL_I64:
			case TOKEN_KIND_LITERAL_STRING:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_OPERATION, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseOperationBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse operation-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_IDENTIFIER:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_IDENTIFIER, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseIdentifierBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse identifier-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_IF:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_IF, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseIfBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse if-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_WHILE:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_WHILE, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseWhileBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse while-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_WITH:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_WITH, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseWithBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse with-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_EXPORT:
			case TOKEN_KIND_KEYWORD_INLINE:
			case TOKEN_KIND_KEYWORD_PROCEDURE:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_PROCEDURE, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseProcedureBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse procedure-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_MODULE:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_MODULE, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseModuleBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse module-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_IMPORT:
			{
				struct Block* block = NULL;

				W_Block_create(&block, BLOCK_KIND_IMPORT, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseImportBlock(&block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse import-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(blocks, block, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_END:
			{
				*succeeded = 1;
				return 1;
			} break;

			// case TOKEN_KIND_KEYWORD_IN:
			// case TOKEN_KIND_KEYWORD_OUT:
			// case TOKEN_KIND_KEYWORD_I64:
			// case TOKEN_KIND_KEYWORD_P64:
			// case TOKEN_KIND_KEYWORD_DO:
			default: // all unhandled cases that should not be on their own in the respective scopes.
			{
				W_Logger_log(LOG_KIND_ERROR, token->location,
					"encountered an invalid token `%.*s`!",
					(signed int)token->source.length, token->source.buffer);
				*succeeded = 0;
				return 1;
			} break;
		}
	}

	*succeeded = 1;
	return 1;
}

static signed char Parser_tryParseOperationBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_OPERATION);
	(*block)->inner.operationBlock = (struct OperationBlock) {0};

	struct Token* token = (struct Token*)_parser_current->data; 

	switch (token->kind)
	{
		case TOKEN_KIND_KEYWORD_RETURN:
		case TOKEN_KIND_INTRINSIC_ADD:
		case TOKEN_KIND_INTRINSIC_SUBTRACT:
		case TOKEN_KIND_INTRINSIC_MULTIPLY:
		case TOKEN_KIND_INTRINSIC_DIVIDE:
		case TOKEN_KIND_INTRINSIC_MODULUS:
		case TOKEN_KIND_INTRINSIC_EQUAL:
		case TOKEN_KIND_INTRINSIC_NEQUAL:
		case TOKEN_KIND_INTRINSIC_GREATER:
		case TOKEN_KIND_INTRINSIC_LESS:
		case TOKEN_KIND_INTRINSIC_BAND:
		case TOKEN_KIND_INTRINSIC_BOR:
		case TOKEN_KIND_INTRINSIC_BNOT:
		case TOKEN_KIND_INTRINSIC_SHIFTL:
		case TOKEN_KIND_INTRINSIC_SHIFTR:
		case TOKEN_KIND_INTRINSIC_SYSCALL0:
		case TOKEN_KIND_INTRINSIC_SYSCALL1:
		case TOKEN_KIND_INTRINSIC_SYSCALL2:
		case TOKEN_KIND_INTRINSIC_SYSCALL3:
		case TOKEN_KIND_INTRINSIC_SYSCALL4:
		case TOKEN_KIND_INTRINSIC_SYSCALL5:
		case TOKEN_KIND_INTRINSIC_SYSCALL6:
		case TOKEN_KIND_INTRINSIC_CLONE:
		case TOKEN_KIND_INTRINSIC_DROP:
		case TOKEN_KIND_INTRINSIC_OVER:
		case TOKEN_KIND_INTRINSIC_SWAP:
		case TOKEN_KIND_LITERAL_I64:
		case TOKEN_KIND_LITERAL_STRING:
		{
			(*block)->inner.operationBlock.token = token;
			*succeeded = 1;
			return 1;
		} break;

		default:
		{
			W_Logger_log(LOG_KIND_ERROR, token->location,
				"encountered an invalid token `%.*s` while parsing operation-block!",
				(signed int)token->source.length, token->source.buffer);
			*succeeded = 0;
			return 1;
		} break;
	}
}

static signed char Parser_tryParseIdentifierBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_IDENTIFIER);
	(*block)->inner.identifierBlock = (struct IdentifierBlock) {0};

	struct Token* token = (struct Token*)_parser_current->data; 

	switch (token->kind)
	{
		case TOKEN_KIND_IDENTIFIER:
		{
			(*block)->inner.identifierBlock.nameToken = token;
			(*block)->inner.identifierBlock.referenceBlock = NULL;
			*succeeded = 1;
			return 1;
		} break;

		default:
		{
			W_Logger_log(LOG_KIND_ERROR, token->location,
				"encountered an invalid token `%.*s` while parsing identifier-block!",
				(signed int)token->source.length, token->source.buffer);
			*succeeded = 0;
			return 1;
		} break;
	}
}

static signed char Parser_tryParseIfBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_IF);
	(*block)->inner.ifBlock = (struct IfBlock) {0};

	struct Token* ifToken = (struct Token*)_parser_current->data;

	if (ifToken->kind != TOKEN_KIND_KEYWORD_IF)
	{
		W_Logger_log(LOG_KIND_INTERNAL, ifToken->location,
			"encountered an invalid token `%.*s` instead of the `if` keyword!",
			(signed int)ifToken->source.length, ifToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.ifBlock.ifToken = ifToken;

	W_List_create(&(*block)->inner.ifBlock.conditionBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	W_List_create(&(*block)->inner.ifBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, ifToken->location, "%s",
			"missing the condition and body of the if-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	for (; _parser_current != NULL; _parser_current = _parser_current->next)
	{
		const struct Token* const token = (const struct Token* const)_parser_current->data;

		switch (token->kind)
		{
			case TOKEN_KIND_INTRINSIC_ADD:
			case TOKEN_KIND_INTRINSIC_SUBTRACT:
			case TOKEN_KIND_INTRINSIC_MULTIPLY:
			case TOKEN_KIND_INTRINSIC_DIVIDE:
			case TOKEN_KIND_INTRINSIC_MODULUS:
			case TOKEN_KIND_INTRINSIC_EQUAL:
			case TOKEN_KIND_INTRINSIC_NEQUAL:
			case TOKEN_KIND_INTRINSIC_GREATER:
			case TOKEN_KIND_INTRINSIC_LESS:
			case TOKEN_KIND_INTRINSIC_BAND:
			case TOKEN_KIND_INTRINSIC_BOR:
			case TOKEN_KIND_INTRINSIC_BNOT:
			case TOKEN_KIND_INTRINSIC_SHIFTL:
			case TOKEN_KIND_INTRINSIC_SHIFTR:
			case TOKEN_KIND_INTRINSIC_SYSCALL0:
			case TOKEN_KIND_INTRINSIC_SYSCALL1:
			case TOKEN_KIND_INTRINSIC_SYSCALL2:
			case TOKEN_KIND_INTRINSIC_SYSCALL3:
			case TOKEN_KIND_INTRINSIC_SYSCALL4:
			case TOKEN_KIND_INTRINSIC_SYSCALL5:
			case TOKEN_KIND_INTRINSIC_SYSCALL6:
			case TOKEN_KIND_INTRINSIC_CLONE:
			case TOKEN_KIND_INTRINSIC_DROP:
			case TOKEN_KIND_INTRINSIC_OVER:
			case TOKEN_KIND_INTRINSIC_SWAP:
			case TOKEN_KIND_LITERAL_I64:
			case TOKEN_KIND_LITERAL_STRING:
			{
				struct Block* block2 = NULL;

				W_Block_create(&block2, BLOCK_KIND_OPERATION, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseOperationBlock(&block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse operation-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(&(*block)->inner.ifBlock.conditionBlocks, block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_IDENTIFIER:
			{
				struct Block* block2 = NULL;

				W_Block_create(&block2, BLOCK_KIND_IDENTIFIER, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseIdentifierBlock(&block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse identifier-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(&(*block)->inner.ifBlock.conditionBlocks, block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_DO:
			{
				goto parsing_if_block_body;
			} break;

			default: // all unhandled cases that should not be on their own in the respective scopes.
			{
				W_Logger_log(LOG_KIND_ERROR, token->location,
					"encountered an invalid token `%.*s` while parsing if-block's condition!",
					(signed int)token->source.length, token->source.buffer);
				*succeeded = 0;
				return 1;
			} break;
		}
	}

parsing_if_block_body:
	static_assert(1); // Hack for the label issue ^

	struct Token* doToken = (struct Token*)_parser_current->data;

	if (doToken->kind != TOKEN_KIND_KEYWORD_DO)
	{
		W_Logger_log(LOG_KIND_INTERNAL, doToken->location,
			"encountered an invalid token `%.*s` instead of the `do` keyword!",
			(signed int)doToken->source.length, doToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.ifBlock.doToken = doToken;

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, doToken->location, "%s",
			"missing the body of the if-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	W_Parser_tryParseBlocks(&(*block)->inner.ifBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, doToken->location, "%s",
			"failed to parse the if-block's body block!");
		*succeeded = 0;
		return 1;
	},
	{});

	struct Token* endToken = (struct Token*)_parser_current->data;

	if (endToken->kind != TOKEN_KIND_KEYWORD_END)
	{
		W_Logger_log(LOG_KIND_INTERNAL, endToken->location,
			"encountered an invalid token `%.*s` instead of the `end` keyword!",
			(signed int)endToken->source.length, endToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.ifBlock.endToken = endToken;

	*succeeded = 1;
	return 1;
}

static signed char Parser_tryParseWhileBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_WHILE);
	(*block)->inner.whileBlock = (struct WhileBlock) {0};

	struct Token* whileToken = (struct Token*)_parser_current->data;

	if (whileToken->kind != TOKEN_KIND_KEYWORD_WHILE)
	{
		W_Logger_log(LOG_KIND_INTERNAL, whileToken->location,
			"encountered an invalid token `%.*s` instead of the `while` keyword!",
			(signed int)whileToken->source.length, whileToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.whileBlock.whileToken = whileToken;

	W_List_create(&(*block)->inner.whileBlock.conditionBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	W_List_create(&(*block)->inner.whileBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, whileToken->location, "%s",
			"missing the condition and body of the while-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	for (; _parser_current != NULL; _parser_current = _parser_current->next)
	{
		const struct Token* const token = (const struct Token* const)_parser_current->data;

		switch (token->kind)
		{
			case TOKEN_KIND_INTRINSIC_ADD:
			case TOKEN_KIND_INTRINSIC_SUBTRACT:
			case TOKEN_KIND_INTRINSIC_MULTIPLY:
			case TOKEN_KIND_INTRINSIC_DIVIDE:
			case TOKEN_KIND_INTRINSIC_MODULUS:
			case TOKEN_KIND_INTRINSIC_EQUAL:
			case TOKEN_KIND_INTRINSIC_NEQUAL:
			case TOKEN_KIND_INTRINSIC_GREATER:
			case TOKEN_KIND_INTRINSIC_LESS:
			case TOKEN_KIND_INTRINSIC_BAND:
			case TOKEN_KIND_INTRINSIC_BOR:
			case TOKEN_KIND_INTRINSIC_BNOT:
			case TOKEN_KIND_INTRINSIC_SHIFTL:
			case TOKEN_KIND_INTRINSIC_SHIFTR:
			case TOKEN_KIND_INTRINSIC_SYSCALL0:
			case TOKEN_KIND_INTRINSIC_SYSCALL1:
			case TOKEN_KIND_INTRINSIC_SYSCALL2:
			case TOKEN_KIND_INTRINSIC_SYSCALL3:
			case TOKEN_KIND_INTRINSIC_SYSCALL4:
			case TOKEN_KIND_INTRINSIC_SYSCALL5:
			case TOKEN_KIND_INTRINSIC_SYSCALL6:
			case TOKEN_KIND_INTRINSIC_CLONE:
			case TOKEN_KIND_INTRINSIC_DROP:
			case TOKEN_KIND_INTRINSIC_OVER:
			case TOKEN_KIND_INTRINSIC_SWAP:
			case TOKEN_KIND_LITERAL_I64:
			case TOKEN_KIND_LITERAL_STRING:
			{
				struct Block* block2 = NULL;

				W_Block_create(&block2, BLOCK_KIND_OPERATION, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseOperationBlock(&block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse operation-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(&(*block)->inner.whileBlock.conditionBlocks, block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_IDENTIFIER:
			{
				struct Block* block2 = NULL;

				W_Block_create(&block2, BLOCK_KIND_IDENTIFIER, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseIdentifierBlock(&block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse identifier-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(&(*block)->inner.whileBlock.conditionBlocks, block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_DO:
			{
				goto parsing_while_block_body;
			} break;

			default: // all unhandled cases that should not be on their own in the respective scopes.
			{
				W_Logger_log(LOG_KIND_ERROR, token->location,
					"encountered an invalid token `%.*s` while parsing while-block's condition!",
					(signed int)token->source.length, token->source.buffer);
				*succeeded = 0;
				return 1;
			} break;
		}
	}

parsing_while_block_body:
	static_assert(1); // Hack for the label issue ^

	struct Token* doToken = (struct Token*)_parser_current->data;

	if (doToken->kind != TOKEN_KIND_KEYWORD_DO)
	{
		W_Logger_log(LOG_KIND_INTERNAL, doToken->location,
			"encountered an invalid token `%.*s` instead of the `do` keyword!",
			(signed int)doToken->source.length, doToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.whileBlock.doToken = doToken;

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, doToken->location, "%s",
			"missing the body of the while-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	W_Parser_tryParseBlocks(&(*block)->inner.whileBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, doToken->location, "%s",
			"failed to parse the while-block's body block!");
		*succeeded = 0;
		return 1;
	},
	{});

	struct Token* endToken = (struct Token*)_parser_current->data;

	if (endToken->kind != TOKEN_KIND_KEYWORD_END)
	{
		W_Logger_log(LOG_KIND_INTERNAL, endToken->location,
			"encountered an invalid token `%.*s` instead of the `end` keyword!",
			(signed int)endToken->source.length, endToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.whileBlock.endToken = endToken;

	*succeeded = 1;
	return 1;
}

static signed char Parser_tryParseWithBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_WITH);
	(*block)->inner.withBlock = (struct WithBlock) {0};

	struct Token* withToken = (struct Token*)_parser_current->data;

	if (withToken->kind != TOKEN_KIND_KEYWORD_WITH)
	{
		W_Logger_log(LOG_KIND_INTERNAL, withToken->location,
			"encountered an invalid token `%.*s` instead of the `with` keyword!",
			(signed int)withToken->source.length, withToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.withBlock.withToken = withToken;

	W_List_create(&(*block)->inner.withBlock.identifierBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	W_List_create(&(*block)->inner.withBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, withToken->location, "%s",
			"missing the identifiers and body of the with-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	for (; _parser_current != NULL; _parser_current = _parser_current->next)
	{
		const struct Token* const token = (const struct Token* const)_parser_current->data;

		switch (token->kind)
		{
			case TOKEN_KIND_IDENTIFIER:
			{
				struct Block* block2 = NULL;

				W_Block_create(&block2, BLOCK_KIND_IDENTIFIER, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseIdentifierBlock(&block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"failed to parse identifier-block `%.*s`",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(&(*block)->inner.withBlock.identifierBlocks, block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_DO:
			{
				goto parsing_with_block_body;
			} break;

			default: // all unhandled cases that should not be on their own in the respective scopes.
			{
				W_Logger_log(LOG_KIND_ERROR, token->location,
					"encountered an invalid token `%.*s` while parsing with-block's identifiers!",
					(signed int)token->source.length, token->source.buffer);
				*succeeded = 0;
				return 1;
			} break;
		}
	}

parsing_with_block_body:
	static_assert(1); // Hack for the label issue ^

	if ((*block)->inner.withBlock.identifierBlocks.count <= 0)
	{
		W_Logger_log(LOG_KIND_INTERNAL, (*block)->inner.withBlock.withToken->location, "%s",
			"missing identifiers in the with-block. At least one identifier is required!");
		*succeeded = 0;
		return 1;
	}

	struct Token* doToken = (struct Token*)_parser_current->data;

	if (doToken->kind != TOKEN_KIND_KEYWORD_DO)
	{
		W_Logger_log(LOG_KIND_INTERNAL, doToken->location,
			"encountered an invalid token `%.*s` instead of the `do` keyword!",
			(signed int)doToken->source.length, doToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.withBlock.doToken = doToken;

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, doToken->location, "%s",
			"missing the body of the with-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	W_Parser_tryParseBlocks(&(*block)->inner.withBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, doToken->location, "%s",
			"failed to parse the with-block's body block!");
		*succeeded = 0;
		return 1;
	},
	{});

	struct Token* endToken = (struct Token*)_parser_current->data;

	if (endToken->kind != TOKEN_KIND_KEYWORD_END)
	{
		W_Logger_log(LOG_KIND_INTERNAL, endToken->location,
			"encountered an invalid token `%.*s` instead of the `end` keyword!",
			(signed int)endToken->source.length, endToken->source.buffer);
		*succeeded = 0;
		return 1;
	}

	(*block)->inner.withBlock.endToken = endToken;

	*succeeded = 1;
	return 1;
}

static signed char Parser_tryParseProcedureBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_PROCEDURE);
	(*block)->inner.procedureBlock = (struct ProcedureBlock) {0};

	struct Token* token = (struct Token*)_parser_current->data;

	if (token->kind == TOKEN_KIND_KEYWORD_EXPORT)
	{
		(*block)->inner.procedureBlock.isExported = 1;

		if (_parser_current->next == NULL)
		{
			W_Logger_log(LOG_KIND_ERROR, token->location,
				"missing the `inline` or `procedure` keyword after the `%.*s` keyword!",
				(signed int)token->source.length, token->source.buffer);
			*succeeded = 0;
			return 1;
		}

		_parser_current = _parser_current->next;
		token = (struct Token*)_parser_current->data;
	}

	if (token->kind == TOKEN_KIND_KEYWORD_INLINE)
	{
		(*block)->inner.procedureBlock.isInlined = 1;

		if (_parser_current->next == NULL)
		{
			W_Logger_log(LOG_KIND_ERROR, token->location,
				"missing the `procedure` keyword after the `%.*s` keyword!",
				(signed int)token->source.length, token->source.buffer);
			*succeeded = 0;
			return 1;
		}

		_parser_current = _parser_current->next;
		token = (struct Token*)_parser_current->data;
	}

	if (token->kind != TOKEN_KIND_KEYWORD_PROCEDURE)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"encountered an invalid token `%.*s` instead of `procedure` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"missing the identifier for the procedure!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;
	token = (struct Token*)_parser_current->data;

	struct Block* block2 = NULL;

	W_Block_create(&block2, BLOCK_KIND_IDENTIFIER, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	W_Parser_tryParseIdentifierBlock(&block2, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"failed to parse identifier for the procedure!");
		*succeeded = 0;
		return 1;
	},
	{});

	(*block)->inner.procedureBlock.identifierBlock = block2;

	if (((*block)->inner.procedureBlock.identifierBlock->inner.identifierBlock.nameToken->source.length == 4)
	 && (strncmp(
		(*block)->inner.procedureBlock.identifierBlock->inner.identifierBlock.nameToken->source.buffer,
		"main",
		(*block)->inner.procedureBlock.identifierBlock->inner.identifierBlock.nameToken->source.length) == 0))
	{
		(*block)->inner.procedureBlock.isMain = 1;
	}

	token = (struct Token*)_parser_current->data;

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"missing the `do` keyword for the procedure!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;
	token = (struct Token*)_parser_current->data;

	if (token->kind == TOKEN_KIND_KEYWORD_IN)
	{
		W_List_create(&(*block)->inner.procedureBlock.inTypesTokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// TODO: log!
			*succeeded = 0;
			return 1;
		},
		{});

		if (_parser_current->next == NULL)
		{
			W_Logger_log(LOG_KIND_ERROR, token->location,
				"expected at least one type specifier after `in` keyword!",
				(signed int)token->source.length, token->source.buffer);
			*succeeded = 0;
			return 1;
		}

		_parser_current = _parser_current->next;

		for (; _parser_current != NULL; _parser_current = _parser_current->next)
		{
			token = (struct Token*)_parser_current->data;

			switch (token->kind)
			{
				case TOKEN_KIND_KEYWORD_OUT:
				case TOKEN_KIND_KEYWORD_DO:
				{
					goto parsing_in_types_block_end;
				} break;

				case TOKEN_KIND_KEYWORD_I64:
				case TOKEN_KIND_KEYWORD_P64:
				{
					W_List_pushLast(&(*block)->inner.procedureBlock.inTypesTokens, token, succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						// TODO: log!
						*succeeded = 0;
						return 1;
					},
					{});
				} break;

				default:
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"encountered an invalid token `%.*s` in the type specifiers of the `in` keyword!",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				} break;
			}
		}

parsing_in_types_block_end:
		if ((*block)->inner.procedureBlock.inTypesTokens.count <= 0)
		{
			W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
				"`in` keyword requires at least on type specifier keyword to follow!");
			*succeeded = 0;
			return 1;
		}
	}

	if (token->kind == TOKEN_KIND_KEYWORD_OUT)
	{
		W_List_create(&(*block)->inner.procedureBlock.outTypesTokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// TODO: log!
			*succeeded = 0;
			return 1;
		},
		{});

		if (_parser_current->next == NULL)
		{
			W_Logger_log(LOG_KIND_ERROR, token->location,
				"expected at least one type specifier after `out` keyword!",
				(signed int)token->source.length, token->source.buffer);
			*succeeded = 0;
			return 1;
		}

		_parser_current = _parser_current->next;

		for (; _parser_current != NULL; _parser_current = _parser_current->next)
		{
			token = (struct Token*)_parser_current->data;

			switch (token->kind)
			{
				case TOKEN_KIND_KEYWORD_DO:
				{
					goto parsing_out_types_block_end;
				} break;

				case TOKEN_KIND_KEYWORD_I64:
				case TOKEN_KIND_KEYWORD_P64:
				{
					W_List_pushLast(&(*block)->inner.procedureBlock.outTypesTokens, token, succeeded,
					{
						*succeeded = 0;
						return 0;
					},
					{
						// TODO: log!
						*succeeded = 0;
						return 1;
					},
					{});
				} break;

				default:
				{
					W_Logger_log(LOG_KIND_ERROR, token->location,
						"encountered an invalid token `%.*s` in the type specifiers of the `out` keyword!",
						(signed int)token->source.length, token->source.buffer);
					*succeeded = 0;
					return 1;
				} break;
			}
		}

parsing_out_types_block_end:
		if ((*block)->inner.procedureBlock.outTypesTokens.count <= 0)
		{
			W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
				"`out` keyword requires at least on type specifier keyword to follow!");
			*succeeded = 0;
			return 1;
		}
	}

	if (token->kind != TOKEN_KIND_KEYWORD_DO)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"encountered an invalid token `%.*s` instead of `do` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"missing the body of the procedure-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	W_List_create(&(*block)->inner.procedureBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	W_Parser_tryParseBlocks(&(*block)->inner.procedureBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"failed to parse the procedure-block's body block!");
		*succeeded = 0;
		return 1;
	},
	{});

	token = (struct Token*)_parser_current->data;

	if (token->kind != TOKEN_KIND_KEYWORD_END)
	{
		W_Logger_log(LOG_KIND_INTERNAL, token->location,
			"encountered an invalid token `%.*s` instead of the `end` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	*succeeded = 1;
	return 1;
}

static signed char Parser_tryParseModuleBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_MODULE);
	(*block)->inner.moduleBlock = (struct ModuleBlock) {0};

	struct Token* token = (struct Token*)_parser_current->data;

	if (token->kind != TOKEN_KIND_KEYWORD_MODULE)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"encountered an invalid token `%.*s` instead of the `module` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"missing the identifier for the `module` keyword!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;
	token = (struct Token*)_parser_current->data;

	if (token->kind != TOKEN_KIND_IDENTIFIER)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"encountered an invalid token `%.*s` instead of an identifier!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	struct Block* block2 = NULL;

	W_Block_create(&block2, BLOCK_KIND_IDENTIFIER, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	W_Parser_tryParseIdentifierBlock(&block2, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"failed to parse identifier for the module!");
		*succeeded = 0;
		return 1;
	},
	{});

	(*block)->inner.moduleBlock.identifierBlock= block2;

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"missing the `do` keyword for the module!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;
	token = (struct Token*)_parser_current->data;

	if (token->kind != TOKEN_KIND_KEYWORD_DO)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"encountered an invalid token `%.*s` instead of a `do` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"missing the body of the module-block!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	W_List_create(&(*block)->inner.moduleBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	W_Parser_tryParseBlocks(&(*block)->inner.moduleBlock.bodyBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"failed to parse do-to-end blocks for the module!");
		*succeeded = 0;
		return 1;
	},
	{});

	token = (struct Token*)_parser_current->data;

	if (token->kind != TOKEN_KIND_KEYWORD_END)
	{
		W_Logger_log(LOG_KIND_INTERNAL, token->location,
			"encountered an invalid token `%.*s` instead of the `end` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	*succeeded = 1;
	return 1;
}

static signed char Parser_tryParseImportBlock(
	struct Block** const block,
	signed char* const succeeded)
{
	if (_parser_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _parser_current is invalid (null)!");
		return 0;
	}

	if (block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block` is invalid (null)!");
		return 0;
	}

	if (*block == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `block`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	assert((*block)->kind == BLOCK_KIND_IMPORT);
	(*block)->inner.importBlock = (struct ImportBlock) {0};

	struct Token* token = (struct Token*)_parser_current->data;

	if (token->kind != TOKEN_KIND_KEYWORD_IMPORT)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location,
			"encountered an invalid token `%.*s` instead of the `import` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	if (_parser_current->next == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
			"missing the identifier for the `import` keyword!");
		*succeeded = 0;
		return 1;
	}

	_parser_current = _parser_current->next;

	W_List_create(&(*block)->inner.importBlock.identifierBlocks, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		*succeeded = 0;
		return 1;
	},
	{});

	for (; _parser_current != NULL; _parser_current = _parser_current->next)
	{
		token = (struct Token*)_parser_current->data;

		switch (token->kind)
		{
			case TOKEN_KIND_IDENTIFIER:
			{
				struct Block* block2 = NULL;

				W_Block_create(&block2, BLOCK_KIND_IDENTIFIER, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});

				W_Parser_tryParseIdentifierBlock(&block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					W_Logger_log(LOG_KIND_ERROR, token->location, "%s",
						"failed to parse identifier for the import!");
					*succeeded = 0;
					return 1;
				},
				{});

				W_List_pushLast(&(*block)->inner.importBlock.identifierBlocks, block2, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					// TODO: log!
					*succeeded = 0;
					return 1;
				},
				{});
			} break;

			case TOKEN_KIND_KEYWORD_END:
			{
				goto parsing_import_block_end;
			} break;

			default:
			{
				W_Logger_log(LOG_KIND_ERROR, token->location,
					"encountered an invalid token `%.*s` instead of an identifier!",
					(signed int)token->source.length, token->source.buffer);
				*succeeded = 0;
				return 1;
			} break;
		}
	}

parsing_import_block_end:
	(*block)->inner.importBlock.referenceBlock = NULL;

	token = (struct Token*)_parser_current->data;

	if (token->kind != TOKEN_KIND_KEYWORD_END)
	{
		W_Logger_log(LOG_KIND_INTERNAL, token->location,
			"encountered an invalid token `%.*s` instead of the `end` keyword!",
			(signed int)token->source.length, token->source.buffer);
		*succeeded = 0;
		return 1;
	}

	*succeeded = 1;
	return 1;
}

#endif

/**
 * @}
 */
