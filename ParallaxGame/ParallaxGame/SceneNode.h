//
//  SceneNode.h
//  ParallaxGame
//
//  Created by Joshua Scorca on 10/14/13.
//
//
#ifndef __ParallaxGame__SceneNode__
#define __ParallaxGame__SceneNode__

#include "cocos2d.h"

class SceneNode : public cocos2d::CCNode
{
public:
    static SceneNode* create();
    bool init();

    cocos2d::CCPoint offset;
};
#endif /* defined(__ParallaxGame__SceneNode__) */