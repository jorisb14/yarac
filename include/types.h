
/**
 * @file types.h
 *
 * @copyright This file is a part of the project yarac and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-10-30
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <location.h>
#include <containers.h>

#include <stdio.h>

/**
 * @addtogroup types
 * 
 * @{
 */

struct Token
{
	unsigned long long id;

	enum
	{
		TOKEN_KIND_INVALID = 0,
		TOKEN_KIND_IDENTIFIER,
		TOKEN_KIND_IDENTIFIERS,

		TOKEN_KIND_FIRST_KEYWORD,
		TOKEN_KIND_KEYWORD_I8 = TOKEN_KIND_FIRST_KEYWORD,
		TOKEN_KIND_KEYWORD_I16,
		TOKEN_KIND_KEYWORD_I32,
		TOKEN_KIND_KEYWORD_I64,
		TOKEN_KIND_KEYWORD_U8,
		TOKEN_KIND_KEYWORD_U16,
		TOKEN_KIND_KEYWORD_U32,
		TOKEN_KIND_KEYWORD_U64,
		TOKEN_KIND_KEYWORD_F32,
		TOKEN_KIND_KEYWORD_F64,
		TOKEN_KIND_KEYWORD_P8,
		TOKEN_KIND_KEYWORD_P16,
		TOKEN_KIND_KEYWORD_P32,
		TOKEN_KIND_KEYWORD_P64,
		TOKEN_KIND_KEYWORD_NULL,
		TOKEN_KIND_KEYWORD_IMPORT,
		TOKEN_KIND_KEYWORD_FROM,
		TOKEN_KIND_KEYWORD_MODULE,
		TOKEN_KIND_KEYWORD_EXPORT,
		TOKEN_KIND_KEYWORD_ALIAS,
		TOKEN_KIND_KEYWORD_CONST,
		TOKEN_KIND_KEYWORD_PACKED,
		TOKEN_KIND_KEYWORD_STRUCT,
		TOKEN_KIND_KEYWORD_FIELD,
		TOKEN_KIND_KEYWORD_BYTES,
		TOKEN_KIND_KEYWORD_INLINE,
		TOKEN_KIND_KEYWORD_PROCEDURE,
		TOKEN_KIND_KEYWORD_IN,
		TOKEN_KIND_KEYWORD_OUT,
		TOKEN_KIND_KEYWORD_AS,
		TOKEN_KIND_KEYWORD_RETURN,
		TOKEN_KIND_KEYWORD_IF,
		TOKEN_KIND_KEYWORD_WHILE,
		TOKEN_KIND_KEYWORD_WITH,
		TOKEN_KIND_KEYWORD_DO,
		TOKEN_KIND_KEYWORD_END,
		TOKEN_KIND_LAST_KEYWORD = TOKEN_KIND_KEYWORD_END,

		TOKEN_KIND_FIRST_INTRINSIC,
		TOKEN_KIND_INTRINSIC_ADD = TOKEN_KIND_FIRST_INTRINSIC,
		TOKEN_KIND_INTRINSIC_SUBTRACT,
		TOKEN_KIND_INTRINSIC_MULTIPLY,
		TOKEN_KIND_INTRINSIC_DIVIDE,
		TOKEN_KIND_INTRINSIC_MODULUS,
		TOKEN_KIND_INTRINSIC_EQUAL,
		TOKEN_KIND_INTRINSIC_NEQUAL,
		TOKEN_KIND_INTRINSIC_GREATER,
		TOKEN_KIND_INTRINSIC_LESS,
		TOKEN_KIND_INTRINSIC_BAND,
		TOKEN_KIND_INTRINSIC_BOR,
		TOKEN_KIND_INTRINSIC_BNOT,
		TOKEN_KIND_INTRINSIC_XOR,
		TOKEN_KIND_INTRINSIC_SHIFTL,
		TOKEN_KIND_INTRINSIC_SHIFTR,
		TOKEN_KIND_INTRINSIC_AND,
		TOKEN_KIND_INTRINSIC_OR,
		TOKEN_KIND_INTRINSIC_NOT,
		TOKEN_KIND_INTRINSIC_SYSCALL0,
		TOKEN_KIND_INTRINSIC_SYSCALL1,
		TOKEN_KIND_INTRINSIC_SYSCALL2,
		TOKEN_KIND_INTRINSIC_SYSCALL3,
		TOKEN_KIND_INTRINSIC_SYSCALL4,
		TOKEN_KIND_INTRINSIC_SYSCALL5,
		TOKEN_KIND_INTRINSIC_SYSCALL6,
		TOKEN_KIND_INTRINSIC_CLONE,
		TOKEN_KIND_INTRINSIC_DROP,
		TOKEN_KIND_INTRINSIC_OVER,
		TOKEN_KIND_INTRINSIC_SWAP,
		TOKEN_KIND_INTRINSIC_READ8,
		TOKEN_KIND_INTRINSIC_READ16,
		TOKEN_KIND_INTRINSIC_READ32,
		TOKEN_KIND_INTRINSIC_READ64,
		TOKEN_KIND_INTRINSIC_WRITE8,
		TOKEN_KIND_INTRINSIC_WRITE16,
		TOKEN_KIND_INTRINSIC_WRITE32,
		TOKEN_KIND_INTRINSIC_WRITE64,
		TOKEN_KIND_LAST_INTRINSIC = TOKEN_KIND_INTRINSIC_WRITE64,

		TOKEN_KIND_FIRST_DECORATOR,
		TOKEN_KIND_DECORATOR_COMPILE_TIME = TOKEN_KIND_FIRST_DECORATOR,
		TOKEN_KIND_DECORATOR_SUPPRESS_WARNINGS,
		TOKEN_KIND_DECORATOR_NOT_IMPLEMENTED,
		TOKEN_KIND_LAST_DECORATOR = TOKEN_KIND_DECORATOR_NOT_IMPLEMENTED,

		TOKEN_KIND_FIRST_LITERAL,
		TOKEN_KIND_LITERAL_I8 = TOKEN_KIND_FIRST_LITERAL,
		TOKEN_KIND_LITERAL_I16,
		TOKEN_KIND_LITERAL_I32,
		TOKEN_KIND_LITERAL_I64,
		TOKEN_KIND_LITERAL_U8,
		TOKEN_KIND_LITERAL_U16,
		TOKEN_KIND_LITERAL_U32,
		TOKEN_KIND_LITERAL_U64,
		TOKEN_KIND_LITERAL_F32,
		TOKEN_KIND_LITERAL_F64,
		TOKEN_KIND_LITERAL_P8,
		TOKEN_KIND_LITERAL_P16,
		TOKEN_KIND_LITERAL_P32,
		TOKEN_KIND_LITERAL_P64,
		TOKEN_KIND_LITERAL_STRING, // NOTE: might add char literal
		TOKEN_KIND_LAST_LITERAL = TOKEN_KIND_LITERAL_STRING,

		TOKEN_KINDS_COUNT
	} kind;

	union
	{
		signed char i8;
		signed short i16;
		signed int i32;
		signed long long i64;
		unsigned char u8;
		unsigned short u16;
		unsigned int u32;
		unsigned long long u64;
		float f32;
		long double f64;
		unsigned char p8;
		unsigned short p16;
		unsigned int p32;
		unsigned long long p64;
		struct
		{
			unsigned char* bytes;
			signed long long length;
		} string;
	} value;

	struct
	{
		char* buffer;
		signed long long length;
	} source;

	struct Location location;
};

/**
 * Create a token on the heap. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Token* token;
 *     assert(Token_create(&token) == 1);
 *     // ... 
 * @endcode
 */
signed char Token_create(
	struct Token** const token,
	const unsigned long long id,
	const signed long long kind,
	const struct Location* const location,
	signed char* const succeeded);

#define W_Token_create(_inmacro_token, _inmacro_id, _inmacro_kind, _inmacro_location, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Token_create((_inmacro_token), (_inmacro_id), (_inmacro_kind), (_inmacro_location), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Token_create(...) returned with internal failure!"); \
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
 * Destroy a token on the heap. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Token* token;
 *     // ... 
 *     assert(Token_destroy(&token) == 1);
 *     // ... 
 * @endcode
 */
signed char Token_destroy(
	const struct Token* const * const token,
	signed char* const succeeded);

#define W_Token_destroy(_inmacro_token, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Token_destroy((_inmacro_token), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Token_destroy(...) returned with internal failure!"); \
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

struct OperationBlock
{
	struct Token* token;
};

struct IdentifierBlock
{
	struct Token* nameToken;
	struct Block* referenceBlock; // NOTE: should not be deallocated, since it is a reference to an actual block!
};

struct ImportBlock
{
	struct List* identifierBlocks;
	struct Block* referenceBlock; // NOTE: should not be deallocated, since it is a reference to an actual block!
};

struct IfBlock
{
	struct Token* ifToken;
	struct List* conditionBlocks;
	struct Token* doToken;
	struct List* bodyBlocks;
	struct Token* endToken;
};

struct WhileBlock
{
	struct Token* whileToken;
	struct List* conditionBlocks;
	struct Token* doToken;
	struct List* bodyBlocks;
	struct Token* endToken;
};

struct WithBlock
{
	struct Token* withToken;
	struct List* identifierBlocks;
	struct List* typesTokens;
	struct Token* doToken;
	struct List* bodyBlocks;
	struct Token* endToken;
};

struct ProcedureBlock
{
	struct Block* identifierBlock;
	struct List* inTypesTokens;
	struct List* outTypesTokens;
	struct List* bodyBlocks;
	signed char isExported;
	signed char isInlined;
	signed char isMain;
};

struct ModuleBlock
{
	struct Block* identifierBlock;
	struct List* bodyBlocks;
};

struct CompoundBlock
{
	enum
	{
		COMPOUND_BLOCK_KIND_IF = 0,
		COMPOUND_BLOCK_KIND_WHILE,
		COMPOUND_BLOCK_KIND_WITH,
		COMPOUND_BLOCK_KIND_PROCEDURE,
		COMPOUND_BLOCK_KIND_MODULE,

		COMPOUND_BLOCK_KINDS_COUNT
	} kind;

	union
	{
		struct IfBlock ifBlock;
		struct WhileBlock whileBlock;
		struct WithBlock withBlock;
		struct ProcedureBlock procedureBlock;
		struct ModuleBlock moduleBlock;
	} inner;
};

struct Block
{
	enum
	{
		BLOCK_KIND_OPERATION = 0,
		BLOCK_KIND_IDENTIFIER,
		BLOCK_KIND_COMPOUND,
		BLOCK_KIND_IMPORT,

		BLOCK_KINDS_COUNT
	} kind;

	union
	{
		struct OperationBlock operationBlock;
		struct IdentifierBlock identifierBlock;
		struct ImportBlock importBlock;
		struct CompoundBlock compoundBlock;
	} inner;
};

/**
 * Create a block on the heap. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Block* block;
 *     assert(Block_create(&block, BLOCK_KIND_IF) == 1);
 *     // ... 
 * @endcode
 */
signed char Block_create(
	struct Block** const block,
	const signed long long kind,
	signed char* const succeeded);

#define W_Block_create(_inmacro_block, _inmacro_kind, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Block_create((_inmacro_block), (_inmacro_kind), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Block_create(...) returned with internal failure!"); \
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
 * Destroy a block on the heap. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Block* block;
 *     // ... 
 *     assert(Block_destroy(&block, BLOCK_KIND_IF) == 1);
 *     // ... 
 * @endcode
 */
signed char Block_destroy(
	const struct Block* const * const block,
	signed char* const succeeded);

#define W_Block_destroy(_inmacro_block, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Block_destroy((_inmacro_block), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Block_destroy(...) returned with internal failure!"); \
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

struct Frame
{
	struct List* bodyBlocks;
};

/**
 * Create a frame on the heap. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Frame* frame;
 *     assert(Frame_create(&frame) == 1);
 *     // ... 
 * @endcode
 */
signed char Frame_create(
	struct Frame** const frame,
	signed char* const succeeded);

#define W_Frame_create(_inmacro_frame, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Frame_create((_inmacro_frame), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Frame_create(...) returned with internal failure!"); \
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
 * Destroy a frame on the heap. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Frame* frame;
 *     // ... 
 *     assert(Frame_destroy(&frame) == 1);
 *     // ... 
 * @endcode
 */
signed char Frame_destroy(
	const struct Frame* const * const frame,
	signed char* const succeeded);

#define W_Frame_destroy(_inmacro_frame, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Frame_destroy((_inmacro_frame), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Frame_destroy(...) returned with internal failure!"); \
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
