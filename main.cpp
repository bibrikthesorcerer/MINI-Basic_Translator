// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include "LexBlock/lex_block.h"
#include "SynthBlock/synth_block.h"

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
   Lex_block ADAM("D:/Github/MINI-BASIC_Translator/input.txt");
   ADAM.parse();
   BF_grammar EVA("D:/Github/MINI-BASIC_Translator/grammar.txt");
   EVA.fill_symbol_list(ADAM.get_lexem_list());
   EVA.synth_analize();
   return 0;
}
