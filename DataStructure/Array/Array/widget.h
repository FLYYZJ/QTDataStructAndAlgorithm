#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QPainter>
#include "dynamicarray.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;
    DynamicArray<int>* m_dynamicArray = nullptr;

// 控件
private:
    void DynamicArrayPaint();

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void on_pushButton_InitArray_clicked();
    void on_pushButton_SetValue_clicked();
    void on_pushButton_SetLength_clicked();
};

#endif // WIDGET_H
