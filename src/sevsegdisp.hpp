#pragma once

#include <vector>
#include <cmath>
#include <string>


const std::string numbers[10][5] = {
    {
        "╻══╻",
        "║  ║",
        "║  ║",
        "║  ║",
        "╹══╹"
    },

    {
        "   ╻",
        "   ║",
        "   ║",
        "   ║",
        "   ╹"
    },

    {
        " ══╻",
        "   ║",
        "╻══╹",
        "║   ",
        "╹══ "
    },

    {
        " ══╻",
        "   ║",
        " ══║",
        "   ║",
        " ══╹"
    }, 

    {
        "╻  ╻",     
        "║  ║",     
        "╹══║",     
        "   ║",     
        "   ╹"
    },

    {
        "╻══ ",
        "║   ",
        "╹══╻",
        "   ║",
        " ══╹"
    },

    {
        "╻══ ",
        "║   ",
        "║══╻",
        "║  ║",
        "╹══╹"
    },

    {
        " ══╻",
        "   ║",
        "   ║",
        "   ║",
        "   ╹"
    },

    {
        "╻══╻",
        "║  ║",
        "║══║",
        "║  ║",
        "╹══╹"
    },
    
    {
        "╻══╻",
        "║  ║",
        "╹══║",
        "   ║",
        " ══╹"
    }

};

class SevSegDisp{
    public:
        SevSegDisp(int,int);
        
        void operator ++(){
            if(number > int(std::pow(10, noOfDigits)) - 1) return;
            else ++number;
        }

        void operator --(){
            if(number) --number;
        }
        
        void set(int);
        void update(const std::string&);

    
    private:
    int noOfDigits;
    int number;
};

extern SevSegDisp flagDisplay;

