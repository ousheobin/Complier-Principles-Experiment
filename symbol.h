//
//  symbol.h 编译的符号类
//  Complier 编译原理实验
//
//  Created by Ou Sheobin on 2017/12/21.
//  Copyright © 2017年 Ou Sheobin. All rights reserved.
//

#ifndef symbol_hpp
#define symbol_hpp

#include<string>
#include<sstream>

using namespace std;

class symbol {
public:
    
    int         code;                // 种别码
    string    orign;                // 字符串原貌
    double  value;               // value属性
    int         integer_value;  // 整形数值
    double  double_value;  // 浮点数值
    string    type;                // 类型
    
    symbol(int code,string orign);
    symbol(int code,string orign,int value,string type);
    symbol(int code,string orign,double value,string type);
    
    string get_lexcial_string();
    
};

#endif
