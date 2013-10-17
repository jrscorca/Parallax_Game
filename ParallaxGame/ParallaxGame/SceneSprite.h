//
//  SceneSprite.h
//  ParallaxGame
//
//  Created by Joshua Scorca on 10/14/13.
//
//

#ifndef __ParallaxGame__SceneSprite__
#define __ParallaxGame__SceneSprite__

#include "cocos2d.h"

class SceneSprite : public cocos2d::CCSprite
{
public:
    static SceneSprite* create(const char* name);
    bool init(const char* name);
    
    int wrapperCountX;
    int wrapperCountY;
};

#endif /* defined(__ParallaxGame__SceneSprite__) */