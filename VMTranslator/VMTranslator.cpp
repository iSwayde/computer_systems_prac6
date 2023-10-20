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
        temp += "\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D";
    }
    //static
    else if (segment == "static"){
        temp += "\nD+M\n@16\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D";
    }
    //pointer
    else if (segment == "pointer"){
        temp += "\nD+M\n@3\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D";
    }
    //temp
    else if (segment == "temp"){
        temp += "\nD+M\n@5\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D";
    }
    //local
    else if (segment == "local"){
        temp += "\nD=A\n@LOCAL\nA=D+M\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D";
    }
    //argument
    else if (segment == "argument"){
        temp += "\nD=M\n@ARG\nA=D+M\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D";
    }
    //this
    else if (segment == "this"){
        temp += "\nD+M\n@THIS\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D";
    }
    //that
    else if (segment == "that"){
        temp += "\nD+M\n@THAT\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D";
    }    
    return temp;;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){    
    return "";
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M\n";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "@SP\nAM=M-1\nD=M\nM=-D\n";
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