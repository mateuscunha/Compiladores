cmake_minimum_required(VERSION 3.6)
project(Compila)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    back/Lexer1.h
    a.exe
    AFD.jpg
    c.bat
    Def.h
    exemplo.l
    exemplo2.l
    lexeme
    Lexer.h
    Lista-de-Tokens.docx
    main.cpp
    SymbolsTable.h
    Syntax.h
        Token.h
    token_number
    Util.h)

add_executable(Compila ${SOURCE_FILES})