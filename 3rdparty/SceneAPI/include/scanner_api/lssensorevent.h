#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsevent.h>
#include <core_api/ref_ptr.h>

#include <memory>

namespace SCENE_API {

// Forward declarations
class LSSensor;

/// An event that is caused by a sensor and can contain extra data.
/// \version	SCENE API Version 2.0.14.
template<typename T>
class LSSensorEvent : public LSInterface, public LSEvent
{
	LS_UNCOPYABLE(LSSensorEvent)

public:
	/// Returns the data attached to the event.
	/// \version	SCENE API Version 2.0.14.
	T& getData();

protected:
	LS_INTERFACE_TEMPLATE(LSSensorEvent, T, LSInterface)
};

template<>
class LSSensorEvent<void> : public LSInterface, public LSEvent
{
	LS_UNCOPYABLE(LSSensorEvent)

protected:
	LS_INTERFACE_TEMPLATE(LSSensorEvent, void, LSInterface)
};

/// A special type of sensor event for frame-specific data.
/// \version	SCENE API Version 2.0.14.
template<typename T>
class LSFrameEvent : public LSSensorEvent<T>
{
	LS_UNCOPYABLE(LSFrameEvent)

public:
	/// Returns the frame id.
	/// \version		SCENE API Version 2.0.14.
	int getFrameId() const;

protected:
	LS_INTERFACE_TEMPLATE2(LSFrameEvent, T, LSSensorEvent)
};

#define SENSOR_SIGNAL(...) LSSignal<ref_ptr<LSSensorEvent<__VA_ARGS__>>>
#define FRAME_SIGNAL(...) LSSignal<ref_ptr<LSFrameEvent<__VA_ARGS__>>>

}
