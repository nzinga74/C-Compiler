#ifndef LEX_ANALISER_H
#define LEX_ANALISER_H

#include <iostream>
#include "./tokens/type_token.h"
#include "file_reader.h"
#include "./tokens/token.h"
#include <algorithm>
#include "./validators/bit_relacional_operator.h"
#include "./validators/special_operator.h"
#include "./validators/arithmetric_operator.h"
#include "./validators/delimiter.h"
#include "./validators/commentary.h"
#include "./validators/Identifier.h"
#include "./validators/values.h"
#include "./validators/directives.h"
#include "utils.h"
using namespace std;

class LexAnaliser

{
private:
    FileReader *reader;
    Token *RelacionalAndBitOperator()
    {
        char ch = reader->readNextCaracter();

        if (ch == '<')
        {
            ch = reader->readNextCaracter();
            switch (ch)
            {
            case '=':
                return new Token(TOKEN_LESS_IGUAL_THAN, "<=", reader->getLine());
            case '<':
                return new Token(TOKEN_LEFT_SHIFT, "<<", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_LESS_THAN, "<", reader->getLine());
        }
        else if (ch == '>')
        {
            ch = reader->readNextCaracter();
            switch (ch)
            {
            case '=':
                return new Token(TOKEN_GREAT_IGUAL_THAN, ">=", reader->getLine());
            case '>':
                return new Token(TOKEN_RIGHT_SHIFT, ">>", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_GREAT_THAN, ">", reader->getLine());
        }
        else if (ch == '=')
        {
            ch = reader->readNextCaracter();
            switch (ch)
            {
            case '=':
                return new Token(TOKEN_EGUAL, "==", reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_ATRIB, "=", reader->getLine());
        }
        return NULL;
    }
    Token *End()
    {
        char ch = reader->readNextCaracter();
        if (ch == EOF)
        {
            return new Token(TOKEN_END, "end", reader->getLine());
        }
        return NULL;
    }

    void ignoreEspace()
    {
        char ch = reader->readNextCaracter();
        if (Utils::isWhiteSpace(ch))
        {
            if (Utils::isEnter(ch))
            {
                reader->increaseLine();
            }
            while ((ch = reader->readNextCaracter()) && Utils::isWhiteSpace(ch))
            {
                if (Utils::isEnter(ch))
                {
                    reader->increaseLine();
                }
            }
            reader->goBack();
        }
        else
        {
            reader->goBack();
        }
    }

public:
    LexAnaliser()
    {
        reader = new FileReader("code.txt");
    }
    Token *nextToken()
    {
        BitAndRelacionalOperator *bitOperator = new BitAndRelacionalOperator(reader);
        SpecialOperator *specialOperator = new SpecialOperator(reader);
        ArithmetricOperator *arithmetricOperator = new ArithmetricOperator(reader);
        Delimiter *delimiter = new Delimiter(reader);
        Commentary *commentary = new Commentary(reader);
        Identifier *identifier = new Identifier(reader);
        Directives *directives = new Directives(reader);
        Values *values = new Values(reader);

        ignoreEspace();
        reader->confirm();
        Token *next = NULL;
        next = End();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        // DIRECTIVAS
        next = directives->directivesValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        // COMMENTARY
        next = commentary->commentaryValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        // VALUES
        next = values->valueValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        // SPECIAL OPERATOR
        next = specialOperator->specialOperatorValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        // IDENTIFIER
        next = identifier->identifierValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        // RELACIONAL OPERATOR
        next = RelacionalAndBitOperator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        next = arithmetricOperator->arithmeticOperatorValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        next = bitOperator->bitRelacionalOperatorValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }
        // DELIMITER
        next = delimiter->delimiterValidator();
        if (next == NULL)
        {
            reader->clear();
        }
        else
        {
            reader->confirm();
            return next;
        }

        // NOT FOUNDS
        char c = reader->readNextCaracter();
        reader->confirm();
        return new Token(TOKEN_NOT_FOUND, reader->getLexema(), reader->getLine());
    }
};
#endif