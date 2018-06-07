#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMouseEvent>
#include <QKeyEvent>
#include "utils.h"
#include <qDebug>

Dialog::Dialog(Game *game, std::string stageFlag, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_game(game),
    m_stageFlag(stageFlag)
{
    ui->setupUi(this);

    // for animating (i.e. movement, collision) every animFrameMS
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(nextAnim()));
    aTimer->start(animFrameMS);

    // for drawing every drawFrameMS milliseconds
    dTimer = new QTimer(this);
    connect(dTimer, SIGNAL(timeout()), this, SLOT(tryRender()));
    dTimer->start(drawFrameMS);

    // set the window size to be at least the table size
    this->resize(game->getMinimumWidth(), game->getMinimumHeight());
    // save the original state of the game when it starts
    m_memento = m_game->save();
    m_cueBallColor = m_game->getBalls()->front()->getColor();
}

Dialog::~Dialog()
{
    delete aTimer;
    delete dTimer;
    delete m_game;
    delete ui;
}

void Dialog::tryRender() {
    this->update();
}

void Dialog::nextAnim() {
    m_game->animate(1.0/(double)animFrameMS);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // save the game when the cue ball has stoped
    if(m_stageFlag == "StageThree"){
        m_cueBallColor2 = m_game->getBalls()->front()->getColor();

        if(!m_saveFlag && m_cueBallColor == m_cueBallColor2){
            if(m_game->cueBallStop()){
                m_memento = m_game->save();
                m_saveFlag = true;
            }
        }

        if(m_cueBallColor != m_cueBallColor2){
            m_game->load(m_memento->getBalls());
        }
    }

    m_game->render(painter);
}

void Dialog::keyPressEvent(QKeyEvent *event){
    //press R to load the last step, press F to enter flash light mode
    if(m_stageFlag == "StageThree"){
        switch (event->key()){
            case Qt::Key_R:
                m_game->load(m_memento->getBalls());
                m_memento = m_game->save();
            break;
            case Qt::Key_F:
                m_game->flashLightMode();
                break;
        }
    }
}

void Dialog::mousePressEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseClickFn, event);
    m_saveFlag = false;
}

void Dialog::mouseReleaseEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseRelFn, event);
    m_saveFlag = false;
}
void Dialog::mouseMoveEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseMoveFn, event);
}

void Dialog::evalAllEventsOfTypeSpecified(MouseEventable::EVENTS t, QMouseEvent *event) {
    // handle all the clicky events, and remove them if they've xPIRED
    MouseEventable::EventQueue& Qu = m_game->getEventFns();
    for (ssize_t i = Qu.size()-1; i >= 0; i--) {
        if (auto spt = (Qu.at(i)).lock()) {
            if (spt->second == t) {
                spt->first(event);
            }
        } else {
            // remove this element from our vector
            Qu.erase(Qu.begin() + i);
        }
    }
}
