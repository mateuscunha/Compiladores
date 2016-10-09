#ifndef UTIL_H
#define	UTIL_H

#include <string>

#include <algorithm>

#include <stdio.h>




using namespace std;


typedef struct Symbols_Table_Item {
    string Lexeme; 
    Symbols_Table_Item * address;
    int TokenNumber; 
     
} Symbols_Table_Item;

typedef struct Register {
    int token_number; // Para tokens de palavras reservadas
    Symbols_Table_Item* address;
    std::string lexeme;
    

    

} Register;
















/**
 * Imprime Erro e aborta a execução.
 * @param line Linha onde foi encontrado erro.
 * @param msg Mensagem a ser impressa.
 * @param lexeme Lexema encontrado.
 */
void PrintError(int line, std::string msg, std::string lexeme) {
    //    printf(FBOLD KRED "%02d:%s [%s].\n" KRST, line, msg.c_str(), lexeme.c_str());
    printf("%02d:%s [%s].\n", line, msg.c_str(), lexeme.c_str());
    exit(EXIT_FAILURE);
}

/**
 * Imprime Erro e aborta a execução.
 * @param line Linha onde foi encontrado erro.
 * @param msg Mensagem a ser imprimida.
 */
void PrintError(int line, std::string msg) {
    //    printf(FBOLD KRED "%02d:%s.\n" KRST, line, msg.c_str());
    printf("%02d:%s.\n", line, msg.c_str());
    exit(EXIT_FAILURE);
}

/**
 * Imprime Erro e aborta a execução.
 * @param msg Mensagem a ser imprimida.
 * @param lexeme Lexema encontrado.
 */
void PrintError(std::string msg, std::string lexeme) {
    //    printf(FBOLD KRED "%s [%s].\n" KRST, msg.c_str(), lexeme.c_str());
    printf("%s [%s].\n", msg.c_str(), lexeme.c_str());
    exit(EXIT_FAILURE);
}

/**
 * Imprime Erro e aborta a execução.
 * @param msg Mensagem a ser imprimida.
 */
void PrintError(std::string msg) {
    //    printf(FBOLD KRED "%s.\n" KRST, msg.c_str());
    printf("%s.\n", msg.c_str());
    //    printf(FBOLD "\n%s\n" KRST, "Execução terminada com erro!");
    exit(EXIT_FAILURE);
}

#endif