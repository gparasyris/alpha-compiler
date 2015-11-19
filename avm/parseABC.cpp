#include <iostream>
#include <string>
#include <algorithm>
#include "avm.h"
//ONE PARSER to rule them all, ONE PARSER to parse them,
//ONE PARSER to bring them all and in the darkness bind them.
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
unsigned int totalGlobals = 0;

string line,temp,templine;
size_t found;
double doublecounter,d;
unsigned int linecounter=1, temporary, alphaline;
int itemcounter, numbercounter, addr, tlocals, tmp;
userfunc functoAdd;
instr ins;
vmarg res,arg1,arg2;
vmopcode op;
int j=0;
bool finished = false;
int srcLine=0;
string pline;
void parse_abc(){
	while(std::getline(infile,line)){
		if(finished) break;
		if(linecounter==1){
			linecounter++;
			found=line.find("magicnumber");
			if(found==string::npos){
			//IMPLEMENT ERROR
			cout << "ERROR NOT AN ALPHA BINARY FILE" << endl;
			break;
			}
			if(line.substr(12,line.length()-1)!="340200501"){
				//IMPLEMENT ERROR
				cout << "ERROR NOT A VALID ALPHA BINARY FILE" << endl;
				break;
			}
		}
		else{
			found = line.find("strings");
			if(found!=string::npos){
				temp=line.substr(8,line.length()-1);
				itemcounter = std::stoi(temp,nullptr,0);
				totalStrings = itemcounter;
				for(int i=0; i<itemcounter; i++){
					std::getline(infile,line);
					found=line.find("\"");
					//cout << "FIND:" << found << endl;
					if(found!=string::npos){
						line.erase(0,found+1);

						//outfile << "VRIKA ENA:"<<line << endl;
						found = line.find("\"");
						//cout << "FIND:" << string::npos << endl;
						while(found==string::npos){
							//cout << "MPIKA" << endl;
							//outfile << line << endl;
							pline=line+"\n";
							std::getline(infile,line);
							//i++;
							line=pline+line;
							found = line.find("\"");
							if(found!=string::npos){line.erase(found,found+1);}
						}
					}
					found = line.find("\"");
					//i++;
					if(found!=string::npos)line.erase(found,found+1);
					//outfile << line << endl;
					_strings.push_back(line);
				}

			}
			found = line.find("integers");
			if(found!=string::npos){
				temp=line.substr(9,line.length()-1);
				itemcounter = std::stoi(temp,nullptr,0);
				totalNumbers = itemcounter;
				for(int i=0; i<itemcounter; i++){
					std::getline(infile,line);
					numbercounter = std::stoi(line,nullptr,0);
					_numbers.push_back(numbercounter);
				}

			}
			found = line.find("doubles");
			//cout << "DOUBLES" << endl;
			if(found!=string::npos){
				temp=line.substr(8,line.length()-1);
				itemcounter = std::stoi(temp,nullptr,0);
				totalDoubles = itemcounter;
				for(int i=0; i<itemcounter; i++){
					std::getline(infile,line);
					d = std::stod(line);
					//cout << "DOUBES"<< d << endl;
					_doubles.push_back(d);
				}

			}
			found = line.find("userfunctions");
			if(found!=string::npos){
				temp=line.substr(14,line.length()-1);
				itemcounter = std::stoi(temp,nullptr,0);
				totalFuncs = itemcounter;
				for(int i=0; i<itemcounter; i++){
					std::getline(infile,line);

					found = line.find(" ");
					temp.clear();
					temp = line.substr(0,found);
					addr = std::stoi(temp,nullptr,0);
					line.erase(0,found+1);
					found = line.find(" ");
					temp.clear();
					temp = line.substr(0,found);
					tlocals = std::stoi(temp,nullptr,0);
					line.erase(0,found+1);
					functoAdd=create_Func(line,addr,tlocals);
					_userfuncs.push_back(functoAdd);
				}

			}
			found = line.find("libfunctions");
			//cout << "LIBFUNC" << endl;
			if(found!=string::npos){
				temp=line.substr(13,line.length()-1);
				itemcounter = std::stoi(temp,nullptr,0);
				totalLibfuncs = itemcounter;
				for(int i=0; i<itemcounter; i++){
					std::getline(infile,line);
					_libfuncs.push_back(line);
				}

			}
			found = line.find("globals");
			if(found!=string::npos){
				temp=line.substr(8,line.length()-1);
				itemcounter = std::stoi(temp,nullptr,0);
				totalGlobals = itemcounter;
			}
			found = line.find("code");
			if(found!=string::npos){
				temp=line.substr(5,line.length()-1);
				itemcounter = std::stoi(temp,nullptr,0);
				totalCode = itemcounter;
				for(int i=0; i<itemcounter+1; i++){
					std::getline(infile,line);
					if(j>0){
						finished = true;
						found=line.find("OPCODE");
						line.erase(0,found+8);
						found = line.find(" ");
						temp.clear();
						temp = line.substr(0,found);
						op = parse_opcode(temp);
						found = line.find("RESULT");
						line.erase(0,found+9);
						temp.clear();
						found = line.find(" ");
						temp = line.substr(0,found);
						tmp = std::stoi(temp,nullptr,0);
						line.erase(0,found+3);
						temp.clear();
						found = line.find(" ");
						temp = line.substr(0,found);
						line.erase(0,found);
						temporary = std::stoul(temp,nullptr,0);
						res = create_VMarg(tmp,temporary);
						found = line.find("ARG1");
						line.erase(0,found+7);
						temp.clear();
						found = line.find(" ");
						temp = line.substr(0,found);
						tmp = std::stoi(temp,nullptr,0);
						line.erase(0,found+3);
						temp.clear();
						found = line.find(" ");
						temp = line.substr(0,found);
						line.erase(0,found);
						temporary = std::stoul(temp,nullptr,0);
						arg1 = create_VMarg(tmp,temporary);
						found = line.find("ARG2");
						line.erase(0,found+7);
						temp.clear();
						found = line.find(" ");
						temp = line.substr(0,found);
						tmp = std::stoi(temp,nullptr,0);
						line.erase(0,found+3);
						temp.clear();
						found = line.find(" ");
						temp = line.substr(0,found);
						line.erase(0,found);
						temporary = std::stoul(temp,nullptr,0);
						arg2 = create_VMarg(tmp,temporary);
						found = line.find("AL");
						line.erase(0,found+5);
						temp.clear();
						found = line.find(" ");
						temp=line.substr(0,found);
						alphaline = std::stoul(temp,nullptr,0);
						//cout <<"ALPHALINE: "<< alphaline << endl;
						ins=create_Instr(op,res, arg1, arg2,srcLine,alphaline);/* int line);*/
						_instructions.push_back(ins);
						srcLine++;

					}
					j++;
					
					
				}

			}


		}
	
	}
	return;
}

struct userfunction create_Func(string nam, unsigned int addr, unsigned int tlocals){
	userfunc ret;
	ret.name=nam;
	ret.address = addr;
	ret.locals = tlocals;
	return ret;
}

vmarg_t getArgType(int a){
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




instr create_Instr(vmopcode op, vmarg res, vmarg a1, vmarg a2 ,unsigned srcLine, unsigned int alphaline)/*int line)*/{
	instr i;
	i.opcode = op;
	i.result = res;
	i.arg1 = a1;
	i.arg2 = a2;
	i.srcLine = srcLine;
	i.aline = alphaline;
	return i;
}

vmarg create_VMarg(int t, unsigned v){
	vmarg r;
	r.type = getArgType(t);
	r.val = v;
	return r; 
}


vmopcode parse_opcode(string opc){
	if(opc == "assign_vm"){return assign_vm;}
	if(opc == "add_vm")	{return add_vm;}
	if(opc == "sub_vm")	{return sub_vm;}
	if(opc == "mul_vm"){return mul_vm;}
	if(opc == "divide_vm"){return divide_vm;}
	if(opc == "mod_vm"){return mod_vm;}
	if(opc == "uminus_vm"){return uminus_vm;}
	if(opc == "and_op_vm"){return and_op_vm;}
	if(opc == "or_op_vm"){return or_op_vm;}
	if(opc == "not_op_vm"){return not_op_vm;}
	if(opc == "jeq_vm"){return jeq_vm;}
	if(opc == "jne_vm"){return jne_vm;}
	if(opc == "jle_vm"){return jle_vm;}
	if(opc == "jge_vm"){return jge_vm;}
	if(opc == "jlt_vm"){return jlt_vm;}
	if(opc == "jgt_vm"){return jgt_vm;}
	if(opc == "call_vm"){return call_vm;}
	if(opc == "pusharg_vm"){return param_vm;}
	//if(opc == "ret_vm"){return ret_vm;}
	//if(opc == "getretval_vm"){return getretval_vm;}
	if(opc == "enterfunc_vm"){return enterfunc_vm;}
	if(opc == "exitfunc_vm"){return exitfunc_vm;}
	if(opc == "newtable_vm"){return newtable_vm;}
	if(opc == "jump_vm"){return jump_vm;}
	if(opc == "tablegetelem_vm"){return tablegetelem_vm;}
	if(opc == "tablesetelem_vm"){return tablesetelem_vm;}
	assert(0);
}

