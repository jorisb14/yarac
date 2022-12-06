
/**
 * @file utils.h
 *
 * @copyright This file is a part of the project yarac and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-11-03
 */

#ifndef _DEBUG_UTILS_H_
#define _DEBUG_UTILS_H_

#include <logger.h>
#include <containers.h>
#include <types.h>

#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

/**
 * @addtogroup utils
 * 
 * @{
 */

#define INDENT_N(f, n) \
	{ \
		for (unsigned long long _indentsCount = 0; _indentsCount < (n); ++_indentsCount) \
			fprintf((f), "    "); \
	}

void Token_print(
	FILE* const file,
	const struct Token* const * const token,
	const unsigned long long indents,
	signed char* const succeeded)
{
	if (file == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `file` is invalid (null)!");
		return;
	}

	if (token == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `token` is invalid (null)!");
		return;
	}

	if (*token == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `token`'s deref is invalid (null)!");
		return;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return;
	}

	*succeeded = 0;

	// NOTE: this `stringifiedTokensKindsCount` define must be changed when modifying the `stringifiedTokensKinds` set!
	#define stringifiedTokensKindsCount ((unsigned int)94)
	static const char* stringifiedTokensKinds[] =
	{
		[TOKEN_KIND_INVALID] = "invalid",
		[TOKEN_KIND_IDENTIFIER] = "identifier",
		[TOKEN_KIND_IDENTIFIERS] = "identifiers",

		[TOKEN_KIND_KEYWORD_I8] = "keyword_i8",
		[TOKEN_KIND_KEYWORD_I16] = "keyword_i16",
		[TOKEN_KIND_KEYWORD_I32] = "keyword_i32",
		[TOKEN_KIND_KEYWORD_I64] = "keyword_i64",
		[TOKEN_KIND_KEYWORD_U8] = "keyword_u8",
		[TOKEN_KIND_KEYWORD_U16] = "keyword_u16",
		[TOKEN_KIND_KEYWORD_U32] = "keyword_u32",
		[TOKEN_KIND_KEYWORD_U64] = "keyword_u64",
		[TOKEN_KIND_KEYWORD_F32] = "keyword_f32",
		[TOKEN_KIND_KEYWORD_F64] = "keyword_f64",
		[TOKEN_KIND_KEYWORD_P8] = "keyword_p8",
		[TOKEN_KIND_KEYWORD_P16] = "keyword_p16",
		[TOKEN_KIND_KEYWORD_P32] = "keyword_p32",
		[TOKEN_KIND_KEYWORD_P64] = "keyword_p64",
		[TOKEN_KIND_KEYWORD_NULL] = "keyword_null",
		[TOKEN_KIND_KEYWORD_IMPORT] = "keyword_import",
		[TOKEN_KIND_KEYWORD_FROM] = "keyword_from",
		[TOKEN_KIND_KEYWORD_MODULE] = "keyword_module",
		[TOKEN_KIND_KEYWORD_EXPORT] = "keyword_export",
		[TOKEN_KIND_KEYWORD_ALIAS] = "keyword_alias",
		[TOKEN_KIND_KEYWORD_CONST] = "keyword_const",
		[TOKEN_KIND_KEYWORD_PACKED] = "keyword_packed",
		[TOKEN_KIND_KEYWORD_STRUCT] = "keyword_struct",
		[TOKEN_KIND_KEYWORD_FIELD] = "keyword_field",
		[TOKEN_KIND_KEYWORD_BYTES] = "keyword_bytes",
		[TOKEN_KIND_KEYWORD_INLINE] = "keyword_inline",
		[TOKEN_KIND_KEYWORD_PROCEDURE] = "keyword_procedure",
		[TOKEN_KIND_KEYWORD_IN] = "keyword_in",
		[TOKEN_KIND_KEYWORD_OUT] = "keyword_out",
		[TOKEN_KIND_KEYWORD_AS] = "keyword_as",
		[TOKEN_KIND_KEYWORD_RETURN] = "keyword_return",
		[TOKEN_KIND_KEYWORD_IF] = "keyword_if",
		[TOKEN_KIND_KEYWORD_WHILE] = "keyword_while",
		[TOKEN_KIND_KEYWORD_WITH] = "keyword_with",
		[TOKEN_KIND_KEYWORD_DO] = "keyword_do",
		[TOKEN_KIND_KEYWORD_END] = "keyword_end",

		[TOKEN_KIND_INTRINSIC_ADD] = "intrinsic_add",
		[TOKEN_KIND_INTRINSIC_SUBTRACT] = "intrinsic_subtract",
		[TOKEN_KIND_INTRINSIC_MULTIPLY] = "intrinsic_multiply",
		[TOKEN_KIND_INTRINSIC_DIVIDE] = "intrinsic_divide",
		[TOKEN_KIND_INTRINSIC_MODULUS] = "intrinsic_modulus",
		[TOKEN_KIND_INTRINSIC_EQUAL] = "intrinsic_equal",
		[TOKEN_KIND_INTRINSIC_NEQUAL] = "intrinsic_nequal",
		[TOKEN_KIND_INTRINSIC_GREATER] = "intrinsic_greater",
		[TOKEN_KIND_INTRINSIC_LESS] = "intrinsic_less",
		[TOKEN_KIND_INTRINSIC_BAND] = "intrinsic_band",
		[TOKEN_KIND_INTRINSIC_BOR] = "intrinsic_bor",
		[TOKEN_KIND_INTRINSIC_BNOT] = "intrinsic_bnot",
		[TOKEN_KIND_INTRINSIC_XOR] = "intrinsic_xor",
		[TOKEN_KIND_INTRINSIC_SHIFTL] = "intrinsic_shiftl",
		[TOKEN_KIND_INTRINSIC_SHIFTR] = "intrinsic_shiftr",
		[TOKEN_KIND_INTRINSIC_AND] = "intrinsic_and",
		[TOKEN_KIND_INTRINSIC_OR] = "intrinsic_or",
		[TOKEN_KIND_INTRINSIC_NOT] = "intrinsic_not",
		[TOKEN_KIND_INTRINSIC_SYSCALL0] = "intrinsic_syscall0",
		[TOKEN_KIND_INTRINSIC_SYSCALL1] = "intrinsic_syscall1",
		[TOKEN_KIND_INTRINSIC_SYSCALL2] = "intrinsic_syscall2",
		[TOKEN_KIND_INTRINSIC_SYSCALL3] = "intrinsic_syscall3",
		[TOKEN_KIND_INTRINSIC_SYSCALL4] = "intrinsic_syscall4",
		[TOKEN_KIND_INTRINSIC_SYSCALL5] = "intrinsic_syscall5",
		[TOKEN_KIND_INTRINSIC_SYSCALL6] = "intrinsic_syscall6",
		[TOKEN_KIND_INTRINSIC_CLONE] = "intrinsic_clone",
		[TOKEN_KIND_INTRINSIC_DROP] = "intrinsic_drop",
		[TOKEN_KIND_INTRINSIC_OVER] = "intrinsic_over",
		[TOKEN_KIND_INTRINSIC_SWAP] = "intrinsic_swap",
		[TOKEN_KIND_INTRINSIC_READ8] = "intrinsic_read8",
		[TOKEN_KIND_INTRINSIC_READ16] = "intrinsic_read16",
		[TOKEN_KIND_INTRINSIC_READ32] = "intrinsic_read32",
		[TOKEN_KIND_INTRINSIC_READ64] = "intrinsic_read64",
		[TOKEN_KIND_INTRINSIC_WRITE8] = "intrinsic_write8",
		[TOKEN_KIND_INTRINSIC_WRITE16] = "intrinsic_write16",
		[TOKEN_KIND_INTRINSIC_WRITE32] = "intrinsic_write32",
		[TOKEN_KIND_INTRINSIC_WRITE64] = "intrinsic_write64",

		[TOKEN_KIND_DECORATOR_COMPILE_TIME] = "decorator_compile_time",
		[TOKEN_KIND_DECORATOR_SUPPRESS_WARNINGS] = "decorator_suppress_warnings",
		[TOKEN_KIND_DECORATOR_NOT_IMPLEMENTED] = "decorator_not_implemented",

		[TOKEN_KIND_LITERAL_I8] = "literal_i8",
		[TOKEN_KIND_LITERAL_I16] = "literal_i16",
		[TOKEN_KIND_LITERAL_I32] = "literal_i32",
		[TOKEN_KIND_LITERAL_I64] = "literal_i64",
		[TOKEN_KIND_LITERAL_U8] = "literal_u8",
		[TOKEN_KIND_LITERAL_U16] = "literal_u16",
		[TOKEN_KIND_LITERAL_U32] = "literal_u32",
		[TOKEN_KIND_LITERAL_U64] = "literal_u64",
		[TOKEN_KIND_LITERAL_F32] = "literal_f32",
		[TOKEN_KIND_LITERAL_F64] = "literal_f64",
		[TOKEN_KIND_LITERAL_P8] = "literal_p8",
		[TOKEN_KIND_LITERAL_P16] = "literal_p16",
		[TOKEN_KIND_LITERAL_P32] = "literal_p32",
		[TOKEN_KIND_LITERAL_P64] = "literal_p64",
		[TOKEN_KIND_LITERAL_STRING] = "literal_string"
	};
	static_assert(TOKEN_KINDS_COUNT == stringifiedTokensKindsCount,
		"Stringified token kinds are out of sync with the kinds enum!");
	#undef stringifiedTokensKindsCount

	if ((*token)->kind < 0 || (*token)->kind > TOKEN_KINDS_COUNT)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `token`'s kind is invalid (null)!");
		*succeeded = 0;
		return;
	}

	INDENT_N(file, indents);
	fprintf(file, "<id=`%llu` kind=`%s` source=`%.*s` location=`%s:%llu:%llu`>\n",
		(*token)->id,
		stringifiedTokensKinds[(*token)->kind],
		(signed int)(*token)->source.length, (*token)->source.buffer,
		(*token)->location.file, (*token)->location.line, (*token)->location.column);

	*succeeded = 1;
}

void Block_print(
	FILE* const file,
	const struct Block* const * const blockP,
	const unsigned long long indents,
	signed char* const succeeded)
{
	assert(blockP != NULL);
	assert(*blockP != NULL);
	const struct Block* const block = *blockP;

	switch (block->kind)
	{
		case BLOCK_KIND_OPERATION:
		{
			INDENT_N(file, indents);
			fprintf(file, "[OperationBlock]\n");
			Token_print(file, (const struct Token* const * const)&block->inner.operationBlock.token, indents + 1, succeeded);
		} break;

		case BLOCK_KIND_IDENTIFIER:
		{
			INDENT_N(file, indents);
			fprintf(file, "[IdentifierBlock]\n");
			Token_print(file, (const struct Token* const * const)&block->inner.identifierBlock.nameToken, indents + 1, succeeded);
		} break;

		case BLOCK_KIND_COMPOUND:
		{
			switch (block->inner.compoundBlock.kind)
			{
				case COMPOUND_BLOCK_KIND_IF:
				{
					INDENT_N(file, indents);
					fprintf(file, "[IfBlock]\n");

					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.ifBlock.ifToken, indents + 1, succeeded);
					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.ifBlock.doToken, indents + 1, succeeded);
					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.ifBlock.endToken, indents + 1, succeeded);
					fprintf(file, "\n");

					INDENT_N(file, indents + 1);
					fprintf(file, "condition_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.ifBlock.conditionBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);

					INDENT_N(file, indents + 1);
					fprintf(file, "body_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.ifBlock.bodyBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);
				} break;

				case COMPOUND_BLOCK_KIND_WHILE:
				{
					INDENT_N(file, indents);
					fprintf(file, "[WhileBlock]\n");

					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.whileBlock.whileToken, indents + 1, succeeded);
					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.whileBlock.doToken, indents + 1, succeeded);
					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.whileBlock.endToken, indents + 1, succeeded);
					fprintf(file, "\n");

					INDENT_N(file, indents + 1);
					fprintf(file, "condition_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.whileBlock.conditionBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);

					INDENT_N(file, indents + 1);
					fprintf(file, "body_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.whileBlock.bodyBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);
				} break;

				case COMPOUND_BLOCK_KIND_WITH:
				{
					INDENT_N(file, indents);
					fprintf(file, "[WithBlock]\n");

					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.withBlock.withToken, indents + 1, succeeded);
					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.withBlock.doToken, indents + 1, succeeded);
					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.withBlock.endToken, indents + 1, succeeded);
					fprintf(file, "\n");

					INDENT_N(file, indents + 1);
					fprintf(file, "identifier_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.withBlock.identifierBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);

					INDENT_N(file, indents + 1);
					fprintf(file, "body_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.withBlock.bodyBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);
				} break;

				case COMPOUND_BLOCK_KIND_PROCEDURE:
				{
					INDENT_N(file, indents);
					fprintf(file, "[ProcedureBlock]\n");

					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.procedureBlock.identifierBlock->inner.identifierBlock.nameToken, indents + 1, succeeded);

					INDENT_N(file, indents + 1);
					fprintf(file, "is_exported=%s\n", block->inner.compoundBlock.inner.procedureBlock.isExported ? "true" : "false");

					INDENT_N(file, indents + 1);
					fprintf(file, "is_inlined=%s\n", block->inner.compoundBlock.inner.procedureBlock.isInlined ? "true" : "false");

					INDENT_N(file, indents + 1);
					fprintf(file, "is_main=%s\n", block->inner.compoundBlock.inner.procedureBlock.isMain ? "true" : "false");

					fprintf(file, "\n");

					INDENT_N(file, indents + 1);
					fprintf(file, "required_types:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.procedureBlock.inTypesTokens->head; iter != NULL; iter = iter->next)
						Token_print(file, (const struct Token* const * const)&iter->data, indents + 2, succeeded);

					INDENT_N(file, indents + 1);
					fprintf(file, "returned_types:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.procedureBlock.outTypesTokens->head; iter != NULL; iter = iter->next)
						Token_print(file, (const struct Token* const * const)&iter->data, indents + 2, succeeded);

					INDENT_N(file, indents + 1);
					fprintf(file, "body_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.procedureBlock.bodyBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);
				} break;

				case COMPOUND_BLOCK_KIND_MODULE:
				{
					INDENT_N(file, indents);
					fprintf(file, "[ModuleBlock]\n");

					Token_print(file, (const struct Token* const * const)&block->inner.compoundBlock.inner.moduleBlock.identifierBlock->inner.identifierBlock.nameToken, indents + 1, succeeded);

					fprintf(file, "\n");

					INDENT_N(file, indents + 1);
					fprintf(file, "body_blocks:\n");
					for (struct List_Node* iter = block->inner.compoundBlock.inner.moduleBlock.bodyBlocks->head; iter != NULL; iter = iter->next)
						Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);
				} break;

				default:
				{
				} break;
			}
		} break;

		case BLOCK_KIND_IMPORT:
		{
			INDENT_N(file, indents);
			fprintf(file, "[ImportBlock]\n");

			INDENT_N(file, indents + 1);
			fprintf(file, "identifiers_blocks:\n");
			for (struct List_Node* iter = block->inner.importBlock.identifierBlocks->head; iter != NULL; iter = iter->next)
				Block_print(file, (const struct Block* const * const)&iter->data, indents + 2, succeeded);
		} break;

		default:
		{
		} break;
	}
}

void Frame_print(
	FILE* const file,
	const struct Frame* const * const frame,
	const unsigned long long indents,
	signed char* const succeeded)
{
	assert(frame != NULL);
	assert(*frame != NULL);

	INDENT_N(file, indents);
	fprintf(file, "Frame:\n");

	fprintf(file, "\n");
	INDENT_N(file, indents + 1);
	fprintf(file, "body_blocks:\n");

	for (struct List_Node* _iter = (*frame)->bodyBlocks->head; _iter != NULL; _iter = _iter->next)
	{
		const struct Block* const block = (const struct Block* const)_iter->data;
		Block_print(file, &block, indents + 2, succeeded);
	}
}

/**
 * @}
 */

#endif
