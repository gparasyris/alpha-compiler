#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "avm.h"

extern std::ifstream infile;
extern std::ofstream outfile;
extern vector <string> _strings;
extern vector <int> _numbers;
extern vector <userfunc> _userfuncs;
extern vector <string> _libfuncs;
extern vector <instr> _instructions;
extern vector <double> _doubles;

extern unsigned int totalStrings;
extern unsigned int totalNumbers;
extern unsigned int totalFuncs;
extern unsigned int totalCode;
extern unsigned int totalDoubles;
extern unsigned int totalLibfuncs;
extern unsigned int totalGlobals ;


void parse_binary(void){
unsigned int magicnumber;/*, numofStrings;
int integer,numofDoubles;
double dbl;
unsigned int  numofUserfuncs, funcaddr, funclocals,numofLibfuncs,globals,code,numofInts;
infile.open("binary.binary", ios::in | ios::binary);*/
infile.read((char*)&magicnumber, sizeof(unsigned int));
infile.read((char*)&totalStrings, sizeof(unsigned int));
unsigned int  funcaddr, funclocals;
string buffer;
int integer;
double dbl;
char buf;
if(magicnumber != 340200501){
	cout << "NOT AN ALPHA BINARY FILE:" << endl;
}
//cout << "magicnumber: " << magicnumber << endl << "numofStrings: " << numofStrings << endl;
for(int i =0; i<totalStrings; i++){
	infile.read(&buf, sizeof(char));
	while(buf!='\0'){
		if(buf==EOF) break;
		//cout << buf << endl;
		buffer += buf;
		infile.read(&buf, sizeof(char));

	}
	buffer += buf;
	//cout << buffer << endl;
	_strings.push_back(buffer);
	buffer.clear();
	
}
infile.read((char*)&totalNumbers, sizeof(unsigned int));
for(int i =0; i<totalNumbers; i++){
	infile.read((char*)&integer, sizeof(int));
	//cout << integer << endl;
	_numbers.push_back(integer);
}
infile.read((char*)&totalDoubles, sizeof(unsigned int));
for(int i =0; i<totalDoubles; i++){
	infile.read((char*)&dbl, sizeof(double));
	//cout << dbl << endl;
	_doubles.push_back(dbl);
}
infile.read((char*)&totalFuncs, sizeof(unsigned int));
//cout << numofUserfuncs  << endl;
for(int i=0; i<totalFuncs; i++){
	buffer.clear();
	infile.read((char*)&funcaddr, sizeof(unsigned int));
	//cout << funcaddr << ' ';
	infile.read((char*)&funclocals, sizeof(unsigned int));
	//cout << funclocals << ' ';
	infile.read(&buf, sizeof(char));
	while(buf!='\0'){
		if(buf==EOF) break;
		//cout << buf << endl;
		buffer += buf;
		infile.read(&buf, sizeof(char));

	}
	userfunc functoAdd=create_Func1(buffer,funcaddr,funclocals);
	_userfuncs.push_back(functoAdd);
	//cout << buffer << endl;
}

infile.read((char*)&totalLibfuncs, sizeof(unsigned int));
//cout << numofLibfuncs  << endl;
for(int i=0; i<totalLibfuncs; i++){
	buffer.clear();
	infile.read(&buf, sizeof(char));
	while(buf!='\0'){
		if(buf==EOF) break;
		//cout << buf << endl;
		buffer += buf;
		infile.read(&buf, sizeof(char));

	}
	_libfuncs.push_back(buffer);
	//cout << buffer << endl;
}
infile.read((char*)&totalGlobals, sizeof(unsigned int));
infile.read((char*)&totalCode, sizeof(unsigned int ));
unsigned short _opcode;
unsigned int res_type;
unsigned int res_value;
unsigned int arg1_type;
unsigned int arg1_value;
unsigned int arg2_type;
unsigned int arg2_value,alphaline;
vmarg res, arg1, arg2;
instruction ins;
//cout << totalGlobals << ' ' << totalCode << endl;
for(int i=0; i<totalCode; i++){
	infile.read( (char *) &_opcode, sizeof(unsigned short) );
	infile.read( (char *) &res_type, sizeof(unsigned int) );
	infile.read( (char *) &res_value, sizeof(unsigned int) );
	infile.read( (char *) &arg1_type, sizeof(unsigned int) );
	infile.read( (char *) &arg1_value, sizeof(unsigned int) );
	infile.read( (char *) &arg2_type, sizeof(unsigned int) );
	infile.read( (char *) &arg2_value, sizeof(unsigned int) );
	infile.read( (char *) &alphaline, sizeof(unsigned int) );
	res = create_VMarg1(res_type,res_value);
	arg1 = create_VMarg1(arg1_type,arg1_value);
	arg2 = create_VMarg1(arg2_type,arg2_value);
	//cout << "alphaline: " << alphaline << endl; 
	ins=create_Instr1(_opcode,res, arg1, arg2,i,alphaline);
	_instructions.push_back(ins);

	//cout << "INSTRUCTION: " << _opcode << ' ' <<res_type << ' ' <<res_value <<' ' << arg1_type<< ' ' <<arg1_value <<' '<< arg2_type << ' ' <<arg2_value << endl;
}
return;
//cout << buffer << endl;
/*char c;
for(int i=0; i<numofStrings; i++){
	infile.get(&c, sizeof(char));
	cout << c << endl;
	/*while(c!='\0'){
		cout << *c << endl;
		buffer+=*c;
		infile.read(c, sizeof(char));
	}
	//cout << buffer << endl;
}*/
//infile.close();

}

vmarg_t getArgType1(unsigned int a){
	switch(a)
	{
		case 0: return label_a;
		case 1: return global_a;
		case 2: return formal_a;
		case 3: return local_a;
		case 4: return number_a;
		case 5: return string_a;
		case 6: return bool_a;
		case 7: return nil_a;
		case 8: return userfunc_a;
		case 9: return libfunc_a;
		case 10: return retval_a;
		case 11: return realval_a;
		case 12: return undef_a;
		default: assert(0);
	}
}


struct userfunction create_Func1(string nam, unsigned int addr, unsigned int tlocals){
	userfunc ret;
	ret.name=nam;
	ret.address = addr;
	ret.locals = tlocals;
	return ret;
}

instr create_Instr1(unsigned short op, vmarg res, vmarg a1, vmarg a2 ,int srcLine,unsigned int alphaline)/*int line)*/{
	instr i;
	i.opcode = getOpcode(op);
	i.result = res;
	i.arg1 = a1;
	i.arg2 = a2;
	i.srcLine = srcLine;
	i.aline = alphaline;
	return i;
}

vmarg create_VMarg1(unsigned int t, unsigned int v){
	vmarg r;
	r.type = getArgType1(t);
	r.val = v;
	return r; 
}


vmopcode getOpcode(unsigned short a){
	switch(a)
	{
		case 0: return assign_vm;
		case 1: return add_vm;
		case 2: return sub_vm;
		case 3: return mul_vm;
		case 4: return divide_vm;
		case 5: return mod_vm;
		case 6: return uminus_vm;
		case 7: return and_op_vm;
		case 8: return or_op_vm;
		case 9: return not_op_vm;
		case 10: return jeq_vm;
		case 11: return jne_vm;
		case 12: return jle_vm;
		case 13: return jge_vm;
		case 14: return jlt_vm;
		case 15: return jgt_vm;
		case 16: return call_vm;
		case 17: return param_vm;
		//case 18: return ret_vm;
    	//case 19: return getretval_vm;
		case 20: return enterfunc_vm;
		case 21: return exitfunc_vm;
		case 22: return newtable_vm;
		case 23: return jump_vm;
		case 24: return tablegetelem_vm;
		case 25: return tablesetelem_vm;
	}
}