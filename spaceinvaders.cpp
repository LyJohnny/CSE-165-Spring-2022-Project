#include "spaceinvaders.h"
#include <QTimer>

CSpaceInvaders::CSpaceInvaders(QSize oScreenSize, QWidget *pParent) : QGraphicsView(pParent), m_oScreenSize(oScreenSize)
{
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);

    pScene->setSceneRect(0,0, m_oScreenSize.width(), m_oScreenSize.height());

    setBackgroundBrush(QBrush(QImage(":/Resources/SpaceInvadersBg.jpg"))); //fix this?
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void CSpaceInvaders::Run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    m_pCannon = new CCannon(EColor::Red);
    m_pCannon->setPos(m_oScreenSize.width() / 2, m_oScreenSize.height() - gCannonSize.height());
    m_pCannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &CCannon::sigIncreaseScore, this, &CSpaceInvaders::onIncreaseScore);
    connect(m_pCannon, &CCannon::sigDecreaseScore, this, &CSpaceInvaders::onDecreaseScore);

    m_pPoints = new CPoints();
    scene()->addItem(m_pPoints);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CSpaceInvaders::onCreateEnemy);

}

void CSpaceInvaders::CheckPoints()
{

}

void CSpaceInvaders::keyPressEvent(QKeyEvent *pEvent)
{

}

void CSpaceInvaders::onCreateEnemy()
{

}

void CSpaceInvaders::onIncreaseScore()
{

}

void CSpaceInvaders::onDecreaseScore()
{

}

void CSpaceInvaders::onDecreaseHealth()
{

}

void CSpaceInvaders::onGameOver()
{

}
