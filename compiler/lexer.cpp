// lexer.cpp

#include "lexer.h"
#include <iostream>

Lexer::Lexer(const std::string &source) : source(source), pos(0) {}

Token Lexer::getNextToken() {
    while (pos < source.length()) {
        char c = source[pos++];
        if (isspace(c)) continue;
        if (isalpha(c)) return identifier(c);
        if (isdigit(c)) return number(c);

        // Boundary check for two-character operators
        if (pos < source.length()) {
            switch (c) {
                case '=':
                    if (source[pos] == '=') {
                        pos++;
                        return Token{TOKEN_EQUAL, "=="};
                    }
                    return Token{TOKEN_ASSIGN, "="};
                case '!':
                    if (source[pos] == '=') {
                        pos++;
                        return Token{TOKEN_NOT_EQUAL, "!="};
                    }
                    break;
                case '<':
                    if (source[pos] == '=') {
                        pos++;
                        return Token{TOKEN_LESS_EQUAL, "<="};
                    }
                    return Token{TOKEN_LESS, "<"};
                case '>':
                    if (source[pos] == '=') {
                        pos++;
                        return Token{TOKEN_GREATER_EQUAL, ">="};
                    }
                    return Token{TOKEN_GREATER, ">"};
            }
        }

        // Single-character tokens
        switch (c) {
            case '+': return Token{TOKEN_PLUS, "+"};
            case '-': return Token{TOKEN_MINUS, "-"};
            case '{': return Token{TOKEN_LBRACE, "{"};
            case '}': return Token{TOKEN_RBRACE, "}"};
            case '(': return Token{TOKEN_LPAREN, "("};  // Added
            case ')': return Token{TOKEN_RPAREN, ")"};  // Added
            case ';': return Token{TOKEN_SEMICOLON, ";"};
            default: return Token{TOKEN_UNKNOWN, std::string(1, c)};
        }
    }
    return Token{TOKEN_EOF, ""};
}

Token Lexer::identifier(char c) {
    std::string text(1, c);
    while (pos < source.length() && isalnum(source[pos])) text += source[pos++];
    if (text == "int") return Token{TOKEN_INT, text};
    if (text == "if") return Token{TOKEN_IF, text};
    if (text == "else") return Token{TOKEN_ELSE, text}; // Added handling for "else"
    return Token{TOKEN_IDENTIFIER, text};
}

Token Lexer::number(char c) {
    std::string text(1, c);
    bool isFloatingPoint = false;
    while (pos < source.length() && (isdigit(source[pos]) || source[pos] == '.')) {
        if (source[pos] == '.') {
            if (isFloatingPoint) break; // Second '.' encountered, stop parsing
            isFloatingPoint = true;
        }
        text += source[pos++];
    }
    return isFloatingPoint ? Token{TOKEN_FLOAT, text} : Token{TOKEN_NUMBER, text};
}