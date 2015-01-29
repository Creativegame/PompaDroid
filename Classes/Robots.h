#ifndef _ROBOTS_H_
#define _ROBOTS_H_

#include "cocos2d.h"
#include "ActionSprite.h"

class Robot : public ActionSprite
{
public:
    Robot();
    ~Robot();

    bool init();
    CREATE_FUNC(Robot);
};

#endif