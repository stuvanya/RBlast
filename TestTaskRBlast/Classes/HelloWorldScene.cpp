/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Classes/Button.hpp"
#include "Classes/LongPushButton.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    setupButtons();
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::setupButtons()
{
    auto idle_sprite = Sprite::create("b_0_0.png");
    auto pushed_sprite = Sprite::create("b_0_2.png");
    auto dragout_sprite = Sprite::create("b_0_3.png");
    auto long_idle_sprite = Sprite::create("b_1_0.png");
    auto long_pushed_sprite = Sprite::create("b_1_2.png");
    auto long_dragout_sprite = Sprite::create("b_1_3.png");
    auto long_long_pushed_sprite = Sprite::create("b_1_1.png");

    auto content = Rect(idle_sprite->getContentSize() / -2, idle_sprite->getContentSize());
    auto expand = Rect(content.origin + Point(-10, -10), content.size + Size(20, 20));
    auto safe = Rect(content.origin + Point(-20, -20), content.size + Size(40, 40));

    auto button = Button::create(content, expand, safe);
    button->setPosition(Vec2(100, 50));
    button->addDependingElement(idle_sprite, ButtonState::IDLE);
    button->addDependingElement(pushed_sprite, ButtonState::PUSHED);
    button->addDependingElement(dragout_sprite, ButtonState::DRAG_OUT);
    addChild(button);


    auto longButton = LongPushButton::create(content, expand, safe, 2);
    longButton->setPosition(Vec2(200, 50));
    longButton->addDependingElement(long_idle_sprite, ButtonState::IDLE);
    longButton->addDependingElement(long_pushed_sprite, ButtonState::PUSHED);
    longButton->addDependingElement(long_dragout_sprite, ButtonState::DRAG_OUT);
    longButton->addDependingElement(long_long_pushed_sprite, ButtonState::PUSHED_LONG);
    addChild(longButton);

    auto test_sprite = Sprite::create("HelloWorld.png");
    auto test_sprite1 = Sprite::create("HelloWorld.png");
    auto test_sprite2 = Sprite::create("HelloWorld.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    test_sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    test_sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
    test_sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 300));
    addChild(test_sprite);
    addChild(test_sprite1);
    addChild(test_sprite2);

    button->setClickListener([test_sprite]() {
        test_sprite->setVisible(!test_sprite->isVisible());
        });
    longButton->setClickListener([test_sprite1]() {
        test_sprite1->setVisible(!test_sprite1->isVisible());
        });
    longButton->setLongClickListener([test_sprite2]() {
        test_sprite2->setVisible(!test_sprite2->isVisible());
        });
}
