//
//  SceneObject.cpp
//  ParallaxGame
//
//  Created by Joshua Scorca on 10/14/13.
//
//

#include "SceneObject.h"

SceneObject* SceneObject::createWithImageName(const char* name){
    // create a new instance of this class
	SceneObject* pRet = new SceneObject();
    
	// if initialisation was successful, let cocos handle the memory management of the instance
	if( pRet->init(name))
    {
        //pRet->autorelease();
        return pRet;
    }
    
	// if initialisation was not successful, delete the instance
    CC_SAFE_DELETE( pRet );
    return NULL;
}

/** Custom init function
 initialises an instance based on a parameter */
bool SceneObject::init(const char* name){
    // successful
    sprite = SceneSprite::create(name);
    node = SceneNode::create();
    return true;
}