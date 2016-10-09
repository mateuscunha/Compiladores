
#include "SymbolsTable.h" 
#include "Def.h"
#include "Util.h"
#include "Lexer.h"
#include "Token.h"
#include "Syntax.h"

int main ( int argc, char* argv[]) {

    //Register lexReg;
    //SymbolsTable *STable = new SymbolsTable() ;
    //Lexer *lexAnalyser =  new Lexer("exemplo2.l", STable);
    Syntax *parser = new Syntax (argv[1]);
    //lexReg.lexeme = "";
    //lexReg.token_number = 0;
    //int count = 0;
    
    //STable->PrintAll();
   //printf ("%d " ,STable->Search("int"));
   // while (lexReg.token_number != TOKEN_EOF ) {
      // lexAnalyser->NextToken(&lexReg);
       //printf ("%s - %d \n", lexReg.lexeme.c_str(), lexReg.token_number );
      
       
 // } 
        
   printf("ok");
    //parser->Parse();
  //printf("parser");
   // STable->~SymbolsTable(); 
    //lexAnalyser->~Lexer();

    
     parser->Parse();
     parser->~Syntax();
    
}