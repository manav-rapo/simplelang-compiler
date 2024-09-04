// lexer.h

#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <cctype>

enum TokenType {
    TOKEN_INT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_FLOAT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASSIGN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_UNKNOWN
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
public:
    Lexer(const std::string &source);
    Token getNextToken();

private:
    std::string source;
    size_t pos;

    Token identifier(char c);
    Token number(char c);
};

#endif // LEXER_H
