#include "LongPushButton.hpp"

LongPushButton::LongPushButton(Rect content, Rect expand, Rect safe, float time) : Button(content, expand, safe),
	_time(time)
{
}

LongPushButton* LongPushButton::create(Rect content, Rect expand, Rect safe, float time)
{
	auto button = new LongPushButton(content, expand, safe, time);
	return button;
}

float LongPushButton::getTime()
{
	return _time;
}

void LongPushButton::setTime(const float& time)
{
	_time = time;
}

void LongPushButton::setLongClickListener(std::function<void()> callback)
{
	_longTouchCallback = callback;
}

bool LongPushButton::onTouchBegan(Touch* t, Event* e)
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

void LongPushButton::onTouchMoved(Touch* t, Event* e)
{
	if (_state == ButtonState::IDLE)
		return;

	auto loc = convertTouchToNodeSpace(t);
	if (!_expand.containsPoint(loc) && _safe.containsPoint(loc))
		setState(ButtonState::DRAG_OUT);
	else if (_expand.containsPoint(loc))
	{ 
		if (_state != ButtonState::PUSHED_LONG)
			setState(ButtonState::PUSHED);
	}
	else
		setState(ButtonState::IDLE);
}

void LongPushButton::onTouchEnded(Touch* t, Event* e)
{
	if (_state == ButtonState::PUSHED)
	{
		if (_callback)
			_callback();
		EventCustom event("ButtonEvent:PUSHED");
		event.setUserData(this);
		_eventDispatcher->dispatchEvent(&event);
	}
	else if (_state == ButtonState::PUSHED_LONG)
	{
		if (_longTouchCallback)
			_longTouchCallback();
		EventCustom event("ButtonEvent:PUSHED_LONG");
		event.setUserData(this);
		_eventDispatcher->dispatchEvent(&event);
	}
	unschedule(schedule_selector(LongPushButton::updateTimer));
	setState(ButtonState::IDLE);
}

void LongPushButton::updateTimer(float time)
{
	if (_state == ButtonState::PUSHED)
	{
		setState(ButtonState::PUSHED_LONG);
	}
}

void LongPushButton::setState(ButtonState state)
{
	if (_state != state)
	{
		if (state != ButtonState::PUSHED_LONG)
		    unschedule(schedule_selector(LongPushButton::updateTimer));
		if (state == ButtonState::PUSHED)
			scheduleOnce(schedule_selector(LongPushButton::updateTimer), _time);
		_state = state;
		updateSkin();
	}
}
