%{
	#include <cmath>
	#include <iostream>
	#include <iomanip>
	#include <list>
	#include <cstdlib>
	#include <cstring>
	#include <stdlib.h>
	#include <string>
	#include <vector>
	#include <typeinfo>
	#include "parser.hpp"
	#pragma GCC diagnostic ignored "-Wcomment" //asto gia to mac einai 


/*
	#if ! defined(yyFlexLexerOnce)
	#include <FlexLexer.h> //
	#endif
	
*/
	using namespace std;

	

	struct alpha_token_t
	{
		int line_no;
		int token_no;
		string token_name;
		string type;
		int intval;
		double dval;
		
					
	};
	//vector <expre*>  :: iterator it;
	void add_token(int,int,string,string,int,double);

	extern list<int>assignParts;
	extern vector<expre *> expr_list;
	int	token_num =0;
	string buff;
	list<alpha_token_t> lista;
	int errString=0;
	int Linecomerror = 0;
	int commentcount = 0;
	int c;

	

	void add_token (int line_no , int token_no, std::string token_name, std::string type ,int intval,double dval){
		alpha_token_t t;
		string tmp = token_name;
		t.line_no=line_no;
		t.token_no=token_no;
		t.token_name=tmp;
		t.type=type;
		t.intval=intval;
		t.dval=dval;
		lista.push_back(t);

	}

	
	
	
%}
%option noyywrap
%option yylineno

INTCONST ([0-9])+
REALCONST {INTCONST}+"."{INTCONST}*
WHITESPACE [\n\t\v\r ]
ID [a-zA-Z]+[_0-9a-zA-Z]*
LINECOMMENT "//"[.]*



%x STR
%x MLCOMMENT



%%


{WHITESPACE} {BEGIN(INITIAL);}
					
"if"			{return KEYWORD_IF;}
"else"          {return  KEYWORD_ELSE;}
"while" 		{return KEYWORD_WHILE ;}
"for"           {return KEYWORD_FOR ;}
"function"      {return KEYWORD_FUNCTION ;}
"return"        {return KEYWORD_RETURN ;}
"break"         {return KEYWORD_BREAK ;}
"continue"      {return KEYWORD_CONTINUE ;}
"and"           {return KEYWORD_AND ;}
"not"           {return KEYWORD_NOT ;}
"or"            {return KEYWORD_OR ;}
"local"         {return KEYWORD_LOCAL ;}
"true"       	{return KEYWORD_TRUE ;}
"false"         {return KEYWORD_FALSE ;}
"nil"           {return KEYWORD_NIL ;}  

"="				{    assignParts.push_back(5);
   return ASSIGN ;}
"+"             {return PLUS ;}
"-"             {return MINUS ;}
"*"             {return MULTIPLY ;}
"/"             {return DIVIDE ;}
"%"            	{return MODULO ;}
"=="            {return EQUAL ;}
"!="			{return NOT_EQUAL ;}
"++"            {return INCREMENT ;}
"--"            {return DECREMENT ;}
">"             {return GREATER_THAN ;}
"<"				{return LESS_THAN ;}
"<="            {return LESS_EQUAL ;}
">="            {return GREATER_EQUAL ;}

"{"				{return LEFT_BRACE ;}
"}"				{return RIGHT_BRACE ;}
"["				{yylval.startHere=expr_list.size();return LEFT_BRACKET ;}
"]"				{return RIGHT_BRACKET ;}
"("             {yylval.startHere=expr_list.size();return LEFT_PARENTHESIS ;}
")"             {return RIGHT_PARENTHESIS ;}
";"             {return SEMICOLON ;}
","             {return COMMA ;}
":"             {return COLON ;}
"::"            {return DOUBLE_COLON ;}
"."				{return DOT ;}
".."            {return DOUBLE_DOT ;}


{INTCONST} {yylval.intvalue= stoi(yytext,nullptr,0);
			return INTCONST;}

{REALCONST} {yylval.dvalue= stod(yytext,nullptr);
			return REALCONST;}

{ID}	{yylval.strvalue=strdup(yytext);
		return ID;}

{LINECOMMENT} { //add_token(yylineno, ++token_num, yytext,LINECOMMENT,-1,-1);
				int check = yyinput();
					if (check=='\n'){BEGIN(INITIAL);}
					else{
						while(1){
									
									check=yyinput();
									if (check=='\n') {break;BEGIN(INITIAL);}
									continue;
									}	
								}
 			}



"/*" { Linecomerror = 0; commentcount = 1; 
						//add_token(yylineno, ++token_num, yytext, COMMENT,-1,-1);
						BEGIN(MLCOMMENT);}
<MLCOMMENT>['/']+['*'] {commentcount++;
						//add_token(yylineno, ++token_num, "/*", NESTED_COMMENT,-1,-1); 
						BEGIN(MLCOMMENT); }
<MLCOMMENT>['*']+['/'] {
					
					//c = yyinput();
					commentcount--;
					
					if(commentcount == 0 ) {
						//add_token(yylineno, ++token_num, "*/",CLOSE_COMMENT,-1,-1);
						BEGIN(INITIAL);
					}else{
						//add_token(yylineno, ++token_num, "*/",CLOSE_COMMENT,-1,-1);
						BEGIN(MLCOMMENT);
					}
					
				}

<MLCOMMENT>[^*^/]*
<MLCOMMENT>['/']+[^*]
<MLCOMMENT>['*']+[^/]
<MLCOMMENT><<EOF>> {
					cout << "ERROR Multiline Comments Open " << commentcount << endl; 
					Linecomerror = 1; 
					BEGIN(INITIAL);}




\" {
	errString=0;
	BEGIN(STR);
	}

<STR>\" {if (errString==0) {
			yylval.strvalue = strdup(buff.c_str()); } 
			buff.clear();
			BEGIN(INITIAL);
			return STRING;	
		}
<STR>\\  {
				
				int toAdd=0;
				c = yyinput();
				
				if (c=='n') {buff.append("\n");}
				else if (c=='t') {buff.append("\t");	}
				else if (c=='v') {buff.append("\v");	}
				else if (c=='r') {buff.append("\r");	}
				else if (c=='\"') {buff.append("\"");	}
				else if (c=='\\') {
										buff.append("\\");	
										/*c = yyinput();
										while(c=='\\'){c = yyinput();toAdd++;}
										for(int i=0;i<=toAdd;i++){buff.append("\\");}

										std::string s = std::to_string(c);
										string s1; 
										s1=(char) c;

									 	
									 	buff.append(s1);*/
									}
				else if (( c>64 )|| (c<123))	{string s2;s2=(char) c;cout<<"INVALID STRING line:"<<yylineno<<" Invalid escaped char -> "<<s2<<endl;buff.append("\\");string s1;s1=(char) c;buff.append(s1);}
				 }

<STR>[^\\\"]+ {


					buff.append(yytext);
				}

<STR><<EOF>> {  cout<<"INVALID STRING line:"<<yylineno<<endl;
					BEGIN(INITIAL);}

<<EOF>>			{return EOF;}




%%
