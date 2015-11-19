#include "avm.h"



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