#include "parser.h"
#include <iostream>
#include <stdexcept> 
using namespace std;
Parser::Parser(Lexer& lexer) : lexer(lexer) {
    ctoken = lexer.gettoken();
}
void Parser::eat(TokenType type) {
    if (ctoken.type == type)
        ctoken = lexer.gettoken();
    else
        throw runtime_error("Unexpected token");
}
ast* Parser::parse() {
    ast* root = new ast{"program", {}};
    while (ctoken.type != TOKEN_EOF) {
        ast* stmt = statement();
        if (stmt != nullptr)
            root->children.push_back(stmt);
        else
            break; 
    }
    return root;
}
ast* Parser::statement() {
    if (ctoken.type == TOKEN_INT) {
        eat(TOKEN_INT);
        return variableDeclaration();
    } else if (ctoken.type == TOKEN_IDENTIFIER) {
        return assignment();
    } else if (ctoken.type == TOKEN_IF) {
        return conditional();
    }
    return nullptr;
}
ast* Parser::variableDeclaration() {
    if (ctoken.type != TOKEN_IDENTIFIER) {
        cout << "Syntax error" << endl;
        return nullptr;
    }
    string namev = ctoken.text;
    eat(TOKEN_IDENTIFIER);
    eat(TOKEN_SEMICOLON);

    ast* n = new ast{"varDecl", {}};
    ast* nv = new ast{namev, {}};
    n->children.push_back(nv);
    return n;
}
ast* Parser::assignment() {
    string namev = ctoken.text;
    eat(TOKEN_IDENTIFIER);
    eat(TOKEN_ASSIGN);
    ast* exprNode = expression();
    eat(TOKEN_SEMICOLON);

    ast* n = new ast{"assign", {}};
    ast* nv = new ast{namev, {}};
    n->children.push_back(nv);
    n->children.push_back(exprNode);
    return n;
}
ast* Parser::conditional() {
    eat(TOKEN_IF);
    eat(TOKEN_LPAREN); 
    ast* exprNode = expression();
    eat(TOKEN_RPAREN); 
    eat(TOKEN_LBRACE);
    ast* stmtNode = statement();
    eat(TOKEN_RBRACE);

    ast* n = new ast{"if", {exprNode, stmtNode}};
    
    if (ctoken.type == TOKEN_ELSE) {
        eat(TOKEN_ELSE);
        eat(TOKEN_LBRACE);
        ast* elseStmtNode = statement();
        eat(TOKEN_RBRACE);
        n->children.push_back(elseStmtNode);
    }
    return n;
}
ast* Parser::expression() {
    ast* n = term();

    while (ctoken.type == TOKEN_PLUS || ctoken.type == TOKEN_MINUS || ctoken.type == TOKEN_EQUAL|| ctoken.type == TOKEN_LESS_EQUAL) {
        string op = ctoken.text;
        TokenType optype = ctoken.type;
        eat(ctoken.type);
        ast* r = term();
        ast* n1 = new ast{op, {}};
        n1->children.push_back(n);
        n1->children.push_back(r);
        n = n1;
    }
    return n;
}
ast* Parser::term() {
    if (ctoken.type == TOKEN_NUMBER) {
        string num = ctoken.text;
        eat(TOKEN_NUMBER);
        return new ast{num, {}};
    } else if (ctoken.type == TOKEN_IDENTIFIER) {
        string var = ctoken.text;
        eat(TOKEN_IDENTIFIER);
        return new ast{var, {}};
    } else if (ctoken.type == TOKEN_LPAREN) { 
        eat(TOKEN_LPAREN);
        ast* n = expression();
        eat(TOKEN_RPAREN);
        return n;
    }
    return nullptr;
}