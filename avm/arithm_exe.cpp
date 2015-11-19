#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include "avm.h"
/*
arithmetic_func_t arithmeticFuncs[] = {
	add_op,
	sub_op,
	mul_op,
	div_op,
	mod_op
	
};
*/
//extern 

void execute_arithmetic(instruction * instr1) {

	avm_memcell* arg1 = new avm_memcell;
	avm_memcell* arg2 = new avm_memcell;
	avm_memcell* result = new avm_memcell;

	if(regdebug)cout << " EIMAI STON arithmetic"<< endl;
    
    
      

	arg1 = avm_translate_operand(&instr1->arg1, &ax);
	
	arg2 =avm_translate_operand(&instr1->arg2, &bx);
	
	result = avm_translate_operand(&instr1->result,(avm_memcell*)0);
	    //  

	//result = new avm_memcell;
	
	//cout << "cxTYPE:" << retval.type << endl;

	//cout << result->type << " Edw des to type moy "<<result->data.intval<<endl;
	//cout << arg2->data.intval << " Edw des to aval moy "<<endl;
	//cout << arg1->data.intval << " Edw des to aval moy "<<endl;
	if(regdebug)cout << "|||Arg1 type "<<arg1->type << " Arg2 type "<<arg2->type<<" Result type"<<result->type<<endl;
	//cout << "|||Arg1 val "<<arg1->data.realval << " Arg2 val "<<arg2->data.realval<<" Result val"<<result->data.realval<<endl;
	if(debug)cout << "|||Arg1 val "<<arg1->data.intval << " Arg2 val "<<arg2->data.intval<<" Result val"<<result->data.intval<<endl;
	
	double temp1;
	double temp2;
	/*int temp1 = arg1->data.intval;
	int temp2 = arg2->data.intval;
	double temp3 = arg1->data.realval;
	double temp4 = arg2->data.realval;*/
	//result->data.intval  = 0;
	//result->data.realval  = 0;
	//result->type= integer_vm;

	//cout << " Edw des ena kseftilikh"<< arg2->data.realval << arg2->data.realval << arg2->data.intval<<arg1->data.intval<<endl;
	
	if(arg1->type==real_vm){
		//temp1= new double;
		temp1 =  arg1->data.realval;

	}else if(arg1->type==integer_vm){
		temp1 = arg1->data.intval;
	}else{
		cout<<"Error: trying to pass NO numeric argument in arith."<<endl;
		executionFinished =1;
		return;
	}
	if(arg2->type==real_vm){
		temp2 =  arg2->data.realval;
		
	}else if(arg2->type==integer_vm){
		temp2 = arg2->data.intval;
	}else{
		cout<<"Error: trying to pass NO numeric argument in arith."<<endl;	
		executionFinished =1;
		return;
	}
	if(debug){cout <<"temp 2 "<<temp2<<" type "<<arg1->type<<" "<<arg1->data.intval<<" "<<arg1->data.realval<<endl;
		cout<<endl;
		cout <<"temp 1 "<<temp1<<" type "<<arg2->type<<" "<<arg2->data.intval<<" "<<arg2->data.realval<<endl;}

	if(debug){cout <<"temp 1 "<<temp1<<endl;
		cout <<"temp 2 "<<temp2<<endl;}
	if(/*((arg1->type==integer_vm)||(arg1->type==real_vm))&&((arg1->type==integer_vm)||(arg1->type==real_vm))*/false){
		// Edw prp na mpeis enas elegxos
		if(regdebug)cout<< " Bgainw apo edw ! "<<endl;
		executionFinished =1 ;

	}else{
		
		switch (instr1->opcode){
			case add_vm:	{if(regdebug)cout <<"Add vm detected" <<endl;
							if((arg1->type==1)||(arg2->type==1)){ result->type= real_vm;
								result->data.realval = temp1 + temp2;

							}else{
								result->type= integer_vm;
								result->data.intval = temp1 + temp2;
							}
							 //cout << result->data.intval << " Edw des to bval moy "<<endl;
							//cout << arg2->data.intval << " Edw des to bval moy "<<endl;
							//cout << arg1->data.intval << " Edw des to bval moy "<<endl;
							 break;
							}
			case sub_vm:	{if(regdebug)cout <<"Sub vm detected" <<endl;
							if((arg1->type==1)||(arg2->type==1)){ 
								result->type= real_vm;
								result->data.realval = temp1 - temp2;

							}else{
								result->type= integer_vm;
								result->data.intval = temp1 - temp2;
							}
							 break;}
			case mul_vm:	{if(regdebug)cout <<"Mul vm detected" <<endl;
							if((arg1->type==1)||(arg2->type==1)){ 
								result->type= real_vm;
								result->data.realval = (temp1 * temp2);

							}else{
								result->type= integer_vm;
								result->data.intval = temp1 * temp2;
							}
							break;}
			case divide_vm:	{if(regdebug)cout <<"Divide vm detected" <<endl;
							if(temp2==0){
									cout<<"Error trying to divide by 0!";
								executionFinished =1 ;
							break;}
							result->type= real_vm;
							result->data.realval = temp1 / temp2;

							
								break;}
			case mod_vm:	{if(regdebug)cout <<"mod vm detected" <<endl;
							if(temp2==0){
								cout<<"Error trying to mod by 0!";
								executionFinished =1 ;
							break;
							}
							result->type = integer_vm;
							if((arg1->type==1)||(arg2->type==1)){
								result->data.intval = fmod(temp1,temp2);
							}else{
							
								result->data.intval = int(temp1)%int(temp2);
							}
							
							 break;	}
		//avm_memclear(result);
		//avm_assign(&stack[top], &cx);
		
		//if((arg1->type==1)||(arg2->type==1)) result->type= real_vm;
		//else result->type= integer_vm;

//		result->type= integer_vm;
		}
		/*cout << "To result  int val einai : " << result->data.intval<<endl;
		cout << "To result  real val einai : " << result->data.realval<<endl;
	*/}
}


void execute_add(instruction* instr1){
	if(regdebug)cout << "Eimai mesa stn add "<<endl;
	execute_arithmetic(instr1);

}
void execute_sub(instruction* instr1){
	execute_arithmetic(instr1);	

}
void execute_mul(instruction* instr1){
	execute_arithmetic(instr1);

}
void execute_div(instruction* instr1){
	execute_arithmetic(instr1);

}
void execute_mod(instruction* instr1){
	execute_arithmetic(instr1);

}
