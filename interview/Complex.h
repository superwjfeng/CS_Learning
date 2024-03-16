/**
 * @file Complex.h
 * @author Weijian Feng (wj.feng@tum.de)
 * @brief 实现一个 Complex 复数类：包括复数的 +,-,*,/,+=,-=,*=,/=,
 * 前置++,后置++,前置--,后置--,==(条件判断)，!=,>,<=,=(赋值操作符)
 *
 * 注意点：只能提供一个默认构造
 * += 要返回引用，+返回值
 *
 * https://blog.csdn.net/qq_34328833/article/details/52115612
 * @version 0.1
 * @date 2024-02-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cmath>
#include <iostream>

class Complex {
 public:
  Complex(double x = 0.0, double y = 0.0) : _real(x), _image(y) {}
  Complex(const Complex& rhs) : _real(rhs._real), _image(rhs._image) {}
  ~Complex() {}

  Complex& operator=(const Complex& rhs) {
    if (this != &rhs) {
      _real = rhs._real;
      _image = rhs._image;
    }
    return *this;
  }

  void print() {
    std::cout << "<real: " << _real << ", image: " << _image << ">"
              << std::endl;
  }

 public:
  Complex operator+(const Complex& rhs) {
    Complex tmp = *this;  // 也是拷贝构造
    tmp._real += rhs._real;
    tmp._image += rhs._image;
    return tmp;
  }

  Complex operator-(const Complex& rhs) {
    Complex tmp = *this;
    tmp._real -= rhs._real;
    tmp._image -= rhs._image;
    return tmp;
  }

  /**
   * @brief 复数乘法的规则是 (a+bi)*(c+di)
   * = ac-bd + (ad+bc)i
   *
   * @param rhs
   * @return Complex
   */
  Complex operator*(const Complex& rhs) {
    double real = _real * rhs._real - _image * rhs._image;
    double image = _real * rhs._image + _image * rhs._real;
    return {real, image};
  }

  /**
   * @brief 复数除法的规则比较复杂 (a+bi)/(c+di)
   * = (ac+bd) + (bc-ad)i/ (c^2 + d^2)
   * @param rhs
   * @return Complex
   */
  Complex operator/(const Complex& rhs) {
    double real = (_real * rhs._real + _image * rhs._image) /
               (rhs._real * rhs._real + rhs._image * rhs._image);
    double image = (_image * rhs._real - _real * rhs._image) /
                (rhs._real * rhs._real + rhs._image * rhs._image);
    return {real, image};
  }

  Complex& operator+=(const Complex& rhs) {
    _real += rhs._real;
    _image += rhs._image;
    return *this;
  }

  Complex& operator-=(const Complex& rhs) {
    _real -= rhs._real;
    _image -= rhs._image;
    return *this;
  }

  Complex& operator*=(const Complex& rhs) {
    _real = _real * rhs._real - _image * rhs._image;
    _image = _real * rhs._image + _image * rhs._real;
    return *this;
  }

  Complex& operator/=(const Complex& rhs) {
    double dividor = rhs._real * rhs._real + rhs._image * rhs._image;
    _real = (_real * rhs._real - _image * (-rhs._image)) / dividor;
    _image = (_real * (-rhs._image) + _image * rhs._real) / dividor;
    return *this;
  }

  /**
   * @brief 无参是前置++
   *
   * @return Complex&
   */
  Complex& operator++() {
    _real++;
    _image++;
    return *this;
  }

  /**
   * @brief 后置++，要保存原来的值
   *
   * @return Complex
   */
  Complex operator++(int) {
    Complex tmp(*this);
    _real++;
    _image++;
    return tmp;
  }

  Complex& operator--() {
    _real--;
    _image--;
    return *this;
  }

  Complex operator--(int) {
    Complex tmp(*this);
    _real--;
    _image--;
    return tmp;
  }

  bool operator==(const Complex& rhs) {
    return _real == rhs._real && _image == rhs._image;
  }

  bool operator>(const Complex& rhs) {
    return _real > rhs._real && _image > rhs._image;
  }

  bool operator<=(const Complex& rhs) { return *this > rhs; }

 private:
  double _real;
  double _image;
};

void test() {
  Complex a(1, 2);
  Complex b(2, 3);
  a.print();
  b.print();
  Complex c;
  c = a + b;
  c.print();
}