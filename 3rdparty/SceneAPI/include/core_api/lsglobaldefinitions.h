#pragma once

#include <core_api/lsapiversion.h>

// API Namespace
#define SCENE_API SCENE_API_2_0
namespace SCENE_API {}

// Library Export/Import
#if defined(_MSC_VER)
	// Microsoft compilers
#	define LS_DECL_EXPORT __declspec(dllexport)
#	define LS_DECL_IMPORT __declspec(dllimport)
#else
	// Non-Microsoft compilers
#	define LS_DECL_EXPORT __attribute__((__visibility__("default")))
#	define LS_DECL_IMPORT
#endif

#if defined(CORE_API_DLLBUILD)
#	define CORE_API_EXPORT LS_DECL_EXPORT
#else
#	define CORE_API_EXPORT LS_DECL_IMPORT
#endif

#if defined(STANDALONE_API_DLLBUILD)
#	define STANDALONE_API_EXPORT LS_DECL_EXPORT
#else
#	define STANDALONE_API_EXPORT LS_DECL_IMPORT
#endif

#if defined(PLUGIN_API_DLLBUILD)
#	define PLUGIN_API_EXPORT LS_DECL_EXPORT
#else
#	define PLUGIN_API_EXPORT LS_DECL_IMPORT
#endif

#if defined(SCANNER_API_DLLBUILD)
#	define SCANNER_API_EXPORT LS_DECL_EXPORT
#else
#	define SCANNER_API_EXPORT LS_DECL_IMPORT
#endif

// Common Macros
#define LS_UNCOPYABLE(Class) \
	Class(const Class&); \
	Class& operator=(const Class&);

// Common typedefs
#include <Eigen/Core>
namespace Eigen{
	typedef Eigen::Matrix<unsigned int, 2, 1> Vector2ui;
	typedef Eigen::Matrix<unsigned short, 2, 1> Vector2us;
	typedef Eigen::Matrix<unsigned char, 2, 1> Vector2uc;
	typedef Eigen::Matrix<unsigned int, 3, 1> Vector3ui;
	typedef Eigen::Matrix<unsigned short, 3, 1> Vector3us;
	typedef Eigen::Matrix<unsigned char, 3, 1> Vector3uc;
	typedef Eigen::Matrix<unsigned int, 4, 1> Vector4ui;
	typedef Eigen::Matrix<unsigned short, 4, 1> Vector4us;
	typedef Eigen::Matrix<unsigned char, 4, 1> Vector4uc;
}
