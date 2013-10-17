//
//  SceneSprite.cpp
//  ParallaxGame
//
//  Created by Joshua Scorca on 10/14/13.
//
//

#include "SceneSprite.h"

SceneSprite* SceneSprite::create(const char* name){
    // create a new instance of this class
	SceneSprite* pRet = new SceneSprite();
    
	// if initialisation was successful, let cocos handle the memory management of the instance
	if( pRet->init(name))
    {
        pRet->autorelease();
        return pRet;
    }
    
	// if initialisation was not successful, delete the instance
    CC_SAFE_DELETE( pRet );
    return NULL;
}

/** Custom init function
 initialises an instance based on a parameter */
bool SceneSprite::init(const char* name){
    // super init first
    if(!CCSprite::initWithFile(name))
    {
        wrapperCountX = 0;
        wrapperCountY = 0;
        return false;
    }
    
    // successful
    return true;
}