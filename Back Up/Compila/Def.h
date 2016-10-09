/*This file contain all the laguages' reserved words*/

#ifndef DEF_H
#define	DEF_H

#define P_SHORT_NAME    "LC"
#define P_NAME          "L Compiler"
#define P_VERSION       "1.0.1"
#define P_ABOUT         "Mateus Cunha, Milton, Rafael"

/* Palavras Reservadas */
#define TOKEN_FINAL         "final"
#define TOKEN_BOOL          "boolean"
#define TOKEN_INT           "int"
#define TOKEN_BYTE          "byte"
#define TOKEN_STRING        "string"
#define TOKEN_WHILE         "while"
#define TOKEN_IF            "if"
#define TOKEN_ELSE          "else"
#define TOKEN_BEGIN         "begin"
#define TOKEN_ENDWHILE       "endwhile"
#define TOKEN_ENDIF          "endif"
#define TOKEN_ENDELSE        "endelse"
#define TOKEN_READLN         "readln"
#define TOKEN_WRITE          "write"
#define TOKEN_WRITELN        "writeln"
#define TOKEN_CONSTBOOLEANT   "TRUE"
#define TOKEN_CONSTBOOLEANF   "FALSE"
  



/* Separadores */
#define TOKEN_PONTO_VIRGULA      ";"
#define TOKEN_VIRGULA            ","
#define TOKEN_PARENS_L           "("
#define TOKEN_PARENS_R           ")"


/* Operadores Lógicos */
#define TOKEN_E             "&&"
#define TOKEN_OU            "||"
#define TOKEN_NAO           "!"
#define TOKEN_COMP_IGUAL    "="
#define TOKEN_MENOR         "<"
#define TOKEN_MAIOR         ">"
#define TOKEN_DIFERENTE     "!="
#define TOKEN_MENOR_IGUAL   "<="
#define TOKEN_MAIOR_IGUAL   ">="

/* Operadores Aritiméticos */
#define TOKEN_SOMA          "+"
#define TOKEN_SUB           "-"
#define TOKEN_MUL           "*"
#define TOKEN_DIV           "/"
#define TOKEN_ATRIB         "<-"


#endif
