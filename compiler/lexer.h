// lexer.h

#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <cctype>
using namespace std;

enum TokenType {
    TOKEN_INT, TOKEN_IF,TOKEN_ELSE,TOKEN_IDENTIFIER,TOKEN_NUMBER,TOKEN_FLOAT,TOKEN_PLUS,TOKEN_MINUS,TOKEN_ASSIGN,  TOKEN_EQUAL,TOKEN_NOT_EQUAL, TOKEN_LESS,  TOKEN_LESS_EQUAL,TOKEN_GREATER,TOKEN_GREATER_EQUAL,TOKEN_LBRACE, TOKEN_RBRACE,TOKEN_LPAREN,TOKEN_RPAREN,TOKEN_SEMICOLON,TOKEN_EOF,TOKEN_UNKNOWN
};
struct token {
    TokenType type;
    string text;
};
class Lexer {
public:
    Lexer(const string &source);
    token gettoken();
private:
    string source;
    size_t p;
    token identifier(char c);
    token number(char c);
};

#endif 
