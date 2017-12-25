//
//  symbol.cpp
//  Complier Ex
//
//  Created by Ou Sheobin on 2017/12/21.
//  Copyright © 2017年 Ou Sheobin. All rights reserved.
//

#include "symbol.h"
#include "constants.h"

using namespace std;

symbol::symbol(int code,string orign){
    this->code = code;
    this->orign = orign;
    this->type = "NULL";
    this->value = 0.00;
    this->integer_value = 0;
    this->double_value = 0;
}

symbol::symbol(int code,string orign,int value,string type){
    this->code = code;
    this->orign = orign;
    this->type = orign;
    this->value = value;
    this->integer_value = value;
    this->double_value = 0;
}

symbol::symbol(int code,string orign,double value,string type){
    this->code = code;
    this->orign = orign;
    this->type = type;
    this->value = value;
    this->integer_value = 0;
    this->double_value = value;
}

string symbol::get_lexcial_string(){
    stringstream detai_stream;
    if(this->code!=TYPE_ID_INTEGER || this-> code!=TYPE_ID_FLOAT){
        detai_stream << "("<<this->code<<","<<this->orign<<","<<this->value<<","<<this->type<<")";
    }else{
        detai_stream << "("<<this->code<<","<<this->orign<<",NULL,NULL)";
    }
    return detai_stream.str();
}
