/*
 * tanslate.c
 *
 *  Created on: 2013-4-26
 *      Author: y
 */

#include "global.h"
#include "translate.h"

// 无参数
void call_func(item *it) {
	sprintf(code.data[code.quad++], "call FUNC_%d\n",
			symtable[s->d[s->t - 2].attr.value].offset);
}
void call_func_param(item *it) {
	int i;
	for (i = 0; i <= param_queue.tail; i++) {
		sprintf(code.data[code.quad++], "param %d\n", param_queue.value[i]);
	}
	sprintf(code.data[code.quad++], "call FUNC_%d\n",
			symtable[s->d[s->t - 3].attr.value].offset);
}
void param_item_id(item *it) {
	it->attr.value = symtable[s->d[s->t].attr.value].offset;
	it->attr.value_type = VALUE_STACK_ADDR;
}
void param_item_num(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = VALUE_IMM;
}
void param_item_array(item *it) {
}
void param_list(item *it) {
	param_queue.tail++; // 进队
	param_queue.value[param_queue.tail] = s->d[s->t - 1].attr.value;
	param_queue.value_type[param_queue.tail] = s->d[s->t - 1].attr.value_type;
}
// 第一个参数
void param_list_item(item *it) {
	param_queue.tail = 0; // 清空队列
	param_queue.value[0] = s->d[s->t].attr.value;
	param_queue.value_type[0] = s->d[s->t].attr.value_type;
}
void smt_if_while(item *it) {
	it->attr.next_list = s->d[s->t].attr.next_list;
}

void smt_list(item *it) {
	back_patch(s->d[s->t - 2].attr.next_list, s->d[s->t - 1].attr.quad);
	it->attr.next_list = s->d[s->t].attr.next_list;
}
void smt_list_smt(item *it) {
	it->attr.next_list = s->d[s->t].attr.next_list;
}
void M_if_smt(item *it) {
	it->attr.next_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp LABEL_%%d\n");
}
void if_smt(item *it) {
	back_patch(s->d[s->t - 6].attr.true_list, s->d[s->t - 3].attr.quad);
	it->attr.next_list = merge(s->d[s->t - 6].attr.false_list,
			s->d[s->t - 2].attr.next_list);
}
void if_smt_else(item *it) {
	list_item * t;
	back_patch(s->d[s->t - 13].attr.true_list, s->d[s->t - 10].attr.quad);
	back_patch(s->d[s->t - 13].attr.false_list, s->d[s->t - 3].attr.quad);

	t = merge(s->d[s->t - 6].attr.next_list, s->d[s->t - 2].attr.next_list);
	it->attr.next_list = merge(s->d[s->t - 9].attr.next_list, t);
}
void while_smt(item *it) {
	back_patch(s->d[s->t - 6].attr.true_list, s->d[s->t - 3].attr.quad);
	back_patch(s->d[s->t - 2].attr.next_list, s->d[s->t - 7].attr.quad);
	it->attr.next_list = s->d[s->t - 6].attr.false_list;
	sprintf(code.data[code.quad++], "jmp LABEL_%d\n", s->d[s->t - 7].attr.quad);
	code.label[s->d[s->t - 7].attr.quad - 1] = LABEL;
}

void relop_EQ(item *it) {
	it->attr.value = EQ;
}
void relop_NE(item *it) {
	it->attr.value = NE;
}
void relop_LE(item *it) {
	it->attr.value = LE;
}
void relop_GE(item *it) {
	it->attr.value = GE;
}
void relop_LT(item *it) {
	it->attr.value = LT;
}
void relop_GT(item *it) {
	it->attr.value = GT;
}
void M_quad_E(item *it) {
	it->attr.quad = code.quad + 1;
}
void M_bool_exp_E(item *it) {
	it->attr.quad = code.quad + 1;
}
void bool_exp_or(item *it) {
	back_patch(s->d[s->t - 3].attr.false_list, s->d[s->t - 1].attr.quad);
	it->attr.true_list = merge(s->d[s->t - 3].attr.true_list,
			s->d[s->t].attr.true_list);
	it->attr.false_list = s->d[s->t].attr.false_list;
}
void bool_exp_and(item *it) {
	back_patch(s->d[s->t - 3].attr.true_list, s->d[s->t - 1].attr.quad);
	it->attr.false_list = merge(s->d[s->t - 3].attr.false_list,
			s->d[s->t].attr.false_list);
	it->attr.true_list = s->d[s->t].attr.true_list;
}
void bool_exp_not(item *it) {
	it->attr.false_list = s->d[s->t].attr.true_list;
	it->attr.true_list = s->d[s->t].attr.false_list;
}
void bool_exp_bracket(item *it) { // 括号
	it->attr.false_list = s->d[s->t - 1].attr.false_list;
	it->attr.true_list = s->d[s->t - 1].attr.true_list;
}
void bool_exp_relop(item *it) {
	char op[6][3] = { ">", "<", ">=", "<=", "<>", "==" };
	it->attr.true_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "if [%d] %s [%d] jmp LABEL_%%d\n",
			s->d[s->t - 2].attr.value, op[s->d[s->t - 1].attr.value - GT],
			s->d[s->t].attr.value);

	it->attr.false_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp LABEL_%%d\n");
}
void bool_exp_true(item *it) {
	it->attr.true_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp LABEL_%%d\n");
}
void bool_exp_false(item *it) {
	it->attr.false_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp LABEL_%%d\n");
}
void bool_exp_item(item *it) {
	it->attr.false_list = s->d[s->t].attr.false_list;
	it->attr.true_list = s->d[s->t].attr.true_list;
}

void exp_var_exp_item(item *it) {

	switch (s->d[s->t].attr.value_type) {
	case VALUE_STACK_ADDR:
		sprintf(code.data[code.quad++], "movl $%d, %%edi\n",
				s->d[s->t].attr.value);
		sprintf(code.data[code.quad++], "movl temp(,%%edi,4), %%eax\n");
		sprintf(code.data[code.quad++], "movl %%eax, %d(%%ebp)\n",
				s->d[s->t].attr.value,
				symtable[s->d[s->t - 2].attr.value].offset);
		break;
	case VALUE_TEMP_ADDR:
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n",
				s->d[s->t].attr.value);
		sprintf(code.data[code.quad++], "movl %%eax, %d(%%ebp)\n",
				s->d[s->t].attr.value,
				symtable[s->d[s->t - 2].attr.value].offset);
		break;
	case VALUE_IMM:
		sprintf(code.data[code.quad++], "movl $%d, %d(%%ebp)\n",
				s->d[s->t].attr.value,
				symtable[s->d[s->t - 2].attr.value].offset);
		break;
	default:
		break;
	}
}
void var_id(item *it) {
	it->attr.value = s->d[s->t].attr.value;
}

void mulop_mul(item *i) {
	i->attr.value = MUL;
}
void mulop_div(item *i) {
	i->attr.value = DIV;
}
void addop_plus(item *i) {
	i->attr.value = PLUS;
}

void addop_minus(item *i) {
	i->attr.value = MINUS;
}
//
//void addop_(item *i){
//	i->attr.value = DIV;
//}

void term_factor(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = s->d[s->t].attr.value_type;
	;
}
void exp_item_term(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = s->d[s->t].attr.value_type;
	;
}
void addop_mulop(item *it) {
	attribute *r, *op1, *op2, *op;
	char op2_e[16] = { '\0' }; // op2在汇编中的形式
	r = &it->attr;
	op = &s->d[s->t - 1].attr;
	op1 = &s->d[s->t - 2].attr;
	op2 = &s->d[s->t].attr;

	r->value = new_temp();
	r->value_type = VALUE_STACK_ADDR;
	// op1类型
	switch (op1->value_type) {
	case VALUE_STACK_ADDR:
		// 假定所有變量都在棧上
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n", op1->value);
		break;
	case VALUE_IMM:
		sprintf(code.data[code.quad++], "movl $%d, %%eax\n", op1->value);
		break;
	default:
		break;
	}
	// op2类型
	switch (op2->value_type) {
	case VALUE_STACK_ADDR:
//		// 假定所有變量都在棧上
		sprintf(op2_e, "%d(%%ebp)", op2->value);
		break;
	case VALUE_IMM:
		sprintf(op2_e, "$%d", op2->value);
		break;
	default:
		break;
	}
	switch (op->value) {
	case PLUS:
		sprintf(code.data[code.quad++], "addl %s, %%eax\n", op2_e);
		break;
	case MINUS:
		sprintf(code.data[code.quad++], "subl %s, %%eax\n", op2_e);
		break;
	case MUL:
		sprintf(code.data[code.quad++], "mull %s\n", op2_e);
		break;
	case DIV:
		sprintf(code.data[code.quad++], "divl %s\n", op2_e);
		break;
	default:
		break;
	}
	sprintf(code.data[code.quad++], "movl %%eax, %d(ebp)\n", r->value);
}
void exp_item_addop(item *it) {
	addop_mulop(it);
}
void term_term_mulop_factor(item *it) {
	addop_mulop(it);
}
void factor_exp_item(item *it) {
	it->attr.value = s->d[s->t - 1].attr.value;
	it->attr.value_type = VALUE_STACK_ADDR;
}
void factor_id(item *it) {
	it->attr.value = symtable[s->d[s->t].attr.value].offset;
	it->attr.value_type = VALUE_STACK_ADDR;
}
void factor_num(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = VALUE_IMM;
}

void M_func_content_declare(item * it) {
}

void type_int(item * it) {
	it->attr.type = INT;
	it->attr.width = 4;
}
void type_char(item * it) {
	it->attr.type = CHAR;
	it->attr.width = 1;
}
/*
 s->d[s->t].attr.
 */
void t_type_type(item * it) {
	it->attr.type = s->d[s->t].attr.type;
	it->attr.width = s->d[s->t].attr.width;
}
void declare_id(item * it) {
	s->d[s->t].attr.offset = offset;
	update_offset(it->attr.value, offset); // 更新偏移地址
//	printf("it.val:%d, addr:%d\n", it->attr.value, offset);
	offset += s->d[s->t - 1].attr.width;
}

void M_init() {
//	offset = 0;
}

void test(item * item) {
	printf("hello, state is %d\n", item->state);
}

// 无操作的空函数
void null_f(item * item) {
	//printf("hello, state is %d\n", item->state);

	return;
}

