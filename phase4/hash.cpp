// unordered_multimap::begin/end example

#include "hash.h"
#include "intermediate.h"

//#ifndef "hash.h"
#pragma GCC diagnostic ignored "-Wreturn-type" //asto kiauto

/****************/
string blvr;
/****************/  


int f_prefix=0;//vvlk source !!!!!!!!!!!!! change
extern string defaultName;
extern list<int> assignParts;
extern list<string> functions;
extern std::ofstream outfile;

int lastFunctScope=0;// !!!!!!!!!!!!
//hash me sum twn ascii code / prime number 1009

bool  nameLookupFound;

//using now
extern int currentScope;
extern int Fscope;  //funcefs ++ --
extern bool fCall; // f();
extern bool fDef;  // F(){};
extern bool lval;
extern bool callMatched;  
extern int isLoop;
extern bool lvalfunc; 
extern int is_funcdef;
extern int is_call;
extern int yylineno;
extern int is_funcall;
extern int  lineF;
extern unsigned int  currQuad;
extern bool isValid;


 vector <vector<Symbol>>  Fscopelist;

 void ins_toScopeF(Symbol symbol,int scope){
  Fscopelist.resize(Fscopelist.size()+1);
  Fscopelist[scope].push_back(symbol);
};

vector < Symbol*>  templist;

bool  compareByscope(Symbol *sym1, Symbol *sym2)
{
    return sym1->scope < sym2->scope;
}

//

//

typedef unordered_multimap<int,Symbol> hashmap;
hashmap Syriza;

//extern unordered_multimap<int,Symbol> Syriza;

vector<vector<Symbol>> Scopelist;

list<string> libFuncList;


int hashme (string word)   
{       int sum = 0;
        for (int k = 0; k < word.length(); k++)
            sum = sum + int(word[k])+k;
        return  sum % HASH_SIZE; 
}


//check if name is libfunc name
Symbol * isLibFunct(Symbol toCheck){

  //list<string>::iterator myit = libFuncList.begin();
 // cout<<"PRWTO STOIXEIO LIBFUNC :"<<libFuncList.front()<<endl;
	for (list<string>::iterator it = libFuncList.begin(); it != libFuncList.end(); it++){
		if (it->compare(toCheck.name) == 0){
  //    cout<<" isLibFunct succeded :"<<toCheck.name<<endl;
      assignParts.push_back(LIBFUNC);
      //cout<<"vazw assingparts islibfunc "<<LIBFUNC<<endl;
      toCheck.type=LIBFUNC;
      Symbol * temp = new Symbol;
      //temp=&(toCheck);
      //cout << "edwsa libfunc" << endl;
      temp =fill4 (temp ,toCheck.name,toCheck.scope, toCheck.line, toCheck.nameF, toCheck.scopeF,toCheck.lineF,LIBFUNC, 1, toCheck.offset,toCheck.space, toCheck.dotalocal);
			return temp;
		}
	}
//cout<<" isLibFunct failed"<<endl;
return NULL;
}


Symbol* isAncestor(Symbol toCheck){
  bool found = false;
  Symbol max=fill(blvr,0,0,"RmB",-5,0,FUNC,true);
  Symbol *r;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          //cout<<" in ancestor SCOPE_F "<<x.second.scopeF<<" Type:"<<get_type(x.second.type)<<" active :"<<x.second.active<<" name: "<<x.second.name<<" line: "<<yylineno<<endl;
          if((x.second.scopeF < toCheck.scopeF)&&(x.second.active)&&(!(toCheck.name.compare(x.second.name)))){
              if(x.second.type==1){
                                  //cout<<"#### ancestoring ####" <<toCheck.name<<endl;
                                if(x.second.scopeF>max.scopeF){
                                  max=x.second;
                                  r=&(x.second);
                                  found = true;
                                }
               }
               else if ((x.second.type==2)&&(x.second.scope)){
   //               cout<<"EDW RE"<<endl;

                  if(x.second.scopeF>max.scopeF){
                                  max=x.second;
                                  found = false;
                                }

               }
            
          }
        }
      );
  if(found){
     //cout<<" isAncestor succeded "<<endl;
    //lvalfunc =true;
    assignParts.push_back(max.type);
    //cout<<"vazw assingparts is ancestor"<<max.type<<endl;
    return r; 
  }
  else { return NULL;}
  // cout<<" isAncestor failed "<<endl;
  


}

//checks start
//Symbol fill (name, scope, line, nameF, scopeF, lineF, type, active, *next);
Symbol* isActiveProgFunct(Symbol toCheck){
	bool found = false;
  Symbol *r;
	auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
  	for_each (range.first, range.second,[&](hashmap::value_type& x){
  				     // iterate through said range
					if((x.second.active == toCheck.active)&&(toCheck.type == FUNC)&&(!(toCheck.name.compare(x.second.name)))){
						//cout<<" this is active progfuct with name isActiveProgFunct : " <<toCheck.name<<"line :"<<toCheck.line<<endl;
						found = true;
            r=&(x.second);
					}
				}
			);
  if(found) return r;
  /*      cout<<" isActiveProgFunct succeded "<<endl; }
  else  cout<<" isActiveProgFunct failed "<<endl; 
*/	
return NULL;

}

Symbol* isSameScopeFFunc(Symbol toCheck){
  bool found = false;
  Symbol *r;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if((x.second.scopeF == toCheck.scopeF)&&(toCheck.type == FUNC)&&(x.second.active)&&(!(toCheck.name.compare(x.second.name)))) {
            //cout<<" this is active progfuct with name isSameScopeFFunc : " <<toCheck.name<<"line :"<<toCheck.line<<" vs :"<<x.second.name<<"line :"<<x.second.line<<endl;
            found = true;
            if(x.second.scope < toCheck.scope)found=false;
            r=&(x.second);
          }
        }
      );
  if(found) return r;
  /*      cout<<" isSameScopeFFunc succeded "<<endl; }
  else  cout<<" isSameScopeFFunc failed "<<endl; 
  */
return NULL;

}

Symbol* isSameFscopeNotFunc(Symbol toCheck){
  bool found = false;
  Symbol *r;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if((x.second.scopeF == toCheck.scopeF)&&(x.second.type != FUNC)&&(!(toCheck.name.compare(x.second.name)))){
            //cout<<" this is active progfuct with name isSameFscopeNotFunc : " <<toCheck.name<<endl;
            found = true;
            r=&(x.second);

          }
        }
      ); 
  if(found) return r;
/*cout<<" isSameFscopeNotFunc succeded "<<endl; }
else { cout<<" isSameFscopeNotFunc failed "<<endl;}*/
return NULL;

}

//Symbol fill (name, scope, line, nameF, scopeF, lineF, type, active, *next); //global 
Symbol* isLocal(Symbol toCheck){
	bool found = false;
  Symbol *r;
	auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
  	for_each (range.first, range.second,[&](hashmap::value_type& x){
  				     // iterate through said range
					if((toCheck.active ==x.second.active )&&(toCheck.type == VAR)&&(!(toCheck.name.compare(x.second.name)))){
						//cout<<" this is local with name :" <<toCheck.name<<endl;
						found = true;
            r=&(x.second);
					}
				}
			);
	if(found) return r;
/*cout<<" isLocal succeded "<<endl; }
else { cout<<" isLocal failed "<<endl;}*/
return NULL;

}

//check gia function an uparxei argument 
Symbol* isArgument(Symbol toCheck){
	bool found = false;
  Symbol *r;
	auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
  	for_each (range.first, range.second,[&](hashmap::value_type& x){
  				     // iterate through said range
          //cout<<"in argument :SCOPE_F "<<x.second.scopeF<<" Type:"<<get_type(x.second.type)<<" active :"<<x.second.active<<" name: "<<x.second.name<<" line: "<<yylineno<<endl;

					if((x.second.type == ARGUMENT)&&(x.second.active)&&(x.second.scopeF==toCheck.scopeF)&&(!(toCheck.name.compare(x.second.name)))){
						//cout<<" this is argmt with name :" <<toCheck.name<<endl;
						found = true;
            assignParts.push_back(x.second.type);
            //cout<<"vazw assingparts isargument"<<x.second.type<<endl;
            r=&(x.second);
					}
				}
			); 
	if(found) return r;
/*cout<<" isArgument succeded "<<endl; }
else { cout<<" isArgument failed "<<endl;}*/
return NULL;

}

Symbol* isActive(Symbol toCheck){
  bool found = false;
  Symbol *r;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if((x.second.active)&&(!(toCheck.name.compare(x.second.name)))){
            //cout<<" this is active with name :" <<toCheck.name<<endl;
            found = true;
            r=&(x.second);
          }
        }
      ); 
  if(found) return r;
/*cout<<" isActive succeded "<<endl; }
else { cout<<" isActive failed "<<endl;}*/
return NULL;

}

Symbol* isSameScope(Symbol toCheck){
  bool found = false;
  Symbol *r;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if((x.second.active)&&(x.second.scope == toCheck.scope)&&(!(toCheck.name.compare(x.second.name)))){
            //cout<<" this is same scope with name simple :" <<toCheck.name<<" :"<<x.second.type<<endl;
            found = true;
            r=&x.second;
          }
        }
      ); 
  if(found) return r;
/*cout<<" isSameScope succeded "<<endl; }
else { cout<<" isSameScope failed "<<endl;}*/
return NULL;

}

Symbol* isSameFScope(Symbol toCheck){
  Symbol *r;
  bool found = false;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if((x.second.scopeF == toCheck.scopeF)&&(!(toCheck.name.compare(x.second.name)))&&(x.second.active)) {
           // cout<<" this is same scope with name F :" <<toCheck.name<<": "<<x.second.type<<endl;
            found = true;
             assignParts.push_back(x.second.type);
            // cout<<"vazw assingparts issamefscope"<<x.second.type<<endl;
            r=&x.second;
            /*if (x.second.type == 1 ) {
                                    lvalfunc =true;
                                    assignParts.push_back(x.second.type);
                                    cout<<"vazw assingparts issamefscope"<<x.second.type<<endl;
                                  }*/

          }
        }
      );
  if(found) return r;
/*cout<<" isSameFScope succeded "<<endl; }
else { cout<<" isSameFScope failed "<<endl;}*/
return NULL;

}

bool isPastVar(Symbol toCheck){
  bool found = false;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if ((x.second.type==VAR)&&(x.second.scope < toCheck.scope)&&(!(toCheck.name.compare(x.second.name)))){
            //cout<<" ablaboublas " <<toCheck.name<<endl;
            found = true;
        } }
      ); 
  //if(found) return x;
/*cout<<" isPastVar succeded "<<endl; }
else { cout<<" isPastVar failed "<<endl;}*/
return found;

}

          


Symbol* isPresentVar(Symbol toCheck){
  Symbol *r;
  bool found = false;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if ((x.second.type==VAR)&&(x.second.scope == toCheck.scope)&&(!(toCheck.name.compare(x.second.name)))){
            //cout<<" ablaboublas " <<toCheck.name<<endl;
            found = true;
            r=&x.second;
        } }
      ); 
  if(found) return r;
/*cout<<" isPresentVar succeded "<<endl; }
else { cout<<" isPresentVar failed "<<endl;}*/
return NULL;

}


//REVERSE OUTCOMES???
Symbol* isVarValid(Symbol toCheck){
  bool found = false;
  Symbol *r;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if ((x.second.type!=VAR)&&(x.second.scope)&&(x.second.scopeF < toCheck.scopeF)&&(!(toCheck.name.compare(x.second.name)))){
            //cout<<" NOT VAR && NOT GLOBAL && LESSER SCOPE :" <<toCheck.name<<endl;
            found = true;
            r=&x.second;
          }
          else if ((x.second.type!=ARGUMENT)&&(x.second.scopeF != toCheck.scopeF)&&(!(toCheck.name.compare(x.second.name)))){
           // cout<<" NOT ARG NOT SCOPE :" <<toCheck.name<<endl;
            found = true;
            r=&x.second;
          }
        }
      ); 
  if(found) return r;
/*cout<<" isVarValid succeded "<<endl; }
else { cout<<" isVarValid failed "<<endl;}*/
return NULL;

}

/*
vector <vector<Symbol>>  templist;

bool compareByscope(Symbol sym1, Symbol sym2)
{
    return sym1.scope < sym2.scope;
}

*/

Symbol* isVarRefValid(Symbol toCheck){
  Symbol *r ;
  Symbol *p = new Symbol;
  templist.clear();
  //templist.resize(20);
  bool found = false;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
              //not func with same Fscope or global scope
          if (((x.second.type!=FUNC)||(x.second.type!=VAR))&&((x.second.scopeF == toCheck.scopeF)||(!(x.second.scope)))&&(!(toCheck.name.compare(x.second.name)))&&(x.second.active)) {
            //cout<<" not func OR VAR with same Fscope or global scope :" <<toCheck.name<<" : -> "<<x.second.line<<endl;
            found = true;
            Symbol pass = x.second;
            Symbol *temp = new Symbol;
            temp= fill4(temp, x.second.name,  x.second.scope ,  x.second.line , x.second.nameF,  x.second.scopeF , x.second.lineF , x.second.type , x.second.active, x.second.offset,x.second.space,x.second.dotalocal);

            templist.push_back(temp);
            //if(r==NULL) r=&x.second;
            //else{ p=compareByscope(r,&x.second); r=p; } 
            r=&x.second;
            //cout<<" found IS TURNING TRUE HERE "<<endl;
            assignParts.push_back(x.second.type);
            //cout<<"vazw assingparts isvarefvalid 1 :"<<x.second.type<<endl;
            if (x.second.type < 2 ){ lvalfunc =true; /*cout<<" LVAL IS TURNING TRUE HERE "<<endl;*/ 
                                  

              }
          }
          else if ((x.second.active)&&(x.second.type!=ARGUMENT)&&(x.second.scopeF == toCheck.scopeF)&&(!(toCheck.name.compare(x.second.name)))) {
            //cout<<" NOT arg &&  SCOPE :" <<toCheck.name<<endl;
            found = true;

            //if(r==NULL) r=&x.second;
            //else{ p=compareByscope(r,&x.second); r=p; }
            r=&x.second;
            //Symbol pass = x.second;
             Symbol *temp = new Symbol;
            temp= fill4(temp, x.second.name,  x.second.scope ,  x.second.line , x.second.nameF,  x.second.scopeF , x.second.lineF , x.second.type , x.second.active, x.second.offset,x.second.space,x.second.dotalocal);

            //cout<<" found IS TURNING TRUE HERE "<<endl;
            assignParts.push_back(x.second.type);
            //cout<<"vazw assingparts isvarefvalid 2"<<x.second.type<<endl;
            if (x.second.type < 2 ) {lvalfunc =true; /*cout<<" LVAL IS TURNING TRUE HERE "<<endl;*/}
          }
        }
      );
  if(found){ 
    sort(templist.begin(),templist.end(),compareByscope);
    if(DEBUG)cout<<templist.size()<<" size | front scope :"<<templist.front()->scope<<" | back : "<<templist.back()->scope<<endl ;
    if(DEBUG)cout<<"  scope returned  :"<<r->scope<<endl;
    r=templist.back();
    return r;
  }
/*cout<<" isVarRefValid succeded "<<endl; }
else { cout<<" isVarRefValid failed "<<endl;}*/
return NULL;

}



//global var check
Symbol* isGlobalVar(Symbol toCheck){
  Symbol *r;
	bool found = false;
	auto range = Syriza.equal_range(hashme(toCheck.name));//get "range" of insertions with the same value   
  	for_each (range.first, range.second,
  					[&](hashmap::value_type& x){
  				     // iterate through said range
					if((x.second.scope == 0)&&(x.second.type==VAR)&&(!(toCheck.name.compare(x.second.name)))){ //&&(toCheck.type == ARGUMENT) isws xreiastw type
						//cout<<" there is global var with name :" <<toCheck.name<<endl;
						found = true ;
            r=&x.second;
            //r= fill4(r, x.second.name,  x.second.scope ,  x.second.line , x.second.nameF,  x.second.scopeF , x.second.lineF , x.second.type , x.second.active, x.second.offset,x.second.space,x.second.dotalocal);

            assignParts.push_back(x.second.type);
            //cout<<"vazw assingparts isGlobalVar"<<x.second.type<<endl;
					}

				}
			); 
if(found) return r;
/*cout<<" isGlobalVar succeded "<<endl; }
else { cout<<" isGlobalVar failed "<<endl;}*/
return NULL;

}


Symbol* isPresent(Symbol toCheck){
  bool found = false;
  Symbol *r;
  auto range = Syriza.equal_range(hashme(toCheck.name));//get "range" of insertions with the same value   
    for_each (range.first, range.second,
            [&](hashmap::value_type& x){
               // iterate through said range
              if(!(toCheck.name.compare(x.second.name))) {
                    found =true;
                    r=&x.second;
                }
            }
      ); 
 if(found) return r;
/*cout<<" isPresent succeded "<<endl; }
else { cout<<" isPresent failed "<<endl;}*/
return NULL;

}

Symbol* isZeroScopeFunc(Symbol toCheck){
  Symbol *r;
  bool found = false;
  auto range = Syriza.equal_range(hashme(toCheck.name));//get "range" of insertions with the same value   
    for_each (range.first, range.second,
            [&](hashmap::value_type& x){
               // iterate through said range
          if((x.second.scope == 0)&&(x.second.type==FUNC)&&(!(toCheck.name.compare(x.second.name)))){ //&&(toCheck.type == ARGUMENT) isws xreiastw type
            //cout<<" there is global function with name :" <<toCheck.name<<endl;
            found =true;
            r=&x.second;
          }

        }
      ); 
  if(found) return r;
/*cout<<" isGlobalFunc succeded "<<endl; }
else { cout<<" isGlobalFunc failed "<<endl;}*/
return NULL;

}


Symbol* isGlobalFunc(Symbol toCheck){
  Symbol *r;
  bool found = false;
  auto range = Syriza.equal_range(hashme(toCheck.name));//get "range" of insertions with the same value   
    for_each (range.first, range.second,
            [&](hashmap::value_type& x){
               // iterate through said range
          if((x.second.scopeF == 0)&&(x.second.type==FUNC)&&(!(toCheck.name.compare(x.second.name)))){ //&&(toCheck.type == ARGUMENT) isws xreiastw type
            //cout<<" there is global function with name :" <<toCheck.name<<endl;
            found =true;
            r=&x.second;
          }

        }
      ); 
  if(found) return r;
/*cout<<" isGlobalFunc succeded "<<endl; }
else { cout<<" isGlobalFunc failed "<<endl;}*/
return NULL;

}


bool isIllegalScopeVarArg(Symbol toCheck){
  bool found = false;
  auto range = Syriza.equal_range(hashme(toCheck.name));               //get "range" of insertions with the same value   
    for_each (range.first, range.second,[&](hashmap::value_type& x){
               // iterate through said range
          if (((x.second.type==VAR)||x.second.type==ARGUMENT)&&(x.second.scopeF < toCheck.scopeF)&&(x.second.scope)&&(!(toCheck.name.compare(x.second.name)))){
            //cout<<" vrika metavliti pou den 8a prepe na borw na ti dw " <<toCheck.name<<endl;
            found = true;

        } }
      ); 
 /* if(found){
cout<<" isIllegalScopeVar succeded "<<endl; }
else { cout<<" isIllegalScopeVar failed "<<endl;}*/
return found;

}

//check end


void initializeHash(){
Scopelist.resize(100);

libFuncList.push_back("print");
libFuncList.push_back("input");
libFuncList.push_back("tableindices");
libFuncList.push_back("tablelength");
libFuncList.push_back("tablecopy");
libFuncList.push_back("totalarguments");
libFuncList.push_back("argument");
libFuncList.push_back("typeof");
libFuncList.push_back("strtonum");
libFuncList.push_back("sqrt");
libFuncList.push_back("sqrt");
libFuncList.push_back("cos");
libFuncList.push_back("sin");


//Symbol fill (name, scope, line, nameF, scopeF, lineF, type, active, *next);

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
//check-remove it 
//Syriza.insert ({hashme("print"),fill("print",12345,0,"print",0,0,LIBFUNC,true,nullptr)} );


}
bool libfuncCheck(string name){
  for (list<string>::iterator it = libFuncList.begin(); it != libFuncList.end(); it++){
    if (it->compare(name) == 0){
      assignParts.push_back(LIBFUNC);
      return true;
    }
  }
return false;
}




//fill symbol item
Symbol fill (string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active){
  Symbol tofill;
    tofill.name=name;
    tofill.scope=scope;
    tofill.line=line;
    tofill.nameF=nameF;
    tofill.scopeF=scopeF;
    tofill.lineF=lineF;
    tofill.type=type;
    tofill.active=active;
    return tofill;
}



Symbol fill3 (string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active,unsigned int offset,scopespace_types space){
      Symbol tofill;
    tofill.name=name;
    tofill.scope=scope;
    tofill.line=line;
    tofill.nameF=nameF;
    tofill.scopeF=scopeF;
    tofill.lineF=lineF;
    tofill.type=type;
    tofill.active=active;
    tofill.space=space;
    tofill.offset = offset;
    //cout<<" name of id is :"<< name << "  tofill add: "<<&tofill<<endl;

    return tofill;

}

Symbol *fill4 ( Symbol *tofill,string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active,unsigned int offset,scopespace_types space, int dotalocal ){
     // Symbol tofill;
    tofill->name=name;
    tofill->scope=scope;
    tofill->line=line;
    tofill->nameF=nameF;
    tofill->scopeF=scopeF;
    tofill->lineF=lineF;
    tofill->type=type;
    tofill->active=active;
    tofill->space=space;
    tofill->offset = offset;
    tofill-> dotalocal = dotalocal;
    //cout<<" name of id is :"<< name << "  tofill add: "<<tofill<<endl;

    return tofill;

}

Symbol *createFSymbol(string name,int scope, int line, string nameF,
  int scopeF,int lineF,vartype type, bool active,unsigned int offset,scopespace_types space)
{
  Symbol *ret = new Symbol;
  ret->name=name;
  ret->scope=scope;
  ret->line=line;
  ret->nameF=nameF;
  ret->scopeF=scopeF;
  ret->lineF=lineF;
  ret->type=type;
  ret->active=active;
  ret->space=space;
  ret->offset=offset;
  return ret;
};

Symbol * insertH(Symbol addMe){ //int insertH(Symbol toAdd)
	
	//int check = addMe.scope;
	bool addthis= true;
	//lval
	//check if name is libfunc name
  //cout<<"in inshertH name : "<<addMe.name<<"    |scope: "<<addMe.scope<<endl;
	if (isLibFunct(addMe)){
		cout<<"Syntax Error Shadowing Lib Func with the name :"<<addMe.name<<endl;
		addthis= false;
    isValid=false;
    return NULL;
		
	}

	if (addthis){
		Syriza.insert ({hashme(addMe.name),addMe} );
    ins_toScope(addMe,addMe.scope);
    ins_toScopeF(addMe,addMe.scopeF);
    inccurrscopeoffset();
    Symbol * result = new Symbol;
    result = &(addMe);
    return result;
		//scpList.insert(addMe.scope(addMe);
//    cout<<"INSERTING HERE :"<<addMe.line<<" : "<<addMe.name<<" : "<<addMe.scopeF<<endl;
		}
	

}

void insertPt(Symbol *s){
	Syriza.insert({hashme(s->name),*s});
	ins_toScope(*s,s->scope);
  ins_toScopeF(*s,s->scopeF);
}


int hideIt(Symbol hideMe){

  //assert(hideMe);
  if (!hideMe.active){return 0;}
  else {hideMe.active= false; return 1;}
}

string setFunctionName(){
    string str2 = to_string(f_prefix);
    string name ;
    name = defaultName;
    name.append(str2);
    f_prefix++;
    return name;
}
//hidefunc
void hideThem(int thisScope){
 
  //cout<<"count: "<<Syriza.bucket_count()<<endl;
  for ( int i = 0; i < Syriza.bucket_count(); ++i) { //check every bucket
    //cout<<" bucket: "<<i<<" size:"<<Syriza.bucket_size(i)<<endl;
    if (Syriza.bucket_size(i)>0){ 
    for ( auto local_it = Syriza.begin(i); local_it!= Syriza.end(i); ++local_it ){ //check every element in said bucket
      //if scope is the highest then false cause we exit
      //cout<<"name :"<<local_it->second.name<<" | line: "<<local_it->second.line<<" | scope:"<<local_it->second.scope<<endl;

      if ((local_it->second.scope >= thisScope)&&(local_it->second.active)&&(local_it->second.type!=FUNC)) {local_it->second.active = false;
      if(DEBUG)cout<<"done: "<<local_it->second.name<<endl;} 
    }
    //cout<<"done2"<<endl;
  }
  //else cout<<"else"<<endl;
  //cout<<"out of if "<<endl;
}
  //cout<<"done3"<<endl;
}

void hideTheScope(int thisScope){
 
  //cout<<"count: "<<Syriza.bucket_count()<<endl;
  for ( int i = 0; i < Syriza.bucket_count(); ++i) { //check every bucket
    //cout<<" bucket: "<<i<<" size:"<<Syriza.bucket_size(i)<<endl;
    if (Syriza.bucket_size(i)>0){ 
    for ( auto local_it = Syriza.begin(i); local_it!= Syriza.end(i); ++local_it ){ //check every element in said bucket
      //if scope is the highest then false cause we exit
      
      if ((local_it->second.scope == thisScope)&&(local_it->second.type==FUNC)&&(local_it->second.active)) {
        local_it->second.active = false;
      //cout<<"Hiding the variable: " << local_it->second.name << " at scope: " << local_it->second.scope << endl; 
      //cout<<"done"<<endl; 
    }
    }
    //cout<<"done2"<<endl;
  }
  //else cout<<"else"<<endl;
  //cout<<"out of if "<<endl;
}
  //cout<<"done3"<<endl;
}



//typedef enum lookup_mode{LVAL_ID,LVAL_LOCAL,LVAL_GLOBAL,FUNCDEF_MODE }lmode;

Symbol* Lookup(Symbol toAdd,lmode mode ){
  Symbol *s = new Symbol;
  //cout <<"******IS FUNC DEF: " << is_funcdef << "   "<< toAdd.name << endl;
  switch(mode){
      case 0: if (is_funcdef){
                is_call=0;
                //return s; LOL
  //              cout<<" IS_IT_A_CALL? is turning OFF : "<<is_call<<" line: "<<yylineno<<endl;
                //cout <<" lookup mode 0 funcdef"<<endl;            
                if (s=isLibFunct(toAdd)){
                  lvalfunc=true;
                   is_funcall=1;
                  //cout << "pira libfunc" << endl;
                  return s;
                  //cout<<" LVALFUNC is turning ON : "<<lvalfunc<<" line: "<<yylineno<<endl;
                  //cout<<"lval func lol"<<endl;

                }
                else if((s=isSameFScope(toAdd))!=NULL) {
                             if(DEBUG) cout<<"samescope "<<yylineno<<endl;


                  return s;

                }
                else if ((s=isAncestor(toAdd))!=NULL){
                  is_funcall=1;
                  if(DEBUG){cout<<" IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;
                        cout<<"refering to active ancestor function";}
                  return s;

                  }
                else if ((s=isArgument(toAdd))!=NULL){

                  if(DEBUG){cout<<"refering to argument"<<endl;}
                  return s;
                }
                
                else if (isIllegalScopeVarArg(toAdd)){
                if(DEBUG){cout<<"Syntax error lvalue ID error illegal scope line : "<<yylineno<<"   "<<endl;}
                isValid=false;

                return NULL;


                }
                else if ((s=isGlobalVar(toAdd))!=NULL){
                    if(DEBUG)cout<<"refering to global var"<<endl;

                      return s;
                  }
                else{
                  
                    insertH(toAdd);
                    assignParts.push_back(toAdd.type);
                    //cout<<"vazw assingparts ID funcdef"<<toAdd.type<<endl;
                    s= &toAdd;
                    return s;              //NOT QUITE SURE VARDAS
                    
                }
              }
              else{
                  if ((s=isVarRefValid(toAdd))!=NULL) {
                    //funcvar same scope
                    if(DEBUG)cout<<"redefined app referencing to that one :"<<yylineno<<endl;
                    if (isPresent(toAdd)){
                        is_funcall=1;
                      if(DEBUG)cout<<" IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;
                      }
                      

                      if(DEBUG)cout<<"isvarvalid true (false?) line: "<<yylineno<<endl;
                      


                      }
                  else if((s=isSameFScope(toAdd))!=NULL) {
                              cout<<"samescope "<<yylineno<<endl;


                  return s;

                }
                  else if ((s=isGlobalVar(toAdd))!=NULL){
                    if(DEBUG)cout<<"refering to global var"<<endl;

                      return s;
                  }
                  else if ((s=isPresentVar(toAdd))!=NULL){
                        is_funcall=1;
                        if(DEBUG){cout<<" IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;
                        cout<<"is present :"<<toAdd.name<<endl;}

                        //!!!!!!
                    }
                  else if (isPastVar(toAdd)){
                        is_funcall=1;
                       if(DEBUG){cout<<" IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;}
                        cout<<"Syntax Error cant get access :"<<toAdd.name<<endl;
                        isValid=false;

                        return NULL;
                    }
                  
                  else{//insert 
                    insertH(toAdd);
                    assignParts.push_back(toAdd.type);
                    if(DEBUG){cout<<"vazw assingparts ID NOT FUNCDEF"<<toAdd.type<<endl;}
                    s= &toAdd;

                    return s;
                  }
                }
              return s;
      case 1: if((s=isSameScope(toAdd))!=NULL){
                  if(DEBUG){cout<<"reference in local id :"<<yylineno<<endl;}
                  if ((s=isPresent(toAdd))!=NULL){
                        is_funcall=1;
                        if(DEBUG)cout<<" SS PRESENT IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;
                    }
                    return s;

              }
              
              else{
                  insertH(toAdd);
                  if ((s=isPresent(toAdd))!=NULL){
                        //is_funcall=1;
                        //cout<<" ELSE  IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;
                    }
                  lvalfunc=0;
                  s= &toAdd;
                  return s;
                  cout<<" ekana insert neo local"<<endl;
                  //return s;
              }
              
      case 2: //cout<<"DEBUGGING ----> TOADD.NAME "<<toAdd.name<<endl;
               if((s=isGlobalVar(toAdd))!=NULL){
                if(DEBUG)cout<<yylineno<<": " "Referring to global var"<<endl;
               }
               else if ((s=isGlobalFunc(toAdd))!=NULL){
               if(DEBUG) cout<<yylineno<<": " "Referring to global function"<<endl;
                is_funcall=1;
                //cout<<" IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;              
               }
               else if((s=isLibFunct(toAdd))!=NULL){

                if(DEBUG)cout<<yylineno<<": " "Referring to lib function"<<endl;
                is_funcall=1;
                //cout<<" IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;
                //return NULL;
                
               }
               else {cout<<yylineno<<": Syntax Error! Undefined global identifer"<<endl;
                  isValid=false;}

              return s;
      case 3: if (isLibFunct(toAdd)){
                cout<<"Syntax error cannot take lib func names"<<endl;
                isValid=false;
                return NULL;
              }
              
              else if ((s=isGlobalVar(toAdd))!=NULL){
                cout<<"Syntax error global var present with same name"<<endl;
                isValid=false;
                return NULL;
              }
              else if((s=isSameScopeFFunc(toAdd))!=NULL){
                cout<<"Syntax error is same scopeF func "<<yylineno<<endl;
                isValid=false;
                return NULL;

              }
              else if((s=isArgument(toAdd))!=NULL){
                cout<<"Syntax error Argument active  present with same name"<<endl;
                isValid=false;
                return NULL;

              }
              else if((isLocal(toAdd)!=NULL)){   //Those two checks are a bit questionable
                cout<<"Syntax error another active function present with same name"<<endl;

                isValid=false;
                return NULL;

              }
              else if ((isPresent(toAdd)!=NULL)&&(isSameScope(toAdd)!=NULL)){ 
                        is_funcall=1;
                        if(DEBUG){cout<<" IS_FUNCALL is turning ON : "<<is_funcall<<" line: "<<yylineno<<endl;
                        cout<<"ispresent in funcdef + samescope"<<endl;}
                  }

              else {
                  toAdd.type=FUNC;
                  insertPt(&toAdd);//currscopespace(),currscopeoffset()
                  if(DEBUG)cout<<" last"<<endl;
                   //lineF = yylineno;
                   //cout<<"emiting funcstart!!!!!!!!!!!!!!!!!!!!!!"<<toAdd.dotalocal  <<endl;
                  //toAdd =fill(functionName,maxScope,yylineno,"none",maxFScope,0,FUNC,true);   //missing
                  expr *ack = new expr;
                  ack = lvalue_symbol(ack,&toAdd); 
                  emit(funcstart,nullptr,nullptr,ack,-1,yylineno);
                  functions.push_back(toAdd.name);

                  //pushStack(loopStack, loopScope);
                  //loopScope = 0;
                  //inccurrscopeoffset();
                  return s;
                  //todo<<
                 

              }

              return s;
      
      default: return NULL;
    }
}

Symbol *nameLookup(string s,int inscope){
  Symbol *r = new Symbol;
  nameLookupFound = false;
  //cout<<" psaxnw onoma: "<<s<<" scopeF "<<inscope<<endl;

  auto range = Syriza.equal_range(hashme(s));
    for_each (range.first, range.second,
            [&](hashmap::value_type& x){
          if((x.second.scopeF == inscope)&&(!(s.compare(x.second.name)))&&((x.second.active))){
            //cout<<" there is temp var with name :" <<s<<endl;
            nameLookupFound = true ;
            //r=&x.second;
            r= fill4(r, x.second.name,  x.second.scope ,  x.second.line , x.second.nameF,  x.second.scopeF , x.second.lineF , x.second.type , x.second.active, x.second.offset,x.second.space,x.second.dotalocal);

            assignParts.push_back(x.second.type);
          }

        }
      ); 
if(nameLookupFound){ return r;}
else{
 if(DEBUG)cout<<" de vrika "<<s<<endl;
return nullptr;}
}

Symbol *LookupName(string s,int inscope){
  Symbol *r = new Symbol;
  nameLookupFound = false;
  //cout<<" psaxnw onoma: "<<s<<" scopeF "<<inscope<<endl;
  auto range = Syriza.equal_range(hashme(s));
    for_each (range.first, range.second,
            [&](hashmap::value_type& x){
          if((x.second.scopeF == inscope)&&(!(s.compare(x.second.name)))&&(x.second.active)){
            //cout<<" there is function defined with the same name in this scope :" <<s<<endl;
            nameLookupFound = true ;
            //r=&x.second;
            //cout<<" lookup success"<<endl;
            r= fill4(r, x.second.name,  x.second.scope ,  x.second.line , x.second.nameF,  x.second.scopeF , x.second.lineF , x.second.type , x.second.active, x.second.offset,x.second.space,x.second.dotalocal);

            assignParts.push_back(x.second.type);
            return r;
          }

        }
      ); 
//if(nameLookupFound){ return r;}
//else{}

return NULL;
}

Symbol *LookupforRef(string s,int inscope){
  Symbol *r = new Symbol;
  nameLookupFound = false;
  auto range = Syriza.equal_range(hashme(s));
    for_each (range.first, range.second,
            [&](hashmap::value_type& x){
          if((x.second.scope < inscope)&&(!(s.compare(x.second.name)))&&(x.second.active)){
            //cout<<" there is function defined with the same name in this scope :" <<s<<endl;
            nameLookupFound = true ;
            r=&x.second;
            assignParts.push_back(x.second.type);
          }

        }
      ); 
if(nameLookupFound){ return r;}
else{

return NULL;}
}


void printSymbols(){ 

    cout << "Syriza's buckets contain:\n";
  for ( unsigned i = 0; i < Syriza.bucket_count(); ++i) {

    if (Syriza.bucket_size(i)>0){ 
      //cout << "bucket:" << i << " contains: "<<Syriza.bucket_size(i)<<endl;
      for ( auto local_it = Syriza.begin(i); local_it!= Syriza.end(i); ++local_it ){
        if(local_it->second.type!=LIBFUNC){
        //cout << " " <<"KEY "<< ":" << local_it->first;
        cout << " " <<"NAME "<< ":" << local_it->second.name;
        cout << " " <<"SCOPE "<< ":" << local_it->second.scope;
        cout << " " <<"LINE "<< ":" << local_it->second.line;
        cout << " " <<"NAMEF "<< ":" << local_it->second.nameF;
        //cout << " " <<"SCOPE_F "<< ":" << local_it->second.scopeF;
        cout << " " <<"LINE_F "<< ":" << local_it->second.lineF;
        cout << " " << "TYPE " << ":" << get_type(local_it->second.type);
        cout << " " << "ACTIVE " << ":" << local_it->second.active<<endl;
        cout << " " << "OFFSET" << ":" << local_it->second.offset<<endl;
        cout << " " << "SCOPESPACE" << ":" << local_it->second.space<<endl;
      }
        
        }
     cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
      }
  }
  printAll();
}
/*typedef struct symT {
    string name; //onoma tis metavlitis
    int scope;  //scope tis metavlitis
    int line;   //grammi tis metavlitis
    string nameF; //onoma tis function pou vrisketai i metavliti
    int scopeF;  //scope tis function pou vrisketai i metavliti
    int lineF;   //line tis function pou vrisketai i metavliti
    vartype type;  //tipos tou node (an einai func , lib_func , var )
    int dotalocal=-1;
    bool active = false;  //0 an einai hide
    enum scopespace_types space;
    unsigned int offset;
} Symbol;*/
//typedef enum variable_type{LIBFUNC,FUNC,VAR,ARGUMENT }vartype;

string get_type(vartype check){


  switch(check){
      case 0: return "LIBFUNC";
      case 1: return "FUNC";
      case 2: return "VAR";
      case 3: return "ARGUMENT";
      
      default: return "varoufakis";
    }



}



void ins_toScope(Symbol symbol,int scope){
  Scopelist[scope].push_back(symbol);
};



void print_scope(int a){
  vector<Symbol>  :: iterator it;
    for(it=Scopelist[a].begin(); it!=Scopelist[a].end(); it++){
      cout << (*it).name << endl;
    }
};






void printAll(){
  cout << "////-----------------------------SCOPE PRINTS----------------------------------------------////" << endl;
  vector <vector<Symbol>>  :: iterator it;
  vector <Symbol> :: iterator jt;
  for(it=Scopelist.begin(); it!=Scopelist.end(); it++){
    if(!(*it).empty()){
    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
        cout << " " <<"NAME: " << (*jt).name;
        cout << "   " <<"SCOPE: " << (*jt).scope;
        cout << "   "<<"SCOPEF: "<< (*jt).scopeF;
        cout << "   " <<"LINE: " << (*jt).line;
        cout << "   " << "TYPE: "  << get_type((*jt).type);
        cout << "   " << "OFFSET" << ":" << (*jt).offset;
        cout << "   " << "SCOPESPACE" << ":" << (*jt).space<<endl;
       // Symbol a;
        //a=(*jt);
        //Fscopelist[(*jt).scopeF].push_back(a);
        

    }
    }
  }

  cout << "////---------------------------------------------------------------------------------------////" << endl;

  if(DEBUG){


  vector <vector<Symbol>>  :: iterator kt;
  vector <Symbol> :: iterator lt;
  for(kt=Fscopelist.begin(); kt!=Fscopelist.end(); kt++){
    if(!(*kt).empty()){
    for(lt=(*kt).begin(); lt!=(*kt).end(); lt++){
        cout << " " <<"NAME: " << (*lt).name;
        cout << "   " <<"SCOPE: " << (*lt).scope;
        cout << "   "<<"SCOPEF: "<< (*lt).scopeF;
        cout << "   " <<"LINE: " << (*lt).line;
        cout << "   " << "TYPE: "  << get_type((*lt).type);
        cout << "   " << "OFFSET" << ":" << (*lt).offset;
        cout << "   " << "SCOPESPACE" << ":" << (*lt).space<<endl;
       // Fscopelist[(*jt).scopeF].push_back(*jt);
        

    }
    }
  }
  }
};





