//
//  lexical_util
//  Complier Ex
//
//  Created by Ou Sheobin on 2017/12/21.
//  Copyright © 2017年 Ou Sheobin. All rights reserved.
//

#include <vector>
#include <iostream>
#include "lexical_util.h"
#include "constants.h"

using namespace std;

bool lexical_util::check(string target, vector<symbol> * symbol_vector){
    int index = 0;
    string errorInfo = "";
    int errorCount = 1;
    while(index < target.length()){
        string output = "";
        int innerIndex = index;
        char character = target[innerIndex];
        if( character == '0' ){
            output.append("0");
            if(innerIndex == target.length()-1){
                int result = 0;
                symbol symb(TYPE_ID_INTEGER,"0",result,NAME_ID_MINUS);
                symbol_vector->push_back(symb);
                break;
            }
            character = target[++innerIndex];
            if(checkIsSymbol(character)){
                int result = 0;
                //                cout<<"(5,"<<result<<","<<result<<",int)"<<endl;
                symbol symb(TYPE_ID_INTEGER,"0",result,NAME_ID_MINUS);
                symbol_vector->push_back(symb);
            }else if( checkIsNumber(character) ){
                while(innerIndex<target.length()){
                    character = target[innerIndex];
                    if(checkIsNumber(character)){
                        output.append(1,character);
                        innerIndex ++;
                        continue;
                    }else{
                        break;
                    }
                }
                index = innerIndex;
                stringstream errorDetail;
                errorDetail << "错误"<<(errorCount++)<<"："<<output<<" 不是一个合法的整形数#"<<innerIndex<<")\n";
                errorInfo.append(errorDetail.str());
            }else if( character == '.' ){
                if( innerIndex == target.length() -1){
                    stringstream errorDetail;
                    errorDetail << "错误"<<(errorCount++)<<"：'"<<output<<".' 不是一个合法的浮点数 (位置#"<<innerIndex<<")\n";
                    errorInfo.append(errorDetail.str());
                    break;
                }
                output.append(".");
                character = target[++innerIndex];
                bool findNotNumber = false;
                if(checkIsNumber(character)){
                    while(innerIndex<target.length()){
                        character = target[innerIndex];
                        if(checkIsNumber(character)){
                            output.append(1,character);
                            innerIndex ++;
                            continue;
                        }else{
                            findNotNumber = true;
                            break;
                        }
                    }
                    if(checkIsSymbol(character) || !findNotNumber){
                        double result = stof(output);
                        //                        cout<<"(8,"<<output<<","<<output<<",double)"<<endl;
                        symbol symb(TYPE_ID_FLOAT,output,result,NAME_ID_FLOAT);
                        symbol_vector->push_back(symb);
                        index = innerIndex;
                        continue;
                    } else if( character == '.'){
                        stringstream errorDetail;
                        errorDetail << "错误"<<(errorCount++)<<"：'"<<output<<".' 不是一个合法的浮点数 (位置#"<<innerIndex<<")\n";
                        errorInfo.append(errorDetail.str());
                        index = innerIndex + 1;
                        continue;
                    } else {
                        double result = stof(output);
                        //                        cout<<"(8,"<<output<<","<<output<<",double)"<<endl;
                        symbol symb(TYPE_ID_FLOAT,output,result,NAME_ID_FLOAT);
                        symbol_vector->push_back(symb);
                        index = innerIndex;
                        stringstream errorDetail;
                        errorDetail << "错误"<<(errorCount++)<<"：存在不可识别的字符'"<<character<<"'(位置#"<<innerIndex<<")\n";
                        errorInfo.append(errorDetail.str());
                        index = innerIndex;
                    }
                }else{
                    output.erase(output.end()-1);
                    int result = stoi(output);
                    //                    cout<<"(5,"<<output<<","<<output<<",int)"<<endl;
                    symbol symb(TYPE_ID_INTEGER,output,result,NAME_ID_INTEGER);
                    symbol_vector->push_back(symb);
                    index = innerIndex - 1;
                    continue;
                }
            }else {
                int result = stoi(output);
                //                cout<<"(5,"<<output<<","<<output<<",int)"<<endl;
                symbol symb(TYPE_ID_INTEGER,output,result,NAME_ID_INTEGER);
                symbol_vector->push_back(symb);
                stringstream errorDetail;
                errorDetail << "错误"<<(errorCount++)<<"：存在不可识别的字符'"<<character<<"'(位置#"<<innerIndex<<")\n";
                errorInfo.append(errorDetail.str());
                index = innerIndex;
            }
        } else if (checkIsNotZeroNumber(character)){
            bool findNotNumber = false;
            while (innerIndex < target.length()) {
                character = target[innerIndex];
                if(checkIsNumber(character)){
                    output.append(1,character);
                }else{
                    findNotNumber = true;
                    break;
                }
                innerIndex ++;
            }
            if(checkIsSymbol(character) || !findNotNumber){
                int result = stoi(output);
                //                cout<<"(5,"<<output<<","<<output<<",int)"<<endl;
                symbol symb(TYPE_ID_INTEGER,output,result,NAME_ID_INTEGER);
                symbol_vector->push_back(symb);
                index = innerIndex;
                index = innerIndex;
                continue;
            } else if(character == '.'){
                if( innerIndex == target.length() -1){
                    int result = stof(output);
                    //                    cout<<"(8,"<<result<<","<<result<<",int)"<<endl;
                    symbol symb(TYPE_ID_INTEGER,output,result,NAME_ID_INTEGER);
                    symbol_vector->push_back(symb);
                    index = innerIndex;
                    stringstream errorDetail;
                    errorDetail << "错误"<<(errorCount++)<<"：小数点后没有数字(位置#"<<innerIndex<<")\n";
                    errorInfo.append(errorDetail.str());
                    break;
                }
                output.append(1,character);
                character = target[++innerIndex];
                if(checkIsNumber(character)){
                    findNotNumber = false;
                    while( innerIndex < target.length()){
                        character = target[innerIndex];
                        if(checkIsNumber(character)){
                            output.append(1,character);
                        }else{
                            findNotNumber = true;
                            break;
                        }
                        innerIndex ++;
                    }
                    if(checkIsSymbol(character) || !findNotNumber){
                        double result = stof(output);
                        //                        cout<<"(8,"<<output<<","<<output<<",double)"<<endl;
                        symbol symb(TYPE_ID_FLOAT,output,result,NAME_ID_FLOAT);
                        symbol_vector->push_back(symb);
                        index = innerIndex;
                        continue;
                    } else if(character == '.') {
                        stringstream errorDetail;
                        errorDetail << "错误"<<(errorCount++)<<"：'"<<output<<".' 不是一个合法的浮点数 (位置#"<<innerIndex<<")\n";
                        errorInfo.append(errorDetail.str());
                        index = innerIndex + 1;
                        continue;
                    } else {
                        double result = stof(output);
                        symbol symb(TYPE_ID_FLOAT,output,result,NAME_ID_FLOAT);
                        symbol_vector->push_back(symb);
                        //                        cout<<"(8,"<<output<<","<<output<<",double)"<<endl;
                        stringstream errorDetail;
                        errorDetail << "错误"<<(errorCount++)<<"：存在不可识别的字符"<<character<<"(位置#"<<innerIndex<<")\n";
                        errorInfo.append(errorDetail.str());
                        index = innerIndex;
                    }
                } else {
                    output.erase(output.end()-1);
                    int result = stoi(output);
                    //                    cout<<"(5,"<<output<<","<<output<<",int)"<<endl;
                    symbol symb(TYPE_ID_INTEGER,output,result,NAME_ID_INTEGER);
                    symbol_vector->push_back(symb);
                    index = innerIndex - 1;
                    continue;
                }
            } else{
                int result = stoi(output);
                //                cout<<"(5,"<<output<<","<<output<<",int)"<<endl;
                symbol symb(TYPE_ID_INTEGER,output,result,NAME_ID_INTEGER);
                symbol_vector->push_back(symb);
                stringstream errorDetail;
                errorDetail << "错误"<<(errorCount++)<<"：存在不可识别的字符"<<character<<"(位置#"<<innerIndex<<")\n";
                errorInfo.append(errorDetail.str());
                index = innerIndex;
            }
        } else if( character == '+' ){
            //            cout << "(1,+,NULL,NULL)" << endl;
            symbol symb(TYPE_ID_PLUS,NAME_ID_PLUS);
            symbol_vector->push_back(symb);
        } else if( character == '-' ){
            //            cout << "(2,-,NULL,NULL)" << endl;
            symbol symb(TYPE_ID_MINUS,NAME_ID_MINUS);
            symbol_vector->push_back(symb);
        } else if( character == '*' ){
            //            cout << "(3,*,NULL,NULL)" << endl;
            symbol symb(TYPE_ID_MULTI,NAME_ID_MULTI);
            symbol_vector->push_back(symb);
        } else if( character == '/' ){
            //            cout << "(4,/,NULL,NULL)" << endl;
            symbol symb(TYPE_ID_DIVISION,NAME_ID_DIVISION);
            symbol_vector->push_back(symb);
        } else if( character == '(' ){
            //            cout << "(6,(,NULL,NULL)" << endl;
            symbol symb(TYPE_ID_LEFT_BRACKETS,NAME_ID_LEFT_BRACKETS);
            symbol_vector->push_back(symb);
        } else if( character == ')' ){
            //            cout << "(7,),NULL,NULL)" << endl;
            symbol symb(TYPE_ID_RIGHT_BRACKETS,NAME_ID_RIGHT_BRACKETS);
            symbol_vector->push_back(symb);
        }else if( character == '.' ){
            bool findNumber = false;
            innerIndex ++;
            while( innerIndex < target.length()){
                character = target[innerIndex];
                if(checkIsNumber(character)){
                    output.append(1,character);
                    findNumber = true;
                }else{
                    break;
                }
                innerIndex ++;
            }
            stringstream errorDetail;
            errorDetail << "错误"<<(errorCount++)<<"：浮点数 '."<<output<<"' 缺少整数部分 (位置#"<<innerIndex<<")\n";
            errorInfo.append(errorDetail.str());
            index = innerIndex - 1;
        } else{
            stringstream errorDetail;
            errorDetail << "错误"<<(errorCount++)<<"：存在不可识别的字符"<<character<<"(位置#"<<innerIndex<<")\n";
            errorInfo.append(errorDetail.str());
            index = innerIndex ++;
        }
        index ++;
    }
    if(errorCount > 1){
        cout << "表达式存在"<<(errorCount-1)<< "处错误"<<endl;
        cout<<errorInfo<<endl;
        return false;
    } else{
        cout << "表达式词法检查正确"<<endl;
        return true;
    }
}

bool lexical_util::checkIsNumber(char param){
    return (param >='0' && param <= '9');
}

bool lexical_util::checkIsNotZeroNumber(char param){
    return (param >'0' && param <= '9');
}

bool lexical_util::checkIsSymbol(char param){
    bool is_symbol = false;
    switch(param){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')': is_symbol = true; break;
        default : is_symbol = false;
    }
    return is_symbol;
}



