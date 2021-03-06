/*
 * global.h
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "word.h"
//#include "translate.h"

typedef int bool;

#define TRUE	1
#define FALSE	0

//#define NULL	0
#define EOS		'\0'
#define DONE	0
#define ERROR	-2
#define NONE	-1
#define STR_MAX	1204
#define FUNC_MAX	16  // 最多FUNC_MAX个函数，包括main
#define	VAR_MAX		16 // 最多VAR_MAX个变量
#define	VAR_NAME_MAX	16

#define VALUE_STACK_ADDR	1 // 栈上分配的变量
#define VALUE_IMM			2
#define VALUE_ADDR			3 // 内存中普通的变量
#define VALUE_TEMP_ADDR		4 // 临时变量.bss
#define VALUE_NONE			5 // inc优化时不需要临时变量
#define VALUE_ARRAY			6 // 給數組賦值

#define NO_LABEL	0
#define LABEL		123

#define NOT_FOUND			-404


#define MAX_ASM_LINE	1024
#define MAX_CHAR_PER_ASM_LINE	128

typedef struct{
	int lex;
	int val;
}lex_s;

FILE* fp;

char token[128];
int tokenval;

int lex; // 当前token
int lineno; // 当前行号

int fatal_error; // 是否发生了严重的语法错误

// 回填使用的数据结构和函数
struct s_list_item{
	int quad;
	struct s_list_item * next;
};
typedef struct s_list_item list_item;


// 符号的属性
typedef struct{
	int addr;
	int offset;
	int width;

	int type;

	int quad;

	int value;
	int value_type; // ADDR or IMM

	list_item * true_list;
	list_item * false_list;
	list_item * next_list;
} attribute ;

// 栈中的一项
typedef struct{
	int state;
	attribute attr;
}item;


void lalr_parse();
void parse();
int lexan();
void error_handle(char *);

//
//typedef struct {
//	char name[32];
//	void (*f)(item*); // 处理该库函数调用的函数指针
//}s_lib_func;
//
//s_lib_func lib_func[] = {
//		{"print", lib_print},
//};

#endif /* GLOBAL_H_ */
