#ifndef HASH_H_
#define HASH_H_

#define HASH_SIZE 1009
#include <list>
#include <stack>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include <fstream>
#define DEBUG 0
//#define cout cout<<__LINE__<<" "<<__FILE__<<" "

using namespace std;

typedef enum scopespace_types { programvar, functionlocal, formalarg }scopespace_t;

typedef enum symbol_types {var_s,programfunc_s,libraryfunc_s}symbol_t;


typedef enum variable_type{LIBFUNC,FUNC,VAR,ARGUMENT }vartype;
typedef enum lookup_mode{LVAL_ID,LVAL_LOCAL,LVAL_GLOBAL,FUNCDEF_MODE }lmode;

typedef enum opcode {
    assign, 
    add, 
    sub, 
    mul, 
    divide, 
    mod,
    uminus, 
    and_op, 
    or_op,
    not_op, 
    if_eq,  
    if_not_eq,
    if_lesseq,  
    if_greatereq,   
    if_less,
    if_greater, 
    call,       
    param,  
    ret, 
    getretval, 
    funcstart,
    funcend,    
    tablecreate, 
    jump, 
    tablegetelem ,
    tablesetelem

}iopcode;

typedef enum expr_type {
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constint_e,
    constreal_e,
    constbool_e,
    conststring_e,

    nil_e
}expr_t;



typedef struct symT {
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
    bool funcused = false;

} Symbol;
/*
enum scopespace_types{
    globalvar,
    formalarg,
    functionlocal
    
};*/

typedef struct expre {
    expr_t  type=nil_e;
    Symbol  *sym;
    expre    *index;
    int     intConst;
    double  numConst;
    string  strConst;
    string  boolConst; //unsinged char
    expre   *next;
    expre   *keyval;
    bool iskey=false;
    bool  isval=false;
    int true_index=-1;
    int false_index=-1;
    int break_index=-1;
    int cont_index=-1;
    int true_end=-1;
    int false_end=-1;
    bool isAnd = nullptr;
    bool changeLabel=false;
    bool fromNot= false;

}expr;

typedef struct quads {
    iopcode op; 
    expr *  result;
    expr *  arg1;
    expr *  arg2;
    unsigned int label;
    unsigned int line;
    int taddress ;
}quad;

//done??
//struct apo vrv need2change


//extern Symbol;
string get_type(vartype check);


//done
//my multimap

//typedef unordered_multimap<int,Symbol> hashmap;
//hashmap Syriza;

void hideTheScope(int thisScope);
//done
//hash me sum twn ascii code / prime number 1009
int hashme (string word) ;

Symbol * isLibFunct(Symbol toCheck);

Symbol *LookupName(string s,int inscope);
Symbol *LookupforRef(string ,int );
//done
//fill symbol item
Symbol fill (string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active);

//done
// initialize symbol with lib funcs
void initializeHash();



//done
// leei o vvl->/* makes active vars in active inside function */ !!!!!!
void hideThem(int thisScope);

//done
//deactivate block
int hideIt(Symbol hideMe);

//done
//unnamed function get a name
string setFunctionName();

//done !! need change format
// print hash table
void printSymbols();

Symbol* Lookup(Symbol toAdd,lmode mode );



//TODO
//all insertions should be checked, using hash insert (for now) without rules until TODO is removed (mainly in initialize)
int insertMe (Symbol toadd);

Symbol* isLocal(Symbol toCheck);

//TODO
// Insert new symbol
Symbol * insertH(Symbol toAdd);

Symbol* isPresent(Symbol toCheck);

Symbol* isSameFscopeNotFunc(Symbol toCheck);

//bool isLibFunct(Symbol toCheck);

Symbol* isGlobalVar(Symbol toAdd);

Symbol* isGlobalFunc(Symbol toAdd);

Symbol* isArgument(Symbol toCheck);

Symbol* isActive(Symbol toCheck);

Symbol* isActiveProgFunct(Symbol toCheck);

Symbol *isSameScope(Symbol toCheck);

Symbol *isSameFScope(Symbol toCheck);

Symbol *isVarValid(Symbol toCheck);

Symbol *isVarRefValid(Symbol toCheck);

Symbol *isAncestor(Symbol toCheck);

Symbol *isPresentVar(Symbol toCheck);

bool isPastVar(Symbol toCheck);

Symbol *isSameScopeFFunc(Symbol toCheck);

bool isIllegalScopeVarArg(Symbol toCheck);

Symbol *isZeroScopeFunc(Symbol toCheck);

Symbol* nameLookup(string,int);

Symbol *createFSymbol(string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active,unsigned int offset,scopespace_types space);

Symbol fill3 (string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active,unsigned int offset,enum scopespace_types space);

Symbol *fill4 ( Symbol *tofill,string name,int scope, int line, string nameF, 
  int scopeF,int lineF,vartype type, bool active,unsigned int offset,scopespace_types space, int dotalocal);

bool isOpValid (string toCheck, int lineno);//den kserw an ti usaroume en telei, rwta ton aristoteli

vector<Symbol> get_list(int);
void ins_toScope(Symbol,int);
void rm_fromScope(Symbol,int);
void print_scope(int);
void printAll(void);

void insertPt(Symbol*);
///

void true_rest();
void false_rest();



#endif




















