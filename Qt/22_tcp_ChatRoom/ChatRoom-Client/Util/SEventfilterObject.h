///////////////////////////////////////////
//*  @file    eventfilterobject.h
//*  @date    2021/10/02 23:16
//*  @brief   过滤器对象(窗口拖动)
//*
//*  @author  Maye(顽石老师)
//*  @contact zcmaye@gmail.com
//*  @微信公众号 C语言Plus
///////////////////////////////////////////
#ifndef EVENTFILTEROBJECT_H
#define EVENTFILTEROBJECT_H

#include <QObject>
#include <QPoint>

class  SEventFilterObject : public QObject
{
public:
    explicit SEventFilterObject(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    QPoint m_pressPos;       //左键点击的坐标
    bool m_isMoving{false}; //是否正在移动
};

#endif // EVENTFILTEROBJECT_H
