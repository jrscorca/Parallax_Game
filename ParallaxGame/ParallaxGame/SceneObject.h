//
//  SceneObject.h
//  ParallaxGame
//
//  Created by Joshua Scorca on 10/14/13.
//
//
#ifndef __ParallaxGame__SceneObject__
#define __ParallaxGame__SceneObject__


#include "cocos2d.h"
#include "SceneSprite.h"
#include "SceneNode.h"

class SceneObject : public cocos2d::CCObject
{
    public:
    SceneNode *node;
    SceneSprite *sprite;
    static SceneObject* createWithImageName(const char* name);
    
    bool init(const char* name);
};
#endif /* defined(__ParallaxGame__SceneObject__) */