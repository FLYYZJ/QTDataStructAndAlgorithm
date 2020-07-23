#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch()
{
}

DepthFirstSearch::~DepthFirstSearch()
{
}

void DepthFirstSearch::DoSearch(void* maze, Point& startP, Point endP,std::vector<Point>& vecPath)
{
    DoSearch(maze, startP, endP, pointStack, vecPath);
}


void DepthFirstSearch::DoSearch(void* maze, Point& startP, Point endP,
                                std::stack<Point>& pointStack,std::vector<Point>& vecPath)
{
    //将给定的任意列数的二维数组还原为指针数组，以支持下标操作
        int** maze2d=new int*[SIZE];
        for(int i=0;i<SIZE;++i)
        {
            maze2d[i]=static_cast<int*>(maze)+i*SIZE;
        }

        //输入错误
        if(maze2d[startP.row][startP.col] == -1 || maze2d[endP.row][endP.col] == -1)
        {
            return;
        }

        //建立各个节点访问标记，表示结点到到起点的权值，也记录了起点到当前结点路径的长度
        int** mark=new int*[SIZE];
        for(int i=0;i<SIZE;++i)
        {
            mark[i]=new int[SIZE];
        }
        for(int i=0;i<SIZE;++i)
        {
            for(int j=0;j<SIZE;++j)
            {
                mark[i][j] = *(static_cast<int*>(maze)+i*SIZE+j);
            }
        }

        //起点等于终点
        if(startP==endP)
        {
            vecPath.push_back(startP);
            return;
        }

        //增加一个终点的已被访问的前驱结点集
        std::vector<Point> visitedEndPointPreNodeVec;

        //将起点入栈
        pointStack.push(startP);
        mark[startP.row][startP.col] = 1;

        //栈不空并且栈顶元素不为结束节点
        while(pointStack.empty() == false)
        {
            Point adjacentNotVisitedNode=getAdjacentNotVisitedNode(mark,pointStack.top());

            //没有符合条件的相邻结点
            if(adjacentNotVisitedNode.row==-1)
            {
                //回溯到上一个节点，继续深度搜索
                pointStack.pop();
                continue;
            }

            //以较短的路径，找到了终点
            if(adjacentNotVisitedNode == endP)
            {
                mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = mark[pointStack.top().row][pointStack.top().col] + 1;
                pointStack.push(endP);
                std::stack<Point> pointStackTemp=pointStack;
                vecPath.clear();
                while (pointStackTemp.empty() == false)
                {
                    //vecPath 存放的是逆序路径
                    vecPath.push_back(pointStackTemp.top());
                    pointStackTemp.pop();
                }
                pointStack.pop(); //将终点出栈
                continue;
            }

            //入栈并设置结点权值
            mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col]=mark[pointStack.top().row][pointStack.top().col]+1;
            pointStack.push(adjacentNotVisitedNode);
        }
}

Point DepthFirstSearch::getAdjacentNotVisitedNode(int** mapData,Point point)
{
    Point resP(-1, -1);
    if(point.row - 1 >= 0)
    {
        if(mapData[point.row-1][point.col] == 0   // 不是障碍
                || mapData[point.row][point.col] + 1 < mapData[point.row-1][point.col]) //表明走这一步比之前更好
        {
            resP.row = point.row - 1;
            resP.col = point.col;
            return resP;
        }
    }

    if(point.row + 1 < SIZE)
    {
        if(mapData[point.row+1][point.col] == 0   // 不是障碍
                || mapData[point.row][point.col] + 1 < mapData[point.row+1][point.col])
        {
            resP.row = point.row + 1;
            resP.col = point.col;
            return resP;
        }
    }

    if(point.col - 1 >= 0)
    {
        if(mapData[point.row][point.col-1] == 0   // 不是障碍
                || mapData[point.row][point.col] + 1 < mapData[point.row][point.col-1])
        {
            resP.row = point.row;
            resP.col = point.col - 1;
            return resP;
        }
    }

    if(point.col + 1 < SIZE)
    {
        if(mapData[point.row][point.col + 1] == 0   // 不是障碍
                || mapData[point.row][point.col] + 1 < mapData[point.row][point.col + 1])
        {
            resP.row = point.row;
            resP.col = point.col + 1;
            return resP;
        }
    }
    return  resP;
}
