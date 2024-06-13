#ifndef COMMENTARY_H
#define COMMENTARY_H
#include <iostream>
#include "../../tokens/type_token.h"
#include "../file_reader.h"
#include "../../tokens/token.h"
#include <algorithm>

class Commentary
{
private:
    FileReader *reader;

public:
    Commentary(FileReader *reader)
    {
        this->reader = reader;
    }
    Token *commentaryValidator()
    {
        char ch = reader->readNextCaracter();
        switch (ch)
        {
        case '/':
        {
            ch = reader->readNextCaracter();
            if (ch == '/')
            {
                while ((ch = reader->readNextCaracter()) != '\n')
                    ;
                reader->increaseLine();
                return new Token(TOKEN_SIMPLE_COMMENT, reader->getLexema(), reader->getLine() - 1);
            }
            else if (ch == '*')
            {
                bool isAsteristik = false;
                while (!((ch = reader->readNextCaracter()) == '/' && isAsteristik == true))
                {
                    isAsteristik = (ch == '*' ? true : false);
                }
                return new Token(TOKEN_MULTLINE_COMMENT, reader->getLexema(), reader->getLine());
            }
        }
        }
        return NULL;
    }
};

#endif