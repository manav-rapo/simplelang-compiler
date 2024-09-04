#ifndef code_generator_h
#define code_generator_h

#include "parser.h"
#include <map>
#include <string>

class Codegenerator {
public:
    void generate(ast* node);
private:
    map<string, int> symbolTable;
    int Count = 0;

    string getLabel();
};

#endif 
