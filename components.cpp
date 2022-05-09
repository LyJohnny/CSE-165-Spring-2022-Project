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
        QPixmap oPixmap(":/Resources/Ammon_HepworthRed.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor::Pink:{
        QPixmap oPixmap(":/Resources/Ammon_HepworthPink.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor:: Blue:{
        QPixmap oPixmap(":/Resources/Ammon_HepworthBlue.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    default:{
        QPixmap oPixmap(":/Resources/Ammon_HepworthRed.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        m_eColor = EColor::Red;

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
        QPixmap oPixmap(":/Resources/SpaceInvadersRed.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor::Pink:{
        QPixmap oPixmap(":/Resources/ScaredStudentPink.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    case EColor:: Blue:{
        QPixmap oPixmap(":/Resources/AsleepStudent.png"); // Change it with Stewart's drawing
        setPixmap(oPixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
        break;
    }
    }
}

void CAlien::onMove()
{
    setPos(x(), y()+3);

    if (pos().y() >= (scene()->height() - gCannonSize.height())) {
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
    SetColor(eColor);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CBullet::onMove);
    pTimer->start(gBulletSpeed);
}

EColor CBullet::GetColor() const
{
    return m_eColor;
}

void CBullet::SetColor(EColor eColor)
{
    m_eColor = eColor;

    switch (eColor){
        case EColor::Red:{
            QPixmap oPixmap(":/Resources/textBeamPolymorphismRed.png");
            setPixmap(oPixmap.scaled(QSize(160, 160), Qt::KeepAspectRatio));
            break;
        }
        case EColor::Pink:{
            QPixmap oPixmap(":/Resources/textBeamDeepBreathPink.png");
            setPixmap(oPixmap.scaled(QSize(160, 160), Qt::KeepAspectRatio));
            break;
        }
        case EColor::Blue:{
            QPixmap oPixmap(":/Resources/textBeamWakeUpBlue.png");
            setPixmap(oPixmap.scaled(QSize(160, 160), Qt::KeepAspectRatio));
            break;
        }
    }
}

void CBullet::onMove()
{
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    for(auto const pItem : lstCollidingItem){
        CAlien* pAlien = dynamic_cast<CAlien*>(pItem);
        if (pAlien != nullptr){
            if (pAlien->GetColor() == GetColor()){
                scene()->removeItem(pAlien);
                scene()->removeItem(this);

                emit sigIncreaseScore();

                delete pAlien;
                delete this;
            }
            else{
                emit sigDecreaseScore();
                scene()->removeItem(this);
                delete this;
            }
            return;
        }
    }
    setPos(x(), y() - 3 ); // Speed of the bullet

    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
}

CPoints::CPoints(QGraphicsItem *pParent) : QGraphicsTextItem(pParent)
{
    setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n" + QString("Score : ") + QString::number(m_nScore));
    setDefaultTextColor(Qt::white);
    setFont(QFont("Courier", 24));
}

void CPoints::IncreaseScore()
{
    m_nScore += 50;
    setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n" + QString("Score : ") + QString::number(m_nScore));
}

void CPoints::DecreaseScore()
{
    m_nScore -= 50;
    setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n" + QString("Score : ") + QString::number(m_nScore));
}

void CPoints::DecreaseHealth()
{
    m_nHealth--;
    setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n" + QString("Score : ") + QString::number(m_nScore));
}

int CPoints::GetHealth() const
{
    return m_nHealth;
}

int CPoints::GetScore() const
{
    return m_nScore;
}

void CPoints::Reset()
{
    m_nScore = 0;
    m_nHealth = gMaxHealth;
    setPlainText(QString("Health : ") + QString::number(m_nHealth) + "\n" + QString("Score : ") + QString::number(m_nScore));
}

