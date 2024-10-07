#pragma once

#include <vector>

/**
 * 输出缓冲类，用于屏幕防闪
 */
class Buffer
{
  public:
    Buffer();
    friend Buffer &operator<<(Buffer &curr, const std::string &str); // 重载输出，使其与cout用法相似
    void goToLine(int); // 切换输出列
    int getCurrLine() const; // 获取当前列
    void display(); // 输出当前缓冲内容到stdout
    void clear(); // 清除缓冲内容

  private:
    int line;
    std::vector<std::string> buf;
    int size;
};

extern Buffer writeBuffer;

