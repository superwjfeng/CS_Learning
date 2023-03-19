#pragma once

#include <iostream>
#include <string>

class Task
{
public:
    Task() : _elemOne(0), _elemTwo(0), _operator('0')
    {
    }

    Task(int one, int two, char op)
        : _elemOne(one), _elemTwo(two), _operator(op)
    {
    }

    int operator()() { //仿函数
        return run();
    }

    int run()
    { // 执行任务
        int result = 0;
        switch (_operator)
        {
        case '+':
            result = _elemOne + _elemTwo;
            break;
        case '-':
            result = _elemOne - _elemTwo;
            break;
        case '*':
            result = _elemOne * _elemTwo;
            break;
        case '/':
        {
            if (_elemTwo == 0)
            {
                std::cout << "div zero, abort" << std::endl;
                result = -1;
            }
            else
            {
                result = _elemOne / _elemTwo;
            }
        }
        break;
        case '%':
        {
            if (_elemTwo == 0)
            {
                std::cout << "mod zero, abort" << std::endl;
                result = -1;
            }
            else
            {
                result = _elemOne % _elemTwo;
            }
        }
        break;
        default:
            std::cout << "非法操作：" << _operator << std::endl;
            break;
        }

        return result;
    }
    int get(int *e1, int *e2, char *op) {
        *e1 = _elemOne;
        *e2 = _elemTwo;
        *op = _operator;
    }
private:
    int _elemOne;
    int _elemTwo;
    char _operator;
};