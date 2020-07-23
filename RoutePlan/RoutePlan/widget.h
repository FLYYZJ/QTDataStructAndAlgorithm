#ifndef WIDGET_H
#define WIDGET_H



#include <QWidget>
#include <QPainter>
#include <QComboBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTime>

#include "depthfirstsearch.h"
#include "breadthfirstsearch.h"

enum ItemType
{
    DESTINATION = -2,
    RUNNER = -3,
    OBSTACLE = -1
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

public slots:
    void BeginSearch();
    void ResetMap();
private:
    Ui::Widget *ui;
    QComboBox *comboSelectRoutePlanAlg;
    QPushButton *btnBeginRoutePlan;
    QPushButton *btnResetMap;
    QPainter *mapPainter;
    int m_mapData[SIZE][SIZE];  // 0 表示无障碍，1表示障碍，2表示物体，3表示出口
    DepthFirstSearch m_dfs;
    BreadthFirstSearch m_bfs;
    int m_beginPointX;
    int m_endPointX;
    std::vector<Point> m_vecPath;
protected:
    void paintEvent(QPaintEvent *) override;
    void SetMap();
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // WIDGET_H
