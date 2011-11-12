// ConfigFile.h
// Class for reading named values from configuration files
// Richard J. Wagner  v2.1  24 May 2004  wagnerr@umich.edu

// Copyright (c) 2004 Richard J. Wagner
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

// Typical usage
// -------------
// 
// Given a configuration file "settings.inp":
//   atoms  = 25
//   length = 8.0  # nanometers
//   name = Reece Surcher
// 
// Named values are read in various ways, with or without default values:
//   ConfigFile config( "settings.inp" );
//   int atoms = config.read<int>( "atoms" );
//   double length = config.read( "length", 10.0 );
//   string author, title;
//   config.readInto( author, "name" );
//   config.readInto( title, "title", string("Untitled") );
// 
// See file example.cpp for more examples.

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using std::wstring;

class ConfigFile {
// Data
protected:
	wstring myDelimiter;  // separator between key and value
	wstring myComment;    // separator between value and comments
	wstring mySentry;     // optional string to signal end of file
	std::map<wstring,wstring> myContents;  // extracted keys and values
	
	typedef std::map<wstring,wstring>::iterator mapi;
	typedef std::map<wstring,wstring>::const_iterator mapci;

// Methods
public:
	ConfigFile( wstring filename,
	            wstring delimiter = L"=",
	            wstring comment = L"#",
				wstring sentry = L"EndConfigFile" );
	ConfigFile();
	
	// Search for key and read value or optional default value
	template<class T> T read( const wstring& key ) const;  // call as read<T>
	template<class T> T read( const wstring& key, const T& value ) const;
	template<class T> bool readInto( T& var, const wstring& key ) const;
	template<class T>
	bool readInto( T& var, const wstring& key, const T& value ) const;
	
	// Modify keys and values
	template<class T> void add( wstring key, const T& value );
	void remove( const wstring& key );
	
	// Check whether key exists in configuration
	bool keyExists( const wstring& key ) const;
	
	// Check or change configuration syntax
	wstring getDelimiter() const { return myDelimiter; }
	wstring getComment() const { return myComment; }
	wstring getSentry() const { return mySentry; }
	wstring setDelimiter( const wstring& s )
		{ wstring old = myDelimiter;  myDelimiter = s;  return old; }  
	wstring setComment( const wstring& s )
		{ wstring old = myComment;  myComment = s;  return old; }
	
	// Write or read configuration
	friend std::wostream& operator<<( std::wostream& os, const ConfigFile& cf );
	friend std::wistream& operator>>( std::wistream& is, ConfigFile& cf );
	
protected:
	template<class T> static wstring T_as_wstring( const T& t );
	template<class T> static T wstring_as_T( const wstring& s );
	static void trim( wstring& s );


// Exception types
public:
	struct file_not_found {
		wstring filename;
		file_not_found( const wstring& filename_ = wstring() )
			: filename(filename_) {} };
	struct key_not_found {  // thrown only by T read(key) variant of read()
		wstring key;
		key_not_found( const wstring& key_ = wstring() )
			: key(key_) {} };
};


/* static */
template<class T>
wstring ConfigFile::T_as_wstring( const T& t )
{
	// Convert from a T to a string
	// Type T must support << operator
	std::wostringstream ost;
	ost << t;
	return ost.str();
}


/* static */
template<class T>
T ConfigFile::wstring_as_T( const wstring& s )
{
	// Convert from a string to a T
	// Type T must support >> operator
	T t;
	std::wistringstream ist(s);
	ist >> t;
	return t;
}


/* static */
template<>
inline wstring ConfigFile::wstring_as_T<wstring>( const wstring& s )
{
	// Convert from a string to a string
	// In other words, do nothing
	return s;
}


/* static */
template<>
inline bool ConfigFile::wstring_as_T<bool>( const wstring& s )
{
	// Convert from a string to a bool
	// Interpret "false", "F", "no", "n", "0" as false
	// Interpret "true", "T", "yes", "y", "1", "-1", or anything else as true
	bool b = true;
	wstring sup = s;
	for( wstring::iterator p = sup.begin(); p != sup.end(); ++p )
		*p = toupper(*p);  // make string all caps
	if( sup==wstring(L"FALSE") || sup==wstring(L"F") ||
	    sup==wstring(L"NO") || sup==wstring(L"N") ||
	    sup==wstring(L"0") || sup==wstring(L"NONE") )
		b = false;
	return b;
}


template<class T>
T ConfigFile::read( const wstring& key ) const
{
	// Read the value corresponding to key
	mapci p = myContents.find(key);
	if( p == myContents.end() ) throw key_not_found(key);
	return wstring_as_T<T>( p->second );
}


template<class T>
T ConfigFile::read( const wstring& key, const T& value ) const
{
	// Return the value corresponding to key or given default value
	// if key is not found
	mapci p = myContents.find(key);
	if( p == myContents.end() ) return value;
	return wstring_as_T<T>( p->second );
}


template<class T>
bool ConfigFile::readInto( T& var, const wstring& key ) const
{
	// Get the value corresponding to key and store in var
	// Return true if key is found
	// Otherwise leave var untouched
	mapci p = myContents.find(key);
	bool found = ( p != myContents.end() );
	if( found ) var = wstring_as_T<T>( p->second );
	return found;
}


template<class T>
bool ConfigFile::readInto( T& var, const wstring& key, const T& value ) const
{
	// Get the value corresponding to key and store in var
	// Return true if key is found
	// Otherwise set var to given default
	mapci p = myContents.find(key);
	bool found = ( p != myContents.end() );
	if( found )
		var = wstring_as_T<T>( p->second );
	else
		var = value;
	return found;
}


template<class T>
void ConfigFile::add( wstring key, const T& value )
{
	// Add a key with given value
	wstring v = T_as_wstring( value );
	trim(key);
	trim(v);
	myContents[key] = v;
	return;
}

#endif  // CONFIGFILE_H

// Release notes:
// v1.0  21 May 1999
//   + First release
//   + Template read() access only through non-member readConfigFile()
//   + ConfigurationFileBool is only built-in helper class
// 
// v2.0  3 May 2002
//   + Shortened name from ConfigurationFile to ConfigFile
//   + Implemented template member functions
//   + Changed default comment separator from % to #
//   + Enabled reading of multiple-line values
// 
// v2.1  24 May 2004
//   + Made template specializations inline to avoid compiler-dependent linkage
//   + Allowed comments within multiple-line values
//   + Enabled blank line termination for multiple-line values
//   + Added optional sentry to detect end of configuration file
//   + Rewrote messy trimWhitespace() function as elegant trim()
