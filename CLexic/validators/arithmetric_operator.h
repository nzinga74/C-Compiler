#ifndef ARITHMETRIC_OPERATOR_H
#define ARITHMETRIC_OPERATOR_H
#include <iostream>
#include "../../tokens/type_token.h"
#include "../file_reader.h"
#include "../../tokens/token.h"
#include <algorithm>

class ArithmetricOperator
{
private:
    FileReader *reader;

public:
    ArithmetricOperator(FileReader *reader)
    {
        this->reader = reader;
    }
    Token *arithmeticOperatorValidator()
    {
        char ch = reader->readNextCaracter();
        if (ch == '+')
        {
            ch = reader->readNextCaracter();
            switch (ch)
            {
            case '=':
                return new Token(TOKEN_OPR_PLUS_EGUAL, "+=", reader->getLine());
            case '+':
                return new Token(TOKEN_OPR_DOUBLE_PLUS, "++", reader->getLine());
            };
            reader->goBack();
            return new Token(TOKEN_OPR_PLUS, "+", reader->getLine());
        }
        else if (ch == '-')
        {
            ch = reader->readNextCaracter();
            switch (ch)
            {
            case '=':
                return new Token(TOKEN_OPR_SUBS_EGUAL, "-=", reader->getLine());
            case '-':
                return new Token(TOKEN_OPR_DOUBLE_SUBS, "--", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_OPR_SUBS, "-", reader->getLine());
        }
        else if (ch == '%')
        {
            ch = reader->readNextCaracter();
            if (ch == '=')
            {
                return new Token(TOKEN_MOD_EGUAL, "%=", reader->getLine());
            }

            reader->goBack();
            return new Token(TOKEN_MOD, "%", reader->getLine());
        }
        else if (ch == '*')
        {
            ch = reader->readNextCaracter();
            if (ch == '=')
            {
                return new Token(TOKEN_OPR_MUL_EGUAL, "*=", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_OPR_MULT, "*", reader->getLine());
        }
        else if (ch == '/')
        {
            ch = reader->readNextCaracter();
            if (ch == '=')
            {
                return new Token(TOKEN_OPR_DIV_EGUAL, "/=", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_OPR_DIV, "/", reader->getLine());
        }
        return NULL;
    }
};
#endif