#ifndef HOMEWORK_PRIME7_SCREEN_H_
#define HOMEWORK_PRIME7_SCREEN_H_

#include <string>
using std::string;

class Screen {
public:
  Screen() = default;
  Screen(unsigned height, unsigned width)
    : height_(height)
    , width_(width)
    , contents_(height * width, ' ')
  {}
  Screen(unsigned height, unsigned width, char c)
    : height_(height)
    , width_(width)
    , contents_(height * width, c)
  {}
private:
  unsigned height_ = 0; // 屏幕高度
  unsigned width_ = 0;  // 屏幕宽度
  unsigned cursor_ = 0; // 光标的当前位置
  string contents_;     // 屏幕的内容
};
#endif