//
//  lexical_util.h 语法检查工具
//  Complier Ex
//
//  Created by Ou Sheobin on 2017/12/21.
//  Copyright © 2017年 Ou Sheobin. All rights reserved.
//

#ifndef dfa_utils_hpp
#define dfa_utils_hpp

#include<string>
#include<sstream>
#include<stdlib.h>
#include<vector>

#include "symbol.h"

using namespace std;

class lexical_util {
    
public:
    bool check(string target , vector<symbol> * symbolVector );
    
private:
    bool checkIsSymbol(char param);
    bool checkIsNumber(char param);
    bool checkIsNotZeroNumber(char param);
};

#endif
