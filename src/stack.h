/*
 * stack.h
 *
 *  Created on: 2013-4-7
 *      Author: y
 */

#ifndef STACK_H_
#define STACK_H_

#define STACK_SIZE	1024


typedef struct stack{
	int top;
	STACK_DATA_TYPE data[STACK_SIZE];
}STACK;


STACK * init_stack();
bool push(STACK_DATA_TYPE val, STACK * s);
STACK_DATA_TYPE pop(STACK * s);
void pop_num(int num, STACK * s);
STACK_DATA_TYPE get_top(int offset, STACK * s);
bool is_full(STACK * s);
bool is_empty(STACK * s);


#endif /* STACK_H_ */
