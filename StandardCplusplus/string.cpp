/*	Copyright (C) 2004 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#define __UCLIBCXX_COMPILE_STRING__ 1

#include <basic_definitions>
#include <char_traits>
//#include <string>
#include <WString.h>
#include <string_iostream>
#include <string.h>
#include <ostream>

namespace std{

#ifdef __UCLIBCXX_EXPAND_STRING_CHAR__

#ifdef __UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template _UCXXEXPORT String::basic_string(const allocator<char> &);
	template _UCXXEXPORT String::basic_string(size_type n, char c, const allocator<char> & );
	template _UCXXEXPORT String::basic_string(const char* s, const allocator<char>& al);
	template _UCXXEXPORT String::basic_string(const basic_string& str, size_type pos, size_type n, const allocator<char>& al);
	template _UCXXEXPORT String::~basic_string();

#endif // __UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template _UCXXEXPORT String & String::append(const char * s, size_type n);

	template _UCXXEXPORT String::size_type String::find(const String & str, size_type pos) const;
	template _UCXXEXPORT String::size_type String::find(const char* s, size_type pos) const;
	template _UCXXEXPORT String::size_type String::find (char c, size_type pos) const;
	template _UCXXEXPORT String::size_type String::rfind(const String & str, size_type pos) const;
	template _UCXXEXPORT String::size_type String::rfind(char c, size_type pos) const;
	template _UCXXEXPORT String::size_type String::rfind(const char* s, size_type pos) const;

	template _UCXXEXPORT String::size_type String::find_first_of(const String &, size_type) const;
	template _UCXXEXPORT String::size_type String::find_first_of(const char *, size_type pos, size_type n) const;
	template _UCXXEXPORT String::size_type String::find_first_of(const char*, size_type pos) const;
	template _UCXXEXPORT String::size_type String::find_first_of(char c, size_type pos) const;

	template _UCXXEXPORT String::size_type String::find_last_of (const String & , size_type pos) const;
	template _UCXXEXPORT String::size_type String::find_last_of (const char* s, size_type pos, size_type n) const;
	template _UCXXEXPORT String::size_type String::find_last_of (const char* s, size_type pos) const;
	template _UCXXEXPORT String::size_type String::find_last_of (char c, size_type pos) const;

	template _UCXXEXPORT String::size_type String::find_first_not_of(const String &, size_type) const;
	template _UCXXEXPORT String::size_type String::find_first_not_of(const char*, size_type, size_type) const;
	template _UCXXEXPORT String::size_type String::find_first_not_of(const char*, size_type) const;
	template _UCXXEXPORT String::size_type String::find_first_not_of(char c, size_type) const;

	template _UCXXEXPORT int String::compare(const String & str) const;
//	template _UCXXEXPORT int string::compare(size_type pos1, size_type n1, const string & str) const;
	template _UCXXEXPORT int String::compare(
		size_type pos1, size_type n1, const String & str, size_type pos2, size_type n2) const;

	template _UCXXEXPORT String String::substr(size_type pos, size_type n) const;

	template _UCXXEXPORT String & String::operator=(const String & str);
	template _UCXXEXPORT String & String::operator=(const char * s);

	template _UCXXEXPORT bool operator==(const String & lhs, const String & rhs);
	template _UCXXEXPORT bool operator==(const char * lhs, const String & rhs);
	template _UCXXEXPORT bool operator==(const String & lhs, const char * rhs);

	template _UCXXEXPORT bool operator!=(const String & lhs, const String & rhs);
	template _UCXXEXPORT bool operator!=(const char * lhs, const String & rhs);
	template _UCXXEXPORT bool operator!=(const String & lhs, const char * rhs);

	template _UCXXEXPORT String operator+(const String & lhs, const char* rhs);
	template _UCXXEXPORT String operator+(const char* lhs, const String & rhs);
	template _UCXXEXPORT String operator+(const String & lhs,	const String & rhs);

	template _UCXXEXPORT bool operator> (const String & lhs, const String & rhs);
	template _UCXXEXPORT bool operator< (const String & lhs, const String & rhs);


//Functions dependent upon OSTREAM
#ifdef __UCLIBCXX_EXPAND_OSTREAM_CHAR__

template _UCXXEXPORT ostream & operator<<(ostream & os, const String & str);

#endif


//Functions dependent upon ISTREAM
#ifdef __UCLIBCXX_EXPAND_ISTREAM_CHAR__

template _UCXXEXPORT istream & operator>>(istream & is, String & str);


#endif


#endif

}
