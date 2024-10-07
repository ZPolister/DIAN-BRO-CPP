//
// Created by Polister on 2024/10/6.
//

#include "sevsegdisp.hpp"
#include "buffer.hpp"
#include "colour.hpp"
#include "setup.hpp"

SevSegDisp::SevSegDisp(int dig, int n){
    noOfDigits = dig;
    number = n;
}

void SevSegDisp::set(int n){
    number = n;
}

void SevSegDisp::update(const std::string& prepend) const {
    int homeLine = writeBuffer.getCurrLine();
    int nos[noOfDigits];
    int num = number;
    int dig = noOfDigits;
    while(num || dig){
        nos[dig-1] = num % 10;
        num /= 10;
        --dig;
    }
    for(int i = 0; i < noOfDigits; ++i){
        for(const auto& str : numbers[nos[i]]){
            if(!i) writeBuffer << reset << prepend;
            writeBuffer << red_fg << str << " " << endl << reset;
        }
        if(i != noOfDigits -1) writeBuffer.goToLine(homeLine);
    }
}

SevSegDisp flagDisplay(5, 0);