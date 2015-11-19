#include "avm.h"
extern vector <string> _libfuncs;
extern unsigned int totalLibfuncs;



unsigned changed =0;

void avm_tableincrefcounter(avm_table* t){
  ++t->refCounter;
if(debug)cout<<" anevasa twra :"<<t->refCounter<<" se pc :"<<pc<<endl;  
}

void avm_tabledecrefcounter(avm_table* t){
  assert(t->refCounter >0);
  if(debug)cout<<" katevasa twra :"<<t->refCounter<<" se pc :"<<pc<<endl; 
  if(!--t->refCounter)
    avm_tabledestroy(t);
}
void memclear_table(avm_memcell* m){
  assert(m->data.tableVal);
  avm_tabledecrefcounter(m->data.tableVal);
}

void avm_tabledestroy(avm_table* t)
{
  avm_tablebucketsdestroy(t->strIndexed);
  avm_tablebucketsdestroy(t->numIndexed);
  delete(t);
}

void avm_tablebucketsdestroy(vector<avm_table_bucket> table){
  unsigned i;
    for (;i<table.size();i++){
    	avm_memcellclear(&table[i].key);
     	avm_memcellclear(&table[i].value);
     	
    }

 }	


void execute_newtable (instruction* instr1){
	if(regdebug)cout<< "In new table "<<endl;
	avm_table * newtab = new avm_table;	
	avm_memcell *  temp = avm_translate_operand(&instr1->result,(avm_memcell*)0);
	temp->type = table_vm;
	temp->data.tableVal= newtab;
	temp->data.tableVal->strIndexed.resize(AVM_TABLE_HASHSIZE); //= new vector<avm_table_bucket>(AVM_TABLE_HASHSIZE);
	temp->data.tableVal->numIndexed.resize(AVM_TABLE_HASHSIZE);//new vector<avm_table_bucket>(AVM_TABLE_HASHSIZE);
	temp->data.tableVal->boolIndexed.resize(2);
	temp->data.tableVal->nilIndexed.resize(1);
	libIndexed_set(temp->data.tableVal->libIndexed);
	userIndexed_set(temp->data.tableVal->userIndexed);
	if(debug)cout << " !!!!!!!!!!!!!!!!!! "<< temp->data.tableVal->boolIndexed.size()<<endl;
	if(debug)cout << "EKANA NEW TABLE " << endl;
	if(debug)cout<<"ref newtable before: "<<temp->data.tableVal->refCounter<<endl;
	avm_tableincrefcounter(temp->data.tableVal);
	if(debug)cout<<"ref newtable before: "<<temp->data.tableVal->refCounter<<endl;



}


void  execute_tablegetelem(instruction* instr1){

	avm_memcell* lv = avm_translate_operand(&instr1->result, (avm_memcell*) 0);
	avm_memcell* tab = avm_translate_operand(&instr1->arg1, (avm_memcell*) 0);
	avm_memcell* indx = avm_translate_operand(&instr1->arg2, &ax);

	if(tab->type!=table_vm){
		cout << "Error trying to get element from non-table "<<endl;
		executionFinished = 1;
		return;
	}
	if(indx->data.intval < 0){
					cout <<"Error : Trying to access  table with negative index! "<<endl;
					executionFinished=1;
					return	;
	}


	if(indx->type == integer_vm){
		
		int index = indx->data.intval%AVM_TABLE_HASHSIZE;
		if(&tab->data.tableVal->numIndexed[index]==NULL){
			cout << "Empty table index"<<endl;
			executionFinished = 1;
		}
		avm_assign(lv,&tab->data.tableVal->numIndexed[index].value);
			
	}else if (indx->type == string_vm){
		

		avm_table_bucket* bucket = new avm_table_bucket;


		avm_assign(&bucket->key,indx);

		avm_memcell * temp = stringIndex_lookup(tab->data.tableVal->strIndexed,*bucket,getme);

		if(temp)avm_assign(lv,temp);
		
		else {
			avm_memcell* tremp = new avm_memcell;
			tremp->type = nil_vm;

			avm_assign(lv,tremp);
			cout<<"Warning : table index might be nil."<<endl;
		}


	}else if (indx->type == bool_vm){
		if((int)indx->data.boolVal==1){
			avm_assign(lv,&tab->data.tableVal->boolIndexed[0].value);
		}else{
			avm_assign(lv,&tab->data.tableVal->boolIndexed[1].value);
		}
		
	}else if (indx->type == libfunc_vm){
		
		int indexed = libfunc_lookup(indx->data.libfuncVal,tab->data.tableVal->libIndexed);
		avm_assign(lv,&tab->data.tableVal->libIndexed[indexed].value);
		if(debug)cout <<" In libIndexed get elem "<<indx->data.libfuncVal<<endl;
		
	}else if (indx->type == userfunc_vm){
		
		int indexed = userfunc_lookup(indx->namef,indx->data.funcVal,tab->data.tableVal->userIndexed);
		if(debug){cout <<" In libIndexed get elem "<<indx->namef<<" "<<indx->data.funcVal<<endl;}
		avm_assign(lv,&tab->data.tableVal->userIndexed[indexed].value);
		
		
	}
	else{
		cout << "Error: in table !"<<endl;
		executionFinished=1;
	}


}


void execute_tablesetelem(instruction* instr1){
	avm_memcell * table = avm_translate_operand(&instr1->arg1,(avm_memcell*)0);
	avm_memcell * indx = avm_translate_operand(&instr1->arg2,&ax);
	avm_memcell * content = avm_translate_operand(&instr1->result,&bx);


	if(table->type!=table_vm){
		cout << "Error set elem at no table operand"<<endl;
		executionFinished = 1;
		return;
	}

	if(debug)cout<<"in set elem one "<<table->type<<endl;

	switch ( indx->type){
		case integer_vm:{
				if(regdebug)cout<<"set int"<<endl;
				

				if(indx->data.intval >=AVM_TABLE_HASHSIZE ) 
					table->data.tableVal->numIndexed.resize(AVM_TABLE_HASHSIZE);
				if(indx->data.intval < 0){
					cout <<"Error : Trying to set  table with negative index! "<<endl;
					executionFinished=1;
					break;
				}
				int index = indx->data.intval%AVM_TABLE_HASHSIZE;

				if(table->data.tableVal->numIndexed[index].value.type==undef_vm)
					table->data.tableVal->totals.numtotal++;
				if(content->type == nil_vm){
					if(debug)cout<<" Edwses  = nil_vm"<<endl;
					avm_memcell * tremp = new avm_memcell;
					tremp->type = undef_vm;
					avm_assign(&table->data.tableVal->numIndexed[index].key,tremp);
					table->data.tableVal->totals.numtotal--;
					break;
				}
				avm_assign(&table->data.tableVal->numIndexed[index].key,indx);
				avm_assign(&table->data.tableVal->numIndexed[index].value,content);


				break;


		}
		case string_vm:{
			
				if(regdebug)cout<<"set str"<<endl;
				avm_table_bucket* bucket = new avm_table_bucket;
				

				avm_assign(&bucket->key,indx);
				avm_assign(&bucket->value,content);
				stringIndex_lookup(table->data.tableVal->strIndexed,*bucket,setme);



				if(regdebug)cout<<"mutH........................................................>"<<changed<<endl;
				table->data.tableVal->totals.strtotal+=changed;
				changed=0;
				break;

		}
		case bool_vm:{
				if(debug)cout<<"bool vall assign "<<indx->type<<endl;
				if(debug)cout<<"bool vall assign "<<(int)indx->data.boolVal<<endl;

				if((int)indx->data.boolVal == 0){
					if(regdebug)cout << " Assign false bool val"<<endl;
					avm_assign(&table->data.tableVal->boolIndexed[1].key,indx);

					if(content->type == nil_vm){
						if(debug)cout<<" Edwses  = nil_vm"<<endl;
						avm_memcell * tremp = new avm_memcell;
						tremp->type = undef_vm;
						avm_assign(&table->data.tableVal->boolIndexed[1].value,tremp);

						if(table->data.tableVal->totals.booltotal >0)
							table->data.tableVal->totals.booltotal--;
						break;
					}

					avm_assign(&table->data.tableVal->boolIndexed[1].value,content);
					if(table->data.tableVal->totals.booltotal <2)
						table->data.tableVal->totals.booltotal++;
				}else{
					avm_assign(&table->data.tableVal->boolIndexed[0].key,indx);

					if(content->type == nil_vm){
						if(debug)cout<<" Edwses  = nil_vm"<<endl;
						avm_memcell * tremp = new avm_memcell;
						tremp->type = undef_vm;
						avm_assign(&table->data.tableVal->boolIndexed[0].value,tremp);

						if(table->data.tableVal->totals.booltotal >0)
							table->data.tableVal->totals.booltotal--;
						break;
					}


					avm_assign(&table->data.tableVal->boolIndexed[0].value,content);
					if(regdebug)cout << " Assign true bool val"<<endl;
					if(table->data.tableVal->totals.booltotal <2)
						table->data.tableVal->totals.booltotal++;

				}	
				
				break;
		}
		case nil_vm:{

			//NIL INDEXED!!!!!!!!!!!!!!!//

			/*avm_assign(&table->data.tableVal->nilIndexed[0].key,indx);
			avm_assign(&table->data.tableVal->nilIndexed[0].value,content);
			if(table->data.tableVal->totals.niltotal == 0){
				
				table->data.tableVal->totals.niltotal++;
			}
			*/
			cout<< "Error : Trying to use nil as index . "<<endl;
			executionFinished=1;
			break;
		}
		case libfunc_vm:{
			if(debug)cout <<" In libIndexed get elem "<<indx->data.libfuncVal<<endl;
			int indexed = libfunc_lookup(indx->data.libfuncVal,table->data.tableVal->libIndexed);
			if(content->type == nil_vm){
						if(debug)cout<<" Edwses  = nil_vm"<<endl;
						avm_memcell * tremp = new avm_memcell;
						tremp->type = undef_vm;
						avm_assign(&table->data.tableVal->libIndexed[indexed].value,tremp);
						//avm_assign(&table->data.tableVal->numIndexed[index].key,(avm_memcell*)0);
						if(table->data.tableVal->totals.libfunctotal >0)
							table->data.tableVal->totals.libfunctotal--;
						break;
			}
			if(table->data.tableVal->libIndexed[indexed].value.type == undef_vm){
				table->data.tableVal->totals.libfunctotal++;
			}
			avm_assign(&table->data.tableVal->libIndexed[indexed].value,content);
			

			if(debug)cout<<"xax xa "<<endl;
			break;
		}
		case userfunc_vm:{
			int indexed = userfunc_lookup(indx->namef,indx->data.funcVal,table->data.tableVal->userIndexed);
			if(debug){cout << " in userfunc set"<<indexed<<":"/*<<table->data.tableVal->totals.userfunctotal*/<<endl;
								cout <<" In libIndexed set elem "<<indx->namef<<" "<<indx->data.funcVal<<endl;}
					if(content->type == nil_vm){
						if(debug)cout<<" Edwses  = nil_vm"<<endl;
						avm_memcell * tremp = new avm_memcell;
						tremp->type = undef_vm;
						avm_assign(&table->data.tableVal->userIndexed[indexed].value,tremp);
						//avm_assign(&table->data.tableVal->numIndexed[index].key,(avm_memcell*)0);
						if(table->data.tableVal->totals.userfunctotal >0)
							table->data.tableVal->totals.userfunctotal--;
						break;
					}

			if(table->data.tableVal->userIndexed[indexed].value.type == undef_vm){
				table->data.tableVal->totals.userfunctotal++;
			}
			avm_assign(&table->data.tableVal->userIndexed[indexed].value,content);
			
			
			break;

		}
		default :{
			cout << "Error: trying to get non existat index !"<<endl;
			executionFinished=1;
			break;
		}
	}
	table->data.tableVal->total = table->data.tableVal->totals.numtotal + table->data.tableVal->totals.strtotal
	+table->data.tableVal->totals.booltotal+table->data.tableVal->totals.niltotal+table->data.tableVal->totals.libfunctotal
	+table->data.tableVal->totals.userfunctotal;

}	


int hashf (const char * s){
	int i;
	int mpla=0;
	while(s[i]!= '\0'){
		i++;
		mpla += 32* (int)s[i] +21;
	}
	return mpla % AVM_TABLE_HASHSIZE;
}

 avm_memcell* stringIndex_lookup	(  vector<avm_table_bucket> &table,avm_table_bucket bucket, mode_type mode ){

	int i=0;
	for (;i<table.size();i++){
		if(table[i].key.type!= undef_vm){

			if (!strcmp(table[i].key.data.strVal,bucket.key.data.strVal)){
				if(mode){
					if(bucket.value.type == nil_vm){
					
						if(debug)cout<<"We are getting somewhere here"<<endl;
						avm_memcell * tremp = new avm_memcell;
						tremp->type = undef_vm;
						avm_assign(&table[i].key,tremp);
						avm_assign(&table[i].value,tremp);	
						
						changed--;
					}
					avm_assign(&table[i].value,&bucket.value);
				}
				return &table[i].value;
			}
		}
		else {
			if(!mode)return NULL;
			changed++;
						
			avm_assign(&table[i].value,&bucket.value);
			avm_assign(&table[i].key,&bucket.key);

			return &table[i].value;

		}

	}
	if(!mode)return NULL;
	changed++;
	table.resize(AVM_TABLE_HASHSIZE);
	avm_assign(&table[i].value,&bucket.value);
	avm_assign(&table[i].key,&bucket.key);

	return &table[i].value;
}

void t2string(avm_table* m){

	unsigned int indexed =0;
	unsigned int printed= 0;
	cout<< "(Table("<< m<<"))";

	cout << "[";
	if(m->totals.strtotal!=0){
		for (int i=0;i<m->strIndexed.size();i++){
			if(m->strIndexed[i].key.type==undef_vm)continue;
			if(i > 0 && printed >0)cout<<",";
			printed++;				
			cout << "{\""; 
			cout<<avm_tostring(&(m->strIndexed[i].key)); 
			cout<<"\": ";
			if(m->strIndexed[i].value.type!=table_vm){
				cout << avm_tostring(&(m->strIndexed[i].value));
			}else{
			
			if(m->strIndexed[i].value.data.tableVal==m) cout << "self";
			else cout <<avm_tostring(&(m->strIndexed[i].value));
			
			}
			cout<<"}";
		}
		if (printed >0 && printed < m->total ){
			cout << ",";
		}
	}

	if(m->totals.numtotal!=0){
			unsigned indexed = 0;

			for (int j=0 ; j < m->numIndexed.size() ; j++){

				if((m->numIndexed[j].key.type==undef_vm)&& (j< m->totals.numtotal) || (m->totals.numtotal<m->total)){
					indexed = 1;
				}
			}
			if(indexed){
				int pin=0;
				
				for (int i=0;i<m->numIndexed.size();i++){
					if(m->numIndexed[i].key.type==undef_vm){ continue;}
					if (pin > 0 && pin < m->totals.numtotal){
						cout << ",";
					}
					cout << "{";
					
					cout<<avm_tostring(&(m->numIndexed[i].key));
					cout<< ":";
					
				if(m->numIndexed[i].value.data.tableVal==m) cout << "self";
				else cout<<avm_tostring(&(m->numIndexed[i].value));
					cout << "}";
					pin++;
				}
				
				printed = printed +pin;

			}else{
				int pin = 0;
				
				for (int i=0;i<m->numIndexed.size();i++){
					if(m->numIndexed[i].key.type==undef_vm){ continue;}

						if (pin > 0 && pin < m->totals.numtotal){
							cout << ",";
						}
						if(m->numIndexed[i].value.data.tableVal==m)cout << "self";
						else cout <<avm_tostring(&(m->numIndexed[i].value));

					pin++;
				}
				
				printed = printed +pin;
			}
			if (printed >1 && printed < m->total ){
				cout << ",";
			}	
		}
		
	
	if(debug)cout<<" prwto printed "<<printed<<endl;
	
	if(m->totals.booltotal!=0){
		
		if(m->boolIndexed[0].value.type!=undef_vm)
		{
			cout<<"{";
			cout << avm_tostring(&(m->boolIndexed[0].key));
			cout <<":";
			cout <<avm_tostring(&(m->boolIndexed[0].value));
			cout<<"}";	
			printed++;
		}
		if(m->totals.booltotal==2)cout<<",";
		if(m->boolIndexed[1].value.type!=undef_vm){

			cout<<"{";
			cout << avm_tostring(&(m->boolIndexed[1].key));
			cout <<":";
			cout <<avm_tostring(&(m->boolIndexed[1].value));
			cout<<"}";
			printed++;
		}
		if (printed >0 && printed < m->total /*&& m->totals.numtotal < printed*/ ){
			cout << ",";
		}
		
	}
	if(debug)cout<<" deutero printed "<<printed<<endl;

	if(m->totals.niltotal!=0){
		cout<<"{";
		cout << avm_tostring(&(m->nilIndexed[0].key));
		cout <<":";
		cout <<avm_tostring(&(m->nilIndexed[0].value));
		cout<<"}";
		printed++;
		if (printed >0 && printed < m->total /*&& m->totals.numtotal < printed*/ ){
			cout << ",";
		}
	}

	if(m->totals.libfunctotal!=0){
		int pin=0;
		if(debug)cout <<" Xa xax a "<<m->totals.libfunctotal<<endl;
		for(int i = 0;i<_libfuncs.size();i++){
			if(m->libIndexed[i].value.type!=undef_vm){
						cout<<"{";
						cout << avm_tostring(&(m->libIndexed[i].key));
						cout <<":";
						cout <<avm_tostring(&(m->libIndexed[i].value));
						cout<<"}";
						pin++;

						if (pin > 0 && pin < m->totals.libfunctotal){
							cout << ",";
						}
			}
			
			
		}
		printed=printed + pin;
		if (printed >0 && printed < m->total ){
				cout << ",";
		}

	}


	if(m->totals.userfunctotal!=0){
		int pin =0;
		for(int i=0;i<_userfuncs.size();i++){
			if(m->userIndexed[i].value.type!=undef_vm){
						cout<<"{";
						cout << avm_tostring(&(m->userIndexed[i].key));
						cout <<":";
						cout <<avm_tostring(&(m->userIndexed[i].value));
						cout<<"}";
						pin++;
						
			}
			if (pin > 1 && pin < m->totals.userfunctotal){
				cout << ",";
			}
		}
		printed =printed + pin;
		if (printed >0 && printed < m->total ){
				cout << ",";
		}
		
	}

	if(debug)cout<<" trito printed "<<printed<<endl;	

	cout << "]";
	
	printed=0;

	}

unsigned int libfunc_lookup(char * x,vector<avm_table_bucket> &table){
	
	if(debug)cout <<" look up ->"<<x<<endl;
	for(int i = 0 ; i <_libfuncs.size();i++){
		if(!strcmp(x,table[i].key.data.libfuncVal)){
			if(debug)cout<<"Brhka lib func "<<x<<" se index "<<i<<" "<<endl;
			return i;
		}
	}
}

void libIndexed_set(vector<avm_table_bucket> &table){
	table.resize(_libfuncs.size());
	avm_memcell *temp ;

	for(int i =0 ; i<_libfuncs.size();i++){
		temp= new avm_memcell;
		temp->type = libfunc_vm;
		temp->data.libfuncVal = strdup(_libfuncs[i].c_str());
		avm_assign(&table[i].key,temp);
	}
}

void userIndexed_set(vector<avm_table_bucket> &table){
	table.resize(_userfuncs.size());
	avm_memcell *temp ;
	
	for(int i =0 ; i<_userfuncs.size();i++){
		temp= new avm_memcell;
		temp->type = userfunc_vm;

		temp->data.funcVal = _userfuncs[i].address;
		temp->namef = strdup(_userfuncs[i].name.c_str());
		avm_assign(&table[i].key,temp);

	}
}


unsigned int userfunc_lookup(char * x,unsigned num,vector<avm_table_bucket> &table){
	 
	if(debug)cout <<" look up in user func ->"<<x<<" "<<num<<endl;
	for(int i = 0 ; i <_userfuncs.size();i++){

		if((!strcmp(x,table[i].key.namef)) && (table[i].key.data.funcVal == num)){
			if(debug)cout<<"Brhka lib func "<<x<<" se index "<<i<<" "<<endl;
			return i;
		}
	}
}