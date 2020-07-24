#include "widget.h"
#include "ui_widget.h"




Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->widgetDynamicArrayShow->installEventFilter(this);

}

Widget::~Widget()
{
    delete ui;
}


bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(m_dynamicArray != nullptr && watched == ui->widgetDynamicArrayShow && event->type() == QEvent::Paint)
    {
        DynamicArrayPaint();

    }
    return QWidget::eventFilter(watched, event);
}

void Widget::DynamicArrayPaint()
{

    const int *data = m_dynamicArray->Data();
    unsigned int length = m_dynamicArray->Length();
    QPainter painter(ui->widgetDynamicArrayShow);
    QPen pen(Qt::blue);
    QBrush brush(Qt::red, Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.begin(ui->widgetDynamicArrayShow);
    int row_count = 1;
    int col_count = 0;
    for(unsigned int i = 0; i < length; i++)
    {
        painter.drawRect(LeftUpX + WIDTH * static_cast<int>(col_count), LeftUpY + WIDTH * row_count, WIDTH, WIDTH);
        painter.drawText(LeftUpX + WIDTH * static_cast<int>(col_count) + WIDTH / 2, LeftUpY + WIDTH / 2 + WIDTH * row_count, "0");
        if(i % 10 == 0 && i != 0)
        {
            row_count += 1;
            col_count = 0;
        }
        else
        {
            col_count ++;
        }
    }
    painter.end();

}

void Widget::on_pushButton_InitArray_clicked()
{
    if(m_dynamicArray != nullptr)
    {
        delete m_dynamicArray;
        m_dynamicArray = nullptr;
    }
    QString init_length = ui->lineEdit_Length->text();
    int i_initl;
    try
    {
        if(init_length == "")
            i_initl = 10;
        else
            i_initl = init_length.toInt();
    }
    catch (...)
    {
        QMessageBox::warning(this, "错误", "请输入合法数值");
        return;
    }
    m_dynamicArray = new DynamicArray<int>(static_cast<uint>(i_initl));
    for(uint i = 0; i<m_dynamicArray->Length(); i++)
    {
        m_dynamicArray[i] = 0;
    }
    update();
}

void Widget::on_pushButton_SetValue_clicked()
{

}

void Widget::on_pushButton_SetLength_clicked()
{

}
