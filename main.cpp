#include <iostream>
#include "Lex_block.h"

/*
Пример программы для теста лексблока из книги Льюиса:
1 rem im going to kill myself
2 rem a1 + = ( ) .
13 let f 1 = 7 / - (63 < > 9)) = * < (
14 let g = - 3 to .65 + .01 = .1) + .8( .6
20 f or i = .3 e 6 8 step . 3e + 6 = 1.3e - 1) (1.3e-9
23 if  10 e6 + 3e1 (1e1 goto 1 2 = h i >
40 next e3
42 + a ^ b ( c ) 2 ( d
45 gosub 1)goto 6
50 ( 9
52 ) . 6 return )end  > = < = < )
 60 7
54 =j0+k1+l2+m3+n4+o5+p6+q7+r8+s9+t+u+v+w+x+y+z
*/

int main()
{
   Lex_block ADAM("input.txt");
   ADAM.parse();
   ADAM.print_lexem_list();
   return 0;
}
