#include "table.h"
#include "ball.h"
#include <iostream>
#include <QSound>
#include "utils.h"

void StageOneTable::render(QPainter &painter, const QVector2D& offset) {
    // our table colour
    painter.setBrush(m_brush);
    // draw table
    painter.drawRect(offset.x(), offset.y(), this->getWidth(), this->getHeight());
}

void StageTwoTable::render(QPainter &painter, const QVector2D& offset) {
    // our table colour
    painter.setBrush(m_brush);
    // draw table
    painter.drawRect(offset.x(), offset.y(), this->getWidth(), this->getHeight());

    // render the pockets relative to this table
    for (Pocket* p : m_pockets) {
        p->render(painter, offset);
    }
}

void StageThreeTable::render(QPainter &painter, const QVector2D& offset) {
    // our table colour
    painter.setBrush(m_brush);
    // draw table
    painter.drawRect(offset.x(), offset.y(), this->getWidth(), this->getHeight());

    // render the pockets relative to this table
    for (Pocket* p : m_pockets) {
        p->render(painter, offset);
    }
    for (Magnet* m : m_magnets) {
        m->render(painter, offset);
    }
}

StageTwoTable::~StageTwoTable() {
    for (Pocket* p : m_pockets) delete p;
}

StageThreeTable::~StageThreeTable() {
    for (Pocket* p : m_pockets) delete p;
    for (Magnet* m : m_magnets) delete m;
}

bool StageTwoTable::sinks(Ball *b) {
    QVector2D absPos = b->getPosition();
    double radius = b->getRadius();
    // check whether any pockets consumes this ball
    for (Pocket* p : m_pockets) {
        // you sunk my scrabbleship
        if (p->contains(absPos, radius)) {
            p->incrementSunk();
            QSound::play(pocketSound_path);
            return true;
        }
    }
    return false;
}

bool StageThreeTable::sinks(Ball *b) {
    QVector2D absPos = b->getPosition();
    double radius = b->getRadius();
    // check whether any pockets consumes this ball
    for (Pocket* p : m_pockets) {
        // you sunk my scrabbleship
        if (p->contains(absPos, radius)) {
            p->incrementSunk();
            QSound::play(pocketSound_path);
            return true;
        }
    }
    return false;
}

// the magnet will push the cue ball away
void StageThreeTable::exclude(Ball* ball){
    for(Magnet* m : m_magnets){
        if((ball->getPosition() - m->getPos()).length() < 150){
            ball->changeVelocity((ball->getPosition()-m->getPos())/100);
        }
    }
}
