// lexer.cpp

#include "lexer.h"
#include <iostream>
using namespace std;

Lexer::Lexer(const string &source) : source(source), p(0) {}
token Lexer::getNextToken() {
    while (p < source.length()) {
        char c = source[p++];
        if (isspace(c)) continue;
        if (isalpha(c)) return identifier(c);
        if (isdigit(c)) return number(c);
        if (p < source.length()) {
            switch (c) {
                case '=':
                    if (source[p] == '=') {
                        p++;
                        return token{TOKEN_EQUAL, "=="};
                    }
                    return token{TOKEN_ASSIGN, "="};
                case '!':
                    if (source[p] == '=') {
                        p++;
                        return token{TOKEN_NOT_EQUAL, "!="};
                    }
                    break;
                case '<':
                    if (source[p] == '=') {
                        p++;
                        return token{TOKEN_LESS_EQUAL, "<="};
                    }
                    return token{TOKEN_LESS, "<"};
                case '>':
                    if (source[p] == '=') {
                        p++;
                        return token{TOKEN_GREATER_EQUAL, ">="};
                                            }
            return token{TOKEN_GREATER, ">"};
         }
        }
        switch (c) {
            case '+': return token{TOKEN_PLUS, "+"};
            case '-': return token{TOKEN_MINUS, "-"};
            case '{': return token{TOKEN_LBRACE, "{"};
            case '}': return token{TOKEN_RBRACE, "}"};
            case '(': return token{TOKEN_LPAREN, "("};  
            case ')': return token{TOKEN_RPAREN, ")"};  
            case ';': return token{TOKEN_SEMICOLON, ";"};
            default: return token{TOKEN_UNKNOWN,string(1, c)};
        }
    }
    return token{TOKEN_EOF, ""};
}
token Lexer::identifier(char c) {
    string text(1, c);
    while (p < source.length() && isalnum(source[p])) text += source[p++];
    if (text == "int") return token{TOKEN_INT, text};
    if (text == "if") return token{TOKEN_IF, text};
    if (text == "else") return token{TOKEN_ELSE, text}; 
        return token{TOKEN_IDENTIFIER, text};
}
token Lexer::number(char c) {
    string text(1, c);
    bool isfloat = false;
    while (p < source.length() && (isdigit(source[p]) || source[p] == '.')) {
        if (source[p] == '.') {
            if (isfloat) break; 
            isfloat = true;
        }
        text += source[p++];
    }
    return isfloat ? token{TOKEN_FLOAT, text} : token{TOKEN_NUMBER, text};
}