
#ifndef	INTERMEDIATE_H_
#define INTERMEDIATE_H_
#include "hash.h"
#include <cstring>
//extern Symbol;
using namespace std;
//extern Symbol;
//extern symT;
//extern symT Symbol;
extern stack <int> aerials;

expr *lvalue_dais(struct symT *s);
expr *emit_table(expr *,expr *,int );

expr* emit_iftableitem(expr* e, int line);
void printStack(void);
//check
void expand(void);

bool validForOp(expr* expr);
//void validPrints(void);
//check
void emit(iopcode op ,expr * arg1, expr * arg2, expr * result, unsigned int label, unsigned int line);

string gettype(vartype );
//check
string newtempname(void);
//check
void resettemp(void);
//check
Symbol* newtemp(void);
//check
scopespace_t currentscopespace(void);
//check
unsigned int currentscopeoffset( void );
//check
void inccurrscopeoffset( void );
//check
void enterscopespace( void );
//check
void exitscopespace( void );
//check
expr* lvalue_expr(string  passit);
//check
expr* newexpr(expr_t t);
//not check
expr* newexpr_conststring(string s);
//check
bool istempname(string s);

void resetformalargoffset(void);

void resetfunctionlocalsoffset(void);

void printQuads(void);

//big todo
expr * insertVal( int val, double dval, string check );

expr * constString_expr(string passit);

expr * constInt_expr(int num);

string printexpr(expr* e );

string printOpcode(iopcode op );

string printLabel(unsigned int label);

void restorecurrscopeoffset( unsigned int n );

void resetfunctionlocaloffset( void );

void resetformalargoffset( void );

//aoua
expr *func_call(expr *lval, expr *args, unsigned int line,int  starthere );
expr *func_methodcall(expr *lval, string idname, unsigned int line,int starthere); //changed

void backpatch(unsigned quadNumber,unsigned int label);

bool uminus_validity(expr *);

//stav

expr *op_emit(iopcode op, expr *arg1 , expr *arg2,int line);

expr *obj_manage(int);
void break_manage(int );
void continue_manage(int ,int);
void printbreak(void) ;


void true_backpatch(int starthere,int endhere,int contjump);
void false_backpatch(int starthere,int endhere,int contjump);


void printtruelist(void);
int load_f();

int load_t();

///
void print_false();
void print_true();
int merge_false( int first , int second);
int merge_true( int first , int second);

void swap(int truer, int falser);
void bool_assign(expr *lval, expr *rval);
void printList(void) ;



expr* true_test(expr*,expr*,int);

void emit_or(iopcode op ,expr * arg1, expr * arg2, expr * result, unsigned int label, unsigned int line , int place);
expr* true_test_or(expr* expr1,expr* arg,expr* arg2 , int l_int);
int load_f_or(int l_int);
int load_t_or(int l_int);
void fix_elist( int,int);
void fix_quads( int t_int ,int f_int );
expr *lvalue_symbol(expr* expre,struct symT *s);


int load_c(int set);
int load_b(int set);
int merge_break( int first , int second);
int merge_cont( int first , int second);
void break_backpatch(int starthere,int endhere,int contjump);
void cont_backpatch(int starthere,int endhere,int contjump);





#endif