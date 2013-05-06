/* production.h
 *  Created on: 2013-4-8
 *      Author: y
 */



#ifndef PRODUCTION_H_
#define PRODUCTION_H_
#include "global.h"
#include "translate.h"
#include "stack.h"


#define PRODUCTION_LEFT_SIZE 32
#define PRODUCTION_RIGHT_SIZE 128



#define E	777 // ERROR
#define N	999
#define AC	0



typedef struct{
	int left;
	char right[PRODUCTION_RIGHT_SIZE];
	int right_count;
	void (*f)(item *); // 翻译函数de指针
}PRODUCTION;









char * production_left[] = {
		"_start",
		"start",
		"main_func",
		"func",
		"func_content",
		"func_list",
		"ret_smt",
		"param_list",
		"param_item",
		"d_param_list",
		"d_param_item",
		"t_type",
		"ret_type",
		"type",
		"array",
		"d_array",
		"d_array_list",
		"d_array_item",
		"declare",
		"exp",
		"exp_item",
		"term",
		"factor",
		"addop",
		"mulop",
		"relop",
		"bolop",
		"ch",
		"smt_list",
		"smt",
		"call_func",
		"loop_list",
		"bool_exp",
		"bool_exp_item",
		"if_smt",
		"if_content",
		"var",
		"while_smt",
		"M_t_type",
		"M_func_content",
		"M_func_content_declare",
		"M_bool_exp",
		"M_quad",
		"M_if_smt",
};


PRODUCTION production[] = {
		{0,"_start->start",1,null_f},
		{0,"_start->start",1,null_f},
		{1,"start->main_func func_list",2,null_f},
		{1,"start->main_func",1,null_f},
		{2,"main_func->void main ( param_list ) { func_content } ",8,null_f},
		{9,"d_param_list->d_param_item d_param_list",2,d_param_list},
		{9,"d_param_list->d_param_item",1,d_param_list_item},
		{9,"d_param_list->, d_param_list",2,null_f},
		{10,"d_param_item->id [ ]",3,d_param_item_array},
		{10,"d_param_item->id",1,d_param_item_id},
		{10,"d_param_item->num",1,d_param_item_num},
		{7,"param_list->param_item param_list",2,param_list},
		{7,"param_list->param_item",1,param_list_item},
		{7,"param_list->, param_list",2,null_f},
		{8,"param_item->t_type M_t_type id [ ]",5,param_item_array},
		{8,"param_item->t_type M_t_type id",3,param_item_id},
		{38,"M_t_type->E",0,null_f},
		{18,"declare->declare semi t_type id",4,declare_id},
		{18,"declare->t_type id",2,declare_id},
		{18,"declare->d_array",1,null_f},
		{15,"d_array->declare = { d_array_list }",5,null_f},
		{16,"d_array_list->d_array_list,d_array_item",3,null_f},
		{16,"d_array_list->d_array_item",1,null_f},
		{17,"d_array_item->num",1,null_f},
		{17,"d_array_item->ch",1,null_f},
		{11,"t_type->array",1,null_f},
		{11,"t_type->type",1,t_type_type},
		{13,"type->float",1,null_f},
		{13,"type->bool",1,null_f},
		{13,"type->char",1,type_char},
		{13,"type->int",1,type_int},
		{14,"array->type[num]",4,null_f},
		{3,"func->ret_typeid (){func_content}",7,null_f},
		{3,"func->ret_type id (param_list){func_content}",8,null_f},
		{4,"func_content->M_func_content_declare declare semi smt_list semi",5,null_f},
		{4,"func_content->smt_listsemi",2,null_f},
		{39,"M_func_content->E",0,null_f},
		{40,"M_func_content_declare->E",0,M_func_content_declare},
		{12,"ret_type->type",1,null_f},
		{12,"ret_type->void",1,null_f},
		{6,"ret_smt->returnnum",2,null_f},
		{6,"ret_smt->returnid",2,null_f},
		{6,"ret_smt->return",1,null_f},
		{5,"func_list->func func_list",2,null_f},
		{5,"func_list->func",1,null_f},
		{23,"addop->+",1,addop_plus},
		{23,"addop->-",1,addop_minus},
		{24,"mulop->/",1,mulop_div},
		{24,"mulop->*",1,mulop_mul},
		{25,"relop->==",1,relop_EQ},
		{25,"relop-><>",1,relop_NE},
		{25,"relop-><=",1,relop_LE},
		{25,"relop->>=",1,relop_GE},
		{25,"relop-><",1,relop_LT},
		{25,"relop->>",1,relop_GT},
		{26,"bolop->and",1,null_f},
		{26,"bolop->or",1,null_f},
		{26,"bolop->not",1,null_f},
		{27,"ch->'char_set'",3,null_f},
		{30,"call_func->id()",3,call_func},
		{30,"call_func->id(d_param_list)",4,call_func_param},
		{19,"exp->var=exp_item",3,exp_var_exp_item},
		{19,"exp->var=call_func",3,null_f},
		{19,"exp->call_func",1,null_f},
		{36,"var->id[exp_item]",4,null_f},
		{36,"var->id",1,var_id},
		{20,"exp_item->exp_item addop term",3,exp_item_addop},
		{20,"exp_item->term",1,exp_item_term},
		{21,"term->term mulop factor",3,term_term_mulop_factor},
		{21,"term->factor",1,term_factor},
		{22,"factor->num",1,factor_num},
		{22,"factor->ch",1,null_f},
		{22,"factor->id",1,factor_id},
		{22,"factor->id[exp_item]",4,null_f},
		{22,"factor->(exp_item)",3,factor_exp_item},
		{28,"smt_list->smt_list semi smt",3,smt_list},
		{28,"smt_list->smt",1,smt_list_smt},
		{42,"M_quad->E",0,M_quad_E},
		{29,"smt->exp",1,null_f},
		{29,"smt->ret_smt",1,null_f},
		{29,"smt->break",1,null_f},
		{29,"smt->continue",1,null_f},
		{29,"smt->while_smt",1,smt_if_while},
		{29,"smt->if_smt",1,smt_if_while},
		{31,"loop_list->loop_list semi M_quad smt",4,smt_list},
		{31,"loop_list->smt",1,smt_list_smt},
		{37,"while_smt->while(M_quad bool_exp){M_quad loop_list semi}",10,while_smt},
		{34,"if_smt->if(bool_exp) { M_quad loop_list semi}M_if_smt else { M_quad loop_list semi }",16,if_smt_else},
		{34,"if_smt->if ( bool_exp ) { M_quad loop_list semi }",9,if_smt},
		{43,"M_if_smt->E",0,M_if_smt},
		{32,"bool_exp->bool_exp_item and M_bool_exp bool_exp",4,bool_exp_and},
		{32,"bool_exp->bool_exp_item or M_bool_exp bool_exp",4,bool_exp_or},
		{32,"bool_exp->not bool_exp_item",2,bool_exp_not},
		{32,"bool_exp->bool_exp_item",1,bool_exp_item},
		{32,"bool_exp->(bool_exp)",3,bool_exp_bracket},
		{41,"M_bool_exp->E",0,M_bool_exp_E},
		{33,"bool_exp_item->exp_item relop exp_item",3,bool_exp_relop},
		{33,"bool_exp_item->true",1,bool_exp_true},
		{33,"bool_exp_item->false",1,bool_exp_false},
};
int action[][42] = {
		{E,-3,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{AC,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{3,-8,E,E,E,E,E,E,E,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,-13,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{44,-8,E,E,E,E,E,E,E,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{2,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-15,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,38,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,30,E,E,E,E,E,30,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,29,E,E,E,E,E,29,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,28,E,E,E,E,E,28,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,27,E,E,E,E,E,27,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-16,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{43,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-17,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,-23,E,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,-25,E,E,-23,E,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,-26,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,12,E,E,-23,E,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,16,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,26,E,E,E,E,E,-29,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,25,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,-23,E,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,-31,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,-32,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,-33,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,11,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-34,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-35,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,13,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,-36,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-47,37,37,37,37,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,E,E,E,E,-47,37,37,37,37,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,15,E,E,15,E,15,15,15,15,E,-54,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-55,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-47,37,37,37,37,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,E,E,-57,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,79,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,78,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-58,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,76,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,63,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,83,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-59,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,82,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-63,E,E,E,E,E,E,E,E,E,E,-64,E,E,E,E,E,E,E,E,E,65,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-65,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-66,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-67,E,E,E,E,E,E,E,-68,E,E,42,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,80,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,-69,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-70,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,31,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,-71,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{32,32,E,E,E,E,E,E,E,32,32,32,32,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,35,E,-47,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,-78,E,E,E,E,-79,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-82,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,19,E,E,E,E,19,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-83,E,E,E,E,-84,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,-87,E,E,-88,-89,E,E,E,E,E,E,E,-90,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-78,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-96,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-97,-98,-99,E,E,E},
		{E,E,E,77,E,E,E,E,77,E,E,E,E,E,E,E,77,77,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,77,77,77,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,41,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,40,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{4,4,E,E,E,E,E,E,E,4,4,4,4,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,14,E,E,14,E,14,14,14,14,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{33,33,E,E,E,E,E,E,E,33,33,33,33,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,75,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,61,-102,-103,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,67,E,E,E,E,E,E,E,E,E,E,67,E,E,E,67,67,67,-105,-106,E,E,E,E,67,67,67,67,67,67,67,67,E,E,E,E,E,E},
		{E,E,E,E,69,E,E,E,E,E,E,E,E,E,E,69,E,E,E,69,69,69,69,69,E,E,E,E,69,69,69,69,69,69,69,69,E,E,E,E,E,E},
		{E,E,E,E,71,E,E,E,E,E,E,E,E,E,E,71,E,E,E,71,71,71,71,71,E,E,E,E,71,71,71,71,71,71,71,71,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,62,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-78,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-63,E,E,E,E,E,E,E,E,E,E,-108,E,E,E,E,72,72,72,72,72,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,70,E,E,E,E,E,E,E,E,E,E,70,E,E,E,70,70,70,70,70,E,E,E,E,70,70,70,70,70,70,70,70,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-109,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,18,E,E,E,E,18,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-47,-9,-10,-11,-12,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,E,-112,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,-113,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,6,E,E,-88,-89,E,E,E,E,E,E,E,-90,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,59,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,-88,-89,E,E,E,E,E,E,E,-90,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,9,E,E,9,9,E,E,E,E,E,-116,E,9,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,10,E,E,10,10,E,E,E,E,E,E,E,10,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-117,E,E,E,E,-102,-103,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,72,E,E,E,E,E,E,E,E,E,-108,72,E,E,E,72,72,72,72,72,E,E,E,E,72,72,72,72,72,72,72,72,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-102,-103,E,E,E,E,E,E,-119,-120,-121,-122,-123,-124,E,E,E,E,E,E,E,E},
		{E,E,E,E,-125,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,93,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-126,-127,E,E,E,E,E,E},
		{E,E,E,-96,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-97,-98,-99,E,E,E},
		{E,E,E,-78,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-98,-99,E,E,E},
		{E,E,E,E,97,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,97,97,E,E,E,E,E,E},
		{E,E,E,E,98,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,98,98,E,E,E,E,E,E},
		{E,E,E,-96,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-97,-98,-99,E,E,E},
		{E,E,E,-78,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,45,E,E,E,E,45,E,E,E,E,E,E,E,45,45,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,46,E,E,E,E,46,E,E,E,E,E,E,E,46,46,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-78,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,48,E,E,E,E,48,E,E,E,E,E,E,E,48,48,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,47,E,E,E,E,47,E,E,E,E,E,E,E,47,47,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,-134,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-102,-103,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-78,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-136,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-137,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-138,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-142,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,60,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,5,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,7,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-143,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,64,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,-78,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,54,E,E,E,E,54,E,E,E,E,E,E,E,54,54,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,53,E,E,E,E,53,E,E,E,E,E,E,E,53,53,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,52,E,E,E,E,52,E,E,E,E,E,E,E,52,52,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,51,E,E,E,E,51,E,E,E,E,E,E,E,51,51,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,50,E,E,E,E,50,E,E,E,E,E,E,E,50,50,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,49,E,E,E,E,49,E,E,E,E,E,E,E,49,49,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,-145,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,95,E,E,E,E,95,E,E,E,E,E,E,E,95,95,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,95,95,95,E,E,E},
		{E,E,E,95,E,E,E,E,95,E,E,E,E,E,E,E,95,95,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,95,95,95,E,E,E},
		{E,E,E,E,-134,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-102,-103,E,E,E,E,E,E,-119,-120,-121,-122,-123,-124,E,E,E,E,E,E,E,E},
		{E,E,E,E,-148,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,92,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,-149,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,66,E,E,E,E,E,E,E,E,E,E,66,E,E,E,66,66,66,-105,-106,E,E,E,E,66,66,66,66,66,66,66,66,E,E,E,E,E,E},
		{E,E,E,E,68,E,E,E,E,E,E,E,E,E,E,68,E,E,E,68,68,68,68,68,E,E,E,E,68,68,68,68,68,68,68,68,E,E,E,E,E,E},
		{E,E,E,E,74,E,E,E,E,E,E,E,E,E,E,74,E,E,E,74,74,74,74,74,E,E,E,E,74,74,74,74,74,74,74,74,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-150,E,E,E,E,-102,-103,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,58,E,58,58,E,E,E,E,E,E,E,58,E,E,E,58,58,58,58,58,E,E,E,E,58,58,58,58,58,58,58,58,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,17,E,E,E,E,17,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,34,E,-47,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,E,E,-151,-152,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,22,22,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,24,24,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,23,23,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,8,E,E,8,8,E,E,E,E,E,E,E,8,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,96,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-102,-103,E,E,E,E,E,E,E,E,E,E,E,E,96,96,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,77,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,77,77,E,E,E,E,E,E,E,E,E,E,E,E,77,77,77},
		{E,E,E,-96,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-97,-98,-99,E,E,E},
		{E,E,E,-96,E,E,E,E,-92,E,E,E,E,E,E,E,-80,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-97,-98,-99,E,E,E},
		{E,E,E,E,94,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,-156,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,73,E,E,E,E,E,E,E,E,E,E,73,E,E,E,73,73,73,73,73,E,E,E,E,73,73,73,73,73,73,73,73,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,20,E,E,E,E,20,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-142,-81,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-47,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,90,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,91,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,77,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,77,77,E,E,E,E,E,E,E,E,E,E,E,E,77,77,77},
		{E,E,E,E,E,E,21,21,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,85,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-161,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-47,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,E,E,-164,E,77,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,77,77,E,E,E,E,E,E,E,E,E,E,E,E,77,77,77},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-165,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,-47,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,88,E,E,E,E,E,E,E,89,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,-168,E,77,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,77,77,E,E,E,E,E,E,E,E,E,E,E,E,77,77,77},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,84,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-169,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,86,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,-170,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,E,E,77,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,77,77,E,E,E,E,E,E,E,E,E,E,E,E,77,77,77},
		{E,E,E,E,E,E,E,E,-47,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-48,-49,E,E,E,E,E,E,E,E,E,E,E,E,-50,-51,-52},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,-173,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{E,E,E,E,E,E,-174,E,77,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,77,77,E,E,E,E,E,E,E,E,E,E,E,E,77,77,77},
		{E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,87,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
};

int go_to[][44] = {
		{N,1,2,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,4,E,5,E,E,E,E,E,E,6,7,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,4,E,14,E,E,E,E,E,E,6,7,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,18,19,E,E,20,E,21,22,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,24,19,E,E,20,E,21,22,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,27,19,E,E,20,E,21,22,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,28,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,30,19,E,E,20,E,21,22,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,37,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,40,41,42,E,E,E,43,E,44,45,E,E,46,E,E,E},
		{N,E,E,E,53,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,40,41,42,E,E,E,43,E,44,45,E,E,46,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,56,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,40,41,42,E,E,E,43,E,44,45,E,E,46,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,60,E,21,22,61,E,E,62,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,E,72,42,E,E,E,43,E,44,45,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,73,74,75,E,E,E,E,76,E,E,77,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,85,86,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,91,74,75,E,E,E,E,76,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,93,74,75,E,E,E,E,76,E,E,E,E,94,95,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,100,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,101,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,104,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,107,74,75,E,E,E,E,76,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,38,E,E,E,E,110,E,21,22,E,E,E,E,39,E,E,E,E,E,E,E,E,111,41,42,E,E,E,43,E,44,45,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,114,86,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,115,86,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,101,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,101,E,118,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,128,74,75,E,E,E,E,76,E,E,E,E,129,95,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,93,74,75,E,E,E,E,76,E,E,E,E,E,130,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,93,74,75,E,E,E,E,76,E,E,E,E,131,95,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,132,75,E,E,E,E,76,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,133,E,E,E,E,76,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,101,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,135,74,75,E,E,E,E,76,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,139,140,E,E,E,E,E,E,E,E,E,141,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,144,74,75,E,E,E,E,76,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,146,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,147,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,101,E,118,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,104,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,101,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,E,72,42,E,E,E,43,E,44,45,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,101,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,153,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,93,74,75,E,E,E,E,76,E,E,E,E,154,95,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,93,74,75,E,E,E,E,76,E,E,E,E,155,95,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,157,E,E,E,E,E,E,E,E,E,141,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,E,158,42,159,E,E,43,E,44,45,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,160,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,E,158,42,162,E,E,43,E,44,45,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,163,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,E,166,42,E,E,E,43,E,44,45,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,167},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,163,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,171,E},
		{N,E,E,E,E,E,38,E,E,E,E,E,E,E,E,E,E,E,E,39,E,E,E,E,E,E,E,E,E,158,42,172,E,E,43,E,44,45,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,163,E},
		{N,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E},
};

#endif /* PRODUCTION_H_ */
