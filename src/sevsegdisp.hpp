#pragma once

#include <vector>
#include <cmath>
#include <string>

/// 类数量定义操作类

/// 数字字模
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

class SevSegDisp {
public:
    SevSegDisp(int, int);

    void operator ++() {
        if (number > int(std::pow(10, noOfDigits)) - 1) return;
        else ++number;
    }

    void operator --() {
        if (number) --number;
    }

    void set(int);

    void update(const std::string &) const;

private:
    int noOfDigits;
    int number;
};

extern SevSegDisp flagDisplay;

