#ifndef Lexer_H
#define	Lexer_H

#include <iostream>
#include <fstream>


       
#include <sstream>
#include "Def.h"
#include "Util.h"
#include "SymbolsTable.h"
#include "Token.h"


using namespace std;

class Lexer {
private:
    SymbolsTable *STable;
    fstream FileReader;
    char c;
    int n_token;
    int line;
    int state;
    int eof_c;

    int GetChar() {
        FileReader.get(c);
        if (!isalpha((int) c) && !isdigit((int) c) && c != ' ' && c != '_' && c != '.' && c != ',' && c != ';'&& c != '&' && c != ':' && c != '(' && c != ')'
                && c != '[' && c != ']' && c != '{' && c != '}' && c != '+' && c != '-' && c != '=' && c != '"' && c != '\''
                && c != '/' && c != '!' && c != '*' && c != '?' && c != '>' && c != '<' && c != '\n' && c != '\r'  && c != '|')
            //PrintError(GetLine() , "caractere invalido");
            {
                printf("%s: %d %d",  GetLine(), "caractere invalido",(int)c);
                exit(EXIT_FAILURE);
            }
            
        return 0;
    }

public:

    Lexer(std::string source_file, SymbolsTable *SymbTable) {
        FileReader.open(source_file, fstream::in);
        if (!FileReader.is_open()) {
            printf("%s: error: %s: No such file.\n", P_SHORT_NAME, source_file.c_str());
            exit(EXIT_FAILURE);
        }
        STable = SymbTable;
        n_token = 0;
        line = 0;
        state = 0;
        
        
    }

    /**
     *  Retorna linha atual de leitura no arquivo. 
     */
    int GetLine() {
        return line/2 +1;
    }

    void NextToken(Register *LexReg) {
        string lexeme= "";
        
        state = 0;
      
        while ( state != 2 ) {
           
            if ( !FileReader.eof()) {
                
                GetChar();
              //  printf (" %d - %d - %d\n",(int)c, line, state );   
                //printf (" %c- %d - %d\n",c ,(int)c, state );                          
            } else {              
                   
                c= std::char_traits<char>::eof();                       
                lexeme = lexeme.substr(0, lexeme.size()-1);    
                                           
            }

            //printf (" %c- %d - %d\n",c ,(int)c, state );  
            switch (state) {
                case 0:
                    
                    if ( c == '\n'|| c =='\r') {
                          line++;
                          
                    }else if (  c == ' ' )    {
                            state =0;
                    }else if (c == ';' ) {
                    
                            lexeme += c;
                               
                            LexReg->token_number = STable->Search(lexeme);
                        
                            LexReg->lexeme = lexeme;
                            

                            state = 2;
                    
                        
                    }else if (c == '*' ) {

                            lexeme += c;
                                                                                                
                            
                            LexReg->token_number =  STable->Search(lexeme);
                        
                            LexReg->lexeme = lexeme;
                            
                            state = 2;

                    }else if (c == '+' ) {
                            
                            lexeme += c;
                               
                            LexReg->token_number =  STable->Search(lexeme);
                        
                            LexReg->lexeme = lexeme;
                            
                            state = 2;

                    }else if (c == '(' ) {
                            
                            lexeme += c;
                               
                            LexReg->token_number =  STable->Search(lexeme);
                        
                            LexReg->lexeme = lexeme;
                            
                            state = 2;

                    }else if (c == ')' ) {
                            
                            lexeme += c;
                               
                            LexReg->token_number =  STable->Search(lexeme);
                        
                            LexReg->lexeme = lexeme;
                            
                            state = 2;

                    }else if (c == ',' ) {

                            lexeme += c;
                               
                            LexReg->token_number =  STable->Search(lexeme);
                        
                            LexReg->lexeme = lexeme;
                            
                            state = 2;

                    }else if (c == '<' ) {

                            lexeme += c;                                                     
                            state = 7;

                    }else if (c == '>' ) {

                            lexeme += c;                                                     
                            state = 6;

                    }else if (c == '&' ) {

                            lexeme += c;                                                     
                            state = 3;

                    }else if (c == '|' ) {

                            lexeme += c;                                                     
                            state = 4;

                    }else if (c == '!' ) {

                            lexeme += c;                                                     
                            state = 5;
                   

                    }else if (c =='_' || isalpha(c)) {
                               
                                lexeme += c;
                                
                                //printf ("%s \n", lexeme1.c_str());                         
                                state = 1;                     
                                   
                    }else if (c =='"') {

                                lexeme += c;
                                                              
                                state = 8;                     
                                   
                    }
                    else if (c =='-') {

                                lexeme += c;
                                                              
                                state = 13;                     
                                   
                    }else if (c =='0') {

                                lexeme += c;
                                                              
                                state = 9;                     
                                   
                    }else if ( isdigit(c)) {

                                lexeme += c;
                                                              
                                state = 10;                     
                                   
                    }else if (c =='/') {

                                lexeme += c;
                                                               
                                state = 14;                     
                                   
                    }else if (c == std::char_traits<char>::eof() ) {

                                //c = std::char_traits<char>::eof();
                                LexReg->lexeme = c;
                                LexReg->token_number = TOKEN_EOF;
                                state = 2;                    
                                   
                    }else {
                        lexeme += c;
                        PrintError(line, "Lexema nao identificado", lexeme);
                        
                    }
                    break;
                case 1:
                    
                   
                    if ( (c =='_' || isalpha(c) || isdigit (c))){
                          
                                
                                lexeme += c;
                                state = 1; 
                                 
                                
                               
                    }else if ( STable->Search(lexeme) > 0 ) {
                          
                            LexReg->token_number =STable->Search(lexeme) ;
                        
                            LexReg->lexeme = lexeme;
                            
                            state = 2; 
                                                
                            FileReader.unget();
                                                       
                    }else {
                            
                            STable->Insert(lexeme, NUMBER_TOKEN_ID );

                            LexReg->token_number = NUMBER_TOKEN_ID ;

                            LexReg->lexeme = lexeme;
                            
                            state = 2;

                            FileReader.unget(); 

                    }   
                                           
                    break;
                case 2:
                    
                    break;
                case 3:
                           
                            if ( c == '&') {

                            lexeme += c;
                            LexReg->token_number =  STable->Search(lexeme);                    
                            LexReg->lexeme = lexeme;
                            
                            state = 2;
                            }  else {
                                 PrintError(GetLine() , "Lexema nao identificado", lexeme);
                            }
                            

                    break;
                case 4:
                
                           if ( c == '|') {
                            lexeme += c;
                            LexReg->token_number =  STable->Search(lexeme);                      
                            LexReg->lexeme = lexeme;                           
                            state = 2;
                            }  else {
                                 PrintError(GetLine() , "Lexema nao identificado", lexeme);
                            }

                    break;
                case 5:

                            if (c == '=') {
                                lexeme += c;
                               
                                LexReg->token_number =  STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2;
                            }  else {
                            
                               
                            LexReg->token_number =  STable->Search(lexeme);
                        
                            LexReg->lexeme = lexeme;
                            
                            state = 2; 
                             
                            FileReader.unget();
                               
                            //dev c    
                            }

                    break;
                case 6:

                     if (c == '=') {

                                lexeme += c;
                               
                                LexReg->token_number =  STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2;
                            }  else {
                                                         
                                LexReg->token_number =  STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2; 

                                 FileReader.unget();
                                    
                                //dev c
                            }

                    break;
                case 7:

                     if (c == '=') {
                         
                                lexeme += c;
                               
                                LexReg->token_number =  STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2;
                            }  else if (c =='-') {

                                lexeme += c;
                               
                                LexReg->token_number =  STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2;                     
                                   
                            }   else {

                                LexReg->token_number =  STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2; 

                                FileReader.unget();
                                //dev c
                            }

                    break;
                case 8:
                if (c == '\n') {
                         
                                lexeme += c;
                               
                                //erro
                            
                                state = 2;
                            }  else if (c =='"'){

                                lexeme += c;
                               
                                LexReg->token_number = NUMBER_TOKEN_CONST ;
                                
                                LexReg->lexeme = lexeme;
                            
                                state = 2;                     
                                   
                            }else if (c == std::char_traits<char>::eof() ) {

                                
                               
                                LexReg->token_number = TOKEN_EOF ;
                                
                                LexReg->lexeme = c;
                            
                                state = 2;                     
                                   
                            } else {

                                lexeme += c;

                            }


                    break; 
                case 9:
                if (isdigit(c)) {
                         
                                lexeme += c;                      
                                state = 10;

                }else if (c =='x') {

                                lexeme += c;                          
                                state = 11;                     

                } else {
                                
 
                                LexReg->token_number = NUMBER_TOKEN_CONST ;
                                
                                LexReg->lexeme = lexeme;
                            
                                state = 2;

				FileReader.unget();
                 }

             break;
                case 10:
                if (isdigit(c)) {
                         
                                lexeme += c;                     
                                
                     } else {
                                              
                                LexReg->token_number =  NUMBER_TOKEN_CONST;
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2; 

                                FileReader.unget( );

                     }
                  
                    break;
                case 11:
                if (isxdigit(c)) {
                         
                                lexeme += c;                           
                                state = 12;
                     } else {
                          PrintError(GetLine() , "Lexema nao identificado", lexeme);
                         //erro
                     }

                    break;
                case 12 :

                if (isxdigit(c)) {
                                
                                lexeme += c;
                                LexReg->token_number =  NUMBER_TOKEN_CONST;
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2;                            
                                
                     } else {
                          PrintError(line, "Lexema nao identificado", lexeme);
                         //erro
                     }

                    break;
                case 13:
                if (isdigit(c)) {
                         
                                lexeme += c;                                                      
                                state = 10;
                     } else {

                         

                                LexReg->token_number = STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2; 

                                FileReader.unget( );
                     }
                    break;
                case 14: 
                if (c =='*'){
                    
                    state = 15;

                } else {
                                // divisao
                                LexReg->token_number =  STable->Search(lexeme);
                        
                                LexReg->lexeme = lexeme;
                            
                                state = 2; 

                                FileReader.unget( );
                }

                 break;
                case 15:
                if (c =='*'){
                    
                    state = 16;

                } else {
                    state = 15;
                }


                 break;
                case 16:
                    if (c =='/'){
                    lexeme.clear();
                    state = 0;
                    

                } else {
                    state = 15;
                    
                }

                 break;
                   
            }     // end switch    
            
        } // end while
         
    } // end nextoken

};
#endif