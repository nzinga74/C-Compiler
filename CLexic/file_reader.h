#ifndef FILE_READER_H
#define FILE_READER_H
#include <fstream>
#include <iostream>
using namespace std;
class FileReader

{
private:
    fstream file;
    const int BUFFER_LENGTH = 40;
    char buffer[80];
    int pointer;
    int currentBuffer;
    int initLexema;
    int line = 1;
    string lexema;

    void initializeBuffer()
    {
        pointer = 0;
        currentBuffer = 2;
        loadFirstBuffer();
        initLexema = 0;
    }
    void loadFirstBuffer()
    {
        if (currentBuffer == 2)
        {
            currentBuffer = 1;
            char ch;
            for (int i = 0; i < BUFFER_LENGTH; i++)
            {
                if (file.get(ch))
                {
                    buffer[i] = ch;
                }
                else
                {
                    buffer[i] = EOF;
                    break;
                }
            }
        }
    }
    void loadSecondBuffer()
    {
        if (currentBuffer == 1)
        {
            currentBuffer = 2;
            char ch;
            for (int i = BUFFER_LENGTH; i < BUFFER_LENGTH * 2; i++)
            {
                if (file.get(ch))
                {
                    buffer[i] = ch;
                }
                else
                {
                    buffer[i] = EOF;
                    break;
                }
            }
        }
    }

    char readCaracterBuffer()
    {
        char ch = buffer[pointer];
        increasePointer();
        return ch;
    }

public:
    FileReader(const string &filename) : file(filename)
    {
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo\n";
            exit(1);
        }
        else
        {

            initializeBuffer();
        }
    }

    char readNextCaracter()
    {
        char ch = readCaracterBuffer();
        lexema += ch;
        return ch;
    }

    bool eof()
    {
        return file.eof();
    }

    void goBack()
    {
        pointer--;
        if (pointer < 0)
        {
            pointer = BUFFER_LENGTH * 2 - 1;
        }
        lexema = lexema.substr(0, lexema.length() - 1);
    }

    void clear()
    {
        pointer = initLexema;
        lexema = "";
    }
    void confirm()
    {
        initLexema = pointer;
        lexema = "";
    }
    string getLexema()
    {
        return lexema;
    }
    void increaseLine()
    {
        this->line++;
    }
    int getLine()
    {
        return this->line;
    }
    void increasePointer()
    {
        pointer++;
        if (pointer == BUFFER_LENGTH)
        {
            loadSecondBuffer();
        }
        else if (pointer == BUFFER_LENGTH * 2)
        {
            loadFirstBuffer();
            pointer = 0;
        }
    }
};
#endif