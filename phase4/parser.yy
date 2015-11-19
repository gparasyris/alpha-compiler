
%{
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include "hash.h"
#include "intermediate.h"
#include "target.h"
#include <fstream>

#include "parser.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

/****************/
extern string blvr;
/****************/	
int Lval_used=0;     	
int is_function=0;	 	
int is_call=0;			
int is_funcall=0;		
int is_funcdef=0; 		// otan pianw funcdef prosoxi stou pou epsitrefei se zero san tin coca cola zero 
string functionName; 	//to function name 8a einai eite yytext eite to paragomeno apo tin sunartisi y=x;
///
string defaultName="_sysfuncName_"; //default pro8ema
int prefix_count=0; 	
bool autoName=false; 	//on when we need autoname (id_tmp = keno )
int illcount=0;
int idcount=0;
int templast=0;
int here=0;
extern string buff; 	// nomizw de to usarw
Symbol toAdd;
Symbol *s, *func1, *argcheck, *localcheck;
bool lvalfunc=false; 	// on when func is found as ID in  lval ID edw 8elei ligo debug
//std::ofstream outfile;

int yylex();
extern char *yytext;
extern int yylineno;
extern FILE* yyin;

extern vector<quad>		quadhead ;
extern unsigned int	total;
extern unsigned int 	currQuad;
extern string tempname;
extern unsigned int tempcounter;

extern unsigned int programVarOffset;
extern unsigned int functionLocalOffset ;
extern unsigned int formalArgOffset ;
extern unsigned int scopeSpaceCounter;

extern vector <vector<Symbol>> Scopelist;
extern unordered_multimap<int,Symbol> Syriza;
list<int> assignParts;
list<string> functions;
vector<expr*> expr_list;
vector<int> breakvector;
vector<int> contvector;
stack <int> aerials;
stack <int> ownage;
vector <vector<int>> contMultiVector;
vector <vector<int>> breakMultiVector;
vector <vector<int>> trueMultiVector;
vector <vector<int>> falseMultiVector;
int vc=0;
int bc=0;
int cc=0;

//
int tracktrue,trackfalse;
//

typedef struct forstruct{
	int test;
	int enter;
}forstr;


typedef struct bc_indexes{
	int break_index=-1;
	int cont_index=-1;
}tf;

bool isLocalVar = nullptr;							//isLocalVar
expr *tmpsym;
expr * tmp, *tmpexpr;
bool uminusValid;

int maxFScope=0;								//might be boolean	deepestFunctionScope
int maxScope=0;									//deepestScope
int isLoop=0;									//might be boolean
int elist_start=0;

bool clearList= false;
bool isValid= true;

int yyerror(const char * yaccProvidedMessage);
struct forstruct *fortmp;
struct true_false_indexes *tftmp;
char* staurosDota;

%}


%error-verbose
%start program

%union{

	int intvalue;
	double dvalue;
	char* strvalue;
	struct expre* exprvalue;
	struct symT * symvalue;
	int isNormalcall=0;
	struct expre* start;
	int startHere;
	int break_index;
	int cont_index;
	struct forstruct* fordata;
	struct bc_indexes * indexes;
	
}

%token <intvalue> INTEGER;
%token <strvalue> STRING;
%token <strvalue> IDENTIFIER;
%token <dvalue> REALNUMBER;

%token <strvalue> KEYWORD_IF KEYWORD_ELSE KEYWORD_WHILE KEYWORD_FOR KEYWORD_FUNCTION KEYWORD_RETURN KEYWORD_BREAK KEYWORD_CONTINUE KEYWORD_AND KEYWORD_NOT KEYWORD_OR KEYWORD_LOCAL KEYWORD_TRUE KEYWORD_FALSE KEYWORD_NIL NOKEY ASSIGN PLUS MINUS MULTIPLY DIVIDE MODULO EQUAL NOT_EQUAL INCREMENT DECREMENT LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA  COLON DOUBLE_COLON DOT DOUBLE_DOT INTCONST REALCONST ID LINECOMMENT COMMENT NESTED_COMMENT CLOSE_COMMENT UNDEFINED
%type <symvalue> funcdef
%type <intvalue> whilestart whilecond S Q L R
%type <strvalue> stmt ifstmt  elseprefix whilestmt forstmt returnstmt block  assignexpr term  primary call objectdef const member elist callsuffix normcall methodcall indexed indexedelem id_tmp
%type <exprvalue> expr lvalue 
%type <fordata> forprefix
%type <symvalue> functionprefix
%type <intvalue> funcbody


%left ASSIGN
%left KEYWORD_OR 
%left KEYWORD_AND
%left KEYWORD_NOT


%nonassoc EQUAL NOT_EQUAL GREATER_THAN GREATER_EQUAL LESS_THAN LESS_EQUAL

%left PLUS MINUS 
%left  MULTIPLY DIVIDE MODULO
%right INCREMENT DECREMENT UMINUS
%left DOT DOUBLE_DOT
%left LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS


%%
program: stmt program 
	|	{
			cout<<yylineno<<": |" << "Program "<< endl;
		}
        ;
stmt:	expr SEMICOLON		
		{
			
			if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			illcount=0;
			assignParts.clear();
			//cout<<yylineno<<": |"<< "Expr Semicolon detected. "<< endl;
			idcount=0;
			if(!($<isNormalcall>1)){
				if($<exprvalue>1->type==boolexpr_e){
					false_backpatch($<exprvalue>1->false_index,0,currQuad);
					emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, $<exprvalue>1, -1, yylineno);
					emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
					true_backpatch($<exprvalue>1->true_index,0,currQuad);
					emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, $<exprvalue>1, -1, yylineno);
					emit(if_eq,$<exprvalue>1,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
					emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
				}
			}
			if ($<exprvalue>1->type==boolexpr_e){
				if(DEBUG){cout<<"kane backpatch"<<endl;}
				false_backpatch($<exprvalue>1->false_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, $<exprvalue>1, -1, yylineno);
				emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
				true_backpatch($<exprvalue>1->true_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, $<exprvalue>1, -1, yylineno);
				//emit(if_eq,$<exprvalue>1,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
				//$<intvalue>$ =  currQuad-1;
			}
			resettemp();
			bc_indexes * bc= new bc_indexes;
			$<indexes>$=bc;
			//$<break_index>$=-1;

		}
	| ifstmt
		{
			//cout<<yylineno<<": |" << "Expr ifstmt detected. "<< endl;
			//$<break_index>$=$<break_index>1;
  			//$<cont_index>$=$<cont_index>1;
  			bc_indexes * bc= new bc_indexes;
  			bc->break_index=$<indexes>1->break_index;
			bc->cont_index=$<indexes>1->cont_index;
			$<indexes>$=bc;
		}
	| whilestmt
		{
			//cout<<yylineno<<": |" << "Expr whilestmt detected. "<< endl;
			//
			//$<break_index>$=-1;
			bc_indexes * bc= new bc_indexes;
			$<indexes>$=bc;
		}
	| forstmt
		{
		//cout<<yylineno<<": |" << "Expr forstmt detected. "<< endl;
		//$<break_index>$=-1;
		bc_indexes * bc= new bc_indexes;
		$<indexes>$=bc;
		}
	| returnstmt
		{	
			if(maxFScope==0){
				cout << "Syntax Error in line :"<< yylineno << "Return out of function ."<<endl;
				isValid=false;

			}
			//cout<<yylineno<<": |" << "Expr Returnstmt  detected. "<< endl;
			//$<break_index>$=-1;
			bc_indexes * bc= new bc_indexes;
			$<indexes>$=bc;
		} 
	| KEYWORD_BREAK SEMICOLON
		{	
			//cout << "ISLOOP: "<< isLoop << endl;
			if(isLoop==0){
				cout << "Syntax Error in line :"<<yylineno <<" Break outside loop." << endl;
				isValid=false;
			}
			//cout<<yylineno<<": |" << "Expr Break  detected. "<< endl;

			bc_indexes * bc= new bc_indexes;
			bc->break_index=load_b(1);
			//break handle
			//breakvector.size();
			breakvector.push_back(quadhead.size());
			///printbreak();
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
			if(DEBUG){cout<<"            inserting into break <<<<<<<<"	<<endl;
			cout<<" passing break; -> stmt"<<$<break_index>$<<endl;
			cout<<" passing break; cont -> stmt"<<$<cont_index>$<<endl;}
			//printbreak();
			$<indexes>$=bc;

		}
	| KEYWORD_CONTINUE SEMICOLON
		{
			if(isLoop==0){
				cout << "Syntax Error in line :"<<yylineno <<" Continue outside loop." << endl;
				isValid=false;
			}
			//cout<<yylineno<<": |" << "Expr Continue  detected. "<< endl;
			bc_indexes * bc= new bc_indexes;
			bc->cont_index=load_c(1);
			contvector.push_back(quadhead.size());
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
			if(DEBUG){cout<<" passing cont; -> stmt"<<$<break_index>1<<endl;
			cout<<" passing cont; -> stmt"<<$<cont_index>$<<endl;}

			$<indexes>$=bc;
			

		}
	| block
		{
			//$<break_index>$=$<break_index>1;
						///contvector cont_index
			//$<cont_index>$=$<cont_index>1;
			if(DEBUG){cout<<yylineno<<": |" << "Expr block  detected. "<< $<break_index>$<<endl;	
			cout<<yylineno<<": |" << "Expr block  detected. "<< $<cont_index>$<<endl;	}
			bc_indexes * bc= new bc_indexes;
			bc->break_index=$<indexes>1->break_index;
			bc->cont_index=$<indexes>1->cont_index;
			$<indexes>$=bc;


		}
	| funcdef
		{
			//cout<<yylineno<<": |" << "Expr funcdef detected. "<< endl;
			bc_indexes * bc= new bc_indexes;
			$<indexes>$=bc;
			//$<break_index>$=-1;
		}
	| SEMICOLON
		{
			//$<break_index>$=-1;
			bc_indexes * bc= new bc_indexes;
			//cout<<yylineno<<": |" << "Expr Semicolon detected. "<< endl;
			$<indexes>$=bc;
		}
	| error SEMICOLON {yyerrok; cout<<"Major Grammar Error in line :"<<yylineno<<endl;
			assignParts.clear();
			bc_indexes * bc= new bc_indexes;
			$<indexes>$=bc;
			//cout<<"ADEIAZW ASSIGN PARTS"<<endl;
			}
	;
expr:	assignexpr		
		{
			//$<exprvalue>$=newexpr(assignexpr_e);
			if(DEBUG)cout<<$<exprvalue>1->type<<" "<<endl;//printexpr($<exprvalue>1->index)<<end;
			//$<exprvalue>$->sym=newtemp();
			//emit(assign,$<exprvalue>1,NULL,$<exprvalue>$,-1,yylineno);
			//resettemp();
			//from here

			//cout<<$<exprvalue>1->sym->name<<" "<<$<exprvalue>1->index->sym->name<<endl;
			expr* result = new expr;
			result = newexpr(assignexpr_e);
			result->sym=newtemp();
			//$<exprvalue>$=newexpr(assignexpr_e);
			//$<exprvalue>$->sym=newtemp();
			
			if ($<exprvalue>1->type==1){
				// eksetasi an stekei!
				emit(tablegetelem,$<exprvalue>1,$<exprvalue>1->index, result ,-1,yylineno);
			}
			else{
				emit(assign,$<exprvalue>1,NULL,result,-1,yylineno);	
			}
			//tohere
			$<exprvalue>$=result;
			//cout<<yylineno<<": |" << "Expr assignexpr  detected. idc: "<<idcount<<" TYPE: " << $<exprvalue>$->type << $<exprvalue>$->sym->offset << endl;
			//$<exprvalue>$ = $<exprvalue>1;
			idcount--;
			//tablegetelem t0 pinakas  
			/*
			[5/9/15, 13:28:15] stayros dag: Αν εννοείς την extra εντολή μετά το tablesetelem, αυτή είναι μια tablegetelem με την οποία κρατάμε την τιμή που μόλις κάναμε assign σε ένα temp ώστε να μπορεί να χρησιμοποιηθεί αργότερα. Συνολικά λοιπόν, 
			το a.b = 3 παράγει τα quads:
			1. tablesetelem a b 3
			2. tablegetelem _t0 a b
			[5/9/15, 13:28:53] stayros dag: ara den 8elei assign
			*/
		}

	//-----------------------------------------Copy here---------------------------------------------------------------------
	| expr PLUS expr			{
									if(DEBUG){cout<<yylineno<<": |" << "Expr + expr => "<<endl;}
									//cout << "TYPE OF 1st EXPR: "<< $<exprvalue>1->type <<  "TYPE OF 2st EXPR: "<< $<exprvalue>3=x->type << endl;
									if(validForOp($<exprvalue>1) && validForOp($<exprvalue>3)){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in addition operation" << endl;
									}
							   		$<exprvalue>$ = op_emit(add,$<exprvalue>1,$<exprvalue>3,yylineno);
							   }

	| expr MINUS expr			{
									if(DEBUG){cout<<yylineno<<": |" << "Expr - expr => "<<endl;}
									if(validForOp($<exprvalue>1) && validForOp($<exprvalue>3)){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in subtraction operation" << endl;
									}
								 $<exprvalue>$ = op_emit(sub,$<exprvalue>1,$<exprvalue>3,yylineno);
								}

	| expr MULTIPLY expr		{
									if(DEBUG){cout<<yylineno<<": |" << "Expr * expr => "<<endl; }
									if(validForOp($<exprvalue>1) && validForOp($<exprvalue>3)){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in multiplication  operation" << endl;
									}
								 	$<exprvalue>$ = op_emit(mul,$<exprvalue>1,$<exprvalue>3,yylineno);
								 }

	| expr DIVIDE expr			{
									if(DEBUG){cout<<yylineno<<": |" << "Expr / expr => "<<endl;}
									if(validForOp($<exprvalue>1) && validForOp($<exprvalue>3)){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in division operation" << endl;
									}
								 	$<exprvalue>$ = op_emit(divide,$<exprvalue>1,$<exprvalue>3,yylineno);
								}

	| expr MODULO expr			{
									if(DEBUG){cout<<yylineno<<": |" << "Expr %% (mod) => "<<endl;}
									if(validForOp($<exprvalue>1) && validForOp($<exprvalue>3)){
										isValid=true;
									}
									else{
										isValid=false;
										cout << "Error line: "<<yylineno<< " illegal operands in modulo operation" << endl;
									}
								 	$<exprvalue>$ = op_emit(mod,$<exprvalue>1,$<exprvalue>3,yylineno);
								}
	///
	| expr GREATER_THAN expr	{
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr > expr => "<< endl; 
			
			emit(if_greater,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			$<exprvalue>$ = result;
			//cout<<"efuga"<<endl;;

			}
	| expr GREATER_EQUAL expr	{
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
		lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr >= expr => "<< endl; 
			
			emit(if_greatereq,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			$<exprvalue>$ = result;

			
			
			//cout <<" in greater eq "<< $<exprvalue>$->true_index << " | "<<$<exprvalue>$->false_index<<endl;
			}
	| expr LESS_THAN expr		{

		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
		lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr < expr => "<<endl;
			emit(if_less,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			$<exprvalue>$ = result;


			}
	| expr LESS_EQUAL expr		{
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr <= expr => "<<endl;
			
			emit(if_lesseq,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			$<exprvalue>$ = result;


			}
	| expr EQUAL expr			{
		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr == expr => "<<endl;

			emit(if_eq,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			$<exprvalue>$ = result;


			}
	| expr NOT_EQUAL expr		{

		if (lvalfunc){//cout<<"kleinw lvalfunc"<<endl;
			lvalfunc=0;}
			//cout<<yylineno<<": |" << "Expr != expr => "<<endl; 

			emit(if_not_eq,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
			emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
			expr *result = new expr;
			result = newexpr(boolexpr_e);
			result->sym = newtemp();
			result->true_index= load_t();
			result->false_index= load_f();
			
			$<exprvalue>$ = result;


			}
	| expr KEYWORD_AND L expr		{
		if (lvalfunc){/*cout<<"kleinw lvalfunc"<<endl;*/lvalfunc=0;}
			//true_backpatch($<exprvalue>1->true_index, $<exprvalue>1->true_index,currQuad);

			//cout<<yylineno<<": |" << "!!!!!!!!!!!!!Expr && expr => "<<$<intvalue>3<< "VS"<<currQuad<<endl; 
	
			////

			expr * arg1= new expr;
			expr * arg2= new expr;
			expr * result = new expr;
			result = newexpr(boolexpr_e);
			result->sym=newtemp();

			arg1 = true_test($<exprvalue>1,arg1,$<intvalue>3);
			if (arg1->changeLabel) $<intvalue>3=currQuad;
			
			//cout <<" ### "<<arg1->false_index<<endl;
			
			arg2 = true_test($<exprvalue>4,arg1,$<intvalue>3);

			true_backpatch(arg1->true_index, arg1->true_end ,$<intvalue>3);
			//cout<<"edw!!!"<<endl;
			result->true_index=arg2->true_index;
			result->false_index=merge_false(arg1->false_index,arg2->false_index);
			result->isAnd = false;
			$<exprvalue>$=result;


			//cout<<"efuga apo to and"<<endl;
			}
	| expr KEYWORD_OR L expr		{
		if (lvalfunc){/*cout<<"kleinw lvalfunc"<<endl;*/lvalfunc=0;}
			//cout<<yylineno<<": |" << "!!!!!!!!!!!!!!Expr || expr => " << $<intvalue>3 << "VS"<<currQuad <<endl; 
			expr * arg1= new expr;
			expr * arg2= new expr;
			expr * result = new expr;
			expr *temp = new expr;
			result = newexpr(boolexpr_e);
			result->sym=newtemp();
			
			/*
			auto it = myvector.emplace ( myvector.begin()+1, 100 );
 			myvector.emplace ( it, 200 );
  			myvector.emplace ( myvector.end(), 300 )
		
		
			*/
			arg1 = true_test_or($<exprvalue>1,arg1,$<exprvalue>4,$<intvalue>3);
			//arg1 = true_test($<exprvalue>1,arg1,$<intvalue>3);
			//expr *temp = new expr;
			if (arg1->changeLabel){ 

				//$<intvalue>3=arg1->false_index;

			}
			

			if(DEBUG){cout<<"============================ indexes :"<<arg1->true_index<<"  |  "<<arg1->false_index<<endl;
			print_true();
	 		print_false();}
			
			//cout <<" ### "<<arg1->false_index<<endl;
			
			arg2 = true_test($<exprvalue>4,arg1,$<intvalue>3);
			/*if (arg1->changeLabel){ 
				temp= arg1;
				arg1=arg2;
				arg2= temp;

			}*/
			if (arg1->changeLabel){ 

				//$<intvalue>3=currQuad;
				//$<intvalue>3=currQuad;
				$<intvalue>3=falseMultiVector[arg1->false_index][0]+1;
				if(DEBUG){cout<<"NEW L"<<$<intvalue>3<<endl;}
				if(DEBUG)cout<<falseMultiVector[arg1->false_index][0]<<endl;
				if(quadhead.size()>falseMultiVector[arg1->false_index][0]){
				if(DEBUG){cout<<"changelabel"<<endl;}
			  	vector<quad>  :: iterator it;
			  	if(!(arg2->changeLabel)) fix_quads(arg2->true_index, arg2->false_index);


				}
			}

			if(DEBUG)cout<<arg1->false_index<<endl;
			if(DEBUG)cout<<arg2->false_index<<endl;
			print_false();
			if(DEBUG)cout<<arg1->true_index<<endl;
			if(DEBUG)cout<<arg2->true_index<<endl;
			print_true();




			false_backpatch(arg1->false_index, arg1->false_end ,$<intvalue>3);
			//cout<<"telos false"<<endl;;
			result->true_index=merge_true(arg1->true_index,arg2->true_index);
			result->false_index=arg2->false_index;
			result->isAnd = false;
			$<exprvalue>$=result;
			


			}



	////
	| term						{
								//cout<<yylineno<<": |" << "Terminal " <<$<isNormalcall>1<< endl;
								expr *tmp = new expr;
								tmp= $<exprvalue>1;
								//if ()
								int normal=$<isNormalcall>1;

								
								//$<true_index>$=tracktrue;
								//$<false_index>$=trackfalse;
								$<exprvalue>$ = tmp;
								$<isNormalcall>$=normal;
								//cout<<"term efuga"<<endl;

								}
	;
	//-------------------------------------------------------------------------------Copy here---------------------------
	
term:	LEFT_PARENTHESIS expr RIGHT_PARENTHESIS	{
				
					if(lvalfunc){
							lvalfunc =0;
					}
					//cout<<yylineno<<": |" << "L_parent Expr R_parent "<< endl;

					expr *tmp = new expr;
					tmp= $<exprvalue>2;


					$<exprvalue>$ = tmp;

					//cout<<"efuga"<<$<exprvalue>$->true_index<<endl;

					//$<exprvalue>$ = $<exprvalue>2;
					}
	| MINUS expr %prec UMINUS	
		{

			if(validForOp($<exprvalue>2)) {
										isValid=true;
										lvalfunc=0;
									}
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. MINUS EXPR"<<endl;
				lvalfunc = 0;
				isValid=false;
			}
			uminusValid = uminus_validity($<exprvalue>2);
			if(uminusValid){
				cout << "Invalid assignment to uminus operator" << endl;
			}
			$<exprvalue>$ = newexpr(arithexpr_e);
			$<exprvalue>$->sym = newtemp();
			emit(uminus ,$<exprvalue>2, NULL, $<exprvalue>$, -1, yylineno);
			//cout<<yylineno<<": |" << "Mnus Expr "<< endl;
		}		
	| KEYWORD_NOT expr
		
		{	
			lvalfunc = 0;
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. NOT EXPR"<<endl;
				lvalfunc = 0;
				isValid=false;
			}
			expr *result = new expr;
			//result = newexpr(boolexpr_e);
			//result->sym = newtemp();

			if($<exprvalue>2->type!=boolexpr_e){
				//emit(if_eq,$<exprvalue>1, , NULL, (int)(currQuad +2), yylineno);
				//emit(if_eq,$<exprvalue>2,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno);
				//emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
				//expr *result = new expr;
				//result = newexpr(boolexpr_e);
				//result->sym = newtemp();
				result =$<exprvalue>2;
				result->true_index= load_t();
				result->false_index= load_f();
				result -> fromNot=true;
				//cout<<"this that?"<<arg1->sym->name<<endl;
				//$<intvalue>3=currQuad;



				/*

				emit(if_not_eq,$<exprvalue>1, $<exprvalue>3, NULL, (int)(currQuad +2), yylineno);
				emit(jump, NULL, NULL, NULL, (int)(currQuad +1), yylineno);
				expr *result = new expr;
				result = newexpr(boolexpr_e);
				result->sym = newtemp();
				result->true_index= load_t();
				result->false_index= load_f();	
				$<exprvalue>$ = result;

				*/
			}
			else{

					result->type=boolexpr_e;
					result->true_index=$<exprvalue>2->true_index;
					result->false_index=$<exprvalue>2->false_index;
					result = $<exprvalue>2;
					swap(result->true_index,result->false_index);
			}


			
			//cout<<" indexes "<<result->true_index<<" "<<result->false_index<<endl;
			
			//result->true_index= $<exprvalue>2->true_index;
			//result->false_index= $<exprvalue>2->false_index;
			$<exprvalue>$=result;
			//$<exprvalue$=$<exprvalue>2;
			//$<exprvalue>$->type=  boolexpr_e;
			//cout<<yylineno<<": |" << "Not expr aaaaaaaaaaaaa "<< endl;
		}

	| INCREMENT lvalue // DONE	
		{	if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. INCR LVL"<<endl;
				lvalfunc = 0;
				isValid=false;
				//cout<<" LVALFUNC is turning off : "<<lvalfunc<<" line: "<<yylineno<<endl;
			}
			//cout<<yylineno<<": |" << "++ LValue "<< endl;

			//$<exprvalue>$ = $<exprvalue>2;

			if ($<exprvalue>2->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				
				$<exprvalue>$=emit_iftableitem($<exprvalue>2, yylineno);
				$<exprvalue>$=op_emit(add,$<exprvalue>$,insertVal(1,-1,"INTCONST"),yylineno);
				emit(tablesetelem,$<exprvalue>2,$<exprvalue>2->index, $<exprvalue>$,-1,yylineno);			
			}
			else 
			{

				$<exprvalue>$=newexpr(var_e);
				emit(add,insertVal(1,-1,"INTCONST"),$<exprvalue>2,$<exprvalue>2,-1,yylineno);
				if(istempname($<exprvalue>2->sym->name))
				{
					$<exprvalue>$->sym = $<exprvalue>2->sym;
				}
				else
				{
					$<exprvalue>$->sym=newtemp();
					emit(assign,$<exprvalue>2,NULL,$<exprvalue>$,-1,yylineno);
				}
			}				
		}
| lvalue INCREMENT //DONE
		{	
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. LVL INCR"<<endl;
				lvalfunc = 0;
				isValid=false;
				//cout<<" LVALFUNC is turning off : "<<lvalfunc<<" line: "<<yylineno<<endl;
			}
			//cout<<yylineno<<": |" << "Lval ++ "<< endl;

			//$<exprvalue>$ = $<exprvalue>1;
			$<exprvalue>$=newexpr(var_e);
			$<exprvalue>$->sym= newtemp();
			
			if ($<exprvalue>1->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				
				expr * temp;
				temp=emit_iftableitem($<exprvalue>1, yylineno);
				emit(assign,temp,NULL,$<exprvalue>$,-1,yylineno);
				emit(add,temp,insertVal(1,-1,"INTCONST"),temp,-1,yylineno);
				emit(tablesetelem,$<exprvalue>1,$<exprvalue>1->index, temp,-1,yylineno);
							
			}
			else 
			{
				emit(assign,$<exprvalue>1,NULL,$<exprvalue>$,-1,yylineno);
				emit(add,insertVal(1,-1,"INTCONST"),$<exprvalue>1,$<exprvalue>1,-1,yylineno);

			}				

		} 

	| DECREMENT lvalue //DONE
		{	
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. DECR LVL"<<endl;
				lvalfunc = 0;
				isValid=false;
			
			}
			//cout<<yylineno<<": |" << "--Lval "<< endl;
			//$<exprvalue>$ = $<exprvalue>2;

			if ($<exprvalue>2->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				$<exprvalue>1=emit_iftableitem($<exprvalue>2, yylineno);
				$<exprvalue>$=op_emit(sub,$<exprvalue>1,insertVal(1,-1,"INTCONST"),yylineno);			
			}
			else 
			{
				emit(sub,$<exprvalue>2,insertVal(1,-1,"INTCONST"),$<exprvalue>2,-1,yylineno);
				$<exprvalue>$=newexpr(arithexpr_e);
				if(istempname($<exprvalue>2->sym->name))
				{
					$<exprvalue>$->sym = $<exprvalue>2->sym;
				}
				else
				{
					$<exprvalue>$->sym=newtemp();
					emit(assign,$<exprvalue>2,NULL,$<exprvalue>$,-1,yylineno);
				}
			}	
					

		} 
	| lvalue DECREMENT
		{	
			if(lvalfunc){
				cout << "Syntax Error in line :"<<yylineno << "Attemp to make Lval action to function. LVL DECR"<<endl;
				lvalfunc = 0;
				isValid=false;
				//cout<<" LVALFUNC is turning off : "<<lvalfunc<<" line: "<<yylineno<<endl;
			}
			//cout<<yylineno<<": |" << "Lval-- "<< endl;

			//$<exprvalue>$ = $<exprvalue>1;
			$<exprvalue>$=newexpr(var_e);
			$<exprvalue>$->sym= newtemp();
			
			if ($<exprvalue>1->type == tableitem_e)
			{	//STAVRO APO EDW GRAFE
				
				expr * temp;
				temp=emit_iftableitem($<exprvalue>1, yylineno);
				emit(assign,temp,NULL,$<exprvalue>$,-1,yylineno);
				emit(sub,temp,insertVal(1,-1,"INTCONST"),temp,-1,yylineno);
				emit(tablesetelem,$<exprvalue>1,$<exprvalue>1->index, temp,-1,yylineno);
							
			}
			else 
			{
				emit(assign,$<exprvalue>1,NULL,$<exprvalue>$,-1,yylineno);
				emit(sub,$<exprvalue>1,insertVal(1,-1,"INTCONST"),$<exprvalue>1,-1,yylineno);

			}					

		} 
	| primary	
		{	
			$<exprvalue>$=$<exprvalue>1;
			//cout<<yylineno<<": |" << "Primary "<< endl;
		}


	;

assignexpr:		lvalue ASSIGN expr
		{



			///meriki
			//if($<exprvalue>1->sym->type<2){cout<<"^^^^^^^^^^^print error?^^^^^^^^^^^^ "<<endl;}
			
			//cout << "EXPRESSION TYPE: "<<$<exprvalue>3->type << endl;
			//cout << "EXPRESSION TYPE: "<<$<exprvalue>3->sym->name << endl;
			//cout << "EXPRESSION TYPE: "<<$<exprvalue>3->sym->type << endl;

			///
			//cout<<yylineno<<": |" << "IN ASSIGNEXPR idc: "<<idcount<<endl;
			illcount=0;
			for (list<int>::iterator it = assignParts.begin(); it != assignParts.end(); it++){
				if(DEBUG)cout<<(*it)<<endl;
					if ((*it < 2 )&& (*it!=5)) {
								illcount++;
 							 	//cout<<" ASSIGNPART FOUND FUNC OR LIBFUNC succeded :"<<yylineno<<" illcount :"<<illcount<<" |:"<<*it<<endl;

									}
					}

			//provlima me ta temp pou eisagontai meta
			//cout<<" assignparts front :"<<assignParts.front()<<" "<<assignParts(1)<<" "<<assignParts(2)<<" back"<< assignParts.back()<<"  size :"<< assignParts.size()<<endl;

			//cout<<" assignparts front :"<<assignParts.front()<<" back"<< assignParts.back()<<"  size :"<< assignParts.size()<<endl;
			
			/*if((illcount>1)||((illcount==1)&&((assignParts.back()!=5)&&assignParts.back()>1)&&(assignParts.size()>1))||((illcount==1)&&(assignParts.front()<2)&&(assignParts.size()==1))||(assignParts.front()<2)) {
					cout<<"SYNTAX ERROR LVAL ON FUNCTION FROM ASSIGNPARTS :"<<yylineno<<endl;
					isValid=false;
					assignParts.pop_back();
					//cout<<"back pop here"<<endl;
					illcount--;

			}*/

			if($<exprvalue>3->fromNot){
					//cout<<"in not "<<endl;

					expr *temp = new expr;
					expr *result = new expr;
					result= newexpr(boolexpr_e);
					result->sym=newtemp();
					temp = newexpr(boolexpr_e);
					temp->sym = $<exprvalue>3 ->sym;
					//$<exprvalue>3->sym = newtemp();
					emit(if_eq,temp,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,(int)(currQuad +2),yylineno);
					emit(jump, NULL, NULL, NULL, (int)(currQuad +3), yylineno);
					emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL,result, -1, yylineno);
					emit(jump, NULL, NULL, NULL, (int)(currQuad +2), yylineno);
					emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, result, -1, yylineno);
					$<exprvalue>3->sym= result->sym;


				}

			
			
			else if($<exprvalue>3->type==boolexpr_e){
				//cout<<"in bool "<<endl;
				//cout<<"efatsa sta type check"<<$<exprvalue>3->type<<endl;
				
				if(DEBUG){cout<<  $<exprvalue>3->sym->name<< " indexes :"<< $<exprvalue>3->true_index <<"  |  "<<$<exprvalue>3->false_index<<endl;}

				/*
				true_backpatch($<exprvalue>3->true_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, $<exprvalue>3, -1, yylineno);
			
				emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
				false_backpatch($<exprvalue>3->false_index,0,currQuad);
				emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, $<exprvalue>3, -1, yylineno);
				*/
				bool_assign($<exprvalue>1, $<exprvalue>3);
				$<exprvalue>$=newexpr(assignexpr_e);
			
			/*----------------------stayros!!!!!!!!!!!!----------------//*/
			}
			else if($<exprvalue>3->type==tableitem_e){
				$<exprvalue>3=emit_iftableitem($<exprvalue>3,yylineno);
			}
			



			if($<exprvalue>1->type==tableitem_e){
				//$<exprvalue>1=emit_iftableitem($<exprvalue>1,yylineno);
				emit(tablesetelem,$<exprvalue>1,$<exprvalue>1->index, $<exprvalue>3,-1,yylineno);
				$<exprvalue>$=$<exprvalue>1;	

			}
			else{
				//cout<<"bika sto else"<<endl;
				emit(assign,$<exprvalue>3,NULL,$<exprvalue>1,-1,yylineno);
				$<exprvalue>$=newexpr(assignexpr_e);
				//cout << $<exprvalue>1->sym->name<< endl;

					if(	istempname($<exprvalue>1->sym->name)){

						$<exprvalue>$->sym=newtemp();
						emit(assign,$<exprvalue>1,NULL,$<exprvalue>$,-1,yylineno);

					}
					else{
						$<exprvalue>$->sym = $<exprvalue>1->sym;
					}
			}
		}

	;

primary:	lvalue
		{	
			$<exprvalue>$ =emit_iftableitem($<exprvalue>1,yylineno);
			Lval_used = 1;
			if(DEBUG){cout<<yylineno<<": |" << "Lval primary "<< endl;}
		}
	| call
		{
			is_call = 1;
			int temp=1;
			expr * calltemp = new expr;
			calltemp= $<exprvalue>1;			
			//cout<<$<exprvalue>1->sym->name<<endl;
			$<isNormalcall>$=temp;
			if(DEBUG){cout<<yylineno<<": |" << "Call "<< $<isNormalcall>$<< endl;}
			$<exprvalue>$ = calltemp;


			/*
			is_call = 1;
			int temp=1;
			expr * calltemp = new expr;
			calltemp= $<exprvalue>1;			
			//cout<<$<exprvalue>1->sym->name<<endl;
			$<isNormalcall>$=temp;
			cout<<yylineno<<": |" << "Call "<< $<isNormalcall>$<< endl;
			$<exprvalue>$ = calltemp;
			//cout<<"''''''''''''''''''''''call "<<$<exprvalue>$->sym->name<<endl;
		

			*/
		}
	| objectdef
		{
			//cout<<yylineno<<": |" << "Object def "<< endl;
			$<exprvalue>$ = newexpr(newtable_e);
			$<exprvalue>$ = $<exprvalue>1;
		}
	| LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS
		{
			//cout<<yylineno<<": |" << "Function Def "<< endl;
			$<exprvalue>$ = newexpr(programfunc_e);
			$<exprvalue>$->sym = $<symvalue>2;

		}
	| const	{
			tmpsym = new expr;
			tmpsym=$<exprvalue>1;
			//cout<<yylineno<<": |" << "Constant :"<<endl;
			$<exprvalue>$ = $<exprvalue>1;
		}
	;

	
lvalue:	ID

		{	
			if(DEBUG){cout<<"IN LVALUE: ID"<<$1<<endl;}
			localcheck =createFSymbol($1,maxScope,yylineno,"none",maxFScope,0,VAR,true,currentscopeoffset(),currentscopespace());   
			if(DEBUG){cout<<"is_funcall :"<<is_funcall<<" || is_call :"<<is_call<<" ||is_funcdef :"<<is_funcdef<<endl;}
			Symbol *kati;
			/*kati=LookupforRef($1,maxScope);
			if(kati==NULL){
				insertPt(localcheck);
				cout<< "CURRENT SCOPE SPACE  " << currentscopeoffset() <<endl;
			}*/
			kati=Lookup(*localcheck,LVAL_ID);
			//cout << "=========NAME===============" << localcheck->name << endl;
			//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
			//inccurrscopeoffset();
			//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
			//cout<<yylineno<<": " << "Identifier "<<endl;

			//cout<<yylineno<<": " << "Identifier "<< kati->name <<endl;
			idcount++;
   			//$<exprvalue>$= lvalue_expr($<strvalue>1);
   			///$<exprvalue>$->sym=kati;
			expr* passme = new expr;
			passme =  lvalue_symbol(passme,kati);
			$<exprvalue>$ = passme;
			//cout<<yylineno<<": |" << "id :"<< ($<exprvalue>$->sym->name) <<endl;										 
		

		}
	| KEYWORD_LOCAL ID 
		{	
			Symbol *kati;
			if(DEBUG)cout<<yylineno<<": " << "Local Identifier "<< $2 << endl;
			idcount++;
			//toAdd =fill($2,maxScope,yylineno,"none",maxFScope,0,VAR,true);   //missing check
			if(DEBUG)cout<<" prin create"<<endl;
			localcheck =createFSymbol($2,maxScope,yylineno,"none",maxFScope,0,VAR,true,currentscopeoffset(),currentscopespace());   
			if(DEBUG)cout<<" after create"<<endl;	
			kati=Lookup(*localcheck,LVAL_LOCAL);
			if(DEBUG)cout<<" after lookup"<<endl;
   			expr* passme = new expr;
			passme =  lvalue_symbol(passme,kati);
			$<exprvalue>$ = passme;


		} 
	| DOUBLE_COLON ID
		{ 	
			Symbol *kati;

			localcheck =createFSymbol($2,maxScope,yylineno,"none",maxFScope,0,VAR,true,currentscopeoffset(),currentscopespace());   

			kati=Lookup(*localcheck,LVAL_GLOBAL);
			if(DEBUG)cout<<yylineno<<": " << "Global Identifier "<< $2 << endl;
			idcount++;
			expr* passme = new expr;
			passme =  lvalue_symbol(passme,kati);
			$<exprvalue>$ = passme;
   			//$<exprvalue>$= lvalue_expr($<strvalue>2);

		}


	| member
		{	

			templast=assignParts.back();
			while ((assignParts.back()!=5)&&assignParts.size()){ assignParts.pop_back();}
			assignParts.push_back(2);
			if(DEBUG){cout<<yylineno<<": " << "Member "<< $1 << endl;}
			$<exprvalue>$=$<exprvalue>1;
		}  
	;

member:	lvalue DOT ID			
					{ 
						if(DEBUG){cout<<yylineno<<": |" << "Lval.ID "<< endl;
						cout<<yylineno<<": " << "Member lval.ID "<< $3 << endl;}
						$<exprvalue>$=emit_table($<exprvalue>1,constString_expr($<strvalue>3),yylineno);
					}	
	| lvalue LEFT_BRACKET expr RIGHT_BRACKET	{

						//cout<<yylineno<<": |" << "Lval[expr] "<< endl;

						$<exprvalue>$=emit_table($<exprvalue>1,$<exprvalue>3,yylineno);
					}
	| call DOT ID			{//cout<<yylineno<<": |" << "Call ID "<< endl;
							}
	| call LEFT_BRACKET  expr RIGHT_BRACKET 	{//cout<<yylineno<<": |" << "Cal[expr] "<< endl;
												}
	;

	
call:	call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
		{
		if(DEBUG){cout<<yylineno<<": |" << "Call(Elist) "<< endl;}
		if(lvalfunc){
					lvalfunc=0;
					}
		
		$<exprvalue>$ = (expr *) func_call($<exprvalue>1, $<exprvalue>3, yylineno , $<startHere>2);
		}
| lvalue callsuffix			{		
							if(DEBUG){cout<<"######IS NORMALCALL? : "<<$<isNormalcall>2<<" elist value "<<expr_list.size()<<endl;}

							if (!($<isNormalcall>2)) {
							$<exprvalue>$ = (expr *) func_call($<exprvalue>1, $<exprvalue>2, yylineno, $<startHere>2);
							}
							else {
							$<exprvalue>$ = (expr *) func_methodcall($<exprvalue>1, $<strvalue>2, yylineno,$<startHere>2);

							}
									

								}
	| LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
	{//cout<<yylineno<<": |" << "Fundef(Elist) "<< endl;
		expr* callfunc = new expr;
		callfunc= newexpr(programfunc_e);
		callfunc ->sym = $<symvalue>2;
		if(DEBUG){cout<<"name of func is "<<callfunc->sym->name<<endl;
		printList();
		cout<<"########"<<endl;}
		//cout<<$<startHere>5<<"   "<<$<startHere>6<<endl;
		$<exprvalue>$ = (expr *) func_call(callfunc, $<exprvalue>5, yylineno, $<startHere>4);


	}
	;

	
callsuffix:	normcall	{
							//cout<<yylineno<<": |" << "Normalcall "<< endl;
							$<exprvalue>$ = $<exprvalue>1;
							$<startHere>$=$<startHere>1;
							$<isNormalcall>$=0;


						}
	| methodcall		{
								//cout<<yylineno<<": |" << "Method call "<< $<strvalue>1 <<endl;
								$<isNormalcall>$=1;
								$<strvalue>$= $<strvalue>1;
								//cout<<yylineno<<": |" << "Method call "<< $<isNormalcall>$ <<endl;

						}
	;
	
	//////////////////////////////////EDW STAMATISES MALAKA////////////////////
normcall:	LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {
											is_call=1;
											//cout<<yylineno<<": |" << "(Elist) "<< endl;
											$<exprvalue>$ = $<exprvalue>1;
											$<startHere>$=$<startHere>1;
											}
	;

	
methodcall:	DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS	
						{
							if(DEBUG){cout<<yylineno<<": |" << "|..ID(Elist) "<<$<strvalue>2 << endl;}
							$<strvalue>$= $<strvalue>2;
						}
	;

elist:	expr elist_tmp	{
								if(DEBUG){cout<<yylineno<<": |" << "Expr "<< endl;}
								$<exprvalue>$ = $<exprvalue>1;
								expr_list.push_back($<exprvalue>1);
						}
	
	| 					{
							if(DEBUG){cout << "Empty elist given" << endl;}
						}
	;
elist_tmp: COMMA expr elist_tmp{
							if(DEBUG){cout<<yylineno<<": |" << "Expr .. Expr"<< endl;}
							$<exprvalue>$=$<exprvalue>2;
							expr_list.push_back($<exprvalue>2);							
						} 
	|			{}
	;

objectdef:	LEFT_BRACKET elist RIGHT_BRACKET	{

						if(DEBUG){cout<<"[ Elist ]"<<endl;}
						expr * table = newexpr(newtable_e);
						elist_start++;
						
    					$<exprvalue>$ = obj_manage($<startHere>1);


}
	| LEFT_BRACKET indexed RIGHT_BRACKET		{
												expr * table = newexpr(newtable_e);
												elist_start++;
    											$<exprvalue>$ = obj_manage($<startHere>1);
												//cout<<yylineno<<": |" << "[Indexed]"<< endl;
    										}
	;

indexed:	indexedelem indexedelemtmp	{
							if(DEBUG){cout<<yylineno<<": |" << "Expr "<< endl;}
								$<exprvalue>$ = $<exprvalue>1;
								expr_list.push_back($<exprvalue>1);
						}
	
;


indexedelemtmp: COMMA indexedelem indexedelemtmp {

			if(DEBUG){cout<<yylineno<<": |" << "Expr .. Expr"<< endl;}
			$<exprvalue>$=$<exprvalue>2;
			expr_list.push_back($<exprvalue>$);


}
|{}
;

indexedelem:	LEFT_BRACE expr COLON expr RIGHT_BRACE	{
														//cout<<yylineno<<": |" << "{ expr : expr } "<< endl;
														$<exprvalue>$ = $<exprvalue>2;
														$<exprvalue>$->iskey = true;
														$<exprvalue>$->keyval = $<exprvalue>4;
															}
	;


block:	LEFT_BRACE 
		{
			maxScope++;
			if(DEBUG){cout<<yylineno<<": |" << "L_brace "<< endl;}
		}
	 	block_stmt{} 
		RIGHT_BRACE{
			hideTheScope(maxScope); 
			maxScope--;
			if(DEBUG){cout<<yylineno<<": |" << "R_brace "<< endl;}

			//both
			//$<break_index>$=$<break_index>3; 
			//$<cont_index>$=$<cont_index>3;
	
			bc_indexes * bc= new bc_indexes;
  			bc->break_index=$<indexes>3->break_index;
			bc->cont_index=$<indexes>3->cont_index;
			$<indexes>$=bc;
			if(DEBUG){
	 		cout<<" passing block_stmt; -> block"<<$<break_index>$<<endl;
			cout<<" passing block_stmt;"<<$<cont_index>$<<endl;
			
			}

		}
	;

block_stmt:	block_stmt stmt	{
			if(DEBUG){cout<<" in block_stmt"<<" blockstmt :"<< $<break_index>1<<" stmt: "<<$<break_index>2<<endl;}
			/*if($<break_index>1>-1){

				if($<break_index>2>-1){

				$<break_index>$=min($<break_index>2,$<break_index>1);

				cout<<" passing block stmt stmt in if -> block_stmt "<<$<break_index>$<<endl;
				}
				else{
						$<break_index>$=$<break_index>1;
				}

			}

			else{
					$<break_index>$=$<break_index>2;	
					cout<<" passing block stmt stmt else -> block_stmt "<<$<break_index>$<<endl;
			}


			if($<cont_index>1>-1){

				$<cont_index>$=min($<cont_index>2,$<cont_index>1);

				cout<<" passing block stmt stmt in if -> block_stmt "<<$<cont_index>$<<endl;

			}
			else{
					$<cont_index>$=$<cont_index>2;
					cout<<" passing block stmt stmt else -> block_stmt "<<$<cont_index>$<<endl;
			}*/
			
			

			bc_indexes * bc= new bc_indexes;
  			bc->break_index=merge_break($<indexes>2->break_index,$<indexes>1->break_index);
			bc->cont_index=merge_break($<indexes>2->cont_index,$<indexes>1->cont_index);
			$<indexes>$=bc;

			} 
	|			{
					
					bc_indexes * bc= new bc_indexes;
					$<indexes>$=bc;
				}
	;



id_tmp:	ID	{
				if(DEBUG){cout<<yylineno<<": " << "Identifier "<<$1<<endl;idcount++;/*cout<<"id++ here"<<endl*/;}

				staurosDota=strdup($<strvalue>1);
				$<strvalue>$=staurosDota;
			}

		|	{	
			//klisi sunartisis edw?

			prefix_count = 1;autoName=true;
			if(DEBUG){cout<<yylineno<<": " << "Identifier {} setting custom name... "<<yytext<< endl;}
			idcount++;

			}
	;

idlist:	ID
		{	//maxScope++;
			//maxFScope++;
			//LookupName($1,maxScope);
			//argcheck = LookupforRef($1,maxScope);
			toAdd =fill3($1,maxScope,yylineno,"none",maxFScope,0,ARGUMENT,true,currentscopeoffset(),currentscopespace());   //missing
			//cout << "FORMAL ARG OFFSET: " << endl << formalArgOffset << endl;
			if(!((isActive(toAdd))&&((isArgument(toAdd))))){
				insertH(toAdd);
				//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
				//inccurrscopeoffset();
				//cout << "EGINE INCREASE TO currentscopeoffset se: " << currentscopeoffset() << endl;
				if(DEBUG){cout<<"inserting  id"<<endl;}
			}
			else{ 
				cout<<yylineno<<": " <<"Syntax error : redefining argument "<<$1<<endl;
				isValid=false;
			}
			idcount++;
			if(DEBUG){cout<<yylineno<<": " << "Idlist ID "<<$1<< endl;}
			//maxScope--;
			//maxFScope--;
		}
	|idlist COMMA ID
		{
			//maxScope++;
			//maxFScope++;
			if(DEBUG){cout << "FORMAL ARG OFFSET: " << endl << formalArgOffset << endl;}
			toAdd =fill3($3,maxScope,yylineno,"none",maxFScope,0,ARGUMENT,true,currentscopeoffset(),currentscopespace());   //missing
			if(!((isActive(toAdd))&&((isArgument(toAdd))))){
				//cout<<"inserting idlist comma id"<<" isactive:"<<isActive(toAdd)<<" , isrgument:"<<isArgument(toAdd)<<endl;
				insertH(toAdd);
				//cout << "EGINE INCREASE TO currentscopeoffset apo: " << currentscopeoffset() << endl;
				//inccurrscopeoffset();
				//cout << "EGINE INCREASE TO currentscopeoffset se: " << currentscopeoffset() << endl;

			}
			else{ 

				if(DEBUG){cout<<yylineno<<": " <<"Syntax error : redefining argument "<<$3<<endl;}
				isValid=false;
			}
			if(DEBUG){cout<<yylineno<<": " << "COMMA Argument "<<$3<< endl;}
			//maxScope--;
			//maxFScope--;
		} 
	|	{;}
	;

functionprefix: KEYWORD_FUNCTION id_tmp
			{

				Symbol *kati= new Symbol;
				is_funcdef=1;
				if(autoName){
					autoName=false;
					functionName=setFunctionName();
				}
				else functionName=$<strvalue>2;
				//i address -> krata to sto  line Function tou Symbol
				toAdd =fill3(functionName,maxScope,yylineno,functionName,maxFScope,currQuad,FUNC,true,-1,currentscopespace());
				Lookup(toAdd,FUNCDEF_MODE);
				localcheck =createFSymbol(functionName,maxScope,yylineno,functionName,maxFScope,currQuad,FUNC,true,-1,currentscopespace());   
				kati=Lookup(*localcheck,LVAL_LOCAL);

				aerials.push(currentscopeoffset());
				ownage.push(isLoop);
				isLoop=0;
				enterscopespace();
				resetformalargoffset();
				//Symbol *temp= new Symbol;
				//temp->name = functionName;
				$<symvalue>$ = kati;

			}
	;

funcargs:  LEFT_PARENTHESIS { maxFScope++; maxScope++; }idlist RIGHT_PARENTHESIS 
		{
			//cout << "----BIKA FuncArgs-----" << endl;
			maxScope--;
			enterscopespace();
			resetfunctionlocaloffset();
		}
	;

funcbody: block
		{	
			is_funcdef=0;
			//$<intvalue>$=currentscopeoffset();
			exitscopespace();
			hideThem(maxFScope);
			maxFScope--;
			
		}
	;

funcdef: functionprefix funcargs funcbody
		{
			
			exitscopespace();
			Symbol *temp= new Symbol;
			temp = $<symvalue>1;
			temp->dotalocal = functionLocalOffset;//$<intvalue>3;
			if(DEBUG){cout<<$<symvalue>1->name <<"  has dotalocal" <<functionLocalOffset<<endl;}
			temp->name = $<symvalue>1->name;
			temp->type = FUNC;

			//$<symvalue>1->dotalocal=$<intvalue>3;
			unsigned oldoffset= aerials.top();
			aerials.pop();
			restorecurrscopeoffset(oldoffset);
			isLoop=ownage.top();
			ownage.pop();
			$<symvalue>$=temp;
			if(DEBUG){cout<<" $$ type"<<$<symvalue>$->type<<endl;}
			expr *ack = new expr;
			ack = lvalue_symbol(ack,temp);
			emit(funcend,nullptr,nullptr,ack,-1,yylineno);
			//cout << "FUNC: "<< $<symvalue>$->name<< "ME ARITHMO locals" << $<symvalue>$->dotalocal << endl;
		}

/*funcdef:	KEYWORD_FUNCTION id_tmp


			expr* passme = new expr;
			passme =  lvalue_symbol(passme,kati);
			$<exprvalue>$ = passme;


		{	//todo<<
			is_funcdef=1;
			//pushOffsetStack(offsetStack,currscopeoffset());
			inccurrscopeoffset();	
			resetformalargoffset();			
			if(autoName){
						autoName=false;
						functionName=setFunctionName();


			}
			else functionName = yytext;
			toAdd =fill(functionName,maxScope,yylineno,"none",maxFScope,0,FUNC,true);   //missing //currscopespace(),currscopeoffset()
			cout<<"is_funcall :"<<is_funcall<<" || is_call :"<<is_call<<" ||is_funcdef :"<<is_funcdef<<endl;
			//pushfStack(createS( f_name , deepestScope , 0 ,f_name  , deepestFunctionScope, 0 , "func" , 1 ,currscopespace(),currscopeoffset())); 
			//

			Lookup(toAdd,FUNCDEF_MODE);


			//
			cout<<yylineno<<": " << "Function "<<functionName<< endl;//error otan dollar
		}
		LEFT_PARENTHESIS 
		{ 	
			maxFScope++;
			maxScope++;
			cout<<yylineno<<": |" << "L_parent "<< endl;
			//todo<<
			enterscopespace();
			//pushOffsetStack(offsetStack,currscopeoffset());
		}
		idlist{
			//todo<<
			resetfunctionlocaloffset(); 
		}
		RIGHT_PARENTHESIS 
		{	
			//maxFScope--;//something more here?
			maxScope--;
			cout<<yylineno<<": |" << "R_parent"<< endl;
		} 
		block 
		{
			is_funcdef=0;
			hideThem(maxFScope);
			maxFScope--;
			cout<<yylineno<<": |" << "Block "<< endl;
			//todo<<
			//restorecurrscopeoffset(popOffsetStack(offsetStack));
			exitscopespace();
			//expr *expr_tmp = new expr;
			///expr_tmp = newexpr(programfunc_e);
			$<exprvalue>$= newexpr(programfunc_e);


			//SEG
		//expr_tmp->sym = fill4(expr_tmp->sym,functions.back(),maxScope,yylineno,functions.back(), maxFScope,0,FUNC,1,1,1)	;			
			//$<symvalue>$ = fill4(expr_tmp->sym,functions.back(),maxScope,yylineno,functions.back(), maxFScope,0,FUNC,1,currentscopeoffset(),currentscopespace())	;	
			//funcbody????
			emit(funcend,nullptr,nullptr,lvalue_expr(functions.back()),currQuad,yylineno);
			functions.pop_back();

		} 
		;
*/

const:	INTCONST			{
								if(DEBUG){cout<<yylineno<<": |" << "INTCONST :"<< $<intvalue>1 <<endl;}
								$<exprvalue>$ = insertVal(yylval.intvalue,-1,"INTCONST");
								}
	| REALCONST				{
								if(DEBUG){cout<<yylineno<<": |" << "Realconst "<< endl;}
								$<exprvalue>$ = insertVal(-1,yylval.dvalue,"REALCONST");
							}
	| STRING				{
								if(DEBUG){cout<<yylineno<<": |" << "String \""<<$1<<"\""<< endl;}
								$<exprvalue>$ = constString_expr(yylval.strvalue);
							}
	| KEYWORD_NIL			{
								if(DEBUG){cout<<yylineno<<": |" << "Nil "<< endl;}
								$<exprvalue>$ = insertVal(-1,-1,"KEYWORD_NIL");

							}
	| KEYWORD_TRUE			{
								if(DEBUG){cout<<yylineno<<": |" << "True "<< endl;}
								$<exprvalue>$ = insertVal(-1,-1,"KEYWORD_TRUE");
							}
	| KEYWORD_FALSE			{
								if(DEBUG){cout<<yylineno<<": |" << "False "<< endl;}
								$<exprvalue>$ = insertVal(-1,-1,"KEYWORD_FALSE");
							}
	;






ifprefix: KEYWORD_IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS
		{

			//cout<<yylineno<<": |" << "Lparent expr R_parent "<< endl;
			if(lvalfunc)
			{
				lvalfunc=0;
				assignParts.clear();
			}
			expr* cond = new expr;
			cond = true_test($<exprvalue>3, cond,-1);
			//if (arg1->changeLabel) $<intvalue>3=currQuad;

			//expr * cond = new expr;
			//true_test($<exprvalue>3,cond,0);

			//
			//arg1 = true_test($<exprvalue>1,arg1,$<intvalue>3);
			//if (arg1->changeLabel) $<intvalue>3=currQuad;
			
			//cout <<" ### "<<arg1->false_index<<endl;
			
			/////arg2 = true_test($<exprvalue>4,arg1,$<intvalue>3);
			//

			//apo edw
			false_backpatch(cond->false_index,0,currQuad);
			//OI MALAKIES EINAI EDW
			emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, cond, -1, yylineno);
			emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
			true_backpatch(cond->true_index,0,currQuad);
			emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, cond, -1, yylineno);
			emit(if_eq,cond,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
			$<intvalue>$ =  currQuad-1;
		}
		;

elseprefix: KEYWORD_ELSE {
			if(DEBUG){cout<<yylineno<<": |" << "Else "<< endl;}
			$<intvalue>$=currQuad;
			if(DEBUG){cout<<" key else int val ### "<<$<intvalue>$<<endl;}
			emit(jump, nullptr,nullptr,nullptr,-1,yylineno);


		}
		;



ifstmt: ifprefix stmt {
				if(DEBUG){cout<<"EGW BACKPATCHARW TWRA"<<endl;}
				backpatch($<intvalue>1,currQuad);
				//$<break_index>$=$<break_index>2;
  				//$<cont_index>$=$<cont_index>2;
  				bc_indexes * bc= new bc_indexes;
  				bc->break_index=$<indexes>2->break_index;
				bc->cont_index=$<indexes>2->cont_index;
				$<indexes>$=bc;



			}
		| ifprefix stmt elseprefix stmt
		{
			if(DEBUG){cout<<yylineno<<": |" << "stmt  "<< endl;}
			backpatch($<intvalue>1,$<intvalue>3+1);
			if(DEBUG){cout<<" key else int val apokatw ### "<<$<intvalue>3<<endl;}
			backpatch($<intvalue>3,currQuad);
			//$<break_index>$=min($<break_index>2,$<break_index>4);
  			//$<cont_index>$=min($<cont_index>2,$<cont_index>4);
  			//$<break_index>$=merge_break($<break_index>2,$<break_index>4);
			//$<cont_index>$=merge_cont($<cont_index>2,$<cont_index>4);

			bc_indexes * bc= new bc_indexes;
  			bc->break_index=merge_break($<indexes>2->break_index,$<indexes>4->break_index);
			bc->cont_index=merge_break($<indexes>2->cont_index,$<indexes>4->cont_index);
			$<indexes>$=bc;
		}
		;

whilestart: KEYWORD_WHILE   {
    //cout << "BIKA WHILESTART" << endl;
    $<intvalue>$ = currQuad;
    if(DEBUG)cout << $<intvalue>$ << endl ;

    isLoop++;
    //


   }
   ;

whilecond: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {
    maxScope++;

    expr* cond = new expr;
	cond = true_test($<exprvalue>2, cond,-1);
    false_backpatch(cond->false_index,0,currQuad);
     //KAI EDW EXEI MALAKIES
	emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, cond, -1, yylineno);
	emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
	true_backpatch(cond->true_index,0,currQuad);
	emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, cond, -1, yylineno);
	emit(if_eq,cond,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
	emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
	$<intvalue>$ =  currQuad-1;
  }
  ;

whileblock: stmt {
  //$<intvalue>1=currQuad+1;
  isLoop--;
  maxScope--;
  if(DEBUG){cout<<yylineno<<": |" << " While(expr)stmt"<< endl;}

  //both
   	//$<break_index>$=$<break_index>1;
  	//$<cont_index>$=$<cont_index>1;
  	bc_indexes * bc= new bc_indexes;
	bc->break_index=$<indexes>1->break_index;
	bc->cont_index=$<indexes>1->cont_index;
	$<indexes>$=bc;

}
;

whilestmt: whilestart whilecond whileblock {
   emit(jump,nullptr,nullptr,nullptr,$<intvalue>1,yylineno);
   if(DEBUG){cout<<yylineno<<": |" << " while "<< endl;}
   backpatch($<intvalue>2,currQuad);

   break_backpatch($<indexes>3->break_index,0,currQuad);
   cont_backpatch($<indexes>3->cont_index,0,$<intvalue>1);
   /*
   if(($<break_index>3>-1) && (breakvector.size())){
  						 break_manage($<break_index>3);
   				}
 	if(($<cont_index>3>-1) && (contvector.size())){
  						 continue_manage($<cont_index>3,$<intvalue>1);
   				}

	*/
   
  } 
  
 ;

//while(a>5){ while(b<5) { x=10;} y=10;}
//if(a>5){ a=1;} else { a=2;}


Q:		{ 
 		$<intvalue>$ = expr_list.size();
 		here=expr_list.size(); 
 		clearList = true;
		//cout<<yylineno<<":|"<<"*****L*****"<<endl;
		}
 	;

	
R: {

	if (clearList) { 
		expr_list.resize(here);
		clearList=false;

	}
}
forstmt:	forprefix S Q  elist R  RIGHT_PARENTHESIS S stmt S	
		{
		//printbreak() ;
			/*
		cout<"from "<<
		backpatch($<fordata>1->enter,$<intvalue>5+1);
		backpatch($<intvalue>2,currQuad);
		backpatch($<intvalue>5,$<fordata>1->test);
		backpatch($<intvalue>7,$<intvalue>2+1);
		cout<<yylineno<<": |" << "Forstmt"<< endl;
		isLoop++;
		
		// 				6765776 			2 						6766656 				0 
		cout<<" "<<$<break_index>1<<" "<<$<break_index>2<<" "<<$<break_index>3<<" "<<$<break_index>4<<" "<<$<break_index>5<<" "<<$<break_index>6<<" "<<$<break_index>7<<endl;
		// 4 						0 					10

		if(($<break_index>6>-1) && (breakvector.size())){
  						 break_manage($<break_index>6);
   				}
 		if(($<cont_index>6>-1) && (contvector.size())){
  						 continue_manage($<cont_index>6,$<intvalue>2+1);
   				}


		}
		*/
		backpatch($<fordata>1->enter,$<intvalue>7+1);
		backpatch($<intvalue>2,currQuad);
		backpatch($<intvalue>7,$<fordata>1->test);
		backpatch($<intvalue>9,$<intvalue>2+1);
		if(DEBUG){cout<<yylineno<<": |" << "Forstmt"<< endl;}
		isLoop--;
		if(DEBUG){cout<<"from "<< $<intvalue>3 <<" to "<< $<intvalue>5 <<endl;}
		// 				6765776 			2 						6766656 				0 
		//cout<<" "<<$<break_index>1<<" "<<$<break_index>2<<" "<<$<break_index>3<<" "<<$<break_index>4<<" "<<$<break_index>5<<" "<<$<break_index>6<<" "<<$<break_index>7<<endl;
		// 4 						0 					10

		break_backpatch($<indexes>8->break_index,0,currQuad);
   		cont_backpatch($<indexes>8->cont_index,0,$<intvalue>2+1);	
   		/*
		if(($<break_index>8>-1) && (breakvector.size())){
  						 break_manage($<break_index>8);
   				}
 		if(($<cont_index>8>-1) && (contvector.size())){
  						 continue_manage($<cont_index>8,$<intvalue>2+1);
   				}

		*/
		}
		
		
		
	;

forprefix: 	KEYWORD_FOR LEFT_PARENTHESIS Q elist R SEMICOLON L expr SEMICOLON
	   	{
		fortmp=new forstr;
		expr * cond = new expr;
		//cout << "$5: "<<$<intvalue>5<<"\tcurrQuad: "<<currQuad<<endl;
		fortmp->test = $<intvalue>7;
		if(DEBUG)
		{
		cout<<"//////////////////////////////////////////////////"<<endl;
		cout<<"from "<< $<intvalue>3 <<" to "<< $<intvalue>5 <<endl;
		}	
		fix_elist( $<intvalue>3, $<intvalue>5);
		cond = true_test($<exprvalue>8, cond,-1);
		false_backpatch(cond->false_index,0,currQuad);
		emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, cond, -1, yylineno);
		emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
		true_backpatch(cond->true_index,0,currQuad);
		emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, cond, -1, yylineno);
		fortmp->enter= currQuad;
		emit(if_eq,cond,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,-1,yylineno);
		
		isLoop++;
		$<fordata>$=fortmp;

		//true_backpatch($<exprvalue>2->true_index,0,currQuad);

		//cout << "test: " << fortmp->test <<"\tenter: " <<fortmp->enter<<endl;
		//cout<<yylineno<<":|" <<"---forprefix---"<<endl;
		/*
		false_backpatch($<exprvalue>2->false_index,0,currQuad);
     //KAI EDW EXEI MALAKIES
	//emit(assign, insertVal(-1,-1,"KEYWORD_FALSE"), NULL, $<exprvalue>2, -1, yylineno);
	//emit(jump, nullptr,nullptr,nullptr,currQuad+2,yylineno);
	true_backpatch($<exprvalue>2->true_index,0,currQuad);
	//emit(assign, insertVal(-1,-1,"KEYWORD_TRUE"), NULL, $<exprvalue>2, -1, yylineno);
	emit(if_eq,$<exprvalue>2,insertVal(-1,-1,"KEYWORD_TRUE"),NULL,currQuad+2,yylineno);
	emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
	$<intvalue>$ =  currQuad-1;*/


	  	}
	;

S: 		{ 
 	 	$<intvalue>$ = currQuad;
		//cout<<yylineno<<":|"<<"*****S*****"<<endl;
 	  	emit(jump, nullptr,nullptr,nullptr,-1,yylineno);
   		}
	;

L:		{ 
 		$<intvalue>$ = currQuad; 
		//cout<<yylineno<<":|"<<"*****L*****"<<endl;
		}
 	;


returnstmt:	KEYWORD_RETURN SEMICOLON
		{
		//cout<<yylineno<<": |" << "return ;"<< endl;
			emit(ret, nullptr, nullptr, nullptr, -1, yylineno);
		}
		| KEYWORD_RETURN expr SEMICOLON
		{
			//cout<<yylineno<<": |" << "return ;"<< endl;
			emit(ret, nullptr, nullptr, $<exprvalue>2, -1, yylineno);

		}
	;	

%%

int yyerror (const char * YaccProvidedMessage)
{	
	isValid=false;
	if ((strstr(YaccProvidedMessage,"$end")))
		cout<<yylineno<<": |"<<"Unexpected reach of the EOF."<<endl;
		//printf("Unexpected reach of the EOF.\n");
	else
		cout<<yylineno<<": |"<<" in line "<<yylineno<<", token "<<yytext<<endl;
		//printf("%s -- in line %d , token %s \n ",YaccProvidedMessage,yylineno,yytext);
	return 0;
}

int main(int argc,char **argv)
{	

	if(DEBUG){
		cout << "KANW DEBUG TWRA KAI KALA" << endl;
	}
	//breakvector.resize(1000);
	Scopelist.resize(100);
	breakMultiVector.resize(20);
	contMultiVector.resize(20);
	trueMultiVector.resize(20);
	falseMultiVector.resize(20);
	FILE *fp1, *fp2;
	streambuf *psbuf, *backup;
  	ofstream filestr;
	ofstream kalaitzos,binarw;
	kalaitzos.open(argv[20]);
  	filestr.open ("quads.txt");
  	ofstream instr;
  	instr.open ("binary.abc");
  	binarw.open("binary.abin", ios::out | ios::binary);
  	      // restore cout's original streambuf
	if(argc>1){
		fp1=freopen(argv[1],"r",stdin);
		if(fp1==NULL) {
			cout << "INPUT FILE NOT FOUND" << endl;
		}
		if(argc>2){
			fp2=freopen(argv[2],"w",stdout);
		}
	}
	//outfile.open("quads.txt");
	yyin=stdin;
	initializeHash();

	//cout<<endl;
	yyparse();
	//cout << "vlakas" << endl;
	//printSymbols();
	//printAll();
	if(DEBUG){printQuads();}
	//printStack();
	if (isValid){
		//cout<<"is valid so printing quads"<<endl;
		//validPrints();
		if(DEBUG){printAll();}
		
		backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = filestr.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf);         // assign streambuf to cout
  		printQuads();
  		cout.rdbuf(backup);

  		//
  		backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = kalaitzos.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf); 
  		//

		generate_binary();
		//backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = instr.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf);         // assign streambuf to cout
  		generate_abc();
  		psbuf = binarw.rdbuf();
  		cout.rdbuf(psbuf);
  		generate_o(binarw);
  		cout.rdbuf(backup);
  		
	} 

	else {
		//cout<<"is not valid, mpaaa"<<endl;
		if(DEBUG)
		{
			printAll();
			printQuads();
		}	
		cout<<"-ggs ownage failed."<<endl;
		
		backup = std::cout.rdbuf();     // back up cout's streambuf
  		psbuf = filestr.rdbuf();        // get file's streambuf
  		cout.rdbuf(psbuf);         // assign streambuf to cout
		cout<<"-ggs ownage failed."<<endl;
  		cout.rdbuf(backup);  
  		
	}
	if(DEBUG)
	{
		print_true();
		print_false();
	}

	//printtruelist();
	if(argc>1){
		fclose(fp1);
		if(argc>2){
			fclose(fp2);
		}
	}
	filestr.close();

	//outfile.close();
	return 0;
}
