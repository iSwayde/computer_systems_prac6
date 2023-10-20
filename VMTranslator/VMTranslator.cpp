#include <string>

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
    //constant
    if (segment == "constant"){
        temp += "@SP\nAM=M-1\nD=M\n@";
        temp += to_string(offset);
        temp += "M=D";
    }
    //static
    if (segment == "static"){
        temp += "@SP\nAM=M-1\nD=M\n@16\n";
        for (int i=0; i<offset; i++)
            temp += "A=A+1\n";
                
        temp += "M=D";
    }
    //pointer
    if (segment == "pointer"){
        temp += "@SP\nAM=M-1\nD=M\n@";
        if (offset == 0)
            temp += "3\n";
        else if (offset == 1)
            temp += "4\n";
                
        temp += "M=D";
    }
    //temp
    if (segment == "temp"){
        temp += "@SP\nAM=M-1\nD=M\n@5\n";
        for (int i=0; i<offset; i++)
            temp += "A=A+1\n";

        temp += "M=D";
    }
    //local
    if (segment == "local"){
        temp += "@SP\nAM=M-1\nD=M\n@LCL\n";
        for (int i=0; i<offset; i++)
            temp += "A=A+1\n";
        
        temp += "M=D";
    }
    //argument
    if (segment == "argument"){
        temp += "@SP\nAM=M-1\nD=M\n@ARG\nM=D";
    }
    //this
    if (segment == "this"){
        temp += "@SP\nAM=M-1\nD=A\n@THIS\nM=D";
    }
    //that
if (segment == "that"){
        temp += "@SP\nAM=M-1\nD=A\n@THAT\nM=D";
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
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
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