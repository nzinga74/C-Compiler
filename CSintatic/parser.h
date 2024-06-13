#ifndef PARSER_H
#define PARSER_H

#include "vector"
#include "../tokens/token.h"
#include "../tokens/type_token.h"
#include <algorithm>
#include "../CLexic/lex_analiser.h"
#include "./sintaticTools.h"
#include "../CLexic/utils.h"
using namespace std;

class Parser
{
private:
    vector<Token *> bufferToken;
    LexAnaliser *lexAnaliser;
    int TAMANHO_BUFFER = 10;
    bool theEnd;

    void readToken()
    {
        if (this->bufferToken.size() > 0)
        {

            this->bufferToken.erase(this->bufferToken.begin());
        }
        while (this->bufferToken.size() < this->TAMANHO_BUFFER && !this->theEnd)
        {

            Token *nextToken = this->lexAnaliser->nextToken();

            if (nextToken->name == TOKEN_END)
            {
                this->theEnd = true;
            }
            else
            {
                this->bufferToken.push_back(nextToken);
            }
        }
    }
    Token *lookAhead(int k)
    {
        if (bufferToken.empty())
        {
            exit(1);
            // return NULL;
        }
        if (k - 1 > bufferToken.size())
        {
            int lastIndex = bufferToken.size() - 1;
            return bufferToken[lastIndex];
        }
        return bufferToken[k - 1];
    }
    void match(TypeToken token)
    {
        if (lookAhead(1)->name == token)
        {
            cout << "Match: " << lookAhead(1)->lexama << endl;
            readToken();
        }
        else
        {
            sintaxeError(Utils::getToken(token));
        }
    }
    void sintaxeError(string str)
    {
        cout << "Esperava receber " + str + " na linha " << lookAhead(1)->line << " Mas encontrou " << lookAhead(1)->lexama << endl;
        recover();
    }
    void recover()
    {
        Token *item = lookAhead(1);

        while (item->name != TOKEN_END)
        {
            readToken();
            item = lookAhead(1);

            if (SintaticTools::isTypeDef(item->name))
            {
                decl();
                return;
            }
            else if (item->name == TOKEN_OPEN_BRACE)
            {
                com_stmt();
                return;
            }
            else if (SintaticTools::isKeyWord(item->name) || item->name == TOKEN_ID)
            {
                stmt();
                recover();
                return;
            }
            else
            {
                readToken(); // Move to the next token
            }
        }
    }

    void decl()
    {
        type_spec();
        match(TOKEN_ID);
        decl_1();
    }
    void type_spec()
    {

        if (SintaticTools::isTypeDef(lookAhead(1)->name))
        {
            match(lookAhead(1)->name);
        }
        else
        {
            sintaxeError("int, float, double, char");
        }
    }
    void decl_1()
    {
        if (SintaticTools::isVarDecl(lookAhead(1)->name))
        {
            var_decl();
            decl();
        }
        else if (SintaticTools::isFuncDecl(lookAhead(1)->name))
        {
            fun_decl();
            decl();
        }
        else
        {
            sintaxeError("; [ = , (");
        }
    }
    void var_decl()
    {
        if (lookAhead(1)->name == TOKEN_SEMICOLON)
        {
            match(TOKEN_SEMICOLON);
        }
        else if (lookAhead(1)->name == TOKEN_OPEN_BRACKET)
        {
            match(TOKEN_OPEN_BRACKET);
            match(TOKEN_VALUE_INT);
            match(TOKEN_CLOSE_BRACKET);
            match(TOKEN_SEMICOLON);
        }
        else if (lookAhead(1)->name == TOKEN_ATRIB)
        {
            match(TOKEN_ATRIB);
            exp();
            match(TOKEN_SEMICOLON);
        }
        else if (lookAhead(1)->name == TOKEN_COMMA)
        {
            match(TOKEN_COMMA);
            match(TOKEN_ID);
            var_decl();
        }
        else
        {
            sintaxeError("; [ = ,");
        }
    }
    void fun_decl()
    {
        match(TOKEN_OPEN_PARENTHESE);
        if (lookAhead(1)->name != TOKEN_CLOSE_PARENTHESE)
        {
            params();
        }
        match(TOKEN_CLOSE_PARENTHESE);
        fun_decl_1();
    }
    void params()
    {
        if (lookAhead(1)->name == TOKEN_VOID)
        {
            match(TOKEN_VOID);
        }
        else if (SintaticTools::isTypeDef(lookAhead(1)->name))
        {
            param();
        }
        else
        {
            sintaxeError("void, int, double ... ");
        }
    }
    void param()
    {
        type_spec();
        match(TOKEN_ID);
        param_1();
    }
    void param_1()
    {
        if (lookAhead(1)->name == TOKEN_OPEN_BRACKET)
        {
            match(TOKEN_OPEN_BRACKET);
            match(TOKEN_CLOSE_BRACKET);
            param_2();
        }
        else if (lookAhead(1)->name == TOKEN_COMMA)
        {
            match(TOKEN_COMMA);
            type_spec();
            match(TOKEN_ID);
            param_1();
        }
        else if (!SintaticTools::isEmptyParams(lookAhead(1)->name))
        {
            sintaxeError("[ ,");
        }
    }
    void param_2()
    {
        if (lookAhead(1)->name == TOKEN_COMMA)
        {
            match(TOKEN_COMMA);
            type_spec();
            match(TOKEN_ID);
            param_1();
        }
    }
    void fun_decl_1()
    {
        if (lookAhead(1)->name == TOKEN_SEMICOLON)
        {
            match(TOKEN_SEMICOLON);
        }
        else if (SintaticTools::isComStmt(lookAhead(1)->name))
        {
            com_stmt();
        }
        else
        {
            sintaxeError("; {");
        }
    }

    void stmt()
    {
        if (SintaticTools::isExpStmt(lookAhead(1)->name) || lookAhead(1)->name == TOKEN_SEMICOLON)
        {
            exp_stmt();
        }
        else if (SintaticTools::isComStmt(lookAhead(1)->name))
        {
            com_stmt();
        }
        else if (SintaticTools::isIfStmt(lookAhead(1)->name))
        {
            if_stmt();
        }
        else if (SintaticTools::isWhileStmt(lookAhead(1)->name))
        {
            while_stmt();
        }
        else if (SintaticTools::isReturnStmt(lookAhead(1)->name))
        {
            return_stmt();
        }
        else if (SintaticTools::isBreakStml(lookAhead(1)->name))
        {
            break_stmt();
        }
        else if (SintaticTools::isForStml(lookAhead(1)->name))
        {
            for_stmt();
        }
        else if (lookAhead(1)->name == TOKEN_PRINTF)
        {
            printf_stmt();
        }
        //     else if (??)
        //     {
        //         scanf_stmt();
        //     }
        else if (SintaticTools::isDoStml(lookAhead(1)->name))
        {
            do_stmt();
        }
        else
        {
            sintaxeError("while, do, for, return, break,if");
        }
    }
    void exp_stmt()
    {
        if (lookAhead(1)->name == TOKEN_SEMICOLON)
        {
            match(TOKEN_SEMICOLON);
        }
        else if (SintaticTools::isExpStmt(lookAhead(1)->name))
        {
            exp();
            match(TOKEN_SEMICOLON);
        }
        else
        {
            sintaxeError(";");
        }
    }
    void com_stmt()
    {
        match(TOKEN_OPEN_BRACE);
        content();
        match(TOKEN_CLOSE_BRACE);
    }
    void if_stmt()
    {
        match(TOKEN_IF);
        match(TOKEN_OPEN_PARENTHESE);
        exp();
        match(TOKEN_CLOSE_PARENTHESE);
        stmt();
        if_stmt_1();
    }
    void if_stmt_1()
    {
        if (lookAhead(1)->name == TOKEN_ELSE)
        {
            match(TOKEN_ELSE);
            stmt();
        }
    }
    void while_stmt()
    {
        match(TOKEN_WHILE);
        match(TOKEN_OPEN_PARENTHESE);
        exp();
        match(TOKEN_CLOSE_PARENTHESE);
        stmt();
    }
    void return_stmt()
    {
        match(TOKEN_RETURN);
        return_stmt_1();
    }

    void break_stmt()
    {
        match(TOKEN_BREAK);
        match(TOKEN_SEMICOLON);
    }
    void for_stmt()
    {
        match(TOKEN_FOR);
        match(TOKEN_OPEN_PARENTHESE);
        for_stmt_1();
        match(TOKEN_SEMICOLON);
        exp();
        match(TOKEN_SEMICOLON);
        exp();
        match(TOKEN_CLOSE_PARENTHESE);
        stmt();
    }
    void for_stmt_1()
    {
        if (SintaticTools::isTypeDef(lookAhead(1)->name))
        {
            match(lookAhead(1)->name);
            match(TOKEN_ID);
            match(TOKEN_ATRIB);
            exp();
        }
        else if (SintaticTools::isExpStmt(lookAhead(1)->name))
        {
            exp();
        }
        else
        {
            sintaxeError("int, float, double, id, + , -, !, number");
        }
    };
    void printf_stmt()
    {
        match(TOKEN_PRINTF);
        match(TOKEN_OPEN_PARENTHESE);
        match(TOKEN_VALUE_STRING);
        arg_list_1();
        match(TOKEN_CLOSE_PARENTHESE);
    }
    void scanf_stmt() {}
    void do_stmt()
    {
        match(TOKEN_DO);
        com_stmt();
        match(TOKEN_WHILE);
        match(TOKEN_OPEN_PARENTHESE);
        exp();
        match(TOKEN_CLOSE_PARENTHESE);
        match(TOKEN_SEMICOLON);
    }
    void return_stmt_1()
    {
        if (lookAhead(1)->name == TOKEN_SEMICOLON)
        {
            match(TOKEN_SEMICOLON);
        }
        else if (SintaticTools::isExpStmt(lookAhead(1)->name))
        {
            exp();
            match(TOKEN_SEMICOLON);
        }
        else
        {
            sintaxeError("; id + - ! number ...");
        }
    }
    void content()
    {
        if (SintaticTools::isTypeDef(lookAhead(1)->name))
        {
            local_decls();
            content();
        }
        else if (SintaticTools::isStmt(lookAhead(1)->name))
        {
            stmt();
            content();
        }
    }
    void local_decls()
    {
        if (SintaticTools::isTypeDef(lookAhead(1)->name))
        {
            type_spec();
            match(TOKEN_ID);
            local_decl_1();
        }
    }
    void local_decl_1()
    {
        if (lookAhead(1)->name == TOKEN_SEMICOLON)
        {
            match(TOKEN_SEMICOLON);
            local_decls();
        }
        else if (lookAhead(1)->name == TOKEN_OPEN_BRACKET)
        {
            match(TOKEN_OPEN_BRACKET);
            match(TOKEN_CLOSE_BRACKET);
            match(TOKEN_SEMICOLON);
            local_decls();
        }
        else if (lookAhead(1)->name == TOKEN_ATRIB)
        {
            match(TOKEN_ATRIB);
            exp();
            match(TOKEN_SEMICOLON);
        }
        else if (lookAhead(1)->name == TOKEN_COMMA)
        {
            match(TOKEN_COMMA);
            match(TOKEN_ID);
            local_decl_2();
        }
        else
        {
            sintaxeError("; [ = ,");
        }
    }
    void local_decl_2()
    {
        if (lookAhead(1)->name == TOKEN_SEMICOLON)
        {
            match(TOKEN_SEMICOLON);
        }
        else if (lookAhead(1)->name == TOKEN_COMMA)
        {
            match(TOKEN_COMMA);
            match(TOKEN_SEMICOLON);
            local_decl_1();
        }
        else
        {
            sintaxeError("; ,");
        }
    }
    void exp()
    {
        if (lookAhead(1)->name == TOKEN_ID)
        {
            match(TOKEN_ID);
            exp1();
            exp3();
        }
        else if (lookAhead(1)->name == TOKEN_OPR_PLUS)
        {
            match(TOKEN_OPR_PLUS);
            exp();
            exp3();
        }
        else if (lookAhead(1)->name == TOKEN_OPR_SUBS)
        {
            match(TOKEN_OPR_SUBS);
            exp();
            exp3();
        }
        else if (lookAhead(1)->name == TOKEN_NOT)
        {
            match(TOKEN_NOT);
            exp();
            exp3();
        }
        else if (lookAhead(1)->name == TOKEN_VALUE_FLOAT)
        {
            match(TOKEN_VALUE_FLOAT);
            exp3();
        }
        else if (lookAhead(1)->name == TOKEN_VALUE_INT)
        {
            match(TOKEN_VALUE_INT);
            exp3();
        }
        // else if(lookAhead(1)->name == TOKEN_VALUE_CHAR)
        // {
        // }
        else
        {
            sintaxeError("ID, +, -, !, number...");
        }
    }
    void exp1()
    {
        if (lookAhead(1)->name == TOKEN_OPEN_BRACKET)
        {
            match(TOKEN_OPEN_BRACKET);
            exp();
            match(TOKEN_CLOSE_BRACKET);
            exp2();
        }
        else if (lookAhead(1)->name == TOKEN_POINT)
        {
            match(TOKEN_POINT);
            match(TOKEN_SIZEOF);
        }
        else if (lookAhead(1)->name == TOKEN_OPEN_PARENTHESE)
        {
            match(TOKEN_OPEN_PARENTHESE);
            args();
            match(TOKEN_CLOSE_PARENTHESE);
        }
        else if (lookAhead(1)->name == TOKEN_OPR_DOUBLE_PLUS)
        {
            match(TOKEN_OPR_DOUBLE_PLUS);
        }
        else if (lookAhead(1)->name == TOKEN_OPR_DOUBLE_SUBS)
        {
            match(TOKEN_OPR_DOUBLE_SUBS);
        }
    }
    void exp2()
    {
        if (lookAhead(1)->name == TOKEN_ATRIB)
        {
            match(TOKEN_ATRIB);
            exp();
        }
    }
    void exp3()
    {
        if (SintaticTools::isExp3(lookAhead(1)->name))
        {
            match(lookAhead(1)->name);
            exp();
            exp3();
        }
    }
    void arg_list_1()
    {
        if (lookAhead(1)->name == TOKEN_COMMA)
        {
            exp();
            match(TOKEN_COMMA);
            arg_list_1();
        }
    }
    void args()
    {
        if (SintaticTools::isExpStmt(lookAhead(1)->name))
        {
            exp();
            arg_list_1();
        }
    }

public:
    Parser(LexAnaliser *lexAnaliser)
    {
        this->theEnd = false;
        this->lexAnaliser = lexAnaliser;
    }

    void program()
    {
        this->readToken();
        this->decl();

        // this->readToken();
        // lookAhead(1)->name;
        // cout << this->lookAhead(1)->lexama;
    }
};

#endif
