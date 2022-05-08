#include "components.h"

#include <QTimer>
#include <QGraphicsScene>

CCannon::CCannon(EColor eColor, QGraphicsItem *pParent)
{
    SetColor(eColor);
}

void CCannon::Shoot()
{
    CBullet* pBullet = new CBullet(m_eColor);
    connect(pBullet, &CBullet::sigIncreaseScore, this, &CCannon::sigIncreaseScore);
    connect(pBullet, &CBullet::sigDecreaseScore, this, &CCannon::sigDecreaseScore);

    pBullet->setPos(x() + 27, y() - 10);
    scene()->addItem(pBullet);
}

EColor CCannon::GetColor() const
{
    return m_eColor;
}

// Setting the color of the Cannon
void CCannon::SetColor(EColor eColor)
{
    m_eColor = eColor;
    switch (eColor){
    case EColor::Red:{
        QPixmap oPixmap(":/Resources/RedCannon.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor::Pink:{
        QPixmap oPixmap(":/Resources/PinkCannon.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor:: Blue:{
        QPixmap oPixmap(":/Resources/BlueCannon.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    default:{
        QPixmap oPixmap(":/Resources/RedCannon.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    }
}

CAlien::CAlien(EColor eColor, QGraphicsItem *pParent): QGraphicsPixmapItem(pParent)
{
    SetColor(eColor);
    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CAlien:: onMove);
    pTimer->start(gAlienSpeed);
}

EColor CAlien::GetColor() const
{
    return m_eColor;
}

void CAlien::SetColor(EColor eColor)
{
    m_eColor = eColor;
    switch(eColor){

    case EColor::Red:{
        QPixmap oPixmap(":/Resources/RedAlien.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor::Pink:{
        QPixmap oPixmap(":/Resources/PinkAlien.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor:: Blue:{
        QPixmap oPixmap(":/Resources/BlueAlien.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    }
}

void CAlien::onMove()
{
    setPos(x(), y()+5);

    if(pos().y() >= (scene()->height() - gCannonSize.height())) {
        scene()-> removeItem(this);
        emit sigDecreaseHealth();
        delete this;
    }

    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    for(auto const pItem : lstCollidingItem){
        if(dynamic_cast<CCannon*>(pItem))
            emit sigGameOver();
        // comment
    }
}


CBullet::CBullet(EColor eColor, QGraphicsItem *pParent)
{

}

EColor CBullet::GetColor() const
{

}

void CBullet::SetColor(EColor eColor)
{

}

void CBullet::onMove()
{

}

CPoints::CPoints(QGraphicsItem *pParent)
{

}
