#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H
#include "common.h"

class BreadthFirstSearch
{
public:
    BreadthFirstSearch();
    ~BreadthFirstSearch();
    void DoSearch(void* maze, Point& startP, Point endP,std::vector<Point>& vecPath);
    void Clear();
private:
    std::queue<Point> m_pointQueue;
};

#endif // BREADTHFIRSTSEARCH_H
