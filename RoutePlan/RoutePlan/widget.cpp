#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    comboSelectRoutePlanAlg = new QComboBox(this);
    comboSelectRoutePlanAlg->setGeometry(850, 200, 200, 60);
    comboSelectRoutePlanAlg->addItem("选择搜索算法");
    comboSelectRoutePlanAlg->addItem("深度优先搜索");
    comboSelectRoutePlanAlg->addItem("广度优先搜索");
    comboSelectRoutePlanAlg->addItem("A*算法");
    this->setWindowTitle("路径规划算法demo");
    btnBeginRoutePlan = new QPushButton(this);
    btnBeginRoutePlan->setGeometry(850, 300, 200, 60);
    btnBeginRoutePlan->setText("开始搜索");

    btnResetMap = new QPushButton(this);
    btnResetMap->setGeometry(850, 400, 200, 60);
    btnResetMap->setText("重置地图");

    connect(btnResetMap, SIGNAL(clicked()), this, SLOT(ResetMap()));
    connect(btnBeginRoutePlan, SIGNAL(clicked()), this, SLOT(BeginSearch()));

    SetMap();
//    m_mapData[m_beginPointX][0] = RUNNER;
//    m_mapData[m_endPointX][SIZE-1] = DESTINATION;

}

void Widget::ResetMap()
{
    SetMap();
}

inline void Widget::SetMap()
{
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
            m_mapData[i][j] = 0;
    }
    m_beginPointX = qrand() % SIZE;
    m_endPointX = qrand() % SIZE;
    m_vecPath.clear();
    update();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *)
{
    mapPainter = new QPainter;
    mapPainter->begin(this);
    mapPainter->setPen(QPen(Qt::blue,3, Qt::SolidLine));
    mapPainter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    for(int i = 0; i < SIZE; i++)
    {
        mapPainter->drawLine(LeftUpX, LeftUpY + WIDTH * i, LeftUpX + WIDTH * (SIZE - 1), LeftUpY + WIDTH * i);
    }

    for(int i = 0; i < SIZE; i++)
    {
        mapPainter->drawLine(LeftUpX + WIDTH * i, LeftUpY, LeftUpX + WIDTH * i, LeftUpY + WIDTH * (SIZE - 1));
    }
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
        {
            int x_ = LeftUpX + i * WIDTH;
            int y_ = LeftUpY + j * WIDTH;
            if(m_mapData[i][j] == OBSTACLE)
            {
                mapPainter->setPen(QPen(Qt::blue ,3 ,Qt::SolidLine));
                mapPainter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
                mapPainter->drawRect(x_,y_,WIDTH,WIDTH);
            }
            else
            {
                mapPainter->setPen(QPen(Qt::blue,3, Qt::SolidLine));
                mapPainter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
                mapPainter->drawRect(x_,y_,WIDTH,WIDTH);
            }
            if((i == m_beginPointX && j == 0) || m_mapData[i][j] == RUNNER)
            {
                mapPainter->setPen(QPen(Qt::blue,3, Qt::SolidLine));
                mapPainter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
                mapPainter->drawRect(x_,y_,WIDTH,WIDTH);
            }
            if(i == m_endPointX && j == SIZE-1)
            {
                mapPainter->setPen(QPen(Qt::blue,3, Qt::SolidLine));
                mapPainter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                mapPainter->drawRect(x_,y_,WIDTH,WIDTH);
            }
        }
    mapPainter->end();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        int x = event->x();
        int y = event->y();
        if(x < LeftUpX || x > LeftUpX + SIZE * WIDTH || y < LeftUpY || y > LeftUpY + SIZE * WIDTH)
            return;
        int i = (x - LeftUpX) / WIDTH;
        int j = (y - LeftUpY) / WIDTH;
        m_mapData[i][j] = OBSTACLE;
    }
    else if(event->button() == Qt::RightButton)
    {
        int x = event->x();
        int y = event->y();
        if(x < LeftUpX || x > LeftUpX + SIZE * WIDTH || y < LeftUpY || y > LeftUpY + SIZE * WIDTH)
            return;
        int i = (x - LeftUpX) / WIDTH;
        int j = (y - LeftUpY) / WIDTH;
        m_mapData[i][j] = 0;
    }
    update();

}

void Widget::BeginSearch()
{
    int currentAlg = this->comboSelectRoutePlanAlg->currentIndex();

    Point startPoint(m_beginPointX, 0);
    Point endPoint(m_endPointX, SIZE-1);
    switch (currentAlg)
    {
    case 1:
        m_dfs.DoSearch(m_mapData,startPoint, endPoint, m_vecPath);
        break;
    case 2:
        m_bfs.DoSearch(m_mapData, startPoint, endPoint, m_vecPath);
        break;
    case 3:
        break;
    }
    for(auto iter = m_vecPath.begin(); iter != m_vecPath.end(); iter++)
    {
        m_mapData[iter->row][iter->col] = RUNNER;
    }
    update();
    //QMessageBox::warning(this, "hello", "world");
}
