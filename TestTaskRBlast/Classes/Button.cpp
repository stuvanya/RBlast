#include "Button.hpp"
#include <iostream>

Button::Button(Rect content, Rect expand, Rect safe) : ui::Widget(),
	_content(content),
	_expand(expand),
	_safe(safe)
{
	correctRectSizes(_expand, _content);
	correctRectSizes(_safe, _expand);

	_state = ButtonState::IDLE;
	updateSkin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Button::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

Button* Button::create(Rect content, Rect expand, Rect safe)
{
	auto button = new Button(content, expand, safe);
	return button;
}

void Button::setClickListener(std::function<void()> callback)
{
	_callback = callback;
}

void Button::addDependingElement(Node* element, ButtonState state)
{
	if (_dependingElements.find(element) == _dependingElements.end())
	{
		_dependingElements[element] = static_cast<unsigned char>(state);
		addChild(element);
		updateSkin();
	}
	else
	{
		_dependingElements[element] = static_cast<unsigned char>(state) | _dependingElements[element];
	}
}

void Button::removeDependingElement(Node* element)
{
	auto it = _dependingElements.find(element);
	if (it != _dependingElements.end())
	{
		_dependingElements.erase(it);
		removeChild(element);
	}
}

void Button::updateSkin()
{
	for (auto element : _dependingElements)
	{
		element.first->setVisible(element.second & static_cast<unsigned char>(_state));
	}
}

void Button::setState(ButtonState state)
{
	if (_state != state)
	{
		_state = state;
		updateSkin();
	}
}

bool Button::onTouchBegan(Touch* t, Event* e)
{
	if (_expand.containsPoint(convertTouchToNodeSpace(t)))
	{
		setState(ButtonState::PUSHED);
		return true;
	}
	else
	{
		return false;
	}
}

void Button::onTouchMoved(Touch* t, Event* e)
{
	if (_state == ButtonState::IDLE)
		return;

	auto loc = convertTouchToNodeSpace(t);
	if (!_expand.containsPoint(loc) && _safe.containsPoint(loc))
		setState(ButtonState::DRAG_OUT);
	else if (_expand.containsPoint(loc))
		setState(ButtonState::PUSHED);
	else
		setState(ButtonState::IDLE);
}

void Button::onTouchEnded(Touch* t, Event* e)
{
	if (_state == ButtonState::PUSHED)
	{
		if (_callback)
			_callback();

		EventCustom event("ButtonEvent:PUSHED");
		event.setUserData(this);
		_eventDispatcher->dispatchEvent(&event);
	}
	setState(ButtonState::IDLE);
}

void Button::correctRectSizes(Rect bigger, Rect smaller)
{
	if (bigger.getMinX() > smaller.getMinX())
		bigger.setRect(smaller.getMinX(), bigger.getMinY(), bigger.size.width, bigger.size.height);
	if (bigger.getMinY() > smaller.getMinY())
		bigger.setRect(bigger.getMinX(), smaller.getMinY(), bigger.size.width, bigger.size.height);
	if (bigger.size.width < smaller.size.width)
		bigger.size.width = smaller.size.width;
	if (bigger.size.height < smaller.size.height)
		bigger.size.height = smaller.size.height;
}
