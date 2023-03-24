#include <iostream>
#include "det_automa.h"

int main()
{
   std::vector<state> finite_states(1, state::q3);
   std::vector<std::vector<state>> trans_table{ {state::q1, state::qe},
                                                {state::q2, state::qe},
                                                {state::q2, state::q3},
                                                {state::q3, state::q2},
                                                {state::qe, state::qe},
                                                                     };

   automa1 obj(state::q0, trans_table, finite_states, "input.txt");

   obj.parse();

    return 0;
}
