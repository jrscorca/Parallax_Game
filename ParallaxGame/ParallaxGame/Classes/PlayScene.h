#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "SceneNode.h"
#include "SceneObject.h"
#include "SceneSprite.h"

class PlayScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(PlayScene);
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    void update(float dt);
    void draw();
    
    
    SceneObject::SceneObject *knobObject;
    SceneObject::SceneObject *LEDOnObject;
    SceneObject::SceneObject *LEDOffObject;
    SceneObject::SceneObject *volumeObject;
    cocos2d::CCParallaxNode *parallaxNode;
    cocos2d::CCLabelTTF *label;
    
    cocos2d::CCSize winSize;
    float dtX;
    float dtY;
    float resultX;
    float resultY;
    float firstX;
    float firstY;
    float lastX;
    float lastY;
    
   cocos2d::CCPoint lastPosition;
    

    
};

#endif // __PLAY_SCENE_H__
