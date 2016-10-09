#ifndef SymbolsTable_H
#define	SymbolsTable_H
#include <algorithm>

#include <unordered_map>
#include "Def.h"
#include "Util.h"
#include "Token.h"

using namespace std;



typedef unordered_map<string, Symbols_Table_Item> CustomHashTable;

class SymbolsTable {
private:
    CustomHashTable hashtable;
    CustomHashTable::hasher HashFunction = hashtable.hash_function();

    void Add(string lexeme, int t_number) {
        string temp_lexeme = lexeme;

        Symbols_Table_Item temp_item;
        temp_item.Lexeme = temp_lexeme;
        temp_item.TokenNumber = t_number;
        

        hashtable.insert(make_pair(temp_lexeme, temp_item));
    }

    /* Inicia Tabela de Símbolos com Palavras Reservadas */
    void Init() {
        Add(TOKEN_BOOL, NUMBER_TOKEN_BOOL );
        Add(TOKEN_INT, NUMBER_TOKEN_INT);
        Add(TOKEN_BYTE, NUMBER_TOKEN_BYTE);
        Add(TOKEN_STRING, NUMBER_TOKEN_STRING);
        Add(TOKEN_WHILE, NUMBER_TOKEN_WHILE);
        Add(TOKEN_IF, NUMBER_TOKEN_IF);
        Add(TOKEN_ELSE, NUMBER_TOKEN_ELSE);
        Add(TOKEN_BEGIN, NUMBER_TOKEN_BEGIN);
        Add(TOKEN_ENDWHILE, NUMBER_TOKEN_ENDWHILE);
        Add(TOKEN_ENDIF, NUMBER_TOKEN_ENDIF);
        Add(TOKEN_ENDELSE, NUMBER_TOKEN_ENDELSE);
        Add(TOKEN_READLN, NUMBER_TOKEN_READLN);
        Add(TOKEN_WRITE, NUMBER_TOKEN_WRITE );
        Add(TOKEN_WRITELN, NUMBER_TOKEN_WRITELN);       
        Add(TOKEN_VIRGULA, NUMBER_TOKEN_VIRGULA);
        Add(TOKEN_PARENS_L, NUMBER_TOKEN_PARENS_L);
        Add(TOKEN_PARENS_R, NUMBER_TOKEN_PARENS_R);
        Add(TOKEN_PONTO_VIRGULA, NUMBER_TOKEN_PONTO_VIRGULA);
        Add(TOKEN_E, NUMBER_TOKEN_E);
        Add(TOKEN_OU, NUMBER_TOKEN_OU);
        Add(TOKEN_NAO, NUMBER_TOKEN_NAO);
        Add(TOKEN_COMP_IGUAL, NUMBER_TOKEN_COMP_IGUAL);
        Add(TOKEN_MENOR, NUMBER_TOKEN_MENOR);
        Add(TOKEN_MAIOR, NUMBER_TOKEN_MAIOR);
        Add(TOKEN_DIFERENTE, NUMBER_TOKEN_DIFERENTE);
        Add(TOKEN_MENOR_IGUAL, NUMBER_TOKEN_MENOR_IGUAL);
        Add(TOKEN_MAIOR_IGUAL, NUMBER_TOKEN_MAIOR_IGUAL);
        Add(TOKEN_SOMA, NUMBER_TOKEN_SOMA);
        Add(TOKEN_SUB, NUMBER_TOKEN_SUB);
        Add(TOKEN_MUL, NUMBER_TOKEN_MUL);
        Add(TOKEN_DIV, NUMBER_TOKEN_DIV);
        Add(TOKEN_ATRIB, NUMBER_TOKEN_ATRIB);
        Add(TOKEN_FINAL, NUMBER_TOKEN_FINAL);
        Add(TOKEN_CONSTBOOLEANT, NUMBER_TOKEN_CONST);
        Add(TOKEN_CONSTBOOLEANF, NUMBER_TOKEN_CONST);

      
    }
public:

    SymbolsTable() {
        Init();
    }

    /**
     * Insere Identificador
     * @param Lexeme Lexema do Identificador
     * @param Class Classe do Identificador
     * @param Type Tipo do Identificador
     * @return código gerado pela função Hash
     */
    int Insert(string Lexeme, int t_number) {
        string temp_lexeme = Lexeme;

        Symbols_Table_Item temp_item;
        temp_item.Lexeme = temp_lexeme;
        temp_item.TokenNumber = t_number;
        

        hashtable.insert(make_pair(temp_lexeme, temp_item));
        return HashFunction(Lexeme);
    }

    /**
     * Busca por Palavra Reservada
     * @param Lexeme Lexema do Identificador
     * @return Número do Token se encontrar, -1 caso contrário.
     */
    int Search(string Lexeme) {
        CustomHashTable::iterator i = hashtable.find(Lexeme);
        if (i != hashtable.end()) {
            return i->second.TokenNumber;
        }
        return -1;
    }

     void PrintAll() {
        //        printf("-- Table Size: %lu \n", hashtable.size());
        for (CustomHashTable::iterator c = hashtable.begin(); c != hashtable.end(); c++) {
           
                printf("  lexema: %10.15s - Token Number: %.3d \n",
                    c->first.c_str(), c->second.TokenNumber);
        }
    }

     

};
#endif

