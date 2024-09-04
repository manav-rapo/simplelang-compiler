
// parser.h

#ifndef parser_h
#define parser_h

#include "lexer.h"
#include <vector>
#include <string>
using namespace std;

struct ast {
    string value;
    vector<ast*> children;
    
    ~ast() {
        for (ast* child : children) {
            delete child;
        }
    }
};

class Parser {
public:
    Parser(Lexer& lexer);
    ast* parse();

private:
    Lexer& lexer;
    Token currentToken;

    void eat(TokenType type);
    ast* statement();
    ast* variableDeclaration();
    ast* assignment();
    ast* conditional();
    ast* expression();
    ast* term();
};

#endif 