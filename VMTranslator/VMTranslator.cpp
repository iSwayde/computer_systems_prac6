#include <string>
#include <iostream>
#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    string temp = "@";
    temp += to_string(offset);
    //constant
    if (segment == "constant"){
        temp += "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }
    //static
    else if (segment == "static"){
        temp += "\nD=A\n@16\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }
    //pointer
    else if (segment == "pointer"){
        temp += "\nD=A\n@3\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }
    //temp
    else if (segment == "temp"){
        temp += "\nD=A\n@5\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }
    //local
    else if (segment == "local"){
        temp += "\nD=A\n@LCL\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }
    //argument
    else if (segment == "argument"){
        temp += "\nD=A\n@ARG\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }
    //this
    else if (segment == "this"){
        temp += "\nD=A\n@THIS\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }
    //that
    else if (segment == "that"){
        temp += "\nD=A\n@THAT\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1";
    }    
    return temp;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){  
    string temp = "";

    //static (working)
    if (segment == "static"){
        temp += "@SP\nAM=M-1\nD=M\n@16\n";
        for (int i=0; i<offset; i++)
            temp += "A=A+1\n";
                
        temp += "M=D";
    }
    //pointer (working)
    else if (segment == "pointer"){
        temp += "@SP\nAM=M-1\nD=M\n@";
        if (offset == 0)
            temp += "3\n";
        else if (offset == 1)
            temp += "4\n";
                
        temp += "M=D";
    }
    //temp (working)
    else if (segment == "temp"){
        temp += "@SP\nAM=M-1\nD=M\n@5\n";
        for (int i=0; i<offset; i++)
            temp += "A=A+1\n";

        temp += "M=D";
    }
    //local
    else if (segment == "local"){
        //find local 2 and save it to R13
        temp += "@LCL\nD=M\n@";
        temp += to_string(offset);
        //save to r13 and pop into D
        temp += "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n";
        //save D into local 2 which is r13
        temp += "@R13\nA=M\nM=D\n";
    }
    //argument
    else if (segment == "argument"){
    //find argument offset and save it to R13
        temp += "@ARG\nD=M\n@";
        temp += to_string(offset);
        //save to r13 and pop into D
        temp += "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n";
        //save D into argument offset which is r13
        temp += "@R13\nA=M\nM=D\n";
    }
    //this
    else if (segment == "this"){
        temp += "@THIS\nD=M\n@";
        temp += to_string(offset);
        temp += "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n";
        temp += "@R13\nA=M\nM=D\n";
    }
    //that
    else if (segment == "that"){
        temp += "@THAT\nD=M\n@";
        temp += to_string(offset);
        temp += "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n";
        temp += "@R13\nA=M\nM=D\n"; 
    }
    return temp;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "@SP\nAM=M-1\nM=-M\n@SP\nM=M+1";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    string temp = "";
    //subtract two values on the stack and jump to end and leave -1 on the stack
    temp += "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\nM=-1\n@EQUAL\nD;JEQ\n";
    //if not equal leave 0 on the stack
    temp += "@SP\nA=M-1\nM=0\n(EQUAL)";
    return temp;
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    string temp = "";
    //sub value on top of stack from the value below it, put -1 on the stack and jump to end if result is > 0
    temp += "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\nM=-1\n@GREATER\nD;JGT\n";
    //if not > 0, leave 0 on the stack
    temp += "@SP\nA=M-1\nM=0\n(GREATER)\n";
    return temp;
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    string temp = "";
    //same as vm_gt but jump if less than 0
    temp += "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\nM=-1\n@LESS\nD;JLT\n";
    temp += "@SP\nAM=M-1\nM=0\n(LESS)\n";

    return temp;
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    string temp = "";
    temp += "@SP\nAM=M-1\nD=M\nA=A-1\nD=D&M\nM=-1\n@AND\nD;JGT\n";
    temp += "@SP\nAM=M-1\nM=0\n(AND)";
    return temp;
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    string temp = "";
    temp += "@SP\nAM=M-1\nD=M\nA=A-1\nD=D|M\nM=-1\n@OR\nD;JGT\n";
    temp += "@SP\nAM=M-1\nM=0\n(OR)";
    return temp;
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    string temp = "";
    temp += "@SP\nAM=M-1\nM=!M\n";
    return temp;
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}