#include "lexer.h"
#include "parser.h"
#include "code_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    string code;
    ifstream inputFile("input.txt"); 

    if (!inputFile) {
        cerr << "Error: Could not open the input file." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf(); 
    code = buffer.str(); 

    inputFile.close(); 

    Lexer lexer(code);
    Parser parser(lexer);
    ast* root = parser.parse();

    CodeGenerator generator;
    generator.generate(root);

    delete root;

    return 0;
}
