#include "spaceinvaders.h"
#include <QTimer>
#include <math.h>

CSpaceInvaders::CSpaceInvaders(QSize oScreenSize, QWidget *pParent) : QGraphicsView(pParent), m_oScreenSize(oScreenSize)
{
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);

    pScene->setSceneRect(0,0, m_oScreenSize.width(), m_oScreenSize.height());

    setBackgroundBrush(QBrush(QImage(":/Resources/WalmartBg.jpg"))); //Walmart Background for Hepworth :)
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
    pTimer->start(2000);

}


void CSpaceInvaders::CheckPoints()
{

    if((m_pPoints->GetScore() < 0) || (m_pPoints->GetHealth() <= 0)){
        m_pPoints->Reset();
        onGameOver();
    }
}

void CSpaceInvaders::keyPressEvent(QKeyEvent *pEvent)
{
    if (m_pCannon == nullptr)
        return;
    switch (pEvent->key()){
    case Qt::Key_Left:
        if(m_pCannon->pos().x() > 0)
            m_pCannon->setPos(m_pCannon->x() -70, m_pCannon->y());
        break;

    case Qt::Key_Right:
        if((m_pCannon->pos().x() + gCannonSize.width()) < m_oScreenSize.width())
            m_pCannon->setPos(m_pCannon->x() +70, m_pCannon->y());
        break;

        // Keys A and D also move your player left and right
    case Qt::Key_A:
        if(m_pCannon->pos().x() > 0)
            m_pCannon->setPos(m_pCannon->x() -70, m_pCannon->y());
        break;

    case Qt::Key_D:
        if((m_pCannon->pos().x() + gCannonSize.width()) < m_oScreenSize.width())
            m_pCannon->setPos(m_pCannon->x() +70, m_pCannon->y());
        break;

        // Changing color of player
    case Qt::Key_Z:{
        int nColor = static_cast<int>(m_pCannon->GetColor());
        m_pCannon->SetColor(static_cast<EColor>(++nColor));
        break;
    }
        // Shoot some knowledge
    case Qt::Key_Space:
        m_pCannon->Shoot();
        break;
    case Qt::Key_Escape: // To Close/Exit the game
        close();
        break;

    }
}

void CSpaceInvaders::onCreateEnemy()
{
    int nPos = 200 + (rand() % m_oScreenSize.width()-240);
    int nColor = rand() % 3;

    CAlien * pAlien = new CAlien(static_cast<EColor>(nColor));
    pAlien->setPos(nPos,0);

    scene()->addItem(pAlien);

    connect(pAlien, &CAlien::sigGameOver, this, &CSpaceInvaders::onGameOver);
    connect(pAlien, &CAlien::sigDecreaseHealth, this, &CSpaceInvaders::onDecreaseHealth);

}

void CSpaceInvaders::onIncreaseScore()
{
    m_pPoints->IncreaseScore();
    CheckPoints();
}

void CSpaceInvaders::onDecreaseScore()
{
    m_pPoints->DecreaseScore();
    CheckPoints();
}

void CSpaceInvaders::onDecreaseHealth()
{
    m_pPoints->DecreaseHealth();
    CheckPoints();
}

void CSpaceInvaders::onGameOver()
{
    //Displays Game Over Screen
    QGraphicsScene* newScene = new QGraphicsScene();
    setScene(newScene);
    newScene->setSceneRect(-999,-999, m_oScreenSize.width(), m_oScreenSize.height());

    setBackgroundBrush(QBrush(QImage(":/Resources/gameOver.jpg")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");





}
