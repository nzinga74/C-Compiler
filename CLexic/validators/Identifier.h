#ifndef IDENTIFIER_H
#define IDENTIFIER_H
#include <iostream>
#include "../../tokens/type_token.h"
#include "../file_reader.h"
#include "../../tokens/token.h"
#include <algorithm>
#include <cctype>
class Identifier
{
private:
    FileReader *reader;
    bool _isLetter(char ch)
    {
        if ((isalpha(ch) || ch == '_'))
            return true;
        return false;
    }
    bool isNumber(char ch)
    {
        if (ch >= '0' && ch <= '9')
            return true;
        return false;
    }
    TypeToken reservedWord(string key)
    {
        unordered_map<string, TypeToken> reservedWordList = {
            {"if", TOKEN_IF},
            {"while", TOKEN_WHILE},
            {"do", TOKEN_DO},
            {"else", TOKEN_ELSE},
            {"switch", TOKEN_SWITCH},
            {"case", TOKEN_CASE},
            {"break", TOKEN_BREAK},
            {"for", TOKEN_FOR},
            {"continue", TOKEN_CONTINUE},
            {"finally", TOKEN_FINALLY},
            {"auto", TOKEN_AUTO},
            {"const", TOKEN_CONST},
            {"enum", TOKEN_ENUM},
            {"extern", TOKEN_EXTERN},
            {"goto", TOKEN_GOTO},
            {"register", TOKEN_REGISTER},
            {"static", TOKEN_STATIC},
            {"sizeof", TOKEN_SIZEOF},
            {"typedef", TOKEN_TYPEDEF},
            {"union", TOKEN_UNION},
            {"volatile", TOKEN_VOLALILE},
            {"struct", TOKEN_STRUCT},
            {"int", TOKEN_INT},
            {"float", TOKEN_FLOAT},
            {"char", TOKEN_CHAR},
            {"double", TOKEN_DOUBLE},
            {"long", TOKEN_LONG},
            {"short", TOKEN_SHORT},
            {"signed", TOKEN_SIGNED},
            {"unsigned", TOKEN_UNSIGNED},
            {"void", TOKEN_VOID},
            {"return", TOKEN_RETURN},
            {"printf", TOKEN_PRINTF},
        };
        int count = reservedWordList.count(key);

        if (count > 0)
        {
            return reservedWordList[key];
        }
        else
        {
            return TOKEN_ID;
        }
    }

public:
    Identifier(FileReader *reader)
    {
        this->reader = reader;
    }
    Token *identifierValidator()
    {
        char ch = reader->readNextCaracter();
        if (_isLetter(ch))
        {

            while ((ch = reader->readNextCaracter()) && ((_isLetter(ch) || isdigit(ch))))
                ;

            reader->goBack();
            string lexema = reader->getLexema();
            TypeToken token = reservedWord(lexema);
            return new Token(token, lexema, reader->getLine());
        }
        return NULL;
    }
};

#endif