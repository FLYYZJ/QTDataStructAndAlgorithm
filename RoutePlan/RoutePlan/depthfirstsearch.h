#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H
#include "common.h"

class DepthFirstSearch
{
public:
    DepthFirstSearch();
    ~DepthFirstSearch();
    void DoSearch(void* maze, Point& startP, Point endP,std::vector<Point>& vecPath);

private:
    void DoSearch(void* maze, Point& startP, Point endP,
                  std::stack<Point>& pointStack,std::vector<Point>& vecPath);
    std::stack<Point> pointStack;
    Point getAdjacentNotVisitedNode(int **mapData,Point point);
};

#endif // DEPTHFIRSTSEARCH_H
