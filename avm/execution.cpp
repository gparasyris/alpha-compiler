#include "avm.h"


extern unsigned int oldPC;
//

execute_func_t executeFuncs[] = {
  execute_assign, //0
  execute_add,    //1
  execute_sub,    //2
  execute_mul,    //3
  execute_div,    //4
  execute_mod,    //5
  execute_uminus,//6
  execute_and,  //7
  execute_or,   //8
  execute_not,  //9
  execute_jeq,  //10
  execute_jne,  //11
  execute_jle,  //12
  execute_jge,  //13
  execute_jlt,  //14
  execute_jgt,  //15
  execute_call,   //16
  execute_pusharg,  //17
  execute_enterfunc, //18
  execute_funcexit, //19
  execute_newtable, //20
  execute_uncjump, //21
  execute_tablegetelem, //22
  execute_tablesetelem, //23
  execute_nop     //24
};
//=================================================/
unsigned avm_get_envvalue(unsigned i){
	
	unsigned val;
	if(stack[i].type == integer_vm){
		val = (unsigned)stack[i].data.intval;
	}
	else{
		 val = (unsigned)stack[i].data.realval;
	}

	return val;
}

//=================================================/

unsigned avm_totalactuals(void){
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

//=================================================/


avm_memcell* avm_getactual(unsigned i){
	
	return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

//=================================================/

/*
void functorcall(avm_memcell* table){
 
  avm_memcell * indx = new avm_memcell;
  indx->type= string_vm;
  indx->data.strVal=strdup("()");
  avm_table_bucket bucket;
  bucket.key = *indx;
  avm_memcell * temp = stringIndex_lookup(table->data.tableVal->strIndexed,bucket,getme);
  if(temp){
    if(temp->type==table_vm)functorcall(temp);
    else if (temp->type==userfunc_vm){
 
      avm_assign(&stack[top], table);
      ++totalActuals;
      avm_dec_top();
      		if(regdebug)cout<<" ### telos pusharg"<<endl;
      avm_callsaveenvironment();
        	if(regdebug)cout<<"in call ex 2 "<<temp->type<<endl;
      pc = temp->data.funcVal;
          	if(regdebug)cout << "FUNC IN PC :" << pc << endl;
      
      assert(_instructions[pc].opcode == enterfunc_vm);
    }
    else executionFinished = 1;
  }
  else executionFinished = 1;
}
*/
//==========execute_call=======================/

void execute_call (instruction* instr){
  if(regdebug)cout<<"in call ex 1 "<<instr->result.type<<endl;
	avm_memcell* func = avm_translate_operand(&instr->result, &ax);
  
  if (func->type==table_vm){
      functorcall(func);
      
  }
  else{
	assert(func);
	avm_callsaveenvironment();
  if(regdebug)cout<<"in call ex 2 "<<func->type<<endl;
	char* s;
	char * temp;
	switch(func->type)
		{
		case userfunc_vm:
			pc = func->data.funcVal;
      if(regdebug)cout << "FUNC IN PC :" << pc << endl;

      if(regdebug)cout<<"opcode:"<<_instructions[pc].opcode<<endl;
			assert(_instructions[pc].opcode == enterfunc_vm);

			break;
		case string_vm:		

			temp =strdup( func->data.strVal);
			avm_calllibfunc(strdup(temp));
			break;
		case libfunc_vm:
			temp =(func->data.libfuncVal);
      if(regdebug)cout<<" in excall temp    "<<temp<<endl;
			avm_calllibfunc(strdup(temp));
			break;
		default:

			executionFinished = 1;
		}
  }
}

void avm_calllibfunc(string id)
{
  if(regdebug)cout<<"in calllibfunc :"<<id<<endl;
  library_func_t f =  avm_getlibraryfunc(id);
  
  if(!f){
    //fprintf(stdout,"Unsupported lib func '%s' called!", id);
    if(regdebug)cout<<" unsup lbfunc"<<endl;
    executionFinished = 1;
  }
  else{
    topsp =  top;
    totalActuals =  0;
    
    (*f)();
    
    if(!executionFinished)
    {
    	instruction* t = NULL;
      execute_funcexit(t);
    }
  }
}



void avm_callsaveenvironment(void)
{
  avm_push_envvalue(totalActuals);
  avm_push_envvalue(pc+1);
  avm_push_envvalue(top + totalActuals + 2);
  avm_push_envvalue(topsp);
}


void avm_push_envvalue(unsigned val){
  stack[top].type  = integer_vm;
  stack[top].data.intval = val;
  avm_dec_top();
}


void avm_dec_top(void){
  if(!top)
  {
    if(regdebug)cout<<"stack overflow"<<endl;
    executionFinished =  1;
  }
  else
    --top;
  
}

//========execute_funcexit===========================/


void execute_funcexit(instruction* unused){
  unsigned oldTop =  top;
  top =  avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
  pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
  topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
  
  //cout<<" mem clear is off !"<<endl;
  if(regdebug)cout<<oldTop<<" oldtop | top "<<top<<endl;
 while(++oldTop <= top)
  {
    
   avm_memcellclear(&stack[oldTop]);
  }
}


//=======mem_clear===================================/

memclear_func_t memclearFuncs[] = {
  0,
  0,/*number*/
  memclear_string,
  0,/*bool*/
  memclear_table,
  0,/*userfunc*/
  0,/*livfunc*/
  0,/*nil*/
  0,/*undef*/
};


void avm_memcellclear(avm_memcell* m){
  if(m->type !=  undef_vm){
    if(regdebug)cout << "MEMCLEAR TYPE:" << m->type << endl;
    memclear_func_t f = memclearFuncs[m->type];
    if(f)
      (*f)(m);
    m->type = undef_vm;
  }  
}


void memclear_string(avm_memcell* m){

}

//==========execute_pusharg================/


void execute_pusharg (instruction* instr)
{  
	avm_memcell* arg = avm_translate_operand(&(instr->result), &ax);
  if(regdebug)cout << " top "<<top <<" topsp "<<GLOBALS<<endl;
  if(regdebug)cout<<" in pusharg "<<arg->type<< "intval "<< arg->data.intval <<" strVal " <<endl;
	avm_assign(&stack[top], arg);
	++totalActuals;
	avm_dec_top();
  if(regdebug)cout<<" ### telos pusharg"<<endl;

}

//==========execute_assign================/


void execute_assign(instruction* instr){

	avm_memcell* lv = avm_translate_operand(&(instr->result), (avm_memcell*)0);
	avm_memcell* rv = avm_translate_operand(&(instr->arg1), &ax);
	avm_assign(lv,rv);

}


void avm_assign(avm_memcell* lv, avm_memcell* rv){


  if(lv == rv)return;
  if(lv->type == table_vm && rv->type == table_vm && lv->data.tableVal == rv->data.tableVal)return;
  if(rv->type == undef_vm)if(regdebug)cout<<" assigning from 'undef' content! "<<endl;
  
  
  avm_memcellclear(lv);
  memcpy(lv,rv,sizeof(avm_memcell));

  if(lv->type==integer_vm){
    if(regdebug) cout<<"try1 "<<lv->data.intval<<"  "<<lv<<endl;
  }
 
   if(lv->type ==  string_vm)
  {  
    lv->data.strVal =  strdup(rv->data.strVal); 
  }
  else if(lv->type==table_vm) {
    avm_tableincrefcounter(lv->data.tableVal);
   }
}


//==========execute_cycle================/



void execute_cycle(void)
{
  if(regdebug)cout<<" in execute_cycle"<<endl;
  if(executionFinished)
    return;
  else if(pc == totalCode)
      {
        if(regdebug)cout<<" pc == totalCode "<<endl;

        executionFinished = 1;
        return;
      }
  else
  {
		instr* instr1 = new instr; 

		instr1 = &_instructions[pc];
		if(regdebug) cout<<" after fill"<<instr1->opcode<<endl;
	    if(instr1->srcLine){
        
        currLine =  instr1->srcLine;
       if(regdebug) cout << "EXECUTING INSTRUCTION IN LINE: " << currLine << endl;
        }

      oldPC = pc;
      (*executeFuncs[instr1->opcode])(instr1);
      if(pc == oldPC)++pc;

  }
}

//=========Tools==========================/


instruction *fil_instruction(instruction inst){
  if(regdebug)cout<<" ############################ instr"<<endl;
	instruction * temp =new  instruction;
	temp->result = inst.result;
	temp->arg1 = inst.arg1;
	temp->arg2 = inst.arg2;
	temp-> srcLine = inst.srcLine;
	temp->opcode = inst.opcode;
	return temp;
}

vmarg *fill_arg(vmarg arg){
  if(regdebug)cout<<" ############################ arg"<<endl;
  vmarg * temp = &arg;
  return temp;
}


//=========execute_enterfunc==========================/\


void execute_enterfunc(instruction* instr)
{
  avm_memcell* func =  avm_translate_operand(&(instr->result), &ax); 
  totalActuals = 0;
  userfunc* funcInfo =  avm_getfuncinfo(pc);
  topsp =  top;
  top =  top - funcInfo->locals;
}

userfunc* avm_getfuncinfo(unsigned address){
  int i;

  for(i = 0; i < totalFuncs; i++)
    {
    if(address == _userfuncs[i].address)
      {
      userfunc* ret = new userfunc;
      ret->address = _userfuncs[i].address;
      ret->locals = _userfuncs[i].locals;
      ret->name = _userfuncs[i].name;
      return ret;
      }
    }
  cout<<"Error :Enter func error no such userfunc."<<endl;
  executionFinished = 1;
  return NULL;
}

//===============execute_uncjump===========/

void execute_uncjump(instruction* instr){
 
  pc=instr->result.val;
   if(regdebug)cout << "Jump to PC: " << pc << endl;

}

//==============execute_emptyes===========/

void  execute_uminus(instruction* instr){}
void  execute_and(instruction* instr){}
void  execute_or(instruction* instr){}
void  execute_not(instruction* instr){}
void  execute_nop(instruction* instr){}


avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
  
  if(regdebug)cout<<"arg in op :"<<arg->type<<" "<<arg->val <<" pc is :"<<pc<<endl;
  switch(arg->type){
    case global_a: return &stack[AVM_STACKSIZE-1-arg->val];//if(regdebug)cout<<"global_a"<<global_a<<" "<<(4096-1-arg->val)<<" "<<&stack[4096-1-arg->val] <<endl; 
    case local_a: return &stack[topsp-arg->val];
    case formal_a:  return &stack[topsp+ AVM_STACKENV_SIZE +1+arg->val];
    
    case retval_a:  return &retval;

    case number_a:{
      reg->type = integer_vm;
      reg->data.intval = consts_getnumber(arg->val);
      return reg;
    }
  
    case string_a: {
      reg->type = string_vm;
      //string awk = new string;
      string  awk=consts_getstring(arg->val);
      reg->data.strVal=  strdup(awk.c_str());
      //if(regdebug)cout<<"reg in ato string_a :"<<reg->data.strVal<<endl;
      return reg;
    }

    case bool_a: {
      reg->type = bool_vm;
      reg->data.boolVal =  arg->val;
      return reg;
    }

    case nil_a:{ reg->type =  nil_vm; return reg;}

    case userfunc_a: {
      //if(regdebug)cout<< "FUNCTION: " << _userfuncs[arg->val].name << "address : " << _userfuncs[arg->val].address << endl;
      reg->type =  userfunc_vm;
      reg->data.funcVal = _userfuncs[arg->val].address;
      reg->namef = strdup(_userfuncs[arg->val].name.c_str());
      reg->funcoffset = _instructions[reg->data.funcVal].aline;
      //reg->funcoffset = _instructions[_userfuncs[arg->val].address].aline;

      //assert(0);
      return reg;
    }

    case libfunc_a: {
      reg->type =  libfunc_vm;
      if(debug)cout<<" Edw des ligo prin skasei"<<arg->val<<endl;
      reg->data.libfuncVal =  strdup(libfuncs_getused(arg->val).c_str());

      return reg;

    }

    case realval_a: {
      reg->type = real_vm;
      reg->data.realval = consts_getdouble(arg->val);
      return reg;
    }
    if(regdebug)cout<<" assert of avm_translate_operand"<<endl;
    default: assert(0);
  }

}



string consts_getstring(unsigned index)
{
  if(index >=  totalStrings)
  {
    cout<<"ERROR cannot get const string"<<endl;
    executionFinished=1;
  }
  if(index < totalStrings)
  {
    string r = _strings[index];
    return r;
  }
  
}

int consts_getnumber(unsigned index){
  if(index >= totalNumbers){
    cout << "ERROR cannot get const number" << endl;
    executionFinished = 1;
  }
  if(index < totalNumbers){
    int r;
    r = _numbers[index];
    return r;
  }
}

double consts_getdouble(unsigned index){
  if(index >= totalDoubles){
    cout << "ERROR cannot get const bool" << endl;
    executionFinished = 1;
  }
  if(index < totalDoubles){
    double r;
    r = _doubles[index];
    return r;
  }
}

string libfuncs_getused(unsigned index)
{
  if(index >= totalLibfuncs)
  {
    cout<<"ERROR cannot get used libfuncs "<<endl;
    executionFinished=1;
    return "";
  }
  if(index<totalLibfuncs)
  {
    string r = _libfuncs[index];
    return r;
  }
  

}

string printInstrcode(vmopcode op){
    switch(op){

    case 0: return "assign_vm";
        break;
    case 1: return "add_vm";
        break;
    case 2: return "sub_vm";
        break;
    case 3:return "mul_vm";
        break;
    case 4: return "divide_vm";
        break;
    case 5: return "mod_vm" ;
        break;
    case 6:return "uminus_vm" ;
        break;
    case 7: return "and_op_vm";
        break;
    case 8: return "or_op_vm";
        break;
    case 9:return "not_op_vm";
        break;
    case 10:  return "jeq_vm";
        break;
    case 11:  return "jne_vm";
        break;
    case 12:return "jle_vm";
        break;
    case 13:  return "jge_vm";
        break;
    case 14:  return "jlt_vm";
        break;
    case 15:return "jgt_vm";
        break;
    case 16:  return "call_vm";
        break;
    case 17:  return "param_vm";
        break;
    case 18:return "ret_vm";
        break;
    case 19:  return "getretval_vm";
        break;
    case 20:  return "enterfunc_vm";
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
void printINstr(void) {
    outfile << "////-----------------------------INSTR PRINTS----------------------------------------------////" << endl;
    int it;
    int i=0;
    for(it=0; it<totalCode; it++){
        outfile<<i<<": ";
        outfile<<" |" << "OPCODE :"<<printInstrcode(_instructions[it].opcode);
        outfile<<"  " << "RESULT :"<<(_instructions[it].result).type<< " | "<< (_instructions[it].result).val;
      outfile<<"  " << "ARG1 :"<<(_instructions[it].arg1).type << " | "<< (_instructions[it].arg1).val;
        outfile<<"  " << "ARG2 :"<<(_instructions[it].arg2).type<< " | " << (_instructions[it].arg2).val;
        outfile << endl;
        i++;
        
      }
  outfile << "////---------------------------------------------------------------------------------------////" << endl;
}