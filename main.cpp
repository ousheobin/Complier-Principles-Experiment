//
//  main.cpp
//  Complier
//
//  Created by Ou Sheobin on 2017/12/18.
//  Copyright © 2017年 Ou Sheobin. All rights reserved.
//

#include <iostream>
#include <vector>
#include "symbol.h"
#include "lexical_util.h"
#include "syntax_util.h"
#include "constants.h"

using namespace std;

int main(int argc, const char * argv[]) {
    string input;
    lexical_util lex_util;
    while(true){
        getline(cin,input);
        if(input.length() > 0 ){
            vector<symbol> symbol_vector;
            bool lexcial_result = lex_util.check(input, &symbol_vector);
            if(lexcial_result){
                syntax_util syn_util;
                bool syntax_res = syn_util.check_syntax(&symbol_vector);
                if( syntax_res ){
                    // TODO: 语法检查正确，可以进行语义分析和语法制导翻译
                }
            }
        }else{
            continue;
        }
    }
    return 0;
}

