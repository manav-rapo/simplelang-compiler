
// parser.cpp

#include "parser.h"
#include <iostream>
#include <stdexcept> // For runtime_error
using namespace std;

Parser::Parser(Lexer& lexer) : lexer(lexer) {
    currentToken = lexer.getNextToken();
}

void Parser::eat(TokenType type) {
    if (currentToken.type == type)
        currentToken = lexer.getNextToken();
    else
        throw runtime_error("Unexpected token type!");
}

ast* Parser::parse() {
    ast* root = new ast{"program", {}};
    while (currentToken.type != TOKEN_EOF) {
        ast* stmt = statement();
        if (stmt != nullptr)
            root->children.push_back(stmt);
        else
            break; 
    }
    return root;
}

ast* Parser::statement() {
    if (currentToken.type == TOKEN_INT) {
        eat(TOKEN_INT);
        return variableDeclaration();
    } else if (currentToken.type == TOKEN_IDENTIFIER) {
        return assignment();
    } else if (currentToken.type == TOKEN_IF) {
        return conditional();
    }
    return nullptr;
}

ast* Parser::variableDeclaration() {
    if (currentToken.type != TOKEN_IDENTIFIER) {
        cout << "Syntax error! Expected identifier after 'int'" << endl;
        return nullptr;
    }
    string varName = currentToken.text;
    eat(TOKEN_IDENTIFIER);
    eat(TOKEN_SEMICOLON);

    ast* node = new ast{"varDecl", {}};
    ast* varNode = new ast{varName, {}};
    node->children.push_back(varNode);
    return node;
}

ast* Parser::assignment() {
    string varName = currentToken.text;
    eat(TOKEN_IDENTIFIER);
    eat(TOKEN_ASSIGN);
    ast* exprNode = expression();
    eat(TOKEN_SEMICOLON);

    ast* node = new ast{"assign", {}};
    ast* varNode = new ast{varName, {}};
    node->children.push_back(varNode);
    node->children.push_back(exprNode);
    return node;
}

ast* Parser::conditional() {
    eat(TOKEN_IF);
    eat(TOKEN_LPAREN); // Adjusted to use parentheses for condition
    ast* exprNode = expression();
    eat(TOKEN_RPAREN); // Adjusted to use parentheses for condition
    eat(TOKEN_LBRACE);
    ast* stmtNode = statement();
    eat(TOKEN_RBRACE);

    ast* node = new ast{"if", {exprNode, stmtNode}};
    
    if (currentToken.type == TOKEN_ELSE) {
        eat(TOKEN_ELSE);
        eat(TOKEN_LBRACE);
        ast* elseStmtNode = statement();
        eat(TOKEN_RBRACE);
        node->children.push_back(elseStmtNode);
    }
    return node;
}

ast* Parser::expression() {
    ast* node = term();

    while (currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS || currentToken.type == TOKEN_EQUAL) {
        string op = currentToken.text;
        TokenType opType = currentToken.type;
        eat(currentToken.type);
        ast* right = term();
        ast* newNode = new ast{op, {}};
        newNode->children.push_back(node);
        newNode->children.push_back(right);
        node = newNode;
    }

    return node;
}

ast* Parser::term() {
    if (currentToken.type == TOKEN_NUMBER) {
        string num = currentToken.text;
        eat(TOKEN_NUMBER);
        return new ast{num, {}};
    } else if (currentToken.type == TOKEN_IDENTIFIER) {
        string var = currentToken.text;
        eat(TOKEN_IDENTIFIER);
        return new ast{var, {}};
    } else if (currentToken.type == TOKEN_LPAREN) {   // Added handling for parentheses
        eat(TOKEN_LPAREN);
        ast* node = expression();
        eat(TOKEN_RPAREN);
        return node;
    }
    return nullptr;
}