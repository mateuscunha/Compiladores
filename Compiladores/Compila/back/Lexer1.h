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
    char current;
    int n_token;
    int line;
    int state;

    int GetChar() {
        FileReader.get(current);
        if (!isalpha((int) current) && !isdigit((int) current) && current != ' ' && current != '_' && current != '.' && current != ',' && current != ';'&& current != '&' && current != ':' && current != '(' && current != ')'
                && current != '[' && current != ']' && current != '{' && current != '}' && current != '+' && current != '-' && current != '=' && current != '"' && current != '\''
                && current != '/' && current != '!' && current != '*' && current != '?' && current != '>' && current != '<' && current != '\n' && current != '\r')
            PrintError(line, "caractere invalido");
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
        line = 1;
        state = 0;
        
    }

    /**
     *  Retorna linha atual de leitura no arquivo. 
     */
    int GetLine() {
        return line;
    }

    void NextToken(Register *LexReg) {
        stringstream lexeme;
        string lexeme1="";
        state = 0;
       
        while ( state != 2) {

            if ( !FileReader.eof()) {

                GetChar();
                printf ("%c", current); 
               
                
                
            } else {
                
                current = std::char_traits<char>::eof();
                LexReg->lexeme = current;
                LexReg->token_number = TOKEN_EOF;
                
                state = 2;
            }


            switch (state) {
                case 0:
                    
                    if ( current == '\n'|| current =='\r') {
                          line++;
                    }else if (  current == ' ' )    {

                    }
                    }else if (current == ';' ) {
                    
                            lexeme << current;
                               
                            LexReg->token_number = STable->Search(lexeme.str());
                        
                            LexReg->lexeme = lexeme.str();
                            

                            state = 2;
                    
                        
                    }else if (current == '*' ) {

                            lexeme << current;
                                                                                                
                            
                            LexReg->token_number =  STable->Search(lexeme.str());
                        
                            LexReg->lexeme = lexeme.str();
                            
                            state = 2;

                    }else if (current == '+' ) {
                            
                            lexeme << current;
                               
                            LexReg->token_number =  STable->Search(lexeme.str());
                        
                            LexReg->lexeme = lexeme.str();
                            
                            state = 2;

                    }else if (current == ',' ) {

                            lexeme << current;
                               
                            LexReg->token_number =  STable->Search(lexeme.str());
                        
                            LexReg->lexeme = lexeme.str();
                            
                            state = 2;

                    }else if (current == '<' ) {

                            lexeme << current;                                                     
                            state = 7;

                    }else if (current == '>' ) {

                            lexeme << current;                                                     
                            state = 6;

                    }else if (current == '&' ) {

                            lexeme << current;                                                     
                            state = 3;

                    }else if (current == '|' ) {

                            lexeme << current;                                                     
                            state = 4;

                    }else if (current == '!' ) {

                            lexeme << current;                                                     
                            state = 5;
                   

                    }else if (current =='_' || isalpha(current)) {
                               
                                lexeme << current;
                               // lexeme1 += current;
                               // printf ("%s \n", lexeme1.c_str());                         
                                state = 1;                     
                                   
                    }else if (current =='"') {

                                lexeme << current;
                                                              
                                state = 8;                     
                                   
                    }
                    else if (current =='-') {

                                lexeme << current;
                                                              
                                state = 13;                     
                                   
                    }else if ( isdigit(current)) {

                                lexeme << current;
                                                              
                                state = 10;                     
                                   
                    }else if (current =='0') {

                                lexeme << current;
                                                              
                                state = 9;                     
                                   
                    }else if (current =='/') {

                                lexeme << current;
                                                               
                                state = 14;                     
                                   
                    }else {
                        
                        PrintError(line, "Lexema nao identificado", lexeme.str());
                        
                    }
                    break;
                case 1:
                    printf ("%s \n", lexeme1.c_str()); 
                    if (current =='_' || isalpha(current) || isdigit (current)) {
                                
                                lexeme << current;
                                state = 1;  
                    } else if (STable->Search(lexeme.str()) > 0 ) {

                        

                            STable->Insert(lexeme.str(), NUMBER_TOKEN_ID );
                            
                            LexReg->token_number = NUMBER_TOKEN_ID ;
                        
                            LexReg->lexeme = lexeme.str();
                            
                            state = 2; 

                            FileReader.unget();
                            

                    }      
                    break;
                case 2:
                    
                    break;
                case 3:
 
                            
                            if ( current = '&') {
                            lexeme << current;
                            LexReg->token_number =  STable->Search(lexeme.str());
                        
                            LexReg->lexeme = lexeme.str();
                            
                            state = 2;
                            }  else {
                                 PrintError(line, "Lexema nao identificado", lexeme.str());
                            }
                            

                    break;
                case 4:
                
                           if ( current = '|') {
                            lexeme << current;
                            LexReg->token_number =  STable->Search(lexeme.str());
                        
                            LexReg->lexeme = lexeme.str();
                            
                            state = 2;
                            }  else {
                                 PrintError(line, "Lexema nao identificado", lexeme.str());
                            }

                    break;
                case 5:

                            if (current == '=') {
                                lexeme << current;
                               
                                LexReg->token_number =  STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2;
                            }  else {
                            
                               
                            LexReg->token_number =  STable->Search(lexeme.str());
                        
                            LexReg->lexeme = lexeme.str();
                            
                            state = 2; 
                             
                            FileReader.unget();
                               
                            //dev c    
                            }

                    break;
                case 6:

                     if (current == '=') {

                                lexeme << current;
                               
                                LexReg->token_number =  STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2;
                            }  else {
                                                         
                                LexReg->token_number =  STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2; 

                                 FileReader.unget();
                                    
                                //dev c
                            }

                    break;
                case 7:

                     if (current == '=') {
                         
                                lexeme << current;
                               
                                LexReg->token_number =  STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2;
                            }  else if (current =='-') {

                                lexeme << current;
                               
                                LexReg->token_number =  STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2;                     
                                   
                            }   else {

                                LexReg->token_number =  STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2; 

                                FileReader.unget();
                                //dev c
                            }

                    break;
                case 8:
                if (current == '\n') {
                         
                                lexeme << current;
                               
                                //erro
                            
                                state = 2;
                            }  else if (current =='"') {

                                lexeme << current;
                               
                                LexReg->token_number = NUMBER_TOKEN_CONST ;
                                
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2;                     
                                   
                            } else {

                                lexeme << current;

                            }


                    break; 
                case 9:
                if (isdigit(current)) {
                         
                                lexeme << current;                      
                                state = 10;

                }else if (current =='x') {

                                lexeme << current;                          
                                state = 11;                     

                } else {

                                PrintError(line, "Lexema nao identificado", lexeme.str());
                 }

             break;
                case 10:
                if (isdigit(current)) {
                         
                                lexeme << current;                     
                                
                     } else {
                                              
                                LexReg->token_number =  NUMBER_TOKEN_CONST;
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2; 

                                FileReader.unget( );

                     }
                  
                    break;
                case 11:
                if (isxdigit(current)) {
                         
                                lexeme << current;                           
                                state = 12;
                     } else {
                          PrintError(line, "Lexema nao identificado", lexeme.str());
                         //erro
                     }

                    break;
                case 12 :

                if (isxdigit(current)) {
                         
                                lexeme << current;                           
                                state = 12;
                     } else {
                          PrintError(line, "Lexema nao identificado", lexeme.str());
                         //erro
                     }

                    break;
                case 13:
                if (isdigit(current)) {
                         
                                lexeme << current;

                              
                                                       
                                state = 10;
                     } else {

                         

                                LexReg->token_number = STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2; 

                                FileReader.unget( );
                     }
                    break;
                case 14: 
                if (current =='*'){
                    
                    state = 15;

                } else {
                                // divisao
                                LexReg->token_number =  STable->Search(lexeme.str());
                        
                                LexReg->lexeme = lexeme.str();
                            
                                state = 2; 

                                 FileReader.unget( );
                }

                 break;
                case 15:
                if (current =='*'){
                    
                    state = 16;

                } else {
                    state = 15;
                }


                 break;
                case 16:
                    if (current =='/'){
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