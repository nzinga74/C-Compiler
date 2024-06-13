#ifndef DELIMITER_H
#define DELIMINER_H
#include <iostream>
#include "../../tokens/token.h"
#include "../file_reader.h"
#include "../../tokens/token.h"
#include <algorithm>
#include <unordered_map>

class Delimiter
{
private:
    FileReader *reader;

public:
    Delimiter(FileReader *reader)
    {
        this->reader = reader;
    }
    Token *delimiterValidator()
    {
        char ch = reader->readNextCaracter();
        switch (ch)
        {
        case ';':
        {
            return new Token(TOKEN_SEMICOLON, ";", reader->getLine());
        }
        case '(':
        {
            return new Token(TOKEN_OPEN_PARENTHESE, "(", reader->getLine());
        }
        case ')':
        {
            return new Token(TOKEN_CLOSE_PARENTHESE, ")", reader->getLine());
        }
        case '[':
        {
            return new Token(TOKEN_OPEN_BRACKET, "[", reader->getLine());
        }
        case ']':
        {
            return new Token(TOKEN_CLOSE_BRACKET, "]", reader->getLine());
        }
        case '{':
        {
            return new Token(TOKEN_OPEN_BRACE, "{", reader->getLine());
        }
        case '}':
        {
            return new Token(TOKEN_CLOSE_BRACE, "}", reader->getLine());
        }
        }
        return NULL;
    }
};
#endif