#pragma once

#include "Button.hpp"

class LongPushButton :
    public Button
{
public:
    static LongPushButton* create(Rect content, Rect expand, Rect safe, float time);
    float getTime();
    void setTime(const float&time);
    void setLongClickListener(std::function<void()> callback);
private:
    LongPushButton(Rect content, Rect expand, Rect safe, float time);
    float _time;
    std::function<void()> _longTouchCallback;

    bool onTouchBegan(Touch* t, Event* e) override;
    void onTouchMoved(Touch* t, Event* e) override;
    void onTouchEnded(Touch* t, Event* e) override;

    void updateTimer(float time);
    void setState(ButtonState state) override;
};

