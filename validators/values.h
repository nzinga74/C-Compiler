#ifndef VALUES_H
#define VALUES_H
#include <iostream>
#include "../tokens/token.h"
#include "../file_reader.h"
#include "../tokens/token.h"
#include "../utils.h"
#include <algorithm>
#include <unordered_map>

using namespace std;

class Values
{
private:
    FileReader *reader;

public:
    Values(FileReader *reader)
    {
        this->reader = reader;
    }
    Token *valueValidator()
    {
        char ch = reader->readNextCaracter();
        if (isdigit(ch))
        {
            while ((ch = reader->readNextCaracter()) && isdigit(ch))
                ;
            if (ch == '.')
            {
                int count = 0;
                while ((ch = reader->readNextCaracter()) && isdigit(ch))
                    count++;
                reader->goBack();
                if (count <= 7)
                {
                    return new Token(TOKEN_VALUE_FLOAT, reader->getLexema(), reader->getLine());
                }
                return new Token(TOKEN_VALUE_DOUBLE, reader->getLexema(), reader->getLine());
            }
            reader->goBack();
            return new Token(TOKEN_VALUE_INT, reader->getLexema(), reader->getLine());
        }
        else if (ch == '"')
        {
            // printf("%c", reader->readNextCaracter());

            while ((ch = reader->readNextCaracter()) != '"')
                ;

            return new Token(TOKEN_VALUE_STRING, reader->getLexema(), reader->getLine());
        }
        else if (ch == '<')
        {
            if ((ch = reader->readNextCaracter()) && isalpha(ch))
            {
                while ((ch = reader->readNextCaracter()) && (Utils::isValidHeaderCaracter(ch)))
                    ;
                string lexema = reader->getLexema();

                if (Utils::isHeader(lexema))
                {
                    return new Token(TOKEN_HEADER, lexema, reader->getLine());
                }
            }
        }
        return NULL;
    }
};

#endif