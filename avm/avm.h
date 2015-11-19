#ifndef AVM_H_
#define AVM_H_

#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#define AVM_STACKSIZE  4096
#define AVM_STACKENV_SIZE 4
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1
#define AVM_ENDING_PC totalCode
#define AVM_TABLE_HASHSIZE 211
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define GLOBALS totalGlobals
//#define cout cout<<__LINE__<<" "<<__FILE__<<" "

#define AVM_FROM_TOTALARGUMENTS stack[topsp+1].data.intval+4

using namespace std;

typedef enum linetype{
	strings,
	numbers,
	userfunctions,
	libfunctions,
	code
}line_t;

typedef struct userfunction{
	string name;
	unsigned int address;
	unsigned int locals;
}userfunc;

typedef enum vmarg_type {
	label_a		= 0,
	global_a	= 1,
	formal_a	= 2,
	local_a		= 3,
	number_a	= 4,
	string_a	= 5,
	bool_a		= 6,
	nil_a		= 7,
	userfunc_a	= 8,
	libfunc_a	= 9,
	retval_a	= 10,
  realval_a = 11,
	undef_a		= 12
}vmarg_t;

/*
def enum VmincJumparg_t {
    label_a ,//0
    global_a ,//1
    formal_a ,//2
    local_a ,//3
    integer_a ,//4
    string_a ,//5
    bool_a ,//6
    nil_a ,//7
    userfunc_a ,//8
    libfunc_a ,//9
    retval_a,//10
    real_a//11
*/

typedef enum Vmopcode {
    assign_vm, //0
    add_vm, //1
    sub_vm, 
    mul_vm,
    divide_vm,
    mod_vm,
    uminus_vm,
    and_op_vm,
    or_op_vm,
    not_op_vm,
    jeq_vm, //10
    jne_vm,
    jle_vm,
    jge_vm,
    jlt_vm,
    jgt_vm,
    call_vm,
    param_vm,  
    //ret_vm,
    //getretval_vm,
    enterfunc_vm,
    exitfunc_vm,
    newtable_vm,
    jump_vm, 
    tablegetelem_vm,
    tablesetelem_vm
}vmopcode;

typedef struct vmarg {
	vmarg_t  type;
	unsigned val;
} vmarg;

typedef struct instruction {
	vmopcode opcode;
	vmarg    result;
	vmarg    arg1;
	vmarg    arg2;
	unsigned srcLine;
    unsigned int aline;
} instr;

typedef  enum avm_memcell_t{
	integer_vm =0,
	real_vm=1,
	string_vm=2,
	bool_vm =3,
	table_vm=4,
	userfunc_vm=5,
	libfunc_vm=6,
	nil_vm=7,
	undef_vm=8
}avm_memcell_t;


 
typedef struct avm_memcell{
  avm_memcell_t type = undef_vm ;
  char * namef;
  unsigned int funcoffset =-1;
  union{
    double realval;
    int 	intval;
    char* strVal;
    unsigned char boolVal;
    struct avm_table* tableVal;
    unsigned funcVal;
    char* libfuncVal;
  }data;
}avm_memcell;

typedef struct avm_table_bucket{
    struct avm_memcell key;
    struct avm_memcell value;
    //struct avm_table_bucket *next;
  
}avm_table_bucket;


typedef struct avm_table{
  unsigned refCounter=0;
  vector<avm_table_bucket> strIndexed;
  vector<avm_table_bucket> numIndexed;
  vector<avm_table_bucket> boolIndexed;
  vector<avm_table_bucket> nilIndexed;
  vector<avm_table_bucket> libIndexed;
  vector<avm_table_bucket> userIndexed;

  //struct avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
  //struct avm_table_bucket*  numIndexed[AVM_TABLE_HASHSIZE];

  unsigned total=0;
struct{
    unsigned numtotal=0;
    unsigned strtotal=0;
    unsigned booltotal=0;
    unsigned userfunctotal=0;
    unsigned libfunctotal=0;
    unsigned niltotal=0;
    unsigned tabletotal=0;
 }totals;
  
}avm_table;

typedef string (*tostring_func_t)(avm_memcell*);
typedef void (*library_func_t)(void);
typedef void (*memclear_func_t)(avm_memcell*);
typedef void (*execute_func_t)(instruction*);

//typedef void (*execute_func_t)(instruction*);
void parse_binary(void);
struct userfunction create_Func1(string nam, unsigned int addr, unsigned int tlocals);
vmopcode getOpcode(unsigned short a);
vmarg create_VMarg1(unsigned int t, unsigned int v);
instr create_Instr1(unsigned short op, vmarg res, vmarg a1, vmarg a2 ,int srcLine,unsigned int alphaline);

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void parse_abc(void);
userfunction create_Func(string nam, unsigned int addr, unsigned int tlocals);
instr create_Instr(vmopcode op, vmarg res, vmarg a1, vmarg a2 ,unsigned srcLine, unsigned int alphaline);
vmarg_t getArgType(int a);
vmarg create_VMarg(int t, unsigned v);
vmopcode parse_opcode(string opc);
string printInstrcode(vmopcode op);
void printINstr(void);

void initialize_TheMachine(void);
avm_memcell* avm_getactual(unsigned i);
unsigned avm_totalactuals(void);
unsigned avm_get_envvalue(unsigned i);
string consts_getstring(unsigned index);
string libfuncs_getused(unsigned index);
string avm_tostring(avm_memcell* m);
//
string nil_tostring(avm_memcell* m);
string userfunc_tostring(avm_memcell* m);
string string_tostring(avm_memcell* m);
string libfunc_tostring(avm_memcell* m);
string undef_tostring(avm_memcell* m);
string table_tostring(avm_memcell* m);
string bool_tostring(avm_memcell* m);
string real_tostring(avm_memcell* m);
string int_tostring(avm_memcell* m);
//
//Libfuncs
void libfunc_print(void);
void libfunc_input(void);
void libfunc_cos(void);
void libfunc_sin(void);
void libfunc_sqrt(void);
void libfunc_typeof(void);
void libfunc_strtonum(void);
void libfunc_totalarguments(void);
void libfunc_argument(void);
void libfunc_tablecopy(void);
void libfunc_tablelength(void);
void libfunc_tableindices(void);


library_func_t avm_getlibraryfunc(string funcName);
int libhash (string word);
void avm_registerlibfunc(char* id, library_func_t addr);
void avm_calllibfunc(string id);
void avm_callsaveenvironment(void);
void avm_push_envvalue(unsigned val);
void avm_dec_top(void);
int consts_getnumber(unsigned index);
double consts_getdouble(unsigned index);
void avm_memcellclear(avm_memcell* m);

void memclear_string(avm_memcell* m);

void memclear_table(avm_memcell* m);
void avm_tabledecrefcounter(avm_table* t);
void execute_cycle(void);
instruction *fil_instruction(instruction inst);
/*
extern void execute_assign(instruction);//finished
extern void execute_add(instruction);//finished
extern void execute_sub(instruction);//finished
extern void execute_mul(instruction);//finished
extern void execute_div(instruction);//finished
extern void execute_mod(instruction);//finished
extern void execute_uminus(instruction);//finished
///////////////////////////////////////////
extern void execute_and(instruction);
extern void execute_or(instruction);
extern void execute_not(instruction);
/////////////////////////////////////////////
extern void execute_jeq(instruction);//finished
extern void execute_jne(instruction);//finished
extern void execute_jle(instruction);//finished
extern void execute_jge(instruction);//finished
extern void execute_jlt(instruction);//finished
extern void execute_jgt(instruction);//finished
//////////////////////////////////////////////
extern void execute_call(instruction);
extern void execute_pusharg(instruction);
extern void execute_funcenter(instruction);
extern void execute_funcexit(instruction);
/////////////////////////////////////////////////
extern void execute_newtable(instruction);
extern void execute_tablegetelem(instruction);
extern void execute_tablesetelem(instruction);
//////////////////////////////////////////////////
extern void execute_nop(instruction);
*/
void execute_enterfunc(instruction* unused);
void execute_funcexit(instruction* unused);

extern execute_func_t executeFuncs[];


//Arithm
void execute_arithmetic(instruction * unused);
void execute_add(instruction* unused);
void execute_sub(instruction* unused);
void execute_mul(instruction* unused);
void execute_div(instruction* unused);
void execute_mod(instruction* unused);
//


vmarg *fill_arg(vmarg arg);
userfunc* avm_getfuncinfo(unsigned address);
void execute_pusharg (instruction* instr);
void avm_assign(avm_memcell* lv, avm_memcell* rv);
void execute_call (instruction* instr1);
void execute_assign(instruction* instr);

void execute_uncjump(instruction *instr);

extern unsigned top,topsp,pc, initial_topsp;
extern vector <avm_memcell> stack;
extern unsigned int totalGlobals;
extern unsigned char executionFinished;
extern unsigned int totalActuals;
extern  avm_memcell ax, bx, cx, retval;
extern vector <instr> _instructions;
extern unsigned int totalCode;
extern unsigned currLine;

extern unsigned int totalFuncs;
extern  vector <userfunc> _userfuncs;
extern bool debug;
extern bool regdebug;


typedef unsigned char (*cmp_func) (double x, double  y);
void execute_relational(instruction * instr1);
#define execute_jge execute_relational
#define execute_jgt execute_relational
#define execute_jle execute_relational
#define execute_jlt execute_relational


typedef unsigned char (*eq_func) (double x, double y);
void execute_equality(instruction * instr1);
#define execute_jeq execute_equality
#define execute_jne execute_equality


//typedef unsigned char  booltest_t boolFuncs[] = {
typedef unsigned char (*booltest_t)(avm_memcell*);
/*
extern booltest_t boolFuncs[];
unsigned char integerbool(avm_memcell* m);
unsigned char realbool(avm_memcell* m);
unsigned char stringbool(avm_memcell* m); 
unsigned char unused(avm_memcell* m);
unsigned char tablebool(avm_memcell* m);
unsigned char userfuncbool(avm_memcell* m);
unsigned char libfuncbool(avm_memcell* m);
unsigned char nilbool(avm_memcell* m);
unsigned char undefbool(avm_memcell* m);
*/
/*
extern void execute_jge(instruction * instr1);
extern void execute_jgt(instruction * instr1);
extern void execute_jle(instruction * instr1);
extern void execute_jlt(instruction * instr1);
*/

void  execute_uminus(instruction* instr);
void  execute_and(instruction* instr);
void  execute_or(instruction* instr);
void  execute_not(instruction* instr);
//TABLE FUNCS
void  execute_newtable(instruction* instr);
void  execute_tablegetelem(instruction* instr);
void  execute_tablesetelem(instruction* instr);
void  execute_nop(instruction* instr);



void avm_tableincrefcounter(avm_table* t);
//void avm_tabledecrefcounter(avm_table* t);
void avm_tabledestroy(avm_table* t);
void avm_tablebucketsdestroy(vector<avm_table_bucket> table);
//HELPER FUNCS
int hashf (const char * s);

typedef enum mode_type{
    getme,
    setme
} mode_type;

avm_memcell* stringIndex_lookup(  vector<avm_table_bucket> &table,avm_table_bucket bucket,mode_type mode );

avm_memcell* tablecopy(avm_memcell* t);
avm_memcell* tableindices(avm_memcell* t);
unsigned int tablelength(avm_memcell* t);

void copy_bucket( avm_table_bucket &bucket_new, avm_table_bucket &bucket_old );
void InputType(string s);
void t2string(avm_table* m);
void passtotals(avm_memcell *,avm_memcell *t);
unsigned int libfunc_lookup(char * x,vector<avm_table_bucket> &table);
void libIndexed_set(vector<avm_table_bucket> &table);
void userIndexed_set(vector<avm_table_bucket> &table);
unsigned int userfunc_lookup(char * x,unsigned num,vector<avm_table_bucket> &table);

void findef(void);

void functorcall(avm_memcell* table);
//==========Externs=================/
extern std::ifstream infile;
extern std::ofstream outfile;
extern vector <string> _strings;
extern vector <int> _numbers;
extern vector <userfunc> _userfuncs;
extern vector <string> _libfuncs;
extern vector <instr> _instructions;
extern vector <double> _doubles;
extern vector <avm_memcell> stack ;
extern avm_memcell ax, bx, cx, retval;
extern unsigned top,topsp;
extern unsigned currLine ;
extern unsigned int  command, oldPC;
extern vector < int > commandvector;

extern unsigned char executionFinished;
extern unsigned int pc;

extern unsigned int totalStrings;
extern unsigned int totalNumbers;
extern unsigned int totalFuncs;
extern unsigned int totalCode;
extern unsigned int totalDoubles;
extern unsigned int totalLibfuncs;
extern unsigned int totalArgs;
extern unsigned int totalActuals;
extern bool debug;
extern bool regdebug;





//==========Externs_end=================/

#endif