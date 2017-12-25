//
//  syntax_util.cpp
//  Complier Ex
//
//  Created by Ou Sheobin on 2017/12/22.
//  Copyright © 2017年 Ou Sheobin. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "constants.h"
#include "symbol.h"
#include "syntax_util.h"

using namespace std;

bool syntax_util::check_syntax(vector<symbol> *input_vector_ptr){
    vector<symbol> input_vector = *input_vector_ptr;
    check_ok = true;
    bool is_acc = false;
    symbol input_vector_end(TYPE_ID_END,NAME_ID_END);
    input_vector.push_back(input_vector_end);
    symbol_stack.push(NAME_ID_END);
    state_stack.push(0);
    long size = input_vector.size();
    for( long i = size - 1; i >= 0  ; i -- ){
        symbol symb = input_vector[i];
        if(symb.code == TYPE_ID_FLOAT || symb.code == TYPE_ID_INTEGER){
            symb.code = TYPE_ID_NUMBER;
        }
        input_stack.push(symb);
    }
    while(check_ok && ! is_acc ){
        int state = state_stack.top();
        int code = input_stack.top().code;
        switch  (state) {
            case 0 :
                if( code==TYPE_ID_MINUS ){
                    shift(7, NAME_ID_MINUS);
                }else if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(2, NAME_ID_LEFT_BRACKETS);
                }else if( code == TYPE_ID_NUMBER ){
                    shift(6, NAME_ID_NUMBER);
                }else{
                    check_ok = false;
                }
                break;
            case 1:
                if( code==TYPE_ID_END ){
                    is_acc = true;
                }else{
                    check_ok = false;
                }
                break;
            case 2:
                if( code == TYPE_ID_MINUS ){
                    shift(7, NAME_ID_MINUS);
                }else if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(2, NAME_ID_LEFT_BRACKETS);
                }else if( code == TYPE_ID_NUMBER ){
                    shift(6, NAME_ID_NUMBER);
                }else{
                    check_ok = false;
                }
                break;
            case 3:
                if( code==TYPE_ID_PLUS ){
                    shift(13, NAME_ID_PLUS);
                }else if( code == TYPE_ID_MINUS ){
                    shift(14, NAME_ID_MINUS);
                }else if( code == TYPE_ID_RIGHT_BRACKETS ){
                    reduce(4);
                }else if( code == TYPE_ID_END ){
                    reduce(4);
                }else{
                    check_ok = false;
                }
                break;
            case 4:
                if( code == TYPE_ID_PLUS ){
                    reduce(7);
                }else if( code == TYPE_ID_MINUS ){
                    reduce(7);
                }else if( code == TYPE_ID_MULTI ){
                    shift(15, NAME_ID_MULTI);
                }else if( code == TYPE_ID_DIVISION ){
                    shift(16, NAME_ID_DIVISION);
                }else if( code == TYPE_ID_RIGHT_BRACKETS ){
                    reduce(7);
                }else if( code == TYPE_ID_END){
                    reduce(7);
                }else{
                    check_ok = false;
                }
                break;
            case 5:
                if( code != TYPE_ID_NUMBER ){
                    reduce(8);
                }else{
                    check_ok = false;
                }
                break;
            case 6:
                if( code != TYPE_ID_NUMBER ){
                    reduce(10);
                }else{
                    check_ok = false;
                }
                break;
            case 7:
                if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(10, NAME_ID_LEFT_BRACKETS);
                }else{
                    check_ok = false;
                }
                break;
            case 8:
                if( code == TYPE_ID_RIGHT_BRACKETS ){
                    shift(9, NAME_ID_RIGHT_BRACKETS);
                }else{
                    check_ok = false;
                }
                break;
            case 9:
                if( code != TYPE_ID_NUMBER ){
                    reduce(11);
                }else{
                    check_ok = false;
                }
                break;
            case 10:
                if( code == TYPE_ID_MINUS ){
                    shift(7, NAME_ID_MINUS);
                }else if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(2, NAME_ID_LEFT_BRACKETS);
                }else if( code == TYPE_ID_NUMBER ){
                    shift(6, NAME_ID_NUMBER);
                }else{
                    check_ok = false;
                }
                break;
            case 11:
                if( code == TYPE_ID_RIGHT_BRACKETS ){
                    shift(12, NAME_ID_RIGHT_BRACKETS);
                }else{
                    check_ok = false;
                }
                break;
            case 12:
                if( code != TYPE_ID_NUMBER ){
                    reduce(9);
                }else{
                    check_ok = false;
                }
                break;
            case 13:
                if( code == TYPE_ID_MINUS ){
                    shift(7, NAME_ID_MINUS);
                }else if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(2, NAME_ID_LEFT_BRACKETS);
                }else if( code == TYPE_ID_NUMBER ){
                    shift(6, NAME_ID_NUMBER);
                }else{
                    check_ok = false;
                }
                break;
            case 14:
                if( code == TYPE_ID_MINUS ){
                    shift(7, NAME_ID_MINUS);
                }else if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(2, NAME_ID_LEFT_BRACKETS);
                }else if( code == TYPE_ID_NUMBER ){
                    shift(6, NAME_ID_NUMBER);
                }else{
                    check_ok = false;
                }
                break;
            case 15:
                if( code == TYPE_ID_MINUS ){
                    shift(7, NAME_ID_MINUS);
                }else if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(2, NAME_ID_LEFT_BRACKETS);
                }else if( code == TYPE_ID_NUMBER ){
                    shift(6, NAME_ID_NUMBER);
                }else{
                    check_ok = false;
                }
                break;
            case 16:
                if( code == TYPE_ID_MINUS ){
                    shift(7, NAME_ID_MINUS);
                }else if( code == TYPE_ID_LEFT_BRACKETS ){
                    shift(2, NAME_ID_LEFT_BRACKETS);
                }else if( code == TYPE_ID_NUMBER ){
                    shift(6, NAME_ID_NUMBER);
                }else{
                    check_ok = false;
                }
                break;
            case 17:
                if( code == TYPE_ID_RIGHT_BRACKETS ){
                    reduce(2);
                }else if( code == TYPE_ID_END ){
                    reduce(2);
                }else{
                    check_ok = false;
                }
                break;
            case 18:
                if( code == TYPE_ID_RIGHT_BRACKETS ){
                    reduce(3);
                }else if( code == TYPE_ID_END ){
                    reduce(3);
                }else{
                    check_ok = false;
                }
                break;
            case 19:
                if( code == TYPE_ID_PLUS ){
                    reduce(5);
                }else if( code == TYPE_ID_MINUS ){
                    reduce(5);
                }else if( code == TYPE_ID_RIGHT_BRACKETS ){
                    reduce(5);
                }else if( code == TYPE_ID_END ){
                    reduce(5);
                }else{
                    check_ok = false;
                }
                break;
            case 20:
                if( code == TYPE_ID_PLUS ){
                    reduce(6);
                }else if( code == TYPE_ID_MINUS ){
                    reduce(6);
                }else if( code == TYPE_ID_RIGHT_BRACKETS ){
                    reduce(6);
                }else if( code == TYPE_ID_END ){
                    reduce(6);
                }else{
                    check_ok = false;
                }
                break;
            default:
                check_ok = false;
        }
    }
    if(!check_ok){
        if(!input_stack.empty()){
            int code = input_stack.top().code;
            if( code == TYPE_ID_LEFT_BRACKETS ){
                if(symbol_stack.top() == NAME_ID_NUMBER){
                    cout<<"语法错误: 不支持数字和括号连写的写法，请使用 a*(b) 的写法"<<endl;
                }else{
                    cout<<"语法错误: 左括号位置有误"<<endl;
                }
            }else if (code == TYPE_ID_RIGHT_BRACKETS){
                if(symbol_stack.top() == NAME_ID_LEFT_BRACKETS){
                    cout<<"语法错误: 括号内不能为空"<<endl;
                }else{
                    cout<<"语法错误: 存在不匹配的右括号"<<endl;
                }
            }else if( code == TYPE_ID_PLUS ){
                cout<<"语法错误: 存在位置错误的加号，加号需要跟在右括号或数字的后面"<<endl;
            }else if(code == TYPE_ID_MINUS){
                if( symbol_stack.top() == NAME_ID_MINUS ){
                    cout<<"语法错误: 如需要使用连续负号时，请使用-(x)的形式"<<endl;
                }else{
                    cout<<"语法错误: 存在位置错误的减号，减号需要跟在右括号或数字的后面"<<endl;
                }
            }else if( code == TYPE_ID_MULTI ){
                cout<<"语法错误: 存在位置错误的乘号，乘号需要跟在右括号或数字的后面"<<endl;
            }else if(code == TYPE_ID_DIVISION){
                cout<<"语法错误: 存在位置错误的除号，除号需要跟在右括号或数字的后面"<<endl;
            }else if(code ==TYPE_ID_NUMBER){
                string orign =input_stack.top().orign;
                if( symbol_stack.top() == NAME_ID_MINUS ){
                    cout<<"语法错误: 如需要使用负号,请使用以下格式: -("<<orign<<")"<<endl;
                }else{
                     cout<<"语法错误: 存在位置错误的数字: "<<orign<<endl;
                }
            }else{
                cout<<"存在语法错误"<<endl;
            }
        }else{
            cout<<"存在语法错误"<<endl;
        }
    }else{
        cout<<"语法检查正确"<<endl;
    }
    return check_ok;
}

void syntax_util::reduce(int reduce_number){
    bool no_error = true;
    switch (reduce_number) {
        case 1:
            reduce_stack_handler(1);
            symbol_stack.push(NAME_ID_S);
//            cout<<"print(A.val)"<<endl;
            break;
        case 2:
            reduce_stack_handler(3);
            symbol_stack.push(NAME_ID_A);
//            cout<<"A.val = B.val + A.val"<<endl;
            break;
        case 3:
            reduce_stack_handler(3);
            symbol_stack.push(NAME_ID_A);
//            cout<<"A.val = B.val - A.val"<<endl;
            break;
        case 4:
            reduce_stack_handler(1);
            symbol_stack.push(NAME_ID_A);
//            cout<<"A.val = B.val "<<endl;
            break;
        case 5:
            reduce_stack_handler(3);
            symbol_stack.push(NAME_ID_B);
//            cout<<"B.val = C.val * B.val"<<endl;
            break;
        case 6:
            reduce_stack_handler(3);
            symbol_stack.push(NAME_ID_B);
//            cout<<"B.val = C.val / B.val"<<endl;
            break;
        case 7:
            reduce_stack_handler(1);
            symbol_stack.push(NAME_ID_B);
//            cout<<"B.val = C.val"<<endl;
            break;
        case 8:
            reduce_stack_handler(1);
            symbol_stack.push(NAME_ID_C);
//             cout<<"C.val = D.val"<<endl;
            break;
        case 9:
            reduce_stack_handler(4);
            symbol_stack.push(NAME_ID_C);
//            cout<<"C.val = @C.val"<<endl;
            break;
        case 10:
            reduce_stack_handler(1);
            symbol_stack.push(NAME_ID_D);
//             cout<<"D.val = digital.lexval"<<endl;
            break;
        case 11:
            reduce_stack_handler(3);
            symbol_stack.push(NAME_ID_D);
            break;
        default:
            no_error = false;
            break;
    }
    if(no_error){
        int top_state = state_stack.top();
        string top_symbol = symbol_stack.top();
        switch (top_state) {
            case 0:
                if(top_symbol==NAME_ID_A){
                    state_stack.push(1);
                }else if(top_symbol == NAME_ID_B){
                    state_stack.push(3);
                }else if(top_symbol == NAME_ID_C){
                    state_stack.push(4);
                }else if(top_symbol == NAME_ID_D){
                    state_stack.push(5);
                }else{
                    check_ok = false;
                }
                break;
            case 2:
                if(top_symbol==NAME_ID_A){
                    state_stack.push(8);
                }else if(top_symbol == NAME_ID_B){
                    state_stack.push(3);
                }else if(top_symbol == NAME_ID_C){
                    state_stack.push(4);
                }else if(top_symbol == NAME_ID_D){
                    state_stack.push(5);
                }else{
                    check_ok = false;
                }
                break;
            case 10:
                if(top_symbol == NAME_ID_C){
                    state_stack.push(11);
                }else if(top_symbol == NAME_ID_D){
                    state_stack.push(5);
                }else{
                    check_ok = false;
                }
                break;
            case 13:
                if(top_symbol==NAME_ID_A){
                    state_stack.push(17);
                }else if(top_symbol == NAME_ID_B){
                    state_stack.push(3);
                }else if(top_symbol == NAME_ID_C){
                    state_stack.push(4);
                }else if(top_symbol == NAME_ID_D){
                    state_stack.push(5);
                }else{
                    check_ok = false;
                }
                break;
            case 14:
                if(top_symbol==NAME_ID_A){
                    state_stack.push(18);
                }else if(top_symbol == NAME_ID_B){
                    state_stack.push(3);
                }else if(top_symbol == NAME_ID_C){
                    state_stack.push(4);
                }else if(top_symbol == NAME_ID_D){
                    state_stack.push(5);
                }else{
                    check_ok = false;
                }
                break;
            case 15:
                if(top_symbol == NAME_ID_B){
                    state_stack.push(19);
                }else if(top_symbol == NAME_ID_C){
                    state_stack.push(4);
                }else if(top_symbol == NAME_ID_D){
                    state_stack.push(5);
                }else{
                    check_ok = false;
                }
                break;
            case 16:
                if(top_symbol == NAME_ID_B){
                    state_stack.push(20);
                }else if(top_symbol == NAME_ID_C){
                    state_stack.push(4);
                }else if(top_symbol == NAME_ID_D){
                    state_stack.push(5);
                }else{
                    check_ok = false;
                }
                break;
            default:
                check_ok = false;
                break;
        }
    }else{
        check_ok = false;
    }
}

void syntax_util::reduce_stack_handler(int count){
    for(int i = 0 ; i < count ; i ++ ){
        state_stack.pop();
    }
    for(int i = 0 ; i < count ; i ++ ){
        symbol_stack.pop();
    }
}

void syntax_util::shift(int state_number,string push_symbol){
    state_stack.push(state_number);
    symbol_stack.push(push_symbol);
    input_stack.pop();
}

int syntax_util::allocate_reg_memory(){
    return reg_memory_id ++;
}
