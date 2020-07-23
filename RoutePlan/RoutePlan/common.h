#ifndef COMMON_H
#define COMMON_H

/* 参考
 * https://blog.csdn.net/K346K346/article/details/51289478
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

#define LeftUpX 10
#define LeftUpY 10
#define SIZE  40  // 地图行列数
#define WIDTH 20  // 地图中每个方格的宽度

struct Point
{
    int row;
    int col;
    Point(int x, int y)
    {
        this->col = y;
        this->row = x;
    }

    Point()
    {
        this->col = this->row = 1;
    }

    bool operator !=(const Point& rhs)
    {
        if(this->row != rhs.row || this->col != rhs.col)
            return true;
        return false;
    }

    bool operator ==(const Point& rhs)
    {
        if(this->row != rhs.row || this->col != rhs.col)
            return false;
        return true;
    }
};

#endif // COMMON_H

