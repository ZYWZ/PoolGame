#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
#include "ball.h"

class Memento{
public:
    Memento(){}

    void pushToVector(Ball* ball){
        m_balls.push_back(ball);
    }
    std::vector<Ball*> getBalls(){
        return m_balls;
    }
private:
    std::vector<Ball*> m_balls;
};

#endif // MEMENTO_H
