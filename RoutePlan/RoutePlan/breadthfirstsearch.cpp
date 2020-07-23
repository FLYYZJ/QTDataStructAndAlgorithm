#include "breadthfirstsearch.h"

BreadthFirstSearch::BreadthFirstSearch()
{}

BreadthFirstSearch::~BreadthFirstSearch()
{}

void BreadthFirstSearch::Clear()
{
    while (!m_pointQueue.empty()) {
        m_pointQueue.pop();
    }
}

void BreadthFirstSearch::DoSearch(void *maze, Point &startP, Point endP, std::vector<Point> &shortestPath)
{
    // 思路：广度优先可以一次找到最短路径，因此最先到达终点的，即为最短路径
    // 将给定的任意列数的二维数组还原为指针数组，以支持下标操作
    int** maze2d=new int*[SIZE];
    for(int i=0;i<SIZE;++i){
        maze2d[i]=static_cast<int*>(maze)+i*SIZE;
    }

    if(maze2d[startP.row][startP.col]==1||maze2d[startP.row][startP.col]==1) return ; //输入错误

    if(startP==endP){ //起点即终点
        shortestPath.push_back(startP);
        return;
    }

    //mark标记每一个节点的前驱节点，如果没有则为（-1，-1），如果有，则表示已经被访问
    Point** mark=new Point*[SIZE];
    for(int i=0;i<SIZE;++i){
        mark[i]=new Point[SIZE];
    }
    m_pointQueue.push(startP);
    //将起点的前驱节点设置为自己
    mark[startP.row][startP.col]=startP;

    while(m_pointQueue.empty()==false){
        Point pointFront=m_pointQueue.front();
        m_pointQueue.pop();

        if(pointFront.row-1>=0 && maze2d[pointFront.row-1][pointFront.col]==0){//上节点连通
            if(mark[pointFront.row-1][pointFront.col]==Point()){//上节点未被访问，满足条件，如队列
                mark[pointFront.row-1][pointFront.col]=pointFront;
                m_pointQueue.push(Point(pointFront.row-1,pointFront.col)); //入栈
                if(Point(pointFront.row-1,pointFront.col)==endP){ //找到终点
                    break;
                }
            }
        }

        if(pointFront.col+1<SIZE && maze2d[pointFront.row][pointFront.col+1]==0){//右节点连通
            if(mark[pointFront.row][pointFront.col+1]==Point()){//右节点未被访问，满足条件，如队列
                mark[pointFront.row][pointFront.col+1]=pointFront;
                m_pointQueue.push(Point(pointFront.row,pointFront.col+1));	//入栈
                if(Point(pointFront.row,pointFront.col+1)==endP){ //找到终点
                    break;
                }
            }
        }

        if(pointFront.row+1<SIZE && maze2d[pointFront.row+1][pointFront.col]==0){//下节点连通
            if(mark[pointFront.row+1][pointFront.col]==Point()){//下节点未被访问，满足条件，如队列
                mark[pointFront.row+1][pointFront.col]=pointFront;
                m_pointQueue.push(Point(pointFront.row+1,pointFront.col));	//入栈
                if(Point(pointFront.row+1,pointFront.col)==endP){ //找到终点
                    break;
                }
            }
        }

        if(pointFront.col-1>=0 && maze2d[pointFront.row][pointFront.col-1]==0){//左节点连通
            if(mark[pointFront.row][pointFront.col-1]==Point()){//上节点未被访问，满足条件，如队列
                mark[pointFront.row][pointFront.col-1]=pointFront;
                m_pointQueue.push(Point(pointFront.row,pointFront.col-1));	//入栈
                if(Point(pointFront.row,pointFront.col-1)==endP){ //找到终点
                    break;
                }
            }
        }
    }
    if(m_pointQueue.empty()==false){
        int row=endP.row;
        int col=endP.col;
        shortestPath.push_back(endP);
        while(!(mark[row][col]==startP)){
            shortestPath.push_back(mark[row][col]);
            row=mark[row][col].row;
            col=mark[row][col].col;
        }
        shortestPath.push_back(startP);
    }
    Clear();
}

