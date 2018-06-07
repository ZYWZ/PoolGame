#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
#include "ball.h"

class Memento{
public:
    Memento(){}
    /**
     * @brief push a pointer of a ball to the vector of this memento
     * @param pointer of a ball
     */
    void pushToVector(Ball* ball){
        m_balls.push_back(ball);
    }

    /**
     * @brief return the vector
     * @return the vector
     */
    std::vector<Ball*> getBalls(){
        return m_balls;
    }
private:
    std::vector<Ball*> m_balls;
};

#endif // MEMENTO_H
