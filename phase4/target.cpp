#include "hash.h"
#include "intermediate.h"
#include "target.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <sstream>
#include  <iomanip>




vector<inc_jump *> inc_jump_Vector;
//vector<vmarg *> VmargsTable;
//typedef struct Instruction instruction;1
extern vector<quad>		quadhead ;
extern unsigned int currQuad;
vector <instruction> instructions;

vector<int> consts_Int;
vector<string> consts_String;
vector<double> consts_Double;
vector<func_sym*> const_Functions;
vector<Symbol*> globalsyms;
//an einai dunaton omws
//stack<func_sym*> ;
unsigned int globalcounter=0;
stack<instruction*> prefunc ;


vector <string> lib_Functions;
stack <int> funcstack;

int currInstruction=0;
int processedQuad=0;
int currlib=0;
int pushlabel=0;

////////////////
typedef void (*generator_func_t)(quad*);
generator_func_t generators[] = {
	generate_ASSIGN ,
	generate_ADD ,
    generate_SUB ,
    generate_MUL ,
    generate_DIV ,
    generate_MOD ,
	generate_UMINUS ,
	generate_AND,
	generate_OR ,
	generate_NOT ,
	generate_IF_EQ ,
	generate_IF_NOTEQ ,	
	generate_IF_LESSEQ ,
	generate_IF_GREATEREQ ,
	generate_IF_LESS ,
	generate_IF_GREATER ,
	generate_CALL ,
	generate_PARAM ,
	generate_RETURN ,
	generate_GETRETVAL ,
	generate_FUNCSTART ,
	generate_FUNCEND ,
	generate_TABLECREATE ,
	generate_JUMP ,
    generate_TABLEGETELEM ,
    generate_TABLESETELEM ,
    generate_NOP
};

void generate_NOP(quad *q){

	instruction *t = new instruction;
	t->alphaline = q->line;
	t->line = q->taddress;
	t->opcode = nop_vm;
	emitVmarg (t);
};






//
vmarg* make_operand1 (expr *e){
	//assert(arg);
	vmarg * arg = new vmarg;
	//cout<<" EEEEEEEEEEEEEEE"<<e->sym->name<<endl;
	//cout<<" eimai vlakas"<<e->type<<endl;
	if(e==NULL){
			arg->val = -1;
			arg->type=nil_a;
			return arg;
		}
	switch (e->type){
		
		case var_e:
		case tableitem_e:
		case arithexpr_e:
		case boolexpr_e:
		case newtable_e:
		case assignexpr_e:{
		
			assert(e->sym);
			
			arg->val = e->sym->offset;
			
			switch (e->sym->space){
				case programvar: lookglobal(e->sym);arg->type = global_a; break;
				case functionlocal : arg->type = local_a; break;
				case formalarg: arg->type = formal_a; break;
				default: assert(0);
				
			}
			//return arg;
			break;
		}
		case constbool_e: {
		
			arg->val = too_bool(e->boolConst);
			arg->type = bool_a; 
			//return arg;
			break;
			
		}
		
		case conststring_e: {
		
			arg->val = consts_newstring(e->strConst);
			arg->type = string_a;
			//return arg;
			break;
		
		}
		
		case constint_e: {
			//cout<<"############## " << consts_newint(e->intConst)<<endl;
			arg->val = consts_newint(e->intConst);
			//cout<<"############## " <<e->intConst<<endl;

			arg->type = integer_a; 
			//return arg;
			break;
		}
		
		case constreal_e:{
			arg->val = consts_newdouble(e->numConst);
			arg->type = real_a; 
			//return arg;
			break;
		}
		case nil_e: {arg->type = nil_a ; return arg; break;}
		
		//Functions PAME 
		
		case programfunc_e : {
			assert(e->sym->type == FUNC);
			arg->type = userfunc_a;
			int i  =lookup(e->sym); 
			arg->val= i ;
			//int i  =
			//arg->val= lookup(e->sym); 
			//return arg;
			//why?
			//arg->val = userfuncs_newfunc(e->sym);		
			break;
		
		}
		
		case libraryfunc_e : {
			
			arg->type = libfunc_a;
			//arg->val = libfuncs_newused(e->sym->name);
			//cout<<" make_operand_kalaitzos internship"<<endl;
			// why?
			int val = libfuncs_newused(e->sym->name);
			arg->val = val;
			//cout<< arg-> type<<endl;
			//return arg;
			break;
		}
		
		default : cout <<"rimi adfsdf"<<endl;//assert(0); 
		
		//argtopass= arg;
		
		return arg;
	
	}
	
}


//

int nextInstructionLabel(void){
	return currInstruction;
}

int currProcessedQuad(void){
	return processedQuad;
}

vmarg * make_intoperand(int val){
	vmarg *temp = new vmarg;
	//temp->val = AddConstArrayElem(IntToConst(val));
	temp->val=consts_newint(val);
	temp->type = integer_a;
	return temp;

}
vmarg * make_doubleoperand(double val){
	
	vmarg *temp = new vmarg;
	temp->type = real_a;
	return temp;

}

	
vmarg *make_booloperand (vmarg* arg , unsigned val){
	vmarg *temp = new vmarg;
	temp->val=val;
	temp->type=bool_a;
	return temp;
}

vmarg *make_retvaloperand (vmarg* arg ){
	vmarg *temp = new vmarg;
	temp->type = retval_a;
	arg=temp;
	return arg;
}

void generate (vmopcode op, quad* quad){

	instruction *temp = new instruction;

	temp->opcode = op;
	vmarg * arg1 = new vmarg;
	vmarg * arg2 = new vmarg;
	vmarg * result = new vmarg;

	if (quad->arg1 && arg1){
		//make_operand( quad->arg1, temp->arg1 );
		arg1=make_operand1( quad->arg1);
		temp->arg1= arg1;
	}
	else{
		temp->arg1=NULL;
	}
	if (quad->arg2 && temp->arg2){
		//make_operand( quad->arg2, temp->arg2 );
		arg2=make_operand1( quad->arg2);
		temp->arg2 = arg2;
	}
	else{
		temp->arg2=NULL;
	}
	if (quad->result && temp->result){

		result=make_operand1( quad->result);
		temp->result = result;
		//cout<<"bla bla bla "<< temp->result->val<<endl;
	}

	
	quad->taddress = currInstruction;
	temp->line = quad->taddress ;
	temp->alphaline = quad->line;
	//cout<<" placing taddres  :" <<quad->taddress<<"  at  "<<quad->label<<endl;

	emitVmarg( temp );
	//cout<<"bla 1"<< temp->result->val<<endl;
	//cout<<"ok"<<endl;

}





void add_incomplete_jump (unsigned instrNo , unsigned iaddress){
	inc_jump *temp = new inc_jump;

	temp->instrNo = instrNo;
	temp -> iaddress = iaddress;


	inc_jump_Vector.push_back(temp);

};
// TODO vector<inc_jump *> inc_jump_Vector; vector <instruction> instructions;


void backpatch_Inc_jump(void){
	inc_jump * temp = new inc_jump;
	vector<inc_jump *> :: iterator it;
  	for(it=inc_jump_Vector.begin(); it!=inc_jump_Vector.end(); it++){
    
	if((*it)->iaddress == currQuad){
	 instructions[ (*it)->instrNo ].result->val = nextInstructionLabel();
	 if(DEBUG){cout<<" backpatching == currquad"<< (*it)->instrNo << " to "<< instructions[ (*it)->instrNo ].result->val<<endl;}
	
	 }
	else {
		//cout<<" ######"<< (*it)->iaddress<<" __"<<quadhead[(*it)->iaddress].taddress<<endl;
	 	if(DEBUG){cout<<" backpatching != currquad"<< (*it)->instrNo<<" from "<< (*it)->iaddress << " to "<< quadhead[(*it)->iaddress].taddress<<endl;}
		instructions[ (*it)->instrNo ].result->val = quadhead[(*it)->iaddress].taddress;

		//instructions[ (*it)->instrNo ].result->val = (*it)->iaddress;


	}
   	// backpatch((*it),contjump);  
	// quad->taddress = currInstruction;
	//cout<<" )))))))))))))) :" <<quad->taddress<<"       "<<quad->label<<endl;
  }

}

void generate_relational(vmopcode op,quad* quad){
	
	instruction *t = new instruction;
	vmarg * arg1 = new vmarg;
	vmarg * arg2 = new vmarg;
	vmarg * result = new vmarg;

	quad->taddress = currInstruction;
	if(DEBUG){cout<<" placing taddres  :" <<quad->taddress<<"  at  "<<quad->label<<endl;}

	t->opcode = op;
	//arg1=make_operand1(quad->arg1);
	//arg2=make_operand1(quad->arg2);
	
	if (quad->arg1)
		arg1=make_operand1(quad->arg1);
	if (quad->arg2)
		arg2=make_operand1(quad->arg2);
	result->type = label_a;
	//cout<<" ack?"<<endl;
   
	t->line = quad->line;
	if(quad->label < currProcessedQuad()){	
		//result->val = (quads+quad->label)->label;
		result -> val = quadhead[quad->label].taddress;
		//cout<<" !!!!!!!! :" <<quad->taddress<<"       "<<quad->label<<endl;
		// quadhead[quad->label]->label
	}
	else{
		add_incomplete_jump(currInstruction,quad->label);
		//cout<<" !!!!!!!! :" <<quad->taddress<<"       "<<quad->label<<endl;
		//result -> val= 500;
	}
	//t->result = quad->result->value;
	t->line = quad->line;
	t->arg1=arg1;
	t->arg2=arg2;
	t->result=result;
	t->alphaline=quad->line;
	//string stavros =;
	//assert(0);
	
	/*
d	instructions[ (*it)->instrNo ].result->val = quadhead[(*it)->iaddress].label;
	instructions[ (*it)->instrNo ].result->val = (*it)->iaddress;
	*/
	emitVmarg(t);
}

void generate_ADD(quad * quad){
	generate(add_vm,quad);
}

void generate_SUB(quad * quad){
	generate(sub_vm,quad);
}

void generate_MUL(quad * quad){
	generate(mul_vm,quad);
}

void generate_DIV(quad * quad){
	generate(divide_vm,quad);
}

void generate_MOD(quad * quad){
	generate(mod_vm,quad);
}

void generate_TABLECREATE( quad *quad ){
	generate( newtable_vm, quad );
}

void generate_TABLEGETELEM(quad *quad){
	generate( tablegetelem_vm, quad );
}


void generate_TABLESETELEM( quad *quad){
	generate(tablesetelem_vm, quad);
}


void generate_ASSIGN( quad *quad ){
	generate( assign_vm, quad );
}


void generate_JUMP( quad *quad ){
	generate_relational( jump_vm, quad );
}

void generate_IF_EQ( quad *quad ){
	generate_relational( jeq_vm, quad );
}

void generate_IF_NOTEQ( quad *quad ){
	generate_relational( jne_vm, quad );
}

void generate_IF_GREATER( quad *quad ){
	generate_relational( jgt_vm, quad );
}

void generate_IF_GREATEREQ( quad *quad ){
	generate_relational( jge_vm, quad );
}

void generate_IF_LESS( quad *quad ){
	generate_relational( jlt_vm, quad );
}

void generate_IF_LESSEQ( quad *quad ){
	generate_relational( jle_vm, quad );
}


void generate_CALL( quad* quad ){
	quad->taddress = currInstruction;
	if(DEBUG){cout<<" placing taddres  :" <<quad->taddress<<"  at  "<<quad->label<<endl;}

	instruction *t = new instruction;
	vmarg * result = new vmarg;
	vmarg * arg1 = new vmarg;
	vmarg * arg2 = new vmarg;
	result = make_operand1( quad->result);
	if(DEBUG){cout<<"type here is : "<<result->type <<endl;}
	if(quad->result->type == programfunc_e){

		
		int i  =lookup(quad->result->sym); 
		result->val= i ;
		//cout << i<< "NA PARE MALAKA P EINAI ! "<<endl;
	}
	if(quad->result->type == libraryfunc_e){
		result->type= libfunc_a;
		//cout<<" "	<<result->type<<endl;	
		result->val = libfuncs_newused(quad->result->sym->name);
		//cout<<" einai i libfunc :" << quad->result->sym->name<<endl;
		//int i  =lookup(quad->result->sym); 
		//result->val= i ;
		//cout << i<< "NA PARE MALAKA P EINAI ! "<<endl;
	}
	//cout << " Se gamaw k xwris salio "<<quad->result->sym->scopeF<<endl;
	/*if(quad->result->type= ){
		expr *ack = new expr;
		ack = newexpr(libraryfunc_e);
		Symbol *temp= new Symbol;
		temp->offset= -1;
		temp->space=formalarg	;
		ack->sym=temp;
		quad->result=ack;
	}*/
	
	t->opcode = call_vm;
	//result->type= userfunc_a;
	//cout << result->val<<" mpdasd mpdas "<<endl;
	t->arg1 = NULL;
	t->arg2 = NULL;
	t->result= result;
	t->alphaline=quad->line;
	
	emitVmarg( t );


}



void generate_GETRETVAL( quad* quad ){
	quad->taddress = currInstruction;
	if(DEBUG){cout<<" placing taddres  :" <<quad->taddress<<"  at retval  "<<quad->label<<endl;}

	instruction *t = new instruction;
	vmarg *result = new vmarg;
	vmarg *arg1 = new vmarg;
	arg1->type = retval_a;
	//arg1->type = retval_a;
	//arg1->val = -1; 
	t->opcode = assign_vm;
	if(DEBUG){cout << "bmlas "<<endl;}
	result= make_operand1( quad->result );
	//result->type = retval_a;
	t->result= result;
	t->arg1 = arg1;
	//t->arg1= result;
	//t->result=arg1;
	t->arg2 = NULL;
	t->alphaline = quad->line;
//cout << "bmlas "<<endl;	
	emitVmarg( t );


}

// MERIKH.+_
void generate_AND( quad *quad ){
	
}




void generate_NOT (quad* quad) {
	
}

void generate_OR( quad* quad ){

	
}



void generate_PARAM(quad *quad){
	quad->taddress = nextInstructionLabel();
	instruction *t = new instruction;
	vmarg *result = new vmarg;


	t->opcode = pusharg_vm;
	result= make_operand1(quad->result);
	t->result = result;
	t->arg1 = NULL;
	t->arg2 = NULL;
	t->alphaline = quad->line;
	emitVmarg(t);
}
// TODO
void generate_RETURN(quad *quad){
	quad->taddress = currInstruction;
	if(DEBUG){cout<<" placing taddres  :" <<quad->taddress<<"  at  "<<quad->label<<endl;}

	instruction *t = new instruction;

	//cout<<" in return #######"<<endl;
	vmarg *arg1= new vmarg;
	vmarg *fillthis= new vmarg;

	vmarg *arg2= new vmarg;
	vmarg *result= new vmarg;
	//vmarg *targ1= new vmarg;
	//vmarg *targ2= new vmarg;
	result->type = retval_a;
	arg1=make_operand1(quad->result);
	//fillthis=make_operand1(quad->result);
	//cout<<" arg1"<<arg1->type<<" result "<< result->type <<endl;
	t->arg1 = arg1;
	t->arg2 = NULL;
	t->result = result;
	t->opcode=assign_vm;
	t->alphaline= quad->line;
	emitVmarg(t);
	if(DEBUG){cout<<" arg1"<<t->arg1->type<<" result "<< t->arg1->val <<endl;}

	if(!funcstack.empty()){
		int f = funcstack.top();
	
		const_Functions[f]->return_list.push_back(nextInstructionLabel());	
	}
	instruction *t1 = new instruction;
	vmarg *tresult= new vmarg;
	t1->opcode = jump_vm;
	t1->result = tresult;
	t1->result->type= label_a;
	t1->arg1 = NULL;
	t1->arg2 = NULL;
	t1->alphaline= quad->line;
	emitVmarg(t1);
}
// TODO

void retjump ( quad*q ){

	instruction *t1 = new instruction;
	vmarg *tresult= new vmarg;
	t1->opcode = jump_vm;
	//tresult=result;
	t1->result = tresult;
	t1->result->type= retval_a;
	t1->arg1 = NULL;
	t1->arg2 = NULL;
	t1->alphaline= q->line;
	emitVmarg(t1);


}

void generate_FUNCEND(quad *quad){

	instruction *t = new instruction;

	vmarg * result = new vmarg;
	vmarg * arg1 = new vmarg;
	vmarg * arg2 = new vmarg;
	arg1->val = -1;
	arg2->val = -1;


	if( !const_Functions[funcstack.top()]->return_list.empty()){
		int f = funcstack.top();
		
		backpatchre(f , nextInstructionLabel());
		result->val = f;
		
	}
	if(DEBUG){cout<<" size here: "<< const_Functions.size()-1<<endl;}
	funcstack.pop();

	t->opcode = exitfunc_vm;
	quad->taddress = currInstruction;
	if(DEBUG){cout<<" placing taddres  :" <<quad->taddress<<"  at  "<<quad->label<<endl;}

	if(DEBUG){cout << quad->result->sym->dotalocal <<" funcend"<<endl;}
	result=make_operand1(quad->result);
	result->val= userfuncs_funcend(quad->result->sym->dotalocal);
	//result->val = const_Functions.size()-1;
	//const_Functions.pop_back();
	//result ->val=
	if(DEBUG){cout<<" size here: again "<< const_Functions.size()-1<<endl;}

	t->arg1 = NULL;
	t->arg2 = NULL;
	t->result= result;
	t-> alphaline=quad->line;
	emitVmarg(t);
	avoid_patch(quad);

}
void generate_FUNCSTART(quad *quad){
	quad->taddress = currInstruction;
	if(DEBUG){cout<<" placing taddres  :" <<quad->taddress<<"  at  "<<quad->label<<endl;}
	
	avoid_func(quad);//param quad
	quad->result->sym->lineF= nextInstructionLabel();
	

	vmarg * result = new vmarg;
	vmarg * arg1 = new vmarg;
	vmarg * arg2 = new vmarg;
	arg1->val = -1;
	arg2->val = -1;
	instruction *t = new instruction;
	if(DEBUG){cout <<quad->result->type<<" funcstart "<<endl;}
	result= make_operand1(quad->result);
	result->val = userfuncs_newfunc(quad->result->sym);
	result->type = userfunc_a;
	//func bla;
	t->arg1 = NULL;
	t->arg2 = NULL;
	t->result=result;
	funcstack.push(t->result->val);

	//cout << quad->result->type << "bmasd a"<<endl;

	t->opcode= enterfunc_vm;
	t->alphaline = quad->line;
	emitVmarg(t);

}


void generate_UMINUS(quad *quad){
	quad->taddress = currInstruction;
	if(DEBUG){cout<<" placing taddres  :" <<quad->taddress<<"  at  "<<quad->label<<endl;}

	instruction *t = new instruction;
	t->opcode = mul_vm;
	t->arg1=make_operand1(quad->arg1);
	t->arg2 = make_intoperand(-1);
	t->result=make_operand1(quad->result);
	t->line = quad->line;
	t->alphaline = quad->line;
 	emitVmarg(t);
}






unsigned int consts_newstring( string s){
	int i ;
	if(DEBUG)cout<< consts_String.size()<<endl;
	if(!consts_String.empty()) {
		for( i= 0;i < consts_String.size() ; i++ ){
			if(s.compare((consts_String[i]))==0){
				//cout<<" vrika"<<endl;
				return i;
			}

		}
	}
	consts_String.push_back(s);
	return consts_String.size()-1;

};
unsigned int consts_newint( int  i){
	//cout<<" int is :"<<i<<endl;
	for(int j=0 ; j<consts_Int.size();j++){
		if(consts_Int[j] == i){
			return j;
		}
	}
	consts_Int.push_back(i);
	//cout<<" int is again :"<<i<<" size :"<<consts_Int.size()<<endl;

	return consts_Int.size()-1;
};
unsigned int consts_newdouble( double d ){
	for(int j=0 ; j<consts_Double.size();j++){
		if(consts_Double[j] == d){
			return j;
		}
	}
	consts_Double.push_back(d);
	return consts_Double.size()-1;
};
/*
Syriza.insert ({hashme("print"),fill("print",0,0,"print",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("input"),fill("input",0,0,"input",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("tableindices"),fill("tableindices",0,0,"tableindices",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("tablelength"),fill("tablelength",0,0,"tablelength",0,0,LIBFUNC,true)});
Syriza.insert ({hashme("tablecopy"),fill("tablecopy",0,0,"tablecopy",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("totalarguments"),fill("totalarguments",0,0,"totalarguments",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("argument"),fill("argument",0,0,"argument",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("typeof"),fill("typeof",0,0,"typeof",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("strtonum"),fill("strtonum",0,0,"strtonum",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("sqrt"),fill("sqrt",0,0,"sqrt",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("cos"),fill("cos",0,0,"cos",0,0,LIBFUNC,true)} );
Syriza.insert ({hashme("sin"),fill("sin",0,0,"sin",0,0,LIBFUNC,true)} );

*/
unsigned int string_libfuncs (string s){
	unsigned int i= -1;
	if( (s=="print")||( s=="input")||( s== "tableindices")||( s== "tablelength")||( s== "tablecopy")||
		( s== "totalarguments")||( s== "argument" )||( s=="typeof" )||( s=="strtonum" )||( s=="sqrt")||( s== "cos" )||( s=="sin")){

		i = libfuncs_newused(  s );
	}
	return i;
}

unsigned int libfuncs_newused( string s ){
	int i ;
	//cout<< lib_Functions.size()<<endl;
	if(!lib_Functions.empty()) {
		for( i= 0;i < lib_Functions.size() ; i++ ){
			if(s.compare((lib_Functions[i]))==0){
				//cout<<" vrika"<<endl;
				return i;
			}

		}
		lib_Functions.push_back(s);
		//cout<<" de vrika"<<endl;
		return lib_Functions.size()-1;
	}
	lib_Functions.push_back(s);
	//cout<<" den eixe"<<endl;
	//lib_Functions[i]= s;
	//currlib ++;
	return lib_Functions.size()-1;
};
unsigned int userfuncs_newfunc( Symbol *sym ){
	func_sym* temp = new func_sym;
	temp->type = userfunc_a;
	
	temp->nameF = sym->nameF;
	temp->scopeF = sym->scopeF;
	temp->lineF = currInstruction;
	temp->dotalocal = sym->dotalocal;
	
	/*
	Symbol * mysym = new  Symbol;
    mysym= fill4(mysym, s->name,  s->scope ,  s->line , s->nameF,  s->scopeF , s->lineF , s->type , s->active, s->offset,s->space);
    expre->sym=mysym;
	*/

	Symbol * mysym = new  Symbol;
	mysym= fill4(mysym, sym->name,  sym->scope ,  sym->line , sym->nameF,  sym->scopeF , sym->lineF , sym->type , sym->active, sym->offset,sym->space,sym->dotalocal);
	temp->sym = mysym;
	//temp->sym->dotalocal = ;
	//cout << temp->sym->name<<" eimai xazos "<<temp->sym->scopeF <<" K xazoss "<<endl;
	const_Functions.push_back(temp);
	return const_Functions.size()-1;
};


unsigned int userfuncs_funcend( int dotalocal){
	
	//vector <func_sym*>  :: iterator it;
	int  myit= const_Functions.size()-1;
	
	if (myit>-1){
		for(;myit>-1;myit--){
	    	if (!(const_Functions[myit]->funcused)){
	    		const_Functions[myit]->funcused= true;
	    		const_Functions[myit]->sym->dotalocal= dotalocal;
	    		return  myit;
	    	}
	    }

	}
};


unsigned int too_bool(string t){

	if(t.compare("true")==0){
		return 1;
	}else if (t.compare("false")==0){
		return 0;
	}
	else return -1;
}

void emitVmarg(instruction *ins){
	instructions.push_back(*ins);
	currInstruction ++;
}


void generate_binary(){

	//vector<quad>  :: iterator it;
  	//int i=0;

  	unsigned int processedquad=0;
  	for(;processedquad<quadhead.size() ;processedquad++){
      	cout<<processedquad<<": binary :";
      	cout<<"   sql   1111     "<<printOpcode(quadhead[processedquad].op)<<endl;
      	if (quadhead[processedquad].op== assign){

      			cout<<"var "<<quadhead[processedquad].result->sym->name<<"me offset "<<quadhead[processedquad].result->sym->offset<<endl;
      	}
      
      	//iopcode x = quadhead[i].op;
      	//cout<<"   sql   1111     "<<quadhead[processedquad].result->type<<endl;

      	//if(quadhead[processedquad].result->type == libraryfunc_e){

		
		//cout<<" einai i libfunc :" << quadhead[processedquad].result->sym->name<<endl;
		//int i  =lookup(quad->result->sym); 
		//result->val= i ;
		//cout << i<< "NA PARE MALAKA P EINAI ! "<<endl;
		//}
      	(*generators[quadhead[processedquad].op])(&quadhead[processedquad]);
      	cout<<printOpcode(quadhead[processedquad].op)<<endl;
      	

      	
      }
    backpatch_Inc_jump();

}


void backpatchre(int f , int r){
	//cout << "backpatchre !! ! ! "<<endl;
	vector<int> :: iterator it;
	for(it = const_Functions[f]->return_list.begin();it!= const_Functions[f]->return_list.end();it++){

		instructions[(*it)].result->val= r;
		//cout << "se gamaw "<< const_Functions[f]->return_list[0]<<endl;
		//cout << " MASFDA " << r << instructions[(*it)].result->val<<f<<endl;
	}

	
}

//vector<instruction *> InstructionTable;

//vector <instruction> instructions;
/*
vector<int> consts_Int;
vector<string> consts_String;
vector<double> consts_Double;
vector<func_sym*> const_Functions;
*/
void generate_abc(){
	cout<<"magicnumber 340200501"<<endl;
	cout<<"strings "<<consts_String.size()<<endl;
	for (vector<string >  :: iterator it=consts_String.begin();it!=consts_String.end();it++){
		//if((*it)=="\n")cout<<"\\n"<<endl;
		cout<<"\""<<(*it)<<"\""<<endl;
		string_libfuncs((*it));
	}
	cout<<"integers "<<consts_Int.size()<<endl;
	for (vector<int >  :: iterator it=consts_Int.begin();it!=consts_Int.end();it++){
		cout<<(*it)<<endl;
	}
	cout<<"doubles "<<consts_Double.size()<<endl;
	for (vector<double >  :: iterator it=consts_Double.begin();it!=consts_Double.end();it++){
		//std::stringstream ss;
		//ss <<  std::setprecision(17)<< m->data.realval;
		//std::string s = ss.str();
		cout<<(*it)<<std::setprecision(17)<<endl;
	}
	cout<<"userfunctions "<<const_Functions.size()<<endl;

	for (vector<func_sym* >  :: iterator it=const_Functions.begin();it!=const_Functions.end();it++){
		cout<<(*it)->lineF<<" "<<(*it)->sym->dotalocal<<" "<<(*it)->sym->name<<endl;
	}
	/*
	for (vector<string >  :: iterator it=consts_String.begin();it!=consts_String.end();it++){
		//if((*it)=="\n")cout<<"\\n"<<endl;
		//f((-1)!=string_libfuncs((*it)))cout<<"\""<<(*it)<<"\""<<endl;

	}*/
	
	cout<<"libfunctions "<<lib_Functions.size()<<endl;
	if (lib_Functions.size()){
		for (vector<string >  :: iterator it=lib_Functions.begin();it!=lib_Functions.end();it++){
			cout<<(*it)<<endl;//" ";
		}
		//cout<<endl;
	}
	//
	cout<<"globals "<<globalsyms.size()<<endl;
	cout<<"code "<<instructions.size()<<endl;
	printINstr();

}


void generate_o(ofstream &binarw){
	stringstream binary;
	string buffer;
	unsigned int magicNumber = 340200501;
	unsigned int numofStrings = consts_String.size();
	binary.write( (char *) &magicNumber, sizeof(unsigned int) );
	binary.write( (char *) &numofStrings, sizeof(unsigned int ) );
	for (vector<string >  :: iterator it=consts_String.begin();it!=consts_String.end();it++){
		buffer.clear();
		buffer = *it;
		binary.write( buffer.c_str(), buffer.size()+1 );
		string_libfuncs((*it));
	}
	unsigned int integers = consts_Int.size();
	int vardas;
	binary.write( (char *) &integers, sizeof(unsigned int ) );
	for (vector<int >  :: iterator it=consts_Int.begin();it!=consts_Int.end();it++){
		vardas=*it;
		binary.write( (char *) &vardas, sizeof(int) );
	}
	unsigned int  doubles = consts_Double.size();
	double parasyris;
	binary.write( (char *) &doubles, sizeof(unsigned int ) );
	for (vector<double >  :: iterator it=consts_Double.begin();it!=consts_Double.end();it++){
		parasyris=*it;
		binary.write( (char *) &parasyris, sizeof(double) );
	}
    unsigned int  numofUserfuncs = const_Functions.size();
    binary.write( (char *) &numofUserfuncs, sizeof(unsigned int) );
    unsigned int funcaddr, funclocals;
    string funcname;
	for (vector<func_sym* >  :: iterator it=const_Functions.begin();it!=const_Functions.end();it++){
		funcname.clear();
		funcaddr = (*it)->lineF;
		funclocals = (*it)->sym->dotalocal;
		funcname = (*it)->sym->name;
		binary.write( (char *) &funcaddr, sizeof(unsigned int) );
		binary.write( (char *) &funclocals, sizeof(unsigned int) );
		binary.write( funcname.c_str(), funcname.size()+1 );
		//cout<<(*it)->lineF<<" "<<(*it)->sym->dotalocal<<" "<<(*it)->sym->name<<endl;
	}
	unsigned int numofLibfuncs = lib_Functions.size();
	binary.write( (char *) &numofLibfuncs, sizeof(unsigned int) );
	if (numofLibfuncs>0){
		for (vector<string >  :: iterator it=lib_Functions.begin();it!=lib_Functions.end();it++){
			buffer.clear();
			buffer=*it;
			binary.write( buffer.c_str(), buffer.size()+1 );
			//cout<<(*it)<<endl;//" ";
		}
	}
	unsigned int globals = globalsyms.size();
	unsigned int stauros = instructions.size();
	binary.write( (char *) &globals, sizeof(unsigned int ) );
	binary.write( (char *) &stauros, sizeof(unsigned int ) );
	unsigned short _opcode;
	unsigned int type;
	unsigned int value,alphaline;
	vector<instruction >  :: iterator it;
	for(it=instructions.begin(); it!=instructions.end(); it++){
		_opcode = (*it).opcode;
		binary.write( (char *) &_opcode, sizeof(unsigned short) );
		if((*it).result){
			type=((*it).result)->type;
			value = printVal(((*it).result)->val);
		}
		else{
			type=7;
			value =0;
		}
		binary.write( (char *) &type, sizeof(unsigned int) );
		binary.write( (char *) &value, sizeof(unsigned int) );
		if((*it).arg1){
			type=((*it).arg1)->type;
			value = printVal(((*it).arg1)->val);
		}
		else{
			type=7;
			value =0;
		}
		binary.write( (char *) &type, sizeof(unsigned int) );
		binary.write( (char *) &value, sizeof(unsigned int) );
		if((*it).arg2){
			type=((*it).arg2)->type;
			value = printVal(((*it).arg2)->val);
		}
		else{
			type=7;
			value =0;
		}
		binary.write( (char *) &type, sizeof(unsigned int) );
		binary.write( (char *) &value, sizeof(unsigned int) );
		alphaline = (*it).alphaline;
		binary.write( (char *) &alphaline, sizeof(unsigned int) );
	}
	binarw.write(binary.str().c_str(), binary.str().length());

}


void printINstr(void) {
  	cout << "////-----------------------------INSTR PRINTS----------------------------------------------////" << endl;
  	vector<instruction >  :: iterator it;
  	int i=0;
  	for(it=instructions.begin(); it!=instructions.end(); it++){
      	cout<<i<<": ";

      	cout<<" |" << "OPCODE :"<<printInstrcode((*it).opcode);
      	//cout<<" |" << "OPCODE :"<<(Byte)(*it).opcode;
      	if((*it).result) cout<<"  " << "RESULT : "<<((*it).result)->type<< " | "<< printVal(((*it).result)->val);
      	else cout<<"  " << "RESULT : 7 | 0";
      	if((*it).arg1) cout<<"  " << "ARG1 : "<<((*it).arg1)->type<< " | "<<printVal(((*it).arg1)->val);
      	else cout<<"  " << "ARG1 : 7 | 0";
      	if((*it).arg2) cout<<"  " << "ARG2 : "<<((*it).arg2)->type<< " | "<<printVal(((*it).arg2)->val);
      	else cout<<"  " << "ARG2 : 7 | 0";
      	cout<<"  " << "AL : "<<(*it).alphaline;
      	cout<<endl;
      	/*
      	cout<<"  " << "ARG1 :"<< (*it).arg1->val;//->sym->name
      	cout<<"  " << "ARG2 :"<<(*it).arg2->val;
      	*/
      	//cout<<"  " << "LABEL :"<<printLabel((*it).label);
      	//cout<<"  " << "LINE :"<<(*it).line<<endl;

      	/*
      	  vmopcode opcode;
		  vmarg *result;
		  vmarg *arg1;
		  vmarg *arg2;
		  unsigned int line;
      	*/
      	i++;
      	
      }
    	
  
  cout << "////---------------------------------------------------------------------------------------////" << endl;
};

unsigned int printVal( unsigned int q){
	if (q == -1) return 0;
	else return q;
}

/*
vmarg_t print_type( vmarg_t type){
	if (type == NULL) return nil_a;
	else return type;
}

typedef enum Vmopcode {
    assign_vm,
    add_vm,
    sub_vm, 
    mul_vm,
    divide_vm,
    mod_vm,
    uminus_vm,
    and_op_vm,
    or_op_vm,
    not_op_vm,
    jeq_vm,
    jne_vm,
    jle_vm,
    jge_vm,
    jlt_vm,
    jgt_vm,
    call_vm,
    param_vm,  
    ret_vm,
    getretval_vm,
    enterfunc_vm,
    exitfunc_vm,
    newtable_vm,
    jump_vm, 
    tablegetelem_vm,
    tablesetelem_vm

}vmopcode;
*/
string printInstrcode(vmopcode op ) {
	//if (e==NULL){return "-";}
	switch(op){

		case 0:	return "assign_vm";
				break;
		case 1:	return "add_vm";
				break;
		case 2:	return "sub_vm";
				break;
		case 3:return "mul_vm";
				break;
		case 4:	return "divide_vm";
				break;
		case 5:	return "mod_vm" ;
				break;
		case 6:return "uminus_vm" ;
				break;
		case 7:	return "and_op_vm";
				break;
		case 8:	return "or_op_vm";
				break;
		case 9:return "not_op_vm";
				break;
		case 10:	return "jeq_vm";
				break;
		case 11:	return "jne_vm";
				break;
		case 12:return "jle_vm";
				break;
		case 13:	return "jge_vm";
				break;
		case 14:	return "jlt_vm";
				break;
		case 15:return "jgt_vm";
				break;
		case 16:	return "call_vm";
				break;
		case 17:	return "pusharg_vm";
				break;
		case 18:return "ret_vm";
				break;
		case 19:	return "getretval_vm";
				break;
		case 20:	return "enterfunc_vm";
				break;
		case 21:return "exitfunc_vm";
				break;
		case 22:return "newtable_vm";
				break;
		case 23:return "jump_vm";
				break;
		case 24:return "tablegetelem_vm";
				break;
		case 25:return "tablesetelem_vm";
				break;
		
		default: return "invalid opcode";
	}
}

/*
typedef enum Vmarg_t {
   0 label_a ,
   1 global_a ,
   2 formal_a ,
   3 local_a ,
   4 integer_a ,
   5 string_a ,
   6 bool_a ,
   7 nil_a ,
   8 userfunc_a ,
   9 libfunc_a ,
   10 retval_a,
   11 real_a
    
} vmarg_t;

typedef struct Vmarg_p{
   vmarg_t  type;
   unsigned val;
} vmarg;

string printvmarg(vmarg* arg ) {
	if (arg==NULL){return "-";}
	switch(arg->type){

		case 0: case 1: case 2: case 3: return arg->val;

		//
		case 0: case 1: case 2: case 4: case 5: case 6: case 7:	return arg->sym->name;
				break;	
		case 8:	return to_string(arg->intConst);
				break;
		case 9:	return to_string(arg->numConst);
				break;
		case 10:return arg->boolConst;
				break;
		case 11: return arg->strConst;
				break;
		//case 2: return &(e->sym);

		default: return arg->type;//to_string(arg->type);
	}
}*/

//	vector<sym*> globalsyms;

void lookglobal(Symbol *sym){
	//cout<<" in lookglobal"<<endl;
	Symbol* sym1= new Symbol;
	bool insert=true;
	if(globalsyms.size()){
		for(int i = 0;i<globalsyms.size();i++){
			sym1=globalsyms[i];
	    	if ((sym->name==sym1->name)&&(sym->scope==sym1->scope)&&(sym->line == sym1->line)&&( sym->nameF== sym1->nameF)&&(sym->scopeF==sym1->scopeF)&&(sym->lineF==sym1->lineF)&&(sym->type==sym1->type)&&(sym->offset==sym1->offset)&&(sym->space==sym1->space)){
	    		insert=false;
	    		//cout<<"to vrika"<<endl;
			}
	    }

	}
	if(insert)globalsyms.push_back(sym);
}
bool looktrue=true;
unsigned int lookup(Symbol *sym)
{

	Symbol *sym2 = new Symbol;
	int j = 0;
	int i=0;
	//for()

	//				sysfuncName_0 		0 					3 			_sysfuncName_0 				0 			6
	if(DEBUG) cout<<"psaxnw : "<<sym->name<<" "<<sym->scope <<" "<<sym->line<<" "<<sym->nameF<<" "<<sym->scopeF<<" " <<" "<<sym->type<<" "<<sym->active<<" "<<sym->offset<<" "<<sym->space<<endl;

	//	if ((sym->name==sym1->name)&&(sym->scope==sym1->scope)&&(sym->line == sym1->line)&&( sym->nameF== sym1->nameF)&&(sym->scopeF==sym1->scopeF)&&(sym->lineF==sym1->lineF)&&(sym->type==sym1->type)&&(sym->active==sym1->active)(sym->offset==sym1->offset)&&(sym->space==sym1->space)){
	if(looktrue){
		if(DEBUG) cout<<"mesa einai :"<<endl;
		for(;j<const_Functions.size();j++){
			sym2=const_Functions[j]->sym;
			//cout<<"exw :"<<sym->name<<endl;
			//cout<<sym->name<<" "<<sym->scope <<" "<<sym->line<<" "<<sym->nameF<<" "<<sym->scopeF<<" "<<sym->lineF <<" "<<sym->type<<" "<<sym->active<<" "<<sym->offset<<" "<<sym->space<<endl;		
			//cout<<"checkarw "<<sym1->name<<endl;
			if(DEBUG)cout<<sym2->name<<" "<<sym2->scope <<" "<<sym2->line<<" "<<sym2->nameF<<" "<<sym2->scopeF<<" "<<" "<<sym2->type<<" "<<sym2->active<<" "<<sym2->offset<<" "<<sym2->space<<endl;

	    }


	}
	//	}
	//cout<<" in unsigned int lookup(Symbol *sym)"<<endl;
	Symbol *sym1 = new Symbol;
	//int  myit= const_Functions.size()-1;
	i = 0;
	if (const_Functions.size()>0){
		if(DEBUG)cout<<"den einai adeio"<<endl;
		for(;i<const_Functions.size();i++){
			

			sym1=const_Functions[i]->sym;
			//cout<<"exw :"<<sym->name<<endl;
			//cout<<sym->name<<" "<<sym->scope <<" "<<sym->line<<" "<<sym->nameF<<" "<<sym->scopeF<<" "<<sym->lineF <<" "<<sym->type<<" "<<sym->active<<" "<<sym->offset<<" "<<sym->space<<endl;
			
			//cout<<"checkarw "<<sym1->name<<endl;
			//cout<<sym1->name<<" "<<sym1->scope <<" "<<sym1->line<<" "<<sym1->nameF<<" "<<sym1->scopeF<<" "<<sym1->lineF <<" "<<sym1->type<<" "<<sym1->active<<" "<<sym1->offset<<" "<<sym1->space<<endl;
																														//(sym->lineF==sym1->lineF)&&
	    	if ((sym->name==sym1->name)&&(sym->scope==sym1->scope)&&(sym->line == sym1->line)&&( sym->nameF== sym1->nameF)&&(sym->scopeF==sym1->scopeF)&&(sym->type==sym1->type)&&(sym->offset==sym1->offset)&&(sym->space==sym1->space)){
	    		if(DEBUG)cout<<" vrika sti 8esi "<<i<<" userfunc me onoma "<<sym->name<<endl;
	    		return i;
			}
	    }

	}
	return i;
}


void avoid_func(quad *q){

	instruction *t1 = new instruction;
	vmarg * jump = new vmarg;
	jump->val = -1;
	jump->type =label_a;
	t1->opcode = jump_vm;
	t1->result = jump;
	t1->arg1 = NULL;
	t1->arg2 = NULL;
	t1->alphaline=q->line;
	emitVmarg(t1);
	prefunc.push(t1);
}


void avoid_patch(quad *q){
	instruction *t1 = new instruction;
	t1=prefunc.top();
	t1->result->val= currInstruction;
	t1->alphaline=q->line;
	prefunc.pop();

}