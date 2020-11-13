#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

USING_NS_CC;

enum class ButtonState
{
	IDLE = 0x01,
	DRAG_OUT = 0x02,
	PUSHED = 0x04,
	PUSHED_LONG = 0x08
};

class Button : public ui::Widget
{
public:
	static Button* create(Rect content, Rect expand, Rect safe);
	void setClickListener(std::function<void()> callback);
	void addDependingElement(Node* element, ButtonState state);
	void removeDependingElement(Node* element);
	void setContentZone(Rect content);
	void setExpandZone(Rect expand);
	void setSafeZone(Rect safe);
protected:
	Button(Rect content, Rect expand, Rect safe);
	ButtonState _state;
	Rect _content, _expand, _safe;
	std::function<void()> _callback;
	std::map<Node*, unsigned char> _dependingElements;

	void updateSkin();
	virtual void setState(ButtonState state);

	virtual bool onTouchBegan(Touch* t, Event* e) override;
	virtual void onTouchMoved(Touch* t, Event* e) override;
	virtual void onTouchEnded(Touch* t, Event* e) override;

	void correctRectSizes(Rect bigger, Rect smaller);
};

