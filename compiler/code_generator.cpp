#include "code_generator.h"
#include <iostream>
using namespace std;

string Codegenerator::getLabel() {
    return "label_" + to_string(Count++);
}

void Codegenerator::generate(ast* node) {
    if (node == nullptr)
        return;

    if (node->value == "program") {
        for (auto child : node->children) {
            generate(child);
        }
    }
    else if (node->value == "varDecl") {
        
        string varName = node->children[0]->value;
        if (symbolTable.find(varName) == symbolTable.end()) {
            symbolTable[varName] = 0; 
        }
    }
    else if (node->value == "assign") {
        
        string varName = node->children[0]->value;
        generate(node->children[1]); 
        cout << "STA " << varName << "\n";
    }
    else if (node->value == "if") {
       
        generate(node->children[0]); 
        string elseLabel = getLabel();
        string endIfLabel = getLabel();
        cout << "JZ " << elseLabel << "\n";
        generate(node->children[1]); 
        cout << "JMP " << endIfLabel << "\n";
        cout << elseLabel << ":\n";
        cout << endIfLabel << ":\n";
    }
    else if (node->value == "+") {
      
        generate(node->children[0]);
        cout << "ADD " << node->children[1]->value << "\n";
    }
    else if (node->value == "-") {

        generate(node->children[0]); 
        cout << "SUB " << node->children[1]->value << "\n";
    }
    else if (node->value == "==") {
        cout << "CMP " << node->children[1]->value << "\n"; 
    }
    else {
        cout << "LDA " << node->value << "\n";
    }
}
