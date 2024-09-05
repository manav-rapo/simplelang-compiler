#ifndef code_generator_h
#define code_generator_h

#include "parser.h"
#include <map>
#include <string>

class codegenerator {
public:
    void generate(ast* n);
private:
    map<string, int> table;
    int Count = 0;

    string getlabel();
};

#endif 
