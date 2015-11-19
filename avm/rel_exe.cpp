#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include "avm.h"

bool double_equals(double a, double b, double epsilon = 0.001)
{
    return std::abs(a - b) < epsilon;
}

unsigned char jle_op (double  x, double  y) {return (unsigned char)(x<=y)?1:0;}
unsigned char jge_op (double  x, double  y) {return (unsigned char)(x>=y)?1:0;}
unsigned char jlt_op (double  x, double  y) {return (unsigned char)(x<y)?1:0;}
unsigned char jgt_op (double  x, double  y) {return (unsigned char)(x>y)?1:0;}


bool drako= true;
cmp_func comparisonFuncs[] = {
	jle_op,
	jge_op,
	jlt_op,
	jgt_op
};

// strdup(buff.c_str())
unsigned char jeq_op (double  x, double  y) {return (unsigned char)(double_equals(x,y,0.0001))?1:0;}
unsigned char jne_op (double  x, double  y) { return (unsigned char)(!double_equals(x,y,0.0001))?1:0;}

eq_func equalityFuncs[] = {
	jeq_op,
	jne_op
};


unsigned char integerbool(avm_memcell* m){			return (unsigned char)(m->data.intval != 0)?1:0;}
unsigned char realbool(avm_memcell* m){				return (unsigned char)(m->data.realval != 0)?1:0;}
unsigned char stringbool(avm_memcell* m){			return (unsigned char)((string(m->data.strVal)).compare(""))?1:0;}  
unsigned char unused(avm_memcell* m){				return m->data.boolVal;}
unsigned char tablebool(avm_memcell* m){			return 1; }
unsigned char userfuncbool(avm_memcell* m){ 		return 1; }
unsigned char libfuncbool(avm_memcell* m){			return 1;}
unsigned char nilbool(avm_memcell* m){				return 0;}
unsigned char undefbool(avm_memcell* m){ return 0;}

booltest_t boolFuncs[] = {
	integerbool,
	realbool,
	stringbool,
	unused,
	tablebool,
	userfuncbool,
	libfuncbool,
	nilbool,
	undefbool,
};


unsigned char booltest(avm_memcell* m){	return (*boolFuncs[m->type])(m);}
bool drake =false;

void execute_relational(instruction * instr1){
		if(regdebug)cout<<"relational "<<instr1->opcode<<endl;
		avm_memcell* lv  = new avm_memcell;	//avm_translate_operand(&instr1->result,(avm_memcell*)0);
		avm_memcell* rv1 = 	avm_translate_operand(&instr1->arg1, &ax);
		avm_memcell* rv2 = 	avm_translate_operand(&instr1->arg2, &bx);
		if(regdebug)cout<<" rv1 :"<<rv1->type<<" "<<rv1->data.intval<<endl;
		if(regdebug)cout<<" rv2 :"<<rv2->type<<" "<<rv2->data.intval<<endl;
		if(regdebug)cout<<" ######################## "<<endl;
		lv->type=bool_vm;
		if( rv1->type == rv2->type ){
			switch(rv1->type){
				case integer_vm: 	{
									lv->data.boolVal=(*comparisonFuncs[instr1->opcode-12])(rv1->data.intval,rv2->data.intval); 
									if(drake)cout<<"exw integers1"<<endl;
									break;
								}
				case real_vm:		{
									lv->data.boolVal=(*comparisonFuncs[instr1->opcode-12])(rv1->data.realval,rv2->data.realval); 
									if(drake)cout<<"exw real1"<<endl;
									break;
								}
				case bool_vm:		//lv->data.boolVal=(*comparisonFuncs[instr1->opcode-12])((double)rv1->data.boolVal,(double)rv2->data.boolVal);
									//break;
				case string_vm: //error	
				case table_vm:	
				case userfunc_vm: //!!
				case libfunc_vm: //!!
				case nil_vm: 
				case undef_vm:
				default: {cout<<"  unsupported greater or less 1"<<endl;assert(0);}
				//need error 
			}
			if (lv->data.boolVal) pc=instr1->result.val;
			if(regdebug)cout<<" new pc : "<<pc<<endl;
			return;
		}
		else {

			if((rv1->type <2)&&(rv2->type <2)){
				if(!rv1->type) rv1->data.realval = (double)rv1->data.intval;
				if(!rv2->type) rv2->data.realval = (double)rv2->data.intval;
				lv->data.boolVal=(*comparisonFuncs[instr1->opcode-12])(rv1->data.realval,rv2->data.realval);
				if (lv->data.boolVal) pc=instr1->result.val;
				if(regdebug)cout<<" new pc : "<<pc<<endl;

				return;
			}
			cout<<"  unsupported greater or less 2"<<rv1->type<<" "<<rv2->type<<endl;
			assert(0);
			return;
		}
}

void execute_equality(instruction * instr1){
		//if(regdebug)
		if(drake)	cout<<"relational "<<instr1->opcode<<"  "<<pc<<endl;
		avm_memcell* lv  = new avm_memcell;	//avm_translate_operand(&instr1->result,(avm_memcell*)0);
		avm_memcell* rv1 = 	avm_translate_operand(&instr1->arg1, &ax);
		avm_memcell* rv2 = 	avm_translate_operand(&instr1->arg2, &bx);
		if(drake)cout<<" rv1 :"<<rv1->type<<" "<<rv1->data.intval<<endl;
		if(drake)cout<<" rv2 :"<<rv2->type<<" "<<rv2->data.intval<<endl;
		if(regdebug)cout<<" ######################## "<<endl;
		lv->type=bool_vm;
		unsigned int jump;

		/*
case integer_vm: 	{
									lv->data.boolVal=(*comparisonFuncs[instr1->opcode-12])(rv1->data.intval,rv2->data.intval); 
									if(drake)cout<<"exw integers"<<endl;
									break;
								}
				case real_vm:		{
									lv->data.boolVal=(*comparisonFuncs[instr1->opcode-12])(rv1->data.realval,rv2->data.realval); 
									if(drake)cout<<"exw real"<<endl;
									break;
								}
		*/
		if( rv1->type == rv2->type ){
			switch(rv1->type){
				case integer_vm: 	{
									lv->data.boolVal=(*equalityFuncs[instr1->opcode-10])(rv1->data.intval,rv2->data.intval);  
									if(drake)cout<<"exw integers"<<endl;
									break;
					
									}
				case real_vm:		
									{lv->data.boolVal=(*equalityFuncs[instr1->opcode-10])(rv1->data.realval,rv2->data.realval);  
									
									//if(drake)
										if(debug)cout<<"exw real "<<rv1->data.realval<<" "<< rv2->data.realval<<" "<<(unsigned int)lv->data.boolVal<<endl;
										break;

									}				
				case string_vm: {	jump=(string(rv1->data.strVal)).compare(rv2->data.strVal);//0 equal number unequal 
									//cout<<"jump="<<jump<<" gia "<<strdup(rv1->data.strVal)<<" "<<strdup(rv2->data.strVal)<<endl;
									if ((instr1->opcode-10)==1) lv->data.boolVal = (unsigned char)(jump != 0)?1:0;
									else lv->data.boolVal = (unsigned char)(jump == 0)?1:0;
									break;
								}

				case nil_vm:  	{if((instr1->opcode-10)==0) lv->data.boolVal= 1;
									else lv->data.boolVal= 0;
								
								break;}
				case bool_vm:		lv->data.boolVal=(*equalityFuncs[instr1->opcode-10])((double)rv1->data.boolVal,(double)rv2->data.boolVal);
									break;	
				/////////////////////TODO/////////////////////////
				case table_vm://
				case userfunc_vm: //!!
				case libfunc_vm: //!!			 
				case undef_vm:
				default: {cout<<"  unsupported greater or less 3"<<endl;assert(0);}
			}
			if (lv->data.boolVal) pc=instr1->result.val;
			if(regdebug)cout<<" new pc : "<<pc<<endl;
			return;
		}
	else if((rv1->type <2)&&(rv2->type <2)){
				if(!rv1->type) rv1->data.realval = (double)rv1->data.intval;
				if(!rv2->type) rv2->data.realval = (double)rv2->data.intval;
				lv->data.boolVal=(*equalityFuncs[instr1->opcode-10])(rv1->data.realval,rv2->data.realval);
				if (lv->data.boolVal) pc=instr1->result.val;
				if(regdebug)cout<<" new pc : "<<pc<<endl;

				return;
			}

		else{

			if((rv1->type==8)||(rv2->type==8)) {
				executionFinished =1;
				cout<<"Trying to compare with undefined content."<<endl;
				return;
			}
			if((rv1->type==7)||(rv2->type==7)) {
				//executionFinished =1;
				//cout<<"Trying to compare with undefined content."<<endl;
				lv->data.boolVal= 0;
				return;
			}
			//sigkrisi me nil
			//sigkrisi me boolean
			//
			lv->data.boolVal =(*equalityFuncs[instr1->opcode-10])((double)booltest(rv1),(double)booltest(rv2));
			if (lv->data.boolVal) pc=instr1->result.val;
			if(regdebug)cout<<" new pc : "<<pc<<endl;
			return;
		}
}