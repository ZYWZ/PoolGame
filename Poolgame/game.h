#pragma once
#include <QJsonObject>
#include <functional>
#include <QMouseEvent>
#include <QSound>

#include "abstractstagefactory.h"

#include "table.h"
#include "ball.h"
#include "balldecorator.h"
#include "utils.h"
#include "memento.h"

class Game {
    std::vector<Ball*>* m_balls;
    Table* m_table;

    // screenshake stuff
    QVector2D m_screenshake;
    double m_shakeRadius = 0.0;
    double m_shakeAngle = 0;
    static constexpr double SCREENSHAKEDIST = 10.0;

    bool m_flashlight = false;
    double m_flashRadius = 150.0;

    /* increase the amount of screen shake */
    void incrementShake(double amount=SCREENSHAKEDIST) { m_shakeRadius += amount; }
private:
    // store the functions that get scanned through whenever a mouse event happens
    MouseEventable::EventQueue m_mouseEventFunctions;

    /**
     * @brief updateShake - update the screenshake radius (make it smaller)
     * @param dt - the timestep change
     */
    void updateShake(double dt);
public:
    ~Game();
    Game(std::vector<Ball*>* balls, Table* table) :
        m_balls(balls), m_table(table) {}
    /**
     * @brief Draws all owned objects to the screen (balls and table)
     * @param painter - qtpainter to blit to screen with
     */
    void render(QPainter& painter) const;
    /**
     * @brief Updates the positions of all objects within, based on how much time has changed
     * @param dt - time elapsed since last frame in seconds
     */
    void animate(double dt);

    void renderFlashLight(QPainter& painter) const;

    /* how large the window's width should at least be */
    int getMinimumWidth() const { return m_table->getWidth(); }
    /* how large the window's height should at least be */
    int getMinimumHeight() const { return m_table->getHeight(); }

    std::vector<Ball*>* getBalls(){return m_balls;}

    /**
     * @brief resolveCollision - modify the ball's velocity if it is colliding with the table
     * @param table - the table to be bounds checked
     * @param ball - the ball to move
     * @return velocity - the change of velocity that a ball underwent
     */
    QVector2D resolveCollision(const Table* table, Ball* ball);
    /**
     * @brief resolveCollision - resolve both ball's velocity whether these balls collide
     * @param ballA - first ball
     * @param ballB - second ball
     * @param pair<deltaVelocityA, deltaVelocityB> - the change of velocities for each ball
     */
    std::pair<QVector2D, QVector2D> resolveCollision(Ball* ballA, Ball* ballB);

    /**
     * @brief isColliding - returns whether two balls are touching each other
     * @param ballA
     * @param ballB
     * @return whether the two balls are touching each other
     */
    bool isColliding(const Ball* ballA, const Ball* ballB) {
        QVector2D collisionVector = ballB->getPosition() - ballA->getPosition();
        return !(collisionVector.length() > ballA->getRadius() + ballB->getRadius());
    }

    /**
     * @brief addMouseFunctions - append all of the specified functions to be
     *  our eventqueue - these will be cycled through onclick, etc
     * @param fns
     */
    void addMouseFunctions(MouseEventable::EventQueue fns) {
        std::copy(fns.begin(), fns.end(), std::back_inserter(m_mouseEventFunctions));
    }

    /**
     * @brief getEventFns - get all of our event functions (mouseclicksfns, etc)
     * @return event queue of event functions
     */
    MouseEventable::EventQueue& getEventFns() { return m_mouseEventFunctions; }

    /**
     * @brief load the balls stored in memento
     * @param balls
     */
    void load(std::vector<Ball*> balls);

    /**
     * @brief save all the cloned balls to a vector
     * @return a memento which stores a vector of Ball*
     */
    Memento* save();

    /**
     * @brief flashLightMode will render the light around the ball and leave the rest of the table to darkness
     */
    void flashLightMode();

    /**
     * @brief check whether the cue ball has stoped
     * @return yes or no
     */
    bool cueBallStop(){
        bool flag = false;
        if(m_balls->front()->getVelocity().length() < 1){
            flag = true;
        }
        return flag;
    }
};
