//
//  syntax_util.h
//  Complier Ex
//
//  Created by Ou Sheobin on 2017/12/22.
//  Copyright © 2017年 Ou Sheobin. All rights reserved.
//

#ifndef syntax_util_h
#define syntax_util_h

#include <vector>
#include <stack>
#include "constants.h"
#include "symbol.h"

using namespace std;

class syntax_util {
public:
    bool check_syntax( vector<symbol> * input_vector_ptr );
private:
    stack<string> symbol_stack;
    stack<int>      state_stack;
    stack<symbol> input_stack;
    stack<symbol> translate_stack;
    bool check_ok;
    int reg_memory_id = 0;
    void reduce(int reduce_number);
    void reduce_stack_handler(int count);
    void shift(int state_number,string push_symbol);
    int allocate_reg_memory();
};

#endif
