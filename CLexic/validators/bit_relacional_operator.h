#ifndef BIT_RELACIONAL_OPERATOR_H
#define BIT_RELACIONAL_OPERATOR_H

#include <iostream>
#include "../../tokens/type_token.h"
#include "../file_reader.h"
#include "../../tokens/token.h"
#include <algorithm>

class BitAndRelacionalOperator
{
private:
    FileReader *reader;

public:
    BitAndRelacionalOperator(FileReader *reader)
    {
        this->reader = reader;
    }
    Token *bitRelacionalOperatorValidator()
    {
        char ch = reader->readNextCaracter();
        switch (ch)
        {
        case '~':
            return new Token(TOKEN_BIT_NOT, "~", reader->getLine());

        case '|':
        {
            ch = reader->readNextCaracter();
            if (ch == '|')
            {
                return new Token(TOKEN_OR, "||", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_BIT_OR, "|", reader->getLine());
        }

        case '^':
            return new Token(TOKEN_BIT_XOR, "^", reader->getLine());
        case '&':
        {
            ch = reader->readNextCaracter();
            if (ch == '&')
            {
                return new Token(TOKEN_AND, "&&", reader->getLine());
            }
            reader->goBack();

            return new Token(TOKEN_BIT_AND, "&", reader->getLine());
        }
        case '!':
        {
            ch = reader->readNextCaracter();
            if (ch == '=')
            {
                return new Token(TOKEN_DIFFERENT, "!=", reader->getLine());
            }
            reader->goBack();

            return new Token(TOKEN_NOT, "!", reader->getLine());
        }
        }

        return NULL;
    }
};
#endif