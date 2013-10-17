//
//  SceneNode.cpp
//  ParallaxGame
//
//  Created by Joshua Scorca on 10/14/13.
//
//

#include "SceneNode.h"

SceneNode* SceneNode::create(){
    // create a new instance of this class
	SceneNode* pRet = new SceneNode();
    
	// if initialisation was successful, let cocos handle the memory management of the instance
	if( pRet->init())
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
bool SceneNode::init(){
    // super init first
    if(!CCNode::init())
    {
        
        return false;
    }
    
    // successful
    return true;
}


