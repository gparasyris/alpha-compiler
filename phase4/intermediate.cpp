#include "hash.h"
#include "intermediate.h"

// default sizes
/****************/
extern string blvr;
/****************/	

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad)+CURR_SIZE)

vector<quad> quadhead;
unsigned int	total = 0;
unsigned int 	currQuad = 0;
string tempname="_t";
unsigned int tempcounter;

extern int   maxScope;
extern int maxFScope;
extern int elist_start;
extern bool isValid;
//extern 	std::ofstream outfile;
unsigned int programVarOffset = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset = 0;
unsigned int scopeSpaceCounter = 1;
extern Symbol toAdd;
extern int yylineno;
extern unordered_multimap<int,Symbol> Syriza;
extern list<int> assignParts;
extern bool nameLookupFound;
extern vector<int> contvector;
extern vector<int> breakvector;
extern vector<expr*> expr_list;
extern vector <vector<int>> trueMultiVector;
extern vector <vector<int>> falseMultiVector;
extern vector <vector<int>> contMultiVector;
extern vector <vector<int>> breakMultiVector;
extern int vc;
extern int bc;
extern int cc;


void emit(iopcode op ,expr * arg1, expr * arg2, expr * result, unsigned int label, unsigned int line){

	if(isValid==true){
	quad p ;
	if(DEBUG){cout<<"opcode here: "<<printOpcode(op)<<endl;}
	//if(op==assign){cout<< result->sym->type <<endl;}


	
	p.op = op;
	p.arg1 = arg1;
	p.arg2 = arg2;
	p.result = result;
	p.label = label;
	p.line = line;
	quadhead.push_back(p);
	//if(DEBUG){printQuads();}
	currQuad++;
}

}

void emit_or(iopcode op ,expr * arg1, expr * arg2, expr * result, unsigned int label, unsigned int line , int place){

	if(isValid==true){
	quad p ;
	if(DEBUG){cout<<"opcode here: "<<printOpcode(op)<<endl;}
	//if(op==assign){cout<< result->sym->type <<endl;}
	p.op = op;
	p.arg1 = arg1;
	p.arg2 = arg2;
	p.result = result;
	p.label = label;
	p.line = line;


	/*
	auto it = myvector.emplace ( myvector.begin()+1, 100 );
  	myvector.emplace ( it, 200 );
	*/
  	//
  	auto it = quadhead.emplace ( quadhead.begin()+place, p);
	//quadhead.push_back(p);
	//if(DEBUG){printQuads();}
	currQuad++;
}


}

string printLabel(unsigned int label){

	if (label == -1 ) return "No Jump";
	return to_string(label);


}

bool validForOp(expr* expr){
	switch(expr->type){
		case 0:	case 1:	case 4: case 6: case 8: case 9: return true;
			break;
		case 2: case 3: case 5: case 7: case 10: case 11: case 12: return false;
			break;
		default: return true;
	}
}

void printQuads(void) {
  	cout << "////-----------------------------QUAD PRINTS----------------------------------------------////" << endl;
  	vector<quad>  :: iterator it;
  	int i=0;
  	for(it=quadhead.begin(); it!=quadhead.end(); it++){
      	cout<<i<<": ";

      	cout<<" |" << "OPCODE :"<<printOpcode((*it).op);
      	cout<<"  " << "RESULT :"<<printexpr((*it).result);
      	cout<<"  " << "ARG1 :"<< printexpr((*it).arg1);//->sym->name
      	cout<<"  " << "ARG2 :"<<printexpr((*it).arg2);
      	cout<<"  " << "LABEL :"<<printLabel((*it).label);
      	cout<<"  " << "LINE :"<<(*it).line<<endl;
      	i++;
      	
      }
    	
  
  cout << "////---------------------------------------------------------------------------------------////" << endl;
};

/*void validPrints(void){

	outfile << "////-----------------------------QUAD PRINTS----------------------------------------------////" << endl;
  	vector<quad>  :: iterator it;
  	int i=0;
  	for(it=quadhead.begin(); it!=quadhead.end(); it++){
      	outfile<<i<<": ";

      	outfile<<" |" << "OPCODE :"<<printOpcode((*it).op);
      	outfile<<"  " << "RESULT :"<<printexpr((*it).result);
      	outfile<<"  " << "ARG1 :"<< printexpr((*it).arg1);//->sym->name
      	outfile<<"  " << "ARG2 :"<<printexpr((*it).arg2);
      	outfile<<"  " << "LABEL :"<<printLabel((*it).label);
      	outfile<<"  " << "LINE :"<<(*it).line<<endl;
      	i++;
      	
      }
    	
  
  outfile << "////---------------------------------------------------------------------------------------////" << endl;
};*/

string newtempname(){
	string str2 = to_string(tempcounter);
    string name ;
    name = tempname;
    name.append(str2);
    //f_prefix++;
    tempcounter++;
    return name;

}

void resettemp(void){
	//cout << "Running resettemp"<<endl;

	tempcounter = 0;
}

string gettype(vartype check){
	//cout << "Running gettype"<<endl;


  switch(check){
      case 0: return "LIBFUNC";
      case 1: return "FUNC";
      case 2: return "VAR";
      case 3: return "ARGUMENT";
      
      default: return "varoufakis";
    }

}
Symbol *newtemp(void){
	string name = newtempname();
	//printf("BIKE EDW\n");
	
	
	Symbol * sym = new Symbol;
	sym = nameLookup(name,maxFScope);
	
	if( sym!=nullptr ){
		if(DEBUG){cout << "SYMBOLO: " << sym << endl;}
		//sym->offset = currentscopeoffset();
		//sym->space = currentscopespace();
		if(DEBUG){cout<<" refer" <<endl;}
		return sym;
	}
	else{
		//cout<<"elsor"<< sym->name <<endl;

		Symbol * mysym = new  Symbol;
   		mysym= fill4(mysym,name , maxScope , yylineno ,"none", maxFScope , 0 , VAR , 1,currentscopeoffset(),currentscopespace(),-1);
   		//cout << mysym->name << endl;
   		//cout << mysym->scope << endl;

		//sym = mysym;
		insertH(*mysym);
		if(DEBUG){cout<<" newtemp :"<< mysym->name << " offset "<< mysym->offset<<endl;}
		return mysym;
	}
}

//Syriza.insert ({hashme(addMe.name),addMe} );
    //ins_toScope(addMe,addMe.scope);

scopespace_t currentscopespace( void ){
	//cout << "Running currentscopespace"<<endl;

	if( scopeSpaceCounter == 1){
		return programvar;
	}
	else if( scopeSpaceCounter % 2 == 0){
		return formalarg;
	}
	else{
		return functionlocal;
	}
}

unsigned int currentscopeoffset( void ){
	//cout << "Running currentscopeoffset"<<endl;

	switch( currentscopespace() ){
		case programvar		: return programVarOffset;
		case functionlocal 	: return functionLocalOffset;
		case formalarg		: return formalArgOffset;
		default			: assert(0);
	}
}


void inccurrscopeoffset( void ){
	//cout << "Running inccurrscopeoffset"<<endl;

	switch( currentscopespace() ){
		case programvar		: ++programVarOffset; break;
		case functionlocal 	: ++functionLocalOffset; break;
		case formalarg		: ++formalArgOffset; break;
		default			: assert(0);
	}
}

void enterscopespace( void ){
	//cout << "Running enterscopespace"<<endl;
	++scopeSpaceCounter;
}

void exitscopespace( void ){
	//cout << "Running exitscopespace"<<endl;

	///assert(scopeSpaceCounter > 1 );
	//printf("sadfdsfgdfgsfdgdfgdfgdfsg%d",scopeSpaceCounter); 
	--scopeSpaceCounter;
}

///////////COPIA
expr *emit_table(expr *arg1,expr *arg2,int line){
      expr *tmp = emit_iftableitem(arg1,line);
      expr *tmxpr = newexpr(tableitem_e);
      if(DEBUG){
      if(tmp){cout<<"success"<<endl;}
      else{cout<<"bla"<<endl;}
 	 	}	
      tmxpr->sym = tmp->sym;
      tmxpr->index = arg2;
      return(tmxpr);
}

///////////COPIA

expr* emit_iftableitem(expr* e, int line){
	if(e->type!=tableitem_e)
		return e;
	else{
		expr* result = newexpr (var_e);
		result->sym=newtemp();
		emit(tablegetelem,e,e->index,result,-1,yylineno);
		return result;

	}
}

///////////COPIA


expr* newexpr(expr_t t){
	//cout << "Creating newexpr"<<endl;
	expr *e = new expr;
	e->type=t;
	return e;
}

bool istempname(string s){
	//cout << "CHecking istempname"<<endl;
	return (s[0]=='_') ;


}

expr * insertVal( int val, double dval, string check ){
	expr *tmp = new expr;
	if (check=="INTCONST"){
		tmp->type = constint_e;
		tmp->intConst = val;
		
	}
	else if (check=="REALCONST"){
		tmp->type = constreal_e;
		tmp->numConst = dval;
	}
	else if (check=="KEYWORD_NIL"){
		tmp=newexpr(nil_e);

	}
	else if (check=="KEYWORD_TRUE"){
		tmp->type = constbool_e;
		tmp->boolConst = "true";

	}

	else if (check=="KEYWORD_FALSE"){
		tmp->type = constbool_e;
		tmp->boolConst = "false";
	}
	else{

		tmp->type = conststring_e;
		tmp->strConst = check;
		return (tmp);
	}

return (tmp);
}


expr * constString_expr(string passit){
	expr *tmp = new expr;	tmp->type = conststring_e;
	tmp->strConst = passit;
	return (tmp);
}

expr *lvalue_dais(struct symT *s){
	expr * tmp = new  expr;
	tmp->type=var_e;
	tmp->sym=s;
	return tmp;
}

//$<exprval>$ = lvalue_expr(createS(yytext,0,0,"",0,0,"var",1,currscopespace(),currscopeoffset()));		

/*
Symbol *fill4 ( Symbol *tofill,string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active,unsigned int offset,scopespace_types space);
*/
expr *lvalue_symbol(expr* expre,struct symT *s){
	//expr * tmp = new  expr;
	//expre->type=var_e;
	if(s->type==0){
		expre->type=libraryfunc_e;
		if(DEBUG){cout << "LETS DO THIS LIBFUNC!!!" << endl;}

	}
	else if(s->type==1){
		expre->type=programfunc_e;
		if(DEBUG){cout << "LETS DO THIS PROGRAMFUNC!!!" << endl;}

	}
	else{
		if(DEBUG){cout << "LETS DO THIS VARIABLE!!!" << endl;}
		expre->type=var_e;
	}
	//expre->sym=s;
	Symbol * mysym = new  Symbol;
    mysym= fill4(mysym, s->name,  s->scope ,  s->line , s->nameF,  s->scopeF , s->lineF , s->type , s->active, s->offset,s->space,s->dotalocal);
   	//mysym->dotalocal = s->dotalocal;
    expre->sym=mysym;


	return expre;
}

expr *lvalue_expr(string  passit){   
 
   	expr * tmp = new  expr;
   	Symbol * mysym = new  Symbol;
   	mysym= fill4(mysym, passit, maxScope , yylineno ,"none", maxFScope , 0 , VAR , 1,currentscopeoffset(),currentscopespace(),-1);
	tmp->type = var_e;
	tmp -> sym = mysym;
 	return(tmp);
}
/*
typedef enum expr_type {
  0  var_e,
  1  tableitem_e,
  2  programfunc_e,
  3  libraryfunc_e,
  4  arithexpr_e,
  5  boolexpr_e,
  6  assignexpr_e,
  7  newtable_e,
  8  constint_e,
  9  constreal_e,
  10  constbool_e,
  11  conststring_e,
  12  nil_e
}expr_t;


typedef struct expre {
    expr_t  type;
    Symbol  *sym;
    expre    *index;
    int     intConst;
    double  numConst;
    string  *strConst;
    string  boolConst; //unsinged char
    expre   *next;
}expr;
*/
string printexpr(expr* e ) {
	if (e==NULL){return "-";}
	//cout<<"###"<<e->type<<"####"<<endl;
	switch(e->type){
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:	return e->sym->name;
				break;	
		case 8:	return to_string(e->intConst);
				break;
		case 9:	return to_string(e->numConst);
				break;
		case 10:return e->boolConst;
				break;
		case 11: return e->strConst;
				break;
		//case 2: return &(e->sym);

		default: return to_string(e->type);
	}
}



expr *op_emit(iopcode op, expr *arg1 , expr *arg2,int line){
	
	bool decr = false;
	if (printexpr(arg1)[0]=='_') {tempcounter--;decr=true;}
	if ((printexpr(arg2)[0]=='_')&&(!decr)) {tempcounter--;decr=true;}
	if((op<16)&&(op>9)){
		expr *result = new expr;
		result = newexpr(boolexpr_e);
		result->sym = newtemp();
		emit(op, arg1, arg2, NULL, (int)(currQuad +2), line);
		//emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, result, -1, line);
		emit(jump, NULL, NULL, NULL, (int)(currQuad+1 ), line);
		//emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, result, -1, line);
		return (result);

	}
	if((op>6)&&(op<10)){
		expr *result = new expr ;
		result = newexpr(boolexpr_e);
		result->sym = newtemp();
		emit(op, arg1, arg2, result, -1 , line);
		return (result);
	}
	//cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<printexpr(arg1)<<" vs "<<printexpr(arg2)<<endl;
	expr *result = new expr;
	result = newexpr(arithexpr_e);

	if (result->sym = newtemp())
				{

				emit(op,arg1,arg2,result,-1,line);
				//cout << "arg1 " << result->type << " arg2" <<" kanw kati edw :"<<(result->sym->name).c_str()<<endl;
				return result;
				}
	//cout<<"barboutsala"<<endl;
	return NULL;
}


void restorecurrscopeoffset( unsigned int n ){
	switch( currentscopespace()){
		case programvar		: programVarOffset = n; break;
		case functionlocal 	: functionLocalOffset = n; break;
		case formalarg 		: formalArgOffset = n; break;
		default				: assert(0);
	}
}


void resetfunctionlocaloffset( void ){
	functionLocalOffset = 0;
}

void resetformalargoffset( void ){
	formalArgOffset = 0;
}

///copia

void printStack(void){
	cout << "//---------------------------------------------------STACK-----------------------------------------------------//"<<endl;
	for(; aerials.size();){
		cout << aerials.top() << endl;
		aerials.pop();
	}
	cout << "//------------------------------------------------------------------------------------------------------------//"<<endl;
}


void backpatch(unsigned int quadNumber,unsigned int label){
		quadhead[quadNumber].label = label;
		if(DEBUG){cout << "backpatching quad : "<< "OPCODE :"<<printOpcode(quadhead[quadNumber].op);
      	cout<<"  " << "ARG1 :"<< printexpr(quadhead[quadNumber].arg1);//->sym->name
      	cout<<"  " << "RESULT :"<<printexpr(quadhead[quadNumber].result);
      	cout<<"  " << "ARG2 :"<<printexpr(quadhead[quadNumber].arg2);
      	cout<<"  " << "LABEL :"<<printLabel(quadhead[quadNumber].label);
      	cout<<"  " << "LINE :"<<quadhead[quadNumber].line<<endl;}
}
expr *func_call(expr *lval, expr *args, unsigned int line ,int  starthere ){
	if(DEBUG){cout <<"############### in func call ##############"<<endl;}
	expr *functionName = emit_iftableitem(lval,yylineno);
	if(DEBUG){cout <<"############### in func call ############## 1"<<endl;}

	expr * tmp=args;
	expr * paramTable[1024];
	int i = 0;
	if(DEBUG){cout <<"############### in func call ############## 2"<<endl;}

	vector <expr*>  :: iterator it;
	if(DEBUG){cout <<"############### in func call ############## 3-"<< starthere<<endl;}
	
	for(it=expr_list.begin()+starthere; it!=expr_list.end();){
    	//cout << " " <<"NAME: " << (*it)->sym->name;
    	emit(param,NULL,NULL, (*it),-1,line);
    	it = expr_list.erase(it);
    }
	emit(call, NULL, NULL,functionName, -1, line);
	expr *result = newexpr(var_e);
	result -> sym = newtemp();
	emit(getretval, NULL, NULL, result, -1, line);
	return result;
}

expr *func_methodcall(expr *lval, string idname, unsigned int line,int starthere){
	
	expr * passID = new expr;
	//passID=lvalue_expr(idname);
	passID= constString_expr(idname);
	expr * paramTable[1024];
	int i = 0;
	expr *vardas = newexpr(var_e);
	vardas -> sym = newtemp();
	emit(tablegetelem,lval,passID, vardas,-1,line);
	//cout <<"############### in func call ##############  4"<<endl;

	vector <expr*>  :: iterator it;
  	for(it=expr_list.begin(); it!=expr_list.end();){
    	//cout << " " <<"NAME: " << (*it)->sym->name;
    		
    	emit(param,NULL,NULL, (*it),-1,line);

		it = expr_list.erase(it);
    }
	emit(param,NULL,NULL, lval,-1,line);
	expr *result = newexpr(var_e);
	result -> sym = newtemp();
	emit(call, NULL, NULL, vardas, -1, line);
	emit(getretval, NULL, NULL, result, -1, line);
	return result;
}
/*
typedef enum opcode {
 0   assign, 
 1   add, 
 2   sub, 
 3   mul, 
 4   divide, 
 5   mod,
 6   uminus, 
 7   and_op, 
 8   or_op,
 9   not_op, 
 10   if_eq, 
 11  if_not_eq,
 12   if_lesseq,  
 13   if_greatereq,   
 14   if_less,
 15   if_greater,
 16    call,      
 17     param,  
 18   ret,
 19    getretval,
 20     funcstart,
 21   funcend,   
 22   tablecreate, 
 23    jump, 
 24   tablegetelem ,
 25   tablesetelem

}iopcode;*/


 string printOpcode(iopcode op ) {
	//if (e==NULL){return "-";}
	switch(op){

		case 0:	return "assign";
				break;
		case 1:	return "add";
				break;
		case 2:	return "sub";
				break;
		case 3:return "mul";
				break;
		case 4:	return "divide";
				break;
		case 5:	return "mod" ;
				break;
		case 6:return "uminus" ;
				break;
		case 7:	return "and_op";
				break;
		case 8:	return "or_op";
				break;
		case 9:return "not_op";
				break;
		case 10:	return "if_eq";
				break;
		case 11:	return "if_not_eq";
				break;
		case 12:return "if_lesseq";
				break;
		case 13:	return "if_greatereq";
				break;
		case 14:	return "if_less";
				break;
		case 15:return "if_greater";
				break;
		case 16:	return "call";
				break;
		case 17:	return "param";
				break;
		case 18:return "ret";
				break;
		case 19:	return "getretval";
				break;
		case 20:	return "funcstart";
				break;
		case 21:return "funcend";
				break;
		case 22:return "tablecreate";
				break;
		case 23:return "jump";
				break;
		case 24:return "tablegetelem";
				break;
		case 25:return "tablesetelem";
				break;
		
		default: return "invalid opcode";
	}
}

bool uminus_validity(expr *e){

	if (e==NULL){return nullptr;}
	switch(e->type){
		case 2: case 3: case 5: case 7: case 10 : case  11:	return true; break;
		default: return false;
	}
}

void printList(void) {
  	cout << "////-----------------------------LISTERMAN PRINTS----------------------------------------------////" << endl;
  	vector<expr*>  :: reverse_iterator it;
  	int i=0;
  	for(it=expr_list.rbegin(); it!=expr_list.rend(); ++it){
      	cout<<i<<": ";
      	cout<<" |" << "this :"<<printexpr(*it)<<endl;
      	i++;      	
      }
    	
  
  cout << "////---------------------------------------------------------------------------------------////" << endl;
};


void printbreak(void) {
  	cout << "////-----------------------------LISTERMAN PRINTS----------------------------------------------////" << endl;
  	
  	int i=0;
    vector <int>  :: iterator it ;
	
	cout << "	-----------------------BREAKLIST -------------------" << endl;	
  	for(it=breakvector.begin(); it!=breakvector.end(); ++it){
			
			cout<<i<<": ";
      		cout<<" |" << "this :"<<(*it)<<endl;
      		i++;      	
      }

  
  cout << "////---------------------------------------------------------------------------------------////" << endl;
};


expr *obj_manage(int starthere){
	if(DEBUG){cout << "######### obj manage#########" << endl;}
	if(DEBUG)printQuads();
	expr * table = newexpr(newtable_e);
	table->sym = newtemp();
	//expr* iz= new expr;
	if(DEBUG)cout<<" perasa newtemp"<<endl;
	emit(tablecreate, NULL, NULL, table, -1, yylineno);
	if(DEBUG)cout<<table->type<<endl;
	if(DEBUG)cout<<" girisa apo tablecreate"<<endl;
	int i = 0;
	vector <expr*>  :: reverse_iterator it = (expr_list.rbegin() + starthere );
	if(DEBUG)printList();
	//cout << "$$$$$$ VGIKA APO THN TABLECREATE $$$$$$" << endl;
	for(; it!=expr_list.rend(); ++it){
		//if(DEBUG){cout << ">>>>>>>>>>> " <<"NAME: " << printexpr((*it)->keyval)<<endl; }
		if ((*it)->iskey==true) {
			emit(tablesetelem,table,(*it), ((*it)->keyval),-1,yylineno);
			(*it)->keyval->isval=true;

			expr_list.erase( --it.base() );
			i++;
		}
		else{
		emit(tablesetelem,table, insertVal(i,0,"INTCONST"),(*it),-1,yylineno);

		expr_list.erase( --it.base() );
		i++;
		}
		
	}

    return table;
}

void break_manage(int starthere){
	if(DEBUG){cout << "######### obj manage######### offset" << breakvector.size()<< endl;}
	if(isValid){

	vector <int>  :: iterator it = (breakvector.begin() + starthere );
	
	if(DEBUG){cout << "	-----------------------BREAKLIST -------------------" << starthere<<endl;}	
		for(; it!=breakvector.end();it++ ){
			if(starthere>breakvector.size()) break;
			if(DEBUG){cout<<" in breaklist"<<(*it)<<endl;}
			backpatch((*it),currQuad);
			if(DEBUG){cout<<"next break "<<breakvector.size()<<endl;}
			//if(breakvector.size()==1)breakvector.resize(0);
			//else 
			breakvector.erase(it);
			if(DEBUG){cout << "######### in for break manage######### offset" << breakvector.size()<< endl;}

			if (!(breakvector.size())) {/*cout<<"inbreak"<<endl;*/break;}
			if(DEBUG){cout<<"after break"<<endl;}
		}
	//cout<<" out of brklist"<<endl;
	}
}


void continue_manage(int starthere,int contjump){
	if(DEBUG){cout << "######### obj manage######### offset" << starthere<< endl;}
	if(isValid){
	vector <int>  :: iterator it = (contvector.begin() + starthere );
	//cout << "	-----------------------CONTLIST -------------------" << endl;
		
	for(; it!=contvector.end();it++ ){
			
			//cout<<" in breaklist"<<(*it)<<endl;
			backpatch((*it),contjump);
			//cout<<"next break"<<endl;
			contvector.erase(it);
			if (!(contvector.size())) {/*cout<<"inbreak"<<endl;*/break;}
			//cout<<"after break"<<endl;		
			} 
	}	
}

int load_c(int set){
			//cout<<"## loading cont##"<<endl;
			int c_index;
			
			//cout<<vc<<" "<<trueMultiVector.size()<<endl;
			if(vc==contMultiVector.size())contMultiVector.resize(2*contMultiVector.size());
			c_index=cc;
			if(set)contMultiVector[cc].push_back(quadhead.size());
			//cout<<" load passed valuses t /  "<< c_index <<" vs "<<endl;
			//print_true();
			cc++;
			return c_index; 

}

int load_b(int set){
			//cout<<"## loading break##"<<endl;
			int b_index;
			
			//cout<<vc<<" "<<trueMultiVector.size()<<endl;
			if(vc==breakMultiVector.size())breakMultiVector.resize(2*breakMultiVector.size());
			b_index=bc;
			if(set)breakMultiVector[bc].push_back(quadhead.size());
			//cout<<" load passed valuses t /  "<< b_index <<" vs "<<endl;
			//print_true();
			bc++;
			return b_index; 

}
int merge_break( int first , int second){
	int low,high;
	//cout<<" merging ... break "<<first<<" "<<second<<endl;

	//print_true();
	//low=min(first,second);
	//high=max(first,second);
	if(first==-1) return second;
	if(second==-1)return first;
	//cout<<"perasa ta first second"<<endl;
	breakMultiVector[first].insert(breakMultiVector[first].end(), breakMultiVector[second].begin(), breakMultiVector[second].end());
	//cout<<" merging mid  break "<<endl;
	//print_true();
	breakMultiVector[second].clear();	
	//cout<<" merging end  true "<<endl;
	//print_true();
	return first;
}

int merge_cont( int first , int second){
	int low,high;
	//cout<<" merging ... cont "<<endl;
	//low=min(first,second);
	//high=max(first,second);
	if(first==-1) return second;
	if(second==-1)return first;
	contMultiVector[first].insert(contMultiVector[first].end(), contMultiVector[second].begin(), contMultiVector[second].end());
	//cout<<" merging mid  cont "<<endl;
	contMultiVector[second].clear();	
	return first;
}


void break_backpatch(int starthere,int endhere,int contjump){
  //cout << "////-----------------------------break-- backpatch-------------------------------------------////" << endl;
  vector <int> :: iterator it;
  if (starthere==-1)return;
  for(it=breakMultiVector[starthere].begin(); it!=breakMultiVector[starthere].end(); it++){
    
            backpatch((*it),contjump);  
  }

};
void cont_backpatch(int starthere,int endhere,int contjump){
  //cout << "////-----------------------------cont-- backpatch-------------------------------------------////" << endl;
  vector <int> :: iterator it;
  if (starthere==-1)return;
  for(it=contMultiVector[starthere].begin(); it!=contMultiVector[starthere].end(); it++){
    
            backpatch((*it),contjump);  
  }

};
//extern vector <vector<int>> trueMultiVector;
//extern vector <vector<int>> falseMultiVector;
//extern int vc;



int load_t(){
			//cout<<"## loading t##"<<endl;
			int t_index;
			print_true();
			print_false();
			if(DEBUG)cout<<vc<<" "<<trueMultiVector.size()<<endl;
			if(vc==trueMultiVector.size())trueMultiVector.resize(2*trueMultiVector.size());
			t_index=vc;
			trueMultiVector[vc].push_back(quadhead.size()-2);
			//cout<<" load passed valuses t /  "<< t_index <<" vs "<<endl;
			print_true();
			return t_index; 

}





int load_f(){
			//cout<<"## loading f##"<<endl;
			int f_index;
			f_index=vc;
			if(vc==falseMultiVector.size())falseMultiVector.resize(2*falseMultiVector.size());
			//f_index=vc;
			falseMultiVector[vc].push_back(quadhead.size()-1);
			//cout<<" load passed valuses  / f " <<" vs "<< f_index<<endl; 
			vc++;
			print_false();
			return f_index;

}


void swap(int truer, int falser) {
  	
  	if(DEBUG){cout << "////-----------------------------swap PRINTS----------------------------------------------////"
  	<<truer<< "        " <<falser<<endl;
  	print_true();
  	print_false();

  	cout << "////-----------------------------sizes----------------------------------------------////" << endl;}
  	//cout << "------ truevector :" <<truevector.size() <<endl;
  	//cout << "------ falsevector :" <<falsevector.size() <<endl;

	vector<int> temptrue;
	vector<int> tempfalse;

  	temptrue.insert(temptrue.end(), trueMultiVector[truer].begin(), trueMultiVector[truer].end());
  	//cout<<" first"<<endl;;

  	trueMultiVector[truer].clear();
  	//cout<<" second"<<endl;;
  	tempfalse.insert(tempfalse.end(), falseMultiVector[falser].begin(), falseMultiVector[falser].end());
  	//cout<<" third"<<endl;;

  	falseMultiVector[falser].clear();
  	//cout<<" fourth"<<endl;;
  	if(DEBUG){print_true();
  	print_false();}
  	trueMultiVector[truer].insert(trueMultiVector[truer].end(), tempfalse.begin(), tempfalse.end());
  	tempfalse.clear();
  	falseMultiVector[falser].insert(falseMultiVector[falser].end(), temptrue.begin(), temptrue.end());
  	temptrue.clear();

  
  if(DEBUG){cout << "////---------------------------------------------------------------------------------------////" << endl;
  print_true();
  print_false();}
};


void false_backpatch(int starthere,int endhere,int contjump){
 if(DEBUG){ cout << "////-----------------------------false-- backpatch-------------------------------------------////" << endl;}
  vector <int> :: iterator it;
  for(it=falseMultiVector[starthere].begin(); it!=falseMultiVector[starthere].end(); it++){
    
            backpatch((*it),contjump);  
  }
  //cout << "////---------------------------------------------------------------------------------------////" << endl;
  
	//print_false();
	//print_true();
  //falseMultiVector[starthere].resize(0);
  
  //cout<<" after clear false"<<endl;

  //print_false();
  //print_true();
};



void true_backpatch(int starthere,int endhere,int contjump){
  if(DEBUG){cout << "////----------------------------true- backpatch---------------------------------------------////" << endl;}
  vector <int> :: iterator it;
  for(it=trueMultiVector[starthere].begin(); it!=trueMultiVector[starthere].end(); it++){
    
            backpatch((*it),contjump);  
  }
  //cout << "////---------------------------------------------------------------------------------------////" << endl;
  //print_true();

	//print_false();
  //trueMultiVector[starthere].clear();
  //cout<<" after clear true"<<endl;
  //print_true();
  //print_false();
};


void false_rest(){
  cout << "////-----------------------------false rest----------------------------------------------////" << endl;
  vector <vector<int>>  :: iterator it;
  vector <int> :: iterator jt;
  for(it=falseMultiVector.begin(); it!=falseMultiVector.end(); it++){
    if(!(*it).empty()){
    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
       backpatch((*jt),currQuad);
        
    }
    }
  }
  //cout << "////---------------------------------------------------------------------------------------////" << endl;
};

void true_rest(){
  //int iter=  int()(currQuad);
  if(DEBUG){cout << "////-----------------------------true rest---------------------------------------------////" << endl;}
  vector <vector<int>>  :: iterator it;
  vector <int> :: iterator jt;
  for(it=trueMultiVector.begin(); it!=trueMultiVector.end(); it++){
    if(!(*it).empty()){
    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
       backpatch((*jt),currQuad);

    }
    }
  }
  cout << "////---------------------------------------------------------------------------------------////" << endl;
};

int merge_true( int first , int second){
	int low,high;
	//cout<<" merging ... true "<<endl;

	if(DEBUG){print_true();}
	low=min(first,second);
	high=max(first,second);
	trueMultiVector[first].insert(trueMultiVector[first].end(), trueMultiVector[second].begin(), trueMultiVector[second].end());
	


	//vector<std::vector<int>> myVec;
	


	//cout<<" merging mid  true "<<endl;

	if(DEBUG){print_true();}
	//sort(trueMultiVector.begin(), trueMultiVector.end());
	//trueMultiVector.erase(unique(trueMultiVector.begin(), trueMultiVector.end()), trueMultiVector.end());
	trueMultiVector[second].clear();

	//cout<<" mergins ... false "<<endl;
	//sort(trueMultiVector[low].begin(), trueMultiVector[low].end());
	//trueMultiVector[low].erase(unique(trueMultiVector[low].begin(), trueMultiVector[low].end()), trueMultiVector[low].end());
	
	
	//cout<<" merging end  true "<<endl;
	if(DEBUG){print_true();}
	return first;
}


int merge_false( int first , int second){
	//cout<<" merging ... false "<<endl;

	int low,high;
	if(DEBUG){print_false();}
	//low=min(first,second);
	//high=max(first,second);
	falseMultiVector[first].insert(falseMultiVector[first].end(), falseMultiVector[second].begin(), falseMultiVector[second].end());
	//sort(falseMultiVector[low].begin(), falseMultiVector[low].end());
	///falseMultiVector[low].erase(unique(falseMultiVector[low].begin(), falseMultiVector[low].end()), falseMultiVector[low].end());
	if(DEBUG){print_false();
	cout<<" merging mid  false "<<endl;}

	//sort(falseMultiVector.begin(), falseMultiVector.end());
	//falseMultiVector.erase(unique(falseMultiVector.begin(), falseMultiVector.end()), falseMultiVector.end());
	falseMultiVector[second].clear();
	//sort(falseMultiVector[first].begin(), falseMultiVector[first].end());
	//falseMultiVector[first].erase(unique(falseMultiVector[first].begin(), falseMultiVector[first].end()), falseMultiVector[first].end());
	
	if(DEBUG){cout<<" merging end  false "<<endl;
	print_false();}
	return first;
}


void print_true(){
  if(DEBUG){cout << "////-----------------------------true list----------------------------------------------////" << endl;
  vector <vector<int>>  :: iterator it;
  vector <int> :: iterator jt;
  int j=0;
  for(it=trueMultiVector.begin(); it!=trueMultiVector.end(); it++){
    if(!(*it).empty()){cout<<"top index "<<j<<endl;
    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
        cout << " " <<"NAME: " << (*jt)<<endl;
        

    }
    }j++;
  }
  cout << "////---------------------------------------------------------------------------------------////" << endl;}
};


void print_false(){
  if(DEBUG){cout << "////-----------------------------false list----------------------------------------------////" << endl;
  vector <vector<int>>  :: iterator it;
  vector <int> :: iterator jt;
  int i=0;
  for(it=falseMultiVector.begin(); it!=falseMultiVector.end(); it++){
  	
    if(!(*it).empty()){cout<<"top index "<<i<<endl;
    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
        cout << " " <<"NAME: " << (*jt)<<endl;
        

    }
    }i++;
  }
  cout << "////---------------------------------------------------------------------------------------////" << endl;}
};

void bool_assign(expr *lval, expr *rval){

	//cout<<"in boolexpr eimaste "<<rval->sym->type<<endl;
	true_backpatch(rval->true_index,0,currQuad);
	emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, rval, -1, yylineno);
	emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
	false_backpatch(rval->false_index,0,currQuad);
	emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, rval, -1, yylineno);
	//emit(assign,rval,NULL,lval,-1,yylineno);
	//cout<<"out of boolexpr eimaste"<<endl;

}

expr* true_test(expr* expr1,expr* arg, int l_int){

	if(expr1->type!=boolexpr_e){
				//emit(if_eq,$<exprvalue>1, , NULL, (int)(currQuad +2), yylineno);
				emit(if_eq,expr1,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno);
				emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
				//expr *result = new expr;
				arg = newexpr(boolexpr_e);
				arg->sym = newtemp();
				arg->true_index= load_t();
				arg->false_index= load_f();
				//cout<<"this that?"<<arg->sym->name<<endl;
				arg->changeLabel= true;
				//cout <<" ### "<<arg->false_index<<endl;


				if (expr1->fromNot){
					swap(arg->true_index,arg->false_index);
				}

}
else{

				arg=expr1;
				//cout<<"this that?"<<arg->sym->name<<endl;
			}
		return arg;
}


//begin (0) + place
//quadhead.size()-1 einai to last
int load_t_or(int l_int){
			//cout<<"## loading t or ##"<<endl;
			int t_index;
			//quadhead.begin()+place
			t_index=vc;	
			trueMultiVector[vc].push_back(l_int);
			//cout<<" load passed valuses t /  "<< t_index <<" vs "<<endl;
			print_true();
			return t_index; 

}





int load_f_or(int l_int){
			//cout<<"## loading f##"<<endl;
			int f_index;
			f_index=vc;
			falseMultiVector[vc].push_back(l_int+1);
			//cout<<" load passed valuses  / f " <<" vs "<< f_index<<endl; 
			vc++;
			print_false();
			return f_index;

}

/*



void print_false(){
  cout << "////-----------------------------false list----------------------------------------------////" << endl;
  vector <vector<int>>  :: iterator it;
  vector <int> :: iterator jt;
  int i=0;
  for(it=falseMultiVector.begin(); it!=falseMultiVector.end(); it++){
  	
    if(!(*it).empty()){cout<<"top index "<<i<<endl;
    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
        cout << " " <<"NAME: " << (*jt)<<endl;
        

    }
    }i++;
  }
  cout << "////---------------------------------------------------------------------------------------////" << endl;
};
*/

void fix_quads( int t_int ,int f_int ){
	//cout<<"fixing quads--------------"<<endl;
	print_true();
	print_false();
	//cout<<"psaxnw true"<< t_int<<" false "<<f_int<<endl;

  vector <vector<int>>  :: iterator it;
  vector <int> :: iterator jt;
  int i=0;
  for(it=falseMultiVector.begin(); it!=falseMultiVector.end(); it++){
  	
    if(!(*it).empty()){//cout<<"top index "<<i<<endl;
    if (i==f_int){
	    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
	       // cout << " " <<"itan "<<(*jt)<<endl;
	        (*jt)=(*jt)+2;
	        //cout << " " <<"einai "<<(*jt) <<endl;

	        

	    }
	    }i++;
    }
  }
 if(DEBUG){ print_false();}

   i=0;
  for(it=trueMultiVector.begin(); it!=trueMultiVector.end(); it++){
  	
    if(!(*it).empty()){//cout<<"top index "<<i<<endl;
    if (i==t_int){
	    for(jt=(*it).begin(); jt!=(*it).end(); jt++){
	        //cout << " " <<"NAME: " << <<endl;
	        (*jt)=(*jt)+2;
	        

	    }
	    }i++;
    }
  }
  if(DEBUG){print_true();}
}


expr* true_test_or(expr* expr1,expr* arg,expr* arg2 , int l_int) {

	if(expr1->type!=boolexpr_e){
				//emit(if_eq,$<exprvalue>1, , NULL, (int)(currQuad +2), yylineno);
				/*
				if(arg2->type!=boolexpr_e){
					emit_or(if_eq,expr1,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno,l_int);
					emit_or(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno,l_int+1);
					cout<<"edw push"<<endl;

				}
				else{
				emit(if_eq,expr1,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno);
				emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
				}

				*/

				emit_or(if_eq,expr1,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno,l_int);
				emit_or(jump, NULL, NULL, NULL, l_int+1, yylineno,l_int+1);
				//cout<<"edw push"<<endl;

				//expr *result = new expr;
				arg = newexpr(boolexpr_e);
				arg->sym = newtemp();
				arg->true_index= load_t_or(l_int);
				arg->false_index= load_f_or(l_int);
				//cout<<"this that?"<<arg->sym->name<<endl;
				arg->changeLabel= true;
				//cout <<" ### "<<arg->false_index<<endl;
				vector<quad>  :: iterator it;

			  	int i=0;
			  	for(it=quadhead.begin()+l_int+1; it!=quadhead.end(); it++){
			      
			      	if ((*it).label){
							(*it).label= (*it).label+2;
					}
			   		
			     }

				/*
				void printQuads(void) {
			  	cout << "////-----------------------------QUAD PRINTS----------------------------------------------////" << endl;
			  	vector<quad>  :: iterator it;
			  	int i=0;
			  	for(it=quadhead.begin(); it!=quadhead.end(); it++){
			      	cout<<i<<": ";

			      	cout<<" |" << "OPCODE :"<<printOpcode((*it).op);
			      	cout<<"  " << "RESULT :"<<printexpr((*it).result);
			      	cout<<"  " << "ARG1 :"<< printexpr((*it).arg1);//->sym->name
			      	cout<<"  " << "ARG2 :"<<printexpr((*it).arg2);
			      	cout<<"  " << "LABEL :"<<printLabel((*it).label);
			      	cout<<"  " << "LINE :"<<(*it).line<<endl;
			      	i++;
			      	
			      }
			    	
			  
			  cout << "////---------------------------------------------------------------------------------------////" << endl;
			};

				*/

				if (expr1->fromNot){
					swap(arg->true_index,arg->false_index);
				}

			}
else{

				arg=expr1;
				//cout<<"this that?"<<arg->sym->name<<endl;
			}
		return arg;
}




void fix_elist(int from,int to){



	expr_list.resize(from);


}
