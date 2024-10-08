#include "codegenerator.h"
#include <iostream>
using namespace std;

string codegenerator::getlabel() {
    return "label_" + to_string(Count++);
}
void codegenerator::generate(ast* n) {
 if (n == nullptr)
        return;       
 if (n->value == "program") {
        for (auto child : n->children) {
            generate(child);
   } }
    else if (n->value == "varDecl") {
        string namev = n->children[0]->value;
        if (table.find(namev) == table.end()) {
            table[namev] = 0; 
    }
    }
    else if (n->value == "assign") {
        string namev = n->children[0]->value;
        generate(n->children[1]); 
        cout << "STA " << namev << "\n";
    }
    else if (n->value == "if") {
       
        generate(n->children[0]); 
        string elselabel = getlabel();
        string iflabel = getlabel();
        cout << "JZ " << elselabel <<endl;
        generate(n->children[1]); 
        cout << "JMP " << iflabel <<endl;
        cout << elselabel << ":\n";
        cout << iflabel << ":\n";
    }
    else if (n->value == "+") {
      
        generate(n->children[0]);
        cout << "ADD " << n->children[1]->value << "\n";
    }
    else if (n->value == "-") {

        generate(n->children[0]); 
        cout << "SUB " << n->children[1]->value << "\n";
    }
    else if (n->value == "==") {
        cout << "CMP " << n->children[1]->value << "\n"; 
    }
    
    else if (n->value == "<=") {
        cout << "CMP " << n->children[1]->value << "\n"; 
    }
    else {
        cout << "LDA " << n->value << "\n";
    }
}
