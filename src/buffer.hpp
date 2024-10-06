#pragma once

#include <vector>

// 写入缓冲
class Buffer
{
  public:
    Buffer();
    friend Buffer &operator<<(Buffer &curr, const std::string &str);
    void goToLine(int);
    int getCurrLine() const;
    void display();
    void clear();

  private:
    int line;
    std::vector<std::string> buf;
    int size;
};

extern Buffer writeBuffer;

