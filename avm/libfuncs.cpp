#include "avm.h"
#include <cmath>
#include <cerrno>
#include <cfenv>

const double pi = 3.14159265/180 ;
bool is_table=false;

vector<string> stringTypes={"number","number","string"
,"bool","table","userfunc","libfunc","nil","undef"};
//=========libfuncs_tools===============================/
library_func_t avm_getlibraryfunc(string funcName){
	
	switch (libhash(funcName)){

		case 145: 	return libfunc_print;
		case 148:	return libfunc_input;
		case 55 :	return libfunc_tableindices;
		case 162: 	return libfunc_tablelength;
		case 155 :	return libfunc_tablecopy;
		case 144 :	return libfunc_totalarguments;
		case 51:	return libfunc_argument;
		case 45:	return libfunc_typeof;
		case 92:	return libfunc_strtonum;
		case 42:	return libfunc_sqrt;
		case 117:	return libfunc_cos;
		case 122:	return libfunc_sin; 
		default:	return NULL;

	}
}

int libhash (string word)   
{       int sum = 0;
        for (int k = 0; k < word.length(); k++)
            sum = sum + int(word[k])+k;
        return  sum % AVM_TABLE_HASHSIZE; 
}

//=======================================================/





//================libfunc_input==========================/

void libfunc_input(void){
	string temp ;
	
	getline(cin,temp)	;

	InputType(temp);
	
}

void InputType(string s){
		int found 	= 0;
		int dot 	= 0;
		string tofind= s;
		char * 	input = strdup(s.c_str());

		if(s.compare("true")==0){
			if(debug)cout << "to input htan bool true "<<endl;
			retval.type= bool_vm;
			retval.data.boolVal= 1;
			return;
		}else if(s.compare("false")==0){
						if(debug)cout << "to input htan bool false "<<endl;

			retval.type= bool_vm;
			retval.data.boolVal= 0;
			return;

		}else if(s.compare("nil")==0){
			retval.type = nil_vm;
		}else if((s.at(0)=='"') && (s.at(s.size()-1)=='"')){
						if(debug)cout << "to input htan string true "<<endl;
			s.erase(0,1);
			s.erase(s.size()-1,-2);
			input = strdup(s.c_str());
			retval.type= string_vm;
			retval.data.strVal = input;
			return;
		}else{

			for(int i=0;i<s.size(); i++){
				if(s.at(i)=='.'){
					dot		= 1;
					continue;
				}else if(isalpha(s.at(i))){
					found	= 1;
					break;
				}
			}

		}
		if(dot == 1 && found == 0){
			if(debug)cout << "to input htan number real "<<endl;
			retval.type = real_vm;
			retval.data.realval= strtod(input,NULL);
			return;
			//return 1;
		}else if(dot==0 && found == 0 ){
			if(debug)cout << "einai int! !!!!!!!!!!!1"<<endl;
			retval.type= integer_vm;
			retval.data.intval= atoi(input);
			return;
			//cout<<"Perasa sto intval toy retval to "<<retval.data.intval<<endl;	
			//return 0;				
		}else if(found == 1){
			
			retval.type= string_vm;
			retval.data.strVal = input;
			return;
		}


}

//=================libfunc_cos==========================/
bool testcos=false;
void libfunc_cos(void){
	//Error checking
	unsigned z = avm_totalactuals();
	if(z!=1){
		cout<<"ERROR: trying to call lib func with more that one arguments !"<<endl;
		executionFinished=1;
		return;
	}
	
	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);
	double input;
	if(temp->type==integer_vm){
		input = cos(temp->data.intval*pi);
		if(testcos){cout<< "typwnw to type k to intval! "<<temp->type<<" "<<temp->data.intval<<endl;
				cout << " edw typwnw to apotelesma ths cos "<<input<<endl;}
	}else if(temp->type==real_vm){
		input = cos(temp->data.realval*pi);
		if(testcos){cout<< "Typwnw to type k to realval ! "<<temp->type<<" "<<temp->data.realval<<endl;
				cout << "edw typwnw to apotelesma ths cos "<<input<<endl;}
	}
	avm_memcellclear(&retval);
	retval.type = real_vm;
	retval.data.realval =input;

}



//=================libfunc_sin========================/
void libfunc_sin(void){
	//Error checking
	unsigned z = avm_totalactuals();
	if(z!=1){
		cout<<"ERROR: trying to call lib func with more that one arguments !"<<endl;
		executionFinished=1;
		return;
	}
	//===
	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);
	double input;
	if(temp->type==integer_vm){
		double d = ((double)temp->data.intval);
		input = sin(d*pi);
		if(debug){cout<< "typwnw to type k to intval! "<<temp->type<<" "<<temp->data.intval<<endl;
				cout << " edw typwnw to apotelesma ths sin " <<input<<endl;}
	}else if(temp->type==real_vm){
		input = sin(temp->data.realval*pi);
		if(debug){cout<< "Typwnw to type k to realval ! "<<temp->type<<" "<<temp->data.realval<<endl;
				cout << "edw typwnw to apotelesma ths sin " <<input<<endl;}
	}
	avm_memcellclear(&retval);
	retval.type = real_vm;
	retval.data.realval =input;


}
//============libfunc_sqrt===========================/
void libfunc_sqrt(void){
	//Error checking
	unsigned z = avm_totalactuals();
	if(z!=1){
		cout<<"ERROR: trying to call lib func with more that one arguments !"<<endl;
		executionFinished=1;
		return;
	}
	//===
	avm_memcellclear(&retval);
	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);
	double input=1;
	if(temp->type==integer_vm){
		input = sqrt(temp->data.intval);
		if(input!=sqrt(temp->data.intval)) retval.type=nil_vm;
		else input=sqrt(temp->data.intval);
		if(debug)cout<< "typwnw to type k to intval! "<<temp->type<<" "<<temp->data.intval<<endl;
		if(debug)cout << " edw typwnw to apotelesma ths sqrt " <<input<<endl;
	}else if(temp->type==real_vm){
		input = sqrt(temp->data.realval);
		if(debug)cout<< "Typwnw to type k to realval ! "<<temp->type<<" "<<temp->data.realval<<endl;
		if(debug)cout << "edw typwnw to apotelesma ths sqrt " <<input<<endl;
	}
	;
	if(retval.type==nil_vm)return;
	retval.type = real_vm;
	retval.data.realval =input;
	//if




}
//=============libfunc_typeof==============================/
void libfunc_typeof(void){
	//Error checking
	unsigned z = avm_totalactuals();
	if(z!=1){
		cout<<"ERROR: trying to call lib func with more that one arguments !"<<endl;
		executionFinished=1;
		return;
	}
	//===
	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);
	avm_memcellclear(&retval);
	retval.type = string_vm;
	retval.data.strVal =strdup(stringTypes[temp->type].c_str());
	if(debug)cout << "Returning type to string "<<retval.data.strVal<<endl;

}

//==================libfunc_strtonum=================================/
void libfunc_strtonum(void){
	//Error checking
	unsigned z = avm_totalactuals();
	avm_memcell *temp1 = new avm_memcell;
	if(z!=1){
		cout<<"ERROR: trying to call lib func with more that one arguments !"<<endl;
		executionFinished=1;
		return;
	}
	//===
	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);

	if(temp->type!=string_vm){
		cout<<"ERROR :Not string in strtonum"<<endl;
		executionFinished=1;
		return;

	}

	//avm_memcellclear(&retval);
	string tofind= temp->data.strVal;
	for(int i=0 ; i<tofind.size();i++){
		if(isalpha(tofind.at(i))){
			if(debug)cout<<"evala nil"<<endl;
			retval.type =nil_vm;
			return;
		}
	}
	if(tofind.find(".")!= string::npos){
		
		retval.type= real_vm;
		retval.data.realval= strtod(temp->data.strVal,NULL);
		
	}else{
		
		retval.type= integer_vm;
		retval.data.intval= atoi(temp->data.strVal);

	}

	


}
//=============libfunc_totalarguments============================/


void libfunc_totalarguments(void){
	
	if(debug)cout<<topsp<<endl;
	if(debug)cout<<top<<endl;
	unsigned zt = stack[AVM_FROM_TOTALARGUMENTS].data.intval;	
	if(regdebug)
	{cout<<" in total: "<<stack[topsp+4].data.intval<<" "<<stack[topsp+3].data.intval<<"  "<<stack[topsp+2].data.intval<<" "<<stack[topsp+5].data.intval<<endl;
		cout<<" "<<stack[topsp+1].data.intval<<" "<<stack[stack[topsp+1].data.intval+4].data.intval<<endl;
		cout<<" "<<stack[topsp+1].data.intval<<endl;
	}

	if(debug)cout<<zt<<endl;
	if(!zt){

		retval.type=nil_vm;
		return;

	}

	retval.type=integer_vm;
	retval.data.intval=zt;
	if(debug)cout<<"Total arguments "<<retval.data.intval<<endl;

}

//=================libfunc_argument=============================================/

void libfunc_argument(void){
	unsigned mpop = avm_totalactuals();
	unsigned Top_temp = avm_get_envvalue(topsp+AVM_SAVEDTOP_OFFSET);
	unsigned Topsp_temp = avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	unsigned Pc_temp = avm_get_envvalue(topsp+AVM_SAVEDPC_OFFSET);

	if(debug){
		cout<<"avm_totalactuals ! ! ! ! ! ! !  "<<Topsp_temp<<" "<<Top_temp<<" "<<Pc_temp<<endl;
		cout<<"Topsp ! ! ! ! ! ! !  "<<top<<endl;
		cout<<"Top   ! ! ! ! ! ! !  "<<topsp<<endl;
		
		cout << " Dwse pono "<<stack[stack[topsp+2].data.intval].data.intval<<endl;
		cout << " Dwse pono "<<stack[stack[topsp+2].data.intval-3].data.intval<<endl;
	}
	unsigned zt = stack[AVM_FROM_TOTALARGUMENTS].data.intval;	//n
	avm_memcell *temp = new avm_memcell;
	temp = &stack[AVM_FROM_TOTALARGUMENTS];

	if(!temp->data.intval){
		
		avm_memcell * tremp = new avm_memcell;
		tremp->type = nil_vm;
		avm_assign(&retval,tremp);
		return;

	}else if(temp->data.intval > zt){

		cout<<"ERROR: Index out of bounds. "<<endl;
		executionFinished=1;
		return;

	}else{
		temp = avm_getactual(0);
		
		if(debug){cout<<"Argument "<<temp->data.intval <<" val : "<< stack[AVM_FROM_TOTALARGUMENTS + temp->data.intval+1].data.intval
	
			<<" type "<<stack[AVM_FROM_TOTALARGUMENTS + temp->data.intval].type<<endl;}


		avm_assign(&retval,&stack[AVM_FROM_TOTALARGUMENTS + temp->data.intval+1]);
	}
	if(debug)findef();

	



}

//---------------------------------------- table libfuncs -------------------------------------------------//



//==================libfunc_tablelength======================================/

void libfunc_tablelength(void){
	
	if(debug)cout<<"tablelength"<<endl;
	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);
	if(debug)cout<<"tablelength"<<temp->data.tableVal->total<<endl;
	retval.type = integer_vm;
	retval.data.intval=(int)tablelength(temp);

}

//=========================================================================/

//================tablelength==============================================/

unsigned int tablelength(avm_memcell *t){
	return t->data.tableVal->total;
}
//=========================================================================/

//==============libfunc_tableindices=======================================/

void libfunc_tableindices(void){
	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);
	avm_memcellclear(&retval);
	avm_assign(&retval,tableindices(temp));
}

avm_memcell* tableindices(avm_memcell *t){

	avm_table * newtab = new avm_table;	
	avm_memcell *  temp = new avm_memcell;
	temp->type = table_vm;
	temp->data.tableVal= newtab;
	temp->data.tableVal->strIndexed.resize(AVM_TABLE_HASHSIZE) ;
	temp->data.tableVal->numIndexed.resize(AVM_TABLE_HASHSIZE) ;
	if(debug)cout << "EKANA NEW TABLE " << endl;

	if(debug)cout<<" increase refcounter in tableindices"<<endl;
	avm_tableincrefcounter(temp->data.tableVal);
	unsigned int i = 0;

	for(int j = 0;j<t->data.tableVal->numIndexed.size();j++){
			 
			
			if(t->data.tableVal->numIndexed[j].key.type != undef_vm){
				
				avm_memcell*indx = new avm_memcell;
				indx->type = integer_vm;
				indx->data.intval = i;	
				
				avm_assign(&temp->data.tableVal->numIndexed[i].key,indx);
				avm_assign(&temp->data.tableVal->numIndexed[i].value,&t->data.tableVal->numIndexed[j].key);
				i++;
			}
			
			
	}
	for(int j = 0;j<t->data.tableVal->strIndexed.size();j++){
			 
			
			if(t->data.tableVal->strIndexed[j].key.type != undef_vm){
				
				avm_memcell*indx = new avm_memcell;
				indx->type = integer_vm;
				indx->data.intval = i;	
				
				avm_assign(&temp->data.tableVal->numIndexed[i].key,indx);
				avm_assign(&temp->data.tableVal->numIndexed[i].value,&t->data.tableVal->strIndexed[j].key);
				
				i++;
			}
			
			
	}
	if(t->data.tableVal->totals.userfunctotal){
		for(int j = 0;j<t->data.tableVal->userIndexed.size();j++){
			 
			
			if(t->data.tableVal->userIndexed[j].key.type != undef_vm){
				
				avm_memcell*indx = new avm_memcell;
				indx->type = integer_vm;
				indx->data.intval = i;	

				avm_assign(&temp->data.tableVal->numIndexed[i].key,indx);
				avm_assign(&temp->data.tableVal->numIndexed[i].value,&t->data.tableVal->userIndexed[j].key);

				i++;
			}

			
		}

	}
	if(t->data.tableVal->totals.libfunctotal){
		for(int j = 0;j<t->data.tableVal->libIndexed.size();j++){
			 
			
			if(t->data.tableVal->libIndexed[j].key.type != undef_vm){
				if(t->data.tableVal->libIndexed[j].value.type == undef_vm){
					continue;
				}
				avm_memcell*indx = new avm_memcell;
				indx->type = integer_vm;
				indx->data.intval = i;	
				avm_assign(&temp->data.tableVal->numIndexed[i].key,indx);
				avm_assign(&temp->data.tableVal->numIndexed[i].value,&t->data.tableVal->libIndexed[j].key);
				i++;
			}
			
		}
	}

	if(t->data.tableVal->totals.booltotal){
		for(int j = 0;j<t->data.tableVal->boolIndexed.size();j++){
			 
			
			if(t->data.tableVal->boolIndexed[j].key.type != undef_vm){
				if(t->data.tableVal->boolIndexed[j].value.type == undef_vm){
					continue;
				}
				avm_memcell*indx = new avm_memcell;
				indx->type = integer_vm;
				indx->data.intval = i;	
				avm_assign(&temp->data.tableVal->numIndexed[i].key,indx);
				avm_assign(&temp->data.tableVal->numIndexed[i].value,&t->data.tableVal->boolIndexed[j].key);
				i++;
			}
			
		}
	}

	temp->data.tableVal->total=t->data.tableVal->total;
	temp->data.tableVal->totals.numtotal = t->data.tableVal->totals.numtotal;
	return temp;

}
//================libfunc_tablecopy==================================/

void libfunc_tablecopy(void){

	avm_memcell *temp = new avm_memcell;
	temp = avm_getactual(0);	
	avm_memcellclear(&retval);
	avm_assign(&retval,tablecopy(temp));	
	
}

avm_memcell* tablecopy(avm_memcell *t){


	avm_table * newtab = new avm_table;	
	avm_memcell *  temp = new avm_memcell;
	temp->type = table_vm;
	temp->data.tableVal= newtab;
	temp->data.tableVal->strIndexed.resize(AVM_TABLE_HASHSIZE);//(AVM_TABLE_HASHSIZE); //= new vector<avm_table_bucket>(AVM_TABLE_HASHSIZE);
	temp->data.tableVal->numIndexed.resize(AVM_TABLE_HASHSIZE);//(AVM_TABLE_HASHSIZE);// = new vector<avm_table_bucket>(AVM_TABLE_HASHSIZE);

	if(debug)cout<<" increase refcounter in tablecopy"<<endl;
	avm_tableincrefcounter(temp->data.tableVal);
	unsigned int intind=0;
	unsigned int strind=0;
	unsigned int i=0;
	bool strindex=true;
	bool intindex=true;
	for(;i<AVM_TABLE_HASHSIZE;i++){
		
		copy_bucket(temp->data.tableVal->numIndexed[i],t->data.tableVal->numIndexed[i]);
		
		if(intindex){
			if(intind==t->data.tableVal->totals.numtotal)intindex=false;
			else if(intindex){
				copy_bucket(temp->data.tableVal->numIndexed[i],t->data.tableVal->numIndexed[i]);
				intind++;
			}
		}
		if(strindex){
			if(t->data.tableVal->strIndexed[i].key.type==undef_vm)	strindex=false;
			else if(strindex){	
			copy_bucket(temp->data.tableVal->strIndexed[i],t->data.tableVal->strIndexed[i]);
			strind++;
			}
		}
		if(!strindex && !intindex)break;
	}
		
	passtotals(temp,t);
	return temp;
}

void passtotals(avm_memcell *to,avm_memcell *from) {

		to->data.tableVal->total=from->data.tableVal->total;
		to->data.tableVal->totals.numtotal=from->data.tableVal->totals.numtotal;
		to->data.tableVal->totals.strtotal=from->data.tableVal->totals.strtotal;

}


void copy_bucket( avm_table_bucket &bucket_new, avm_table_bucket& bucket_old  ){
		
		avm_assign(&bucket_new.key,&bucket_old.key);
		avm_assign(&bucket_new.value,&bucket_old.value);
		if (bucket_new.value.type==table_vm) {
			if(debug)cout<<"increase refcounter in bucket"<<endl;
			avm_tableincrefcounter(bucket_new.value.data.tableVal);
		}
}

//========================libfunc_print================================/

tostring_func_t tostringFuncs[] = {
	int_tostring,
	real_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};



void libfunc_print(void)
{
    unsigned n = avm_totalactuals();
    unsigned i;
    for(i=0;i<n;i++)
    {
      string s = avm_tostring(avm_getactual(i));
     	avm_memcell_t type= avm_getactual(i)->type;
		if(type!=table_vm){
			if (type==real_vm) cout<< std::fixed << s;
			else cout<<s;
		}
	}
	if(regdebug)cout<<endl;
}


string avm_tostring(avm_memcell* m){
	return (*tostringFuncs[m->type])(m);
}
string int_tostring(avm_memcell* m){
	return to_string(m->data.intval);
}

bool testcos2=false;
string real_tostring(avm_memcell* m){
	
	std::stringstream ss;
	ss <<  std::setprecision(10)<< m->data.realval;
	std::string s = ss.str();


	return s;
}

string string_tostring(avm_memcell* m){ 

        return strdup(m->data.strVal);
}

string bool_tostring(avm_memcell* m){

	if(m->data.boolVal == 1){
		return "true";
	}
	else{
		return "false";
	}
}

string table_tostring(avm_memcell* m){
	assert(m->type == table_vm);

	t2string(m->data.tableVal);
	if(debug)if(regdebug)cout<<m->data.tableVal->refCounter<<endl;
	if(debug)findef();		
	return "";
}

string userfunc_tostring(avm_memcell* m){
	assert(m->type == userfunc_vm);

	string ret = "(userfunc)"+ string(m->namef) +"("+to_string(m->funcoffset)+")";
	return ret;
}

string libfunc_tostring(avm_memcell* m){

	string ret = "(libfunc)"+ string(m->data.libfuncVal) ;
	return ret;
}


string nil_tostring(avm_memcell* m){
	return "nil";
}

string undef_tostring(avm_memcell* m){
        return "undefined.";
}