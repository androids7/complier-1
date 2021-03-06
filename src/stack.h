/*
 * stack.h
 *
 *  Created on: 2013-4-7
 *      Author: y
 */

#ifndef STACK_H_
#define STACK_H_
#include "global.h"
#include "translate.h"

#define STACK_SIZE	1024



#define STACK_DATA_TYPE	item


typedef struct stack{
	int t;
	STACK_DATA_TYPE d[STACK_SIZE];
}STACK;

// 全局栈
STACK * s;

STACK * init_stack();
int push(STACK_DATA_TYPE val, STACK * s);
STACK_DATA_TYPE pop(STACK * s);
void pop_num(int num, STACK * s);
STACK_DATA_TYPE get_top(int offset, STACK * s);
int is_full(STACK * s);
int is_empty(STACK * s);


#endif /* STACK_H_ */
