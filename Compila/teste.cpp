#include <iostream>
#include <string>
#include "util.h"
#include "Def.h"
using namespace std;

int main ()
{
   char c = std::char_traits<char>::eof();
    printf ("%d", (c =='_' || isalpha(c) || isdigit (c)));
   return 0;
}