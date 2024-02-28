#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>
#include <core_api/lsreftype.h>
#include <core_api/lstrackable.h>

namespace SCENE_API {


template<class Event>
class LSSlotBase : public LSRefType
{
	LS_UNCOPYABLE(LSSlotBase)

public:
	LSSlotBase() {}

	virtual void emit(Event event) = 0;

	virtual LSTrackable* getTrackable() const = 0;

	virtual void disconnect_trackable() = 0;
};


template<class Event, class Trackable = void>
class LSSlot : public LSSlotBase<Event>
{
public:
	LSSlot(Trackable* trackable, void(Trackable::*handler)(Event))
		: m_trackable(trackable), m_handler(handler)
	{

	}

	virtual void emit(Event event)
	{
		if (m_trackable)
			(m_trackable->*m_handler)(event);
	}

	virtual LSTrackable* getTrackable() const
	{
		return m_trackable;
	}

	virtual void disconnect_trackable()
	{
		m_trackable = 0;
	}


private:
	Trackable* m_trackable;
	void(Trackable::*m_handler)(Event);
};

template<class Event>
class LSSlot<Event, void> : public LSSlotBase<Event>
{
public:
	LSSlot(void(*handler)(Event))
		: m_handler(handler)
	{

	}

	virtual void emit(Event event)
	{
		m_handler(event);
	}

	virtual LSTrackable* getTrackable() const
	{
		return 0;
	}

	virtual void disconnect_trackable()
	{

	}

private:
	void(*m_handler)(Event);
};

}
