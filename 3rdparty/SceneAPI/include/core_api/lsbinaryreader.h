#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsresult.h>
#include <core_api/lsreftype.h>

namespace SCENE_API
{

/// Abstract interface for reading binary data.
/// The exact overall size of the data stream must be known in advance.
/// This is an interface intended for streaming and the implementations must track the internal position on the data stream.
/// Subsequent calls to read() will consume the stream until the end was reached and will never return the same data.
/// In some cases this interface will be implemented by the SCENE API to allow apps to read data provided by the API, for example when reading Generic Binary Objects.
/// In other cases this interface needs to be implemented by an app to provide data for the API, for example when creating Generic Binary Objects.
/// \ingroup gbo
/// \version SCENE API version 2.0.26.
class LSBinaryReader : public LSRefType
{
public:
	virtual ~LSBinaryReader() {};

	/// Reads the number of requested bytes to the supplied memory buffer until the end of the stream is reached.
	/// \param buffer		Destination buffer, needs to be preallocated.
	/// \param bufferSize	Maximum number of bytes to write into the buffer.
	/// \return				Number of bytes written to buffer.
	///						At the end of the stream this could be less than bufferSize.
	///						If the data stream has reached the end, it will always return 0.
	///						If it returns 0 before all bytes of the stream are read, there was an error.
	/// \version SCENE API Version 2.0.26
	virtual size_t read(uint8_t* buffer, size_t bufferSize) = 0;

	/// Returns the exact overall size in bytes.
	/// May be slow depending on the implementation!
	/// \version SCENE API Version 2.0.26
	virtual size_t getSize() const = 0;
};

}
