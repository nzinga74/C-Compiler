#ifndef SPECIAL_OPERATOR_H
#define SPECIAL_OPERATOR_H
#include <iostream>
#include "../tokens/type_token.h"
#include "../file_reader.h"
#include "../tokens/token.h"
#include <algorithm>
class SpecialOperator
{
private:
    FileReader *reader;

public:
    SpecialOperator(FileReader *reader)
    {
        this->reader = reader;
    }
    Token *specialOperatorValidator()
    {
        char ch = reader->readNextCaracter();
        switch (ch)
        {
        case '?':
        {
            return new Token(TOKEN_QUESTION, "?", reader->getLine());
        }
        case ',':
        {
            return new Token(TOKEN_COMMA, ",", reader->getLine());
        }
        case '.':
        {
            return new Token(TOKEN_POINT, ".", reader->getLine());
        }
        case ':':
        {
            ch = reader->readNextCaracter();
            if (ch == ':')
            {
                return new Token(TOKEN_SCOPE, "::", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_TWO_POINT, ":", reader->getLine());
        }
        case '-':
        {
            ch = reader->readNextCaracter();
            if (ch == '>')
            {
                return new Token(TOKEN_ARROW, "->", reader->getLine());
            }
        }
        }
        return NULL;
    }
};

#endif