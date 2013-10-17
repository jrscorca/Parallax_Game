#include "PlayScene.h"
#include "SimpleAudioEngine.h"

#define kFilteringFactor 0.99999999


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* PlayScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    PlayScene *layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    // ask director the window size
    winSize = CCDirector::sharedDirector()->getWinSize();

    knobObject = SceneObject::createWithImageName("Knod.png");
    LEDOnObject = SceneObject::createWithImageName("LEDOn.png");
    LEDOffObject = SceneObject::createWithImageName("LEDOff.png");
    volumeObject = SceneObject::createWithImageName("Volume.png");

    firstX = 0;
    firstY = 0;
    resultX = 0;
    resultY = 0;
    dtX = 0;
    dtY = 0;
    lastX = 0;
    lastY = 0;
    lastPosition = ccp(0, 0);
    setAccelerometerEnabled(true);
    
    
    CCSprite *bg = CCSprite::create("background.png");
    bg->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(bg,-1);
    parallaxNode = CCParallaxNode::create();
    this->addChild(parallaxNode,-1);
    
    parallaxNode->addChild(knobObject->node, 0, ccp(-2.00, -1.50), ccp(-200+(winSize.width/2), -150+(winSize.height*.45)));
    parallaxNode->addChild(LEDOnObject->node, 0, ccp(2.00, 4.00), ccp(200+(winSize.width*.42), 400+(winSize.height/2)));
    parallaxNode->addChild(LEDOffObject->node, 0, ccp(-1.0, 3.00), ccp(-100+(winSize.width/2), 300+(winSize.height/2)));
    parallaxNode->addChild(volumeObject->node, 0, ccp(2.00, -1.00), ccp(200+(winSize.width/2), -100+(winSize.height*.2)));
    this->addChild(knobObject->sprite);
    this->addChild(LEDOffObject->sprite);
    this->addChild(LEDOnObject->sprite);

    this->addChild(volumeObject->sprite);
    knobObject->sprite->setPosition(ccp(0, 0));
    
    this->scheduleUpdate();
    label = CCLabelTTF::create();
    label->setString("YOU WIN!!!");
    label->setFontSize(36);
    label->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(label);
    label->setVisible(false);
    return true;
}

//For Accelerometer-------------------------------------------------
//SPEED SHOULD BE DIRECTLY PROPORTIONAL TO DISTANCE
//If an object is 1 px away from its origin, it should move 1px/input
//If an object is -25px away from its origin, it should move at 25px/input
void PlayScene::didAccelerate(cocos2d::CCAcceleration* accelerationValue)
{
    CCPoint pAccelerationValue = ccp(accelerationValue->x, accelerationValue->y);
    
    //These values to calibrate the based on the phones initial tilt
    if (firstX == 0) {
        firstX = pAccelerationValue.x;
    }
    
    if (firstY == 0) {
        firstY = pAccelerationValue.y;
    }
    float xAngle =  asin(firstX);
    float yAngle =  asin(firstY);
    
    lastX = resultX;
    lastY = resultY;
    
    resultX = pAccelerationValue.x;
    resultY = pAccelerationValue.y;
    
    if(fabs(resultX - lastX )<.001){
        //resultX = lastX;
    }else{
        float avgXAngle =  asin(resultX);
        avgXAngle -= xAngle;
        //prevent negative values by squaring
        resultX = sin(avgXAngle)*sin(avgXAngle);
        //resultX = .01 * resultX + (1.0 - 0.1) * pAccelerationValue->x;
        resultX = pAccelerationValue.x * kFilteringFactor + resultX * (1.0 - kFilteringFactor);
    }
    
    if(fabs(resultY - lastY)<.001){
        //resultY = lastY;
    }else{
        float avgYAngle =  asin(resultY);
        avgYAngle -= yAngle;
        //prevent negative values by squaring
        resultY = sin(avgYAngle)*sin(avgYAngle);
        //resultY = .01 * resultY + (1.0 - 0.1) * pAccelerationValue->y;
        resultY = pAccelerationValue.y * kFilteringFactor + resultY * (1.0 - kFilteringFactor);
    }

    if (isnan(resultX)) {
        resultX = lastX;
    }
    if (isnan(resultY)) {
        resultY = lastY;
    }
    CCLog("%f", resultY);
    
    

}

void PlayScene::update(float dt){
    //CCLOG("%f",parallaxNode->convertToWorldSpace(knobObject->node->getPosition()).x);
    CCRect winRect = CCRect(winSize.width/2-1, winSize.height/2-1, 2, 2);
    CCRect middle = CCRect(knobObject->sprite->getPosition().x, knobObject->sprite->getPosition().y+30, 10, 10);
    //CCLog("%f, %f, %f, %f", winRect.origin.x, winRect.origin.y, winRect.size.width, winRect.size.height);
    //CCLog("%f, %f, %f, %f", middle.origin.x, middle.origin.y, middle.size.width, middle.size.height);
    
    if(winRect.intersectsRect(middle)){
        label->setVisible(true);
        knobObject->sprite->setPosition(ccp((winSize.width/2), (winSize.height*.45)));
        LEDOnObject->sprite->setPosition(ccp((winSize.width*.42), (winSize.height/2)));
        LEDOffObject->sprite->setPosition( ccp((winSize.width/2), (winSize.height/2)));
        volumeObject->sprite->setPosition(ccp((winSize.width/2), (winSize.height*.2)));
        
        return;
    }
    
    if(label->isVisible()) return;
    CCPoint WPKnob = parallaxNode->convertToWorldSpace(knobObject->node->getPosition());
    CCPoint WPLEDOn = parallaxNode->convertToWorldSpace(LEDOnObject->node->getPosition());
    CCPoint WPLEDOff = parallaxNode->convertToWorldSpace(LEDOffObject->node->getPosition());
    CCPoint WPVolume = parallaxNode->convertToWorldSpace(volumeObject->node->getPosition());
    /*
    if(LEDOffObject->sprite->getPosition().x > winSize.width){
        return;
    }
    if(LEDOffObject->sprite->getPosition().x < 0){
        return;
    }
    if(LEDOffObject->sprite->getPosition().y > winSize.height){
        return;
    }
    if(LEDOffObject->sprite->getPosition().y < 0){
        return;
    }
    */
    //if (fabs((resultX)*winSize.width - parallaxNode->getPosition().x) > .5) {
         parallaxNode->setPosition(ccp((resultX)*winSize.width*.5,parallaxNode->getPosition().y));
    //}
    //if (fabs((resultY)*winSize.height - parallaxNode->getPosition().y) > .5) {
        parallaxNode->setPosition(ccp(parallaxNode->getPosition().x,(resultY)*winSize.height*.5));
    //}
    //parallaxNode->setPosition(ccp((resultX)*winSize.width,(resultY)*winSize.height));
    
    if (knobObject->sprite->getPosition().x > winSize.width) {
        knobObject->sprite->wrapperCountX++;
    }
    if (knobObject->sprite->getPosition().x < 0) {
        knobObject->sprite->wrapperCountX--;
    }
    
    if (LEDOnObject->sprite->getPosition().x > winSize.width) {
        LEDOnObject->sprite->wrapperCountX++;
    }
    if (LEDOnObject->sprite->getPosition().x < 0) {
        LEDOnObject->sprite->wrapperCountX--;
    }
    
    if (LEDOffObject->sprite->getPosition().x > winSize.width) {
        LEDOffObject->sprite->wrapperCountX++;
    }
    if (LEDOffObject->sprite->getPosition().x < 0) {
        LEDOffObject->sprite->wrapperCountX--;
    }
    if (volumeObject->sprite->getPosition().x > winSize.width) {
        volumeObject->sprite->wrapperCountX++;
    }
    if (volumeObject->sprite->getPosition().x < 0) {
        volumeObject->sprite->wrapperCountX--;
    }
    
    if (knobObject->sprite->getPosition().y > winSize.height) {
        knobObject->sprite->wrapperCountY++;
    }
    if (knobObject->sprite->getPosition().y < 0) {
        knobObject->sprite->wrapperCountY--;
    }
    if (LEDOnObject->sprite->getPosition().y > winSize.height) {
        LEDOnObject->sprite->wrapperCountY++;
    }
    if (LEDOnObject->sprite->getPosition().y < 0) {
        LEDOnObject->sprite->wrapperCountY--;
    }
    if (LEDOffObject->sprite->getPosition().y > winSize.height) {
        LEDOffObject->sprite->wrapperCountY++;
    }
    if (LEDOffObject->sprite->getPosition().y < 0) {
        LEDOffObject->sprite->wrapperCountY--;
    }
    if (volumeObject->sprite->getPosition().y > winSize.height) {
        volumeObject->sprite->wrapperCountY++;
    }
    if (volumeObject->sprite->getPosition().y < 0) {
        volumeObject->sprite->wrapperCountY--;
    }
    
    knobObject->sprite->setPosition(ccp(WPKnob.x - (winSize.width*knobObject->sprite->wrapperCountX), WPKnob.y - (winSize.height*knobObject->sprite->wrapperCountY)));
    LEDOnObject->sprite->setPosition(ccp(WPLEDOn.x - (winSize.width*LEDOnObject->sprite->wrapperCountX), WPLEDOn.y - (winSize.height*LEDOnObject->sprite->wrapperCountY)));
    LEDOffObject->sprite->setPosition(ccp(WPLEDOff.x - (winSize.width*LEDOffObject->sprite->wrapperCountX), WPLEDOff.y - (winSize.height*LEDOffObject->sprite->wrapperCountY)));
    volumeObject->sprite->setPosition(ccp(WPVolume.x - (winSize.width*volumeObject->sprite->wrapperCountX), WPVolume.y - (winSize.height*volumeObject->sprite->wrapperCountY)));
     
    
    
    knobObject->sprite->setPosition(WPKnob);
    LEDOnObject->sprite->setPosition(WPLEDOn);
    LEDOffObject->sprite->setPosition(WPLEDOff);
    volumeObject->sprite->setPosition(WPVolume);
    
    

    
}

void PlayScene::draw(){
    //CCRect winRect = CCRect(winSize.width/2-10, winSize.height/2-10, 20, 20);
    //ccDrawRect(ccp(winSize.width/2-10, winSize.height/2-10), ccp(winSize.width/2+10, winSize.height/2+10));
    //ccDrawColor4B(255, 0, 0, 255);

}
     

void PlayScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
