#ifndef code_generator_h
#define code_generator_h

#include "parser.h"
#include <map>
#include <string>

class CodeGenerator {
public:
    void generate(ast* node);
private:
    map<string, int> symbolTable;
    int labelCount = 0;

    string getNewLabel();
};

#endif 
