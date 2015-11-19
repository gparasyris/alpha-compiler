#include "avm.h"

#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define GLOBALS totalGlobals

//===========Tools=============================/
std::ifstream infile;
std::ofstream outfile;
vector <string> _strings;
vector <int> _numbers;
vector <userfunc> _userfuncs;
vector <string> _libfuncs;
vector <instr> _instructions;
vector <double> _doubles;
vector <avm_memcell> stack (4096);
avm_memcell ax, bx, cx, retval;
unsigned top,topsp;
unsigned currLine = 0;
unsigned int  command, oldPC;
vector < int > commandvector;

unsigned char executionFinished = 0;
unsigned int pc=0;

unsigned int totalStrings;
unsigned int totalNumbers;
unsigned int totalFuncs;
unsigned int totalCode;
unsigned int totalDoubles;
unsigned int totalLibfuncs;
unsigned int totalArgs;
unsigned int totalActuals;
extern unsigned int totalGlobals;  //#define GLOBALS totalGlobals
bool debug;
bool regdebug;

//===========Tools=============================/



int main(int argc, char ** argv){
	if(argv[2]){
		infile.open(argv[1], ios::in | ios::binary);
	}
	else{
		infile.open(argv[1]);
	}
	if(infile.fail()){
		cout << "INPUT FILE NOT FOUND" << endl;       
		return -1;
	}
	else{
		debug=true; 
		regdebug=true;
		outfile.open(argv[3]);
		initialize_TheMachine();
		if(argv[2]){
			parse_binary();
		}
		else{
			parse_abc();
		}

		vector <string>:: iterator it;
		int frak=0;
		for( it = _strings.begin(); it!=_strings.end(); it++){
			outfile << *it << " ITERATION: " << frak << endl;
		}

		if(regdebug)cout<<totalGlobals<<endl;

		top= AVM_STACKSIZE -1 -totalGlobals -1 ; //2 kena gia pseudes8isi top topsp
		if(regdebug)cout<<top<<endl;

		while(!(executionFinished)){
			if(regdebug)cout << "###################new instruction #############" <<pc << endl;
			execute_cycle();
			if(regdebug)cout << "FINISHED WITH PC: " <<pc << endl;
			//command++;
		}
		if(pc < totalCode){
			cout<<"Error : Runtime error in line :"<< _instructions[pc].aline <<endl;
		}
	if(regdebug)cout<<" final pc "<<pc<<endl;


	}

	vector <string>:: iterator it;
	int frak=0;
	for( it = _strings.begin(); it!=_strings.end(); it++){
		outfile << *it << " ITERATION: " << frak << endl;
	}
	infile.close();
    outfile.close();
	return 0;
}


void initialize_TheMachine(void){
	unsigned i=0;
	for(; i<4096; i++){
		( memset(&((stack[i])) , 0, sizeof((stack[i]))));stack[i].type = undef_vm;
		}
	ax = stack[AVM_STACKSIZE-1];
 	bx= cx = retval = ax;
 	
}


 
void findef(void){
	unsigned i=0;
	if(regdebug)cout<<" findefing"<<endl;
	for(; i<4096; i++){
		if(stack[i].type==string_vm) if(regdebug)cout<<i<<" me type"<<stack[i].type<<" content "<< strdup(stack[i].data.strVal) <<endl;
		else if(stack[i].type<7) if(regdebug)cout<<i<<" me type"<<stack[i].type<<endl;


	}
}