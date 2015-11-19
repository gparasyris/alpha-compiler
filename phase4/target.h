#ifndef TARGET_H_
#define TARGET_H_

#include "hash.h"
#include "intermediate.h"


using namespace std;

/****************/
extern string blvr;
extern string Imagikas;
extern string PokeMan;
/****************/  
typedef enum Vmopcode {
    assign_vm,
    add_vm,
    sub_vm, 
    mul_vm,
    divide_vm,
    mod_vm,
    uminus_vm,
    and_op_vm,
    or_op_vm,
    nop_vm,
    jeq_vm,
    jne_vm,
    jle_vm,
    jge_vm,
    jlt_vm,
    jgt_vm,
    call_vm,
    pusharg_vm,  
    ret_vm,
    getretval_vm,
    enterfunc_vm,
    exitfunc_vm,
    newtable_vm,
    jump_vm, 
    tablegetelem_vm,
    tablesetelem_vm

}vmopcode;

typedef enum VmincJumparg_t {
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
    
} vmarg_t;


typedef struct Vmarg_p{
   vmarg_t  type= nil_a;
   unsigned val=-1;
} vmarg;



typedef struct Instruction{
  vmopcode opcode;
  vmarg *result;
  vmarg *arg1;
  vmarg *arg2;
  unsigned int line;
  unsigned int alphaline=-1;

}instruction;


typedef struct Incomplete_jump{
  unsigned int instrNo; 
  unsigned int iaddress;    
  
} inc_jump;

typedef struct Function_sym{
    vmarg_t type;
    string nameF;
    unsigned scopeF;
    unsigned lineF;
    unsigned dotalocal;
    vector<int> return_list;
    bool funcused= false;
    Symbol *sym;


}func_sym;

typedef unsigned char Byte;

//Sta var typwnw scopespace / offset






extern void generate_TABLECREATE( quad *quad );
extern void generate_ADD(quad *);
extern void generate_UMINUS(quad *);
extern void generate_IF_LESSEQ(quad *);
extern void generate_AND (quad *);
extern void generate_SUB(quad *);
extern void generate_MUL(quad *);
extern void generate_DIV(quad *);
extern void generate_MOD(quad *);
extern void generate_NEWTABLE(quad *);
extern void generate_TABLEGETELEM(quad *);
extern void generate_TABLESETELEM(quad *);
extern void generate_ASSIGN(quad *);
extern void generate_NOP(quad *);
extern void generate_JUMP(quad *);
extern void generate_IF_EQ(quad *);
extern void generate_IF_NOTEQ(quad *);
extern void generate_IF_GREATER(quad *);
extern void generate_IF_GREATEREQ(quad *);
extern void generate_IF_LESS(quad *);
extern void generate_IF_LESEQ(quad *);
extern void generate_NOT(quad *);
extern void generate_OR(quad *);
extern void generate_PARAM(quad *);
extern void generate_CALL(quad *);
extern void generate_GETRETVAL(quad *);
extern void generate_FUNCSTART(quad *);
extern void generate_RETURN(quad *);
extern void generate_FUNCEND(quad *);

vmarg * make_booloperand( vmarg* , unsigned  );
vmarg * make_retvaloperand( vmarg*  );
vmarg * make_doubleoperand(int );
vmarg * make_intoperand(int );



unsigned int consts_newstring( string );
unsigned int consts_newint( int  );
unsigned int consts_newdouble( double  );
unsigned int libfuncs_newused( string  );
unsigned int userfuncs_newfunc( Symbol *sym );
unsigned int too_bool(string );


unsigned int lookup(Symbol *);
void emitVmarg(instruction *ins);
string printInstrcode(vmopcode op );




int nextinstructionlabel(void);
void printINstr(void) ;
void generate_abc();
void generate_o(ofstream &binarw);

string printInstrcode(vmopcode op );
void generate_binary();
vmarg *make_operand1(expr *e);
void make_operand (expr *e, vmarg *argtopass);
void backpatchre(int f , int r);
unsigned int userfuncs_funcend(int);
unsigned int printVal( unsigned int q);
vmarg_t print_type( vmarg_t type);
void lookglobal(Symbol *sym);
unsigned int string_libfuncs (string s);


void avoid_patch(quad *);
void avoid_func(quad *);
#endif


