#include "lexer.h"
#include "parser.h"
#include "code_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    string code;
    ifstream input("input.txt"); 
    if (!input) {
        cerr<<"file cannot be open"<<endl;
        return 1;
    }
    stringstream buffer;
    buffer << input.rdbuf(); 
    code = buffer.str(); 
    input.close(); 
    Lexer lexer(code);
    Parser parser(lexer);
    ast* root = parser.parse();
    codegenerator generat;
    generat.generate(root);
    delete root;
    return 0;
}
