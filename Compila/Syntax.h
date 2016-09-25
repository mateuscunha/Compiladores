#ifndef SYNTAX_H
#define	SYNTAX_H

#include "SymbolsTable.h" 
#include "Def.h"
#include "Util.h"
#include "Lexer.h"
#include "Token.h"

class Syntax {
    private:
    Register lexReg;
    SymbolsTable *STable;
    Lexer *lexAnalyser;
    void Match_Token ( int esperado){
        if (lexReg.token_number == esperado) {
            lexAnalyser->NextToken(&lexReg);
        }else {
            printf("%02d:%s [%s].\n", lexAnalyser->GetLine(), "Token Nao esperado", lexReg.lexeme.c_str());
            exit(EXIT_FAILURE);
        }
    } 

    
    void CMDS() {

        Match_Token (NUMBER_TOKEN_PARENS_L);
        EXP();
        Match_Token (NUMBER_TOKEN_PARENS_R);
        Match_Token (NUMBER_TOKEN_BEGIN);
        while ( lexReg.token_number != NUMBER_TOKEN_ENDIF ) {
            CMD ();
        }
        Match_Token (NUMBER_TOKEN_ENDIF);
        Match_Token (NUMBER_TOKEN_ELSE);
        Match_Token (NUMBER_TOKEN_BEGIN);
        while ( lexReg.token_number != NUMBER_TOKEN_ENDELSE ) {
            CMD ();
        }
        Match_Token (NUMBER_TOKEN_ENDELSE);
        


    }
    void C_TEST() {

           Match_Token (NUMBER_TOKEN_IF);
           Match_Token (NUMBER_TOKEN_PARENS_L);
           EXP();
           Match_Token (NUMBER_TOKEN_PARENS_R);

    }

    void Fator( ) {

       if (lexReg.token_number == NUMBER_TOKEN_ID) {
           Match_Token (NUMBER_TOKEN_ID);
       }else if (lexReg.token_number == NUMBER_TOKEN_CONST ) {
           Match_Token (NUMBER_TOKEN_CONST);
       }else if (lexReg.token_number == NUMBER_TOKEN_NAO ) {
           Match_Token (NUMBER_TOKEN_NAO);
           Fator();
       }else {
           Match_Token (NUMBER_TOKEN_PARENS_L);
           EXP();
           Match_Token (NUMBER_TOKEN_PARENS_R);
       }
        
    }
   void Termo() {
       Fator ();
               
        while ( lexReg.token_number == NUMBER_TOKEN_MUL || 
                lexReg.token_number == NUMBER_TOKEN_DIV || 
                lexReg.token_number == NUMBER_TOKEN_E ){
                    Match_Token (lexReg.token_number);
                    Fator ();
                }
   }

    void EXPS () {

        if ( lexReg.token_number == NUMBER_TOKEN_SOMA ) {
            Match_Token (NUMBER_TOKEN_SOMA);
        } else if ( lexReg.token_number == NUMBER_TOKEN_SUB  ) {
            Match_Token (NUMBER_TOKEN_SUB);
        }
        Termo ();
        while ( lexReg.token_number == NUMBER_TOKEN_SOMA || 
                lexReg.token_number == NUMBER_TOKEN_SUB || 
                lexReg.token_number == NUMBER_TOKEN_OU ){
                    Match_Token (lexReg.token_number);
                    Termo();
                }
    }


   void COMPARE() {
       if (lexReg.token_number == NUMBER_TOKEN_COMP_IGUAL) {
           Match_Token (NUMBER_TOKEN_COMP_IGUAL);
       }else if (lexReg.token_number == NUMBER_TOKEN_MENOR ) {
           Match_Token (NUMBER_TOKEN_MENOR);
       }else if (lexReg.token_number == NUMBER_TOKEN_MAIOR ) {
           Match_Token (NUMBER_TOKEN_MAIOR);
       }else if (lexReg.token_number == NUMBER_TOKEN_DIFERENTE ) {
           Match_Token (NUMBER_TOKEN_DIFERENTE);
       }else if (lexReg.token_number == NUMBER_TOKEN_MENOR_IGUAL ) {
           Match_Token (NUMBER_TOKEN_MENOR_IGUAL);
       }else {
           Match_Token (NUMBER_TOKEN_MAIOR_IGUAL);
       }
   }


    void EXP () {
        EXPS();
        if (lexReg.token_number == NUMBER_TOKEN_COMP_IGUAL || 
            lexReg.token_number == NUMBER_TOKEN_MENOR ||
            lexReg.token_number == NUMBER_TOKEN_MAIOR ||
            lexReg.token_number == NUMBER_TOKEN_DIFERENTE ||
            lexReg.token_number == NUMBER_TOKEN_MENOR_IGUAL ||
            lexReg.token_number == NUMBER_TOKEN_MAIOR_IGUAL) {
                COMPARE();
                EXPS();
            }         
    }
    void ID_List () {
        Match_Token( NUMBER_TOKEN_ID );
        if (lexReg.token_number == NUMBER_TOKEN_ATRIB) {
            Match_Token (NUMBER_TOKEN_ATRIB);
            Match_Token (NUMBER_TOKEN_CONST);
        }
        while (lexReg.token_number == NUMBER_TOKEN_ATRIB) {
            Match_Token( NUMBER_TOKEN_ID );
            Match_Token( NUMBER_TOKEN_VIRGULA );
            if (lexReg.token_number == NUMBER_TOKEN_ATRIB) {
                Match_Token (NUMBER_TOKEN_ATRIB);
                Match_Token (NUMBER_TOKEN_CONST);
             }
        }
  }
    void C_Atrib() {
        Match_Token(NUMBER_TOKEN_ID);
        Match_Token (NUMBER_TOKEN_ATRIB);
        EXP ();
        Match_Token(NUMBER_TOKEN_PONTO_VIRGULA);   
    }

    void C_REP ( ) {

        Match_Token(NUMBER_TOKEN_WHILE);
        Match_Token (NUMBER_TOKEN_PARENS_L);
        EXP ();
        Match_Token (NUMBER_TOKEN_PARENS_R);
        if  (lexReg.token_number == NUMBER_TOKEN_BEGIN ) {
            Match_Token(NUMBER_TOKEN_BEGIN);
            if ( lexReg.token_number == NUMBER_TOKEN_ENDWHILE ) {
                Match_Token (NUMBER_TOKEN_ENDWHILE);
            } else {
                while (lexReg.token_number != NUMBER_TOKEN_ENDWHILE ) {
                    CMD();
                }
            }
            Match_Token (NUMBER_TOKEN_ENDWHILE);
            
        } else {
             CMD();
        }
       ;
    }
    void CMD () {

        if (lexReg.token_number == NUMBER_TOKEN_ID ) {
             C_Atrib ( );
        }else if (lexReg.token_number == NUMBER_TOKEN_WHILE) {
             C_REP ( );

        }else if (lexReg.token_number == NUMBER_TOKEN_PONTO_VIRGULA) {
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA);
            
        }else if (lexReg.token_number == NUMBER_TOKEN_READLN) {
            Match_Token(NUMBER_TOKEN_READLN);
            Match_Token (NUMBER_TOKEN_PARENS_L);
            Match_Token (NUMBER_TOKEN_ID);
            Match_Token (NUMBER_TOKEN_PARENS_R);
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA);
            
        }else if (lexReg.token_number == NUMBER_TOKEN_WRITE) {
            Match_Token(NUMBER_TOKEN_WRITE);

            Match_Token(NUMBER_TOKEN_PARENS_L);
            EXP( );
            while (lexReg.token_number == NUMBER_TOKEN_VIRGULA){
                Match_Token(NUMBER_TOKEN_VIRGULA);
               EXP( ); 
            }
            Match_Token(NUMBER_TOKEN_PARENS_R);
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA);
            
        }else if (lexReg.token_number == NUMBER_TOKEN_WRITELN) {
            Match_Token(NUMBER_TOKEN_WRITELN);
            Match_Token(NUMBER_TOKEN_PARENS_L);
            EXP( );
            while (lexReg.token_number == NUMBER_TOKEN_VIRGULA){
                Match_Token(NUMBER_TOKEN_VIRGULA);
                EXP( ); 
            }
            Match_Token(NUMBER_TOKEN_PARENS_R);
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA);
                     
        }else {
            C_TEST();
             
        }

    }
    void DEC_V() {
        if (lexReg.token_number == NUMBER_TOKEN_BYTE ) {
            Match_Token(NUMBER_TOKEN_BYTE); 
            ID_List(); 
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA); 
        }else if (lexReg.token_number == NUMBER_TOKEN_INT) {
            Match_Token(NUMBER_TOKEN_INT); 
            ID_List(); 
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA); 

        }else if (lexReg.token_number == NUMBER_TOKEN_STRING) {
            Match_Token(NUMBER_TOKEN_STRING);
            ID_List();
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA); 

        }else {
            Match_Token(NUMBER_TOKEN_BOOL); 
            ID_List(); 
            Match_Token(NUMBER_TOKEN_PONTO_VIRGULA); 

        }
    }
    void DEC_C(){

            Match_Token( NUMBER_TOKEN_FINAL);
            Match_Token( NUMBER_TOKEN_ID );    
            Match_Token (NUMBER_TOKEN_ATRIB);
            Match_Token (NUMBER_TOKEN_CONST);
        

    }
      void DecS(){
          if (lexReg.token_number == NUMBER_TOKEN_BYTE ||
          lexReg.token_number == NUMBER_TOKEN_INT ||
          lexReg.token_number == NUMBER_TOKEN_STRING ||
          lexReg.token_number == NUMBER_TOKEN_BOOL ) {
              DEC_V();
          } else {
              DEC_C();
          }
        
    }
    void S(){
        while ( (lexReg.token_number == NUMBER_TOKEN_BYTE ||
          lexReg.token_number == NUMBER_TOKEN_INT ||
          lexReg.token_number == NUMBER_TOKEN_STRING ||
          lexReg.token_number == NUMBER_TOKEN_BOOL ||
          lexReg.token_number == NUMBER_TOKEN_FINAL)) {
              DecS();
          } 
        
        while (lexReg.token_number != TOKEN_EOF) {
        CMD();
        };
    }
    
    
    
    public:
    Syntax( std::string source_file ) {
        STable = new SymbolsTable() ;
        lexAnalyser =  new Lexer(source_file, STable);
        lexReg.lexeme="";

    }
    void Parse() {
        //while (lexReg.token_number != TOKEN_EOF) {
        lexAnalyser->NextToken(&lexReg);
        
        S();
        if (lexReg.token_number != TOKEN_EOF ) {
            printf("%02d:%s.\n", lexAnalyser->GetLine(), "Fim de arquivo não esperado");
            exit(EXIT_FAILURE);
        }
       // printf ("%s - %d \n", lexReg.lexeme.c_str(), lexReg.token_number );         
    }
    
    

   
};
#endif


    