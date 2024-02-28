#pragma once

#include <core_api/lsglobaldefinitions.h>
#include <core_api/lsinterface.h>

namespace SCENE_API {

// Forward declarations
class LSString_Implementation;

/// String implementation for unicode character strings.
/// \version SCENE API Version 2.0.0.
class LSString : public LSInterface
{
public:

	/// @name Construction, Destruction & Assignment
	//@{ 

	/// Constructs an empty string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString();

	/// Constructs a string containing a copy of the string \a str.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString(const LSString& str);
	
	/// Constructs a string containing a copy of the string \a str.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString(const wchar_t* str);

	/// Constructs a string containing a copy of the character \a c.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString(const wchar_t& c);

	/// Destroys the string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT ~LSString();

	/// Assigns a copy of the string \a str to this string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& operator=(const LSString& str);

	/// Assigns a copy of the string \a str to this string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& operator=(const wchar_t* str);

	//@}


	/// @name Conversion from other string types
	//@{

	/// Creates a copy of the string \a charStr. The string \a charStr
	/// is assumed to be encoded in the current system locale.
	/// \return	A copy of the string \a charStr.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT static LSString fromCharStr(const char* charStr);

	/// Creates a copy of the string \a utf8Str. The string \a utf8Str
	/// is assumed to be encoded in UTF8.
	/// \return	A copy of the string \a utf8Str.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT static LSString fromUtf8Str(const char* utf8Str);

	/// Creates a copy of the string \a wcharStr.
	/// \return	A copy of the string \a wcharStr.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT static LSString fromWcharStr(const wchar_t* wcharStr);

	//@}


	/// @name Conversion to other string types
	//@{

	/// Returns a string representation of the current string encoded
	/// in the current system locale.
	/// \return A string representation of the current string encoded
	/// in the current system locale.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT const char* toCharStr() const;

	/// Returns a string representation of the current string encoded
	/// in UTF8.
	/// \return A string representation of the current string encoded
	/// in UTF8.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT const char* toUtf8Str() const;

	/// Returns a wide character string representation of the current 
	/// string.
	/// \return A wide character string representation of the current string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT const wchar_t* toWcharStr() const;

	//@}


	/// @name String operations
	//@{

	/// Tests whether the string is empty (whether its length is 0).
	/// \return	true if the length of the string is 0, false otherwise.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT bool empty() const;

	/// Returns the length of the string, counted in the number of
	/// characters.
	/// \return	The number of characters in the string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int length() const;

	/// Searches the string for the first occurrence of the string
	/// \a str starting at the position \a pos.
	/// \return	The position of the first character of the first match. If no
	/// match is found -1 is returned.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int find(const LSString& str, int pos = 0) const;

	/// Searches the string for the first occurrence of the string \a
	/// str starting at the position \a pos.
	/// \return	The position of the first character of the first match. If no
	/// match is found -1 is returned.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int find(const wchar_t* str, int pos = 0) const;

	/// Searches the string for the first occurrence of the character
	/// \a c starting at the position \a pos.
	/// \return	The position of the first match. If no match is found -1 
	/// is returned.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int find(const wchar_t& c, int pos = 0) const;

	/// Searches the string for the last occurrence of the string \a
	/// str which is completely located before the position \a pos.
	/// \return The position of the first character of the last match. If no
	/// match is found -1 is returned.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int rfind(const LSString& str, int pos = -1) const;

	/// Searches the string for the last occurrence of the string \a
	/// str which is completely located before the position \a pos.
	/// \return The position of the first character of the last match. If no
	/// match is found -1 is returned.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int rfind(const wchar_t* str, int pos = -1) const;

	/// Searches the string for the last occurrence of the character \a
	/// c which is located before the position \a pos.
	/// \return The position of the last match. If no match is found -1 is 
	/// returned.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int rfind(const wchar_t& c, int pos = -1) const;

	/// Returns a new string which contains a substring of this 
	/// string starting at position \a pos and spanning \a len characters.
	/// \return	A string containing a substring of this object.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString substr(int pos = 0, int len = -1) const;

	/// Lexicographically compares the contents of this string to the
	/// contents of the string \a str.
	/// \return	Returns 0 if the strings are equal, <0 if either the first
	/// character that doesn't match is lower in \a str or all characters match
	/// but \a str is shorter and >0 if either the first character that doesn't
	/// match is greater in \a str or all characters match but \a str is 
	/// longer.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int compare(const LSString& str) const;

	/// Lexicographically compares the contents of this string to the
	/// contents of the string \a str.
	/// \return	Returns 0 if the strings are equal, <0 if either the first
	/// character that doesn't match is lower in \a str or all characters match
	/// but \a str is shorter and >0 if either the first character that doesn't
	/// match is greater in \a str or all characters match but \a str is 
	/// longer.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT int compare(const wchar_t* str) const;

	/// Replaces all occurrences of the string \a before with the string
	/// \a after.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& replace(const LSString& before, const LSString& after);

	/// Replaces all occurrences of the string \a before with the string
	/// \a after.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& replace(const LSString& before, const wchar_t* after);

	/// Replaces all occurrences of the string \a before with the string
	/// \a after.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& replace(const wchar_t* before, const LSString& after);

	/// Replaces all occurrences of the string \a before with the string
	/// \a after.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& replace(const wchar_t* before, const wchar_t* after);

	/// Replaces all occurrences of the character \a before with the 
	/// character \a after.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& replace(const wchar_t& before, const wchar_t& after);

	/// Appends the string \a str to this string.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& append(const LSString& str);

	/// Appends the string \a str to this string.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& append(const wchar_t* str);

	/// Appends the character \a c to this string.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& append(const wchar_t& c);

	/// Appends the string \a str to this string.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& operator+=(const LSString& str);

	/// Appends the string \a str to this string.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& operator+=(const wchar_t* str);

	/// Appends the character \a c to this string.
	/// \return *this.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT LSString& operator+=(const wchar_t& c);

	//@}

	/// @name Element access
	//@{

	/// Returns a reference to the character at position \a pos in the 
	/// string.
	/// \return	The character at the specified position in the string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT wchar_t& operator[](int pos);

	/// Returns a reference to the character at position \a pos in the 
	/// string.
	/// \return	The character at the specified position in the string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT wchar_t operator[](int pos) const;

	/// Returns a reference to the character at position \a pos in the 
	/// string.
	/// \return	The character at the specified position in the string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT wchar_t& at(int pos);

	/// Returns a reference to the character at position \a pos in the 
	/// string.
	/// \return	The character at the specified position in the string.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT wchar_t at(int pos) const;

	//@}


	/// @name New / Delete operators
	//@{

	/// Default allocation function. Overloaded in order to always
	/// allocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void* operator new(size_t tSize);

	/// Default deallocation function. Overloaded in order to always
	/// deallocate LSString objects in the context of this module.
	/// \version	SCENE API Version 2.0.0.
	CORE_API_EXPORT void  operator delete(void* p);

	//@}


protected:
	LS_INTERFACE(LSString, LSInterface)
};

/// @name String concatenation
//@{

/// \relates LSString
/// Returns a new string containing the concatenation of the contents 
/// of the string \a str1 followed by the contents of the string \a str2.
/// \return A string whose value is the concatenation of \a str1 and \a str2.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT LSString operator+(const LSString& str1, const LSString& str2);

/// \relates LSString
/// Returns a new string containing the concatenation of the contents 
/// of the string \a str1 followed by the contents of the string \a str2.
/// \return A string whose value is the concatenation of \a str1 and \a str2.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT LSString operator+(const LSString& str1, const wchar_t* str2);

/// \relates LSString
/// Returns a new string containing the concatenation of the contents 
/// of the string \a str1 followed by the contents of the string \a str2.
/// \return A string whose value is the concatenation of \a str1 and \a str2.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT LSString operator+(const wchar_t* str1, const LSString& str2);


/// \relates LSString
/// Returns a new string containing the concatenation of the contents 
/// of the string \a str followed by the character \a c.
/// \return A string whose value is the concatenation of \a str and \a c.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT LSString operator+(const LSString& str, const wchar_t& c);

/// \relates LSString
/// Returns a new string containing the concatenation of the character 
/// \a c followed by the contents of the string \a str.
/// \return A string whose value is the concatenation of \a c and \a str.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT LSString operator+(const wchar_t& c, const LSString& str);

/// \relates LSString
/// Tests whether the string \a str1 and the string \a str2 are equal.
/// \return	true if \a str1 and \a str2 are equal, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator== (const LSString& str1, const LSString& str2);

//@}

/// @name Relational operators
//@{

/// \relates LSString
/// Tests whether the string \a str1 and the string \a str2 are equal.
/// \return	true if \a str1 and \a str2 are equal, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator== (const LSString& str1, const wchar_t* str2);

/// \relates LSString
/// Tests whether the string \a str1 and the string \a str2 are equal.
/// \return	true if \a str1 and \a str2 are equal, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator== (const wchar_t* str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 and the string \a str2 are unequal.
/// \return	true if \a str1 and \a str2 are unequal, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator!= (const LSString& str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 and the string \a str2 are unequal.
/// \return	true if \a str1 and \a str2 are unequal, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator!= (const LSString& str1, const wchar_t* str2);

/// \relates LSString
/// Tests whether the string \a str1 and the string \a str2 are unequal.
/// \return	true if \a str1 and \a str2 are unequal, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator!= (const wchar_t* str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically smaller than
/// the string \a str2.
/// \return	true if \a str1 is smaller than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator< (const LSString& str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically smaller than
/// the string \a str2.
/// \return	true if \a str1 is smaller than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator< (const LSString& str1, const wchar_t* str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically smaller than
/// the string \a str2.
/// \return	true if \a str1 is smaller than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator< (const wchar_t* str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically smaller or 
/// equal than the string \a str2.
/// \return	true if \a str1 is smaller or equal than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator<= (const LSString& str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically smaller or 
/// equal than the string \a str2.
/// \return	true if \a str1 is smaller or equal than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator<= (const LSString& str1, const wchar_t* str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically smaller or 
/// equal than the string \a str2.
/// \return	true if \a str1 is smaller or equal than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator<= (const wchar_t* str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically greater than 
/// the string \a str2.
/// \return	true if \a str1 is greater than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator> (const LSString& str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically greater than 
/// the string \a str2.
/// \return	true if \a str1 is greater than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator> (const LSString& str1, const wchar_t* str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically greater than 
/// the string \a str2.
/// \return	true if \a str1 is greater than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator> (const wchar_t* str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically greater or 
/// equal than the string \a str2.
/// \return	true if \a str1 is greater or equal than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator>= (const LSString& str1, const LSString& str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically greater or 
/// equal than the string \a str2.
/// \return	true if \a str1 is greater or equal than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator>= (const LSString& str1, const wchar_t* str2);

/// \relates LSString
/// Tests whether the string \a str1 is lexicographically greater or 
/// equal than the string \a str2.
/// \return	true if \a str1 is greater or equal than \a str2, false otherwise.
/// \version	SCENE API Version 2.0.0.
CORE_API_EXPORT bool operator>= (const wchar_t* str1, const LSString& str2);

//@}

}
