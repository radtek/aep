// ConfigFile.cpp

#include "config_file.h"

using std::wstring;

ConfigFile::ConfigFile( wstring filename, wstring delimiter,
                        wstring comment, wstring sentry )
	: myDelimiter(delimiter), myComment(comment), mySentry(sentry)
{
	// Construct a ConfigFile, getting keys and values from given file
	
	std::wifstream in( filename.c_str() );
	
	if( !in ) throw file_not_found( filename ); 
	
	in >> (*this);
}


ConfigFile::ConfigFile()
	: myDelimiter( wstring(1,L'=') ), myComment( wstring(1,L'#') )
{
	// Construct a ConfigFile without a file; empty
}


void ConfigFile::remove( const wstring& key )
{
	// Remove key and its value
	myContents.erase( myContents.find( key ) );
	return;
}


bool ConfigFile::keyExists( const wstring& key ) const
{
	// Indicate whether key is found
	mapci p = myContents.find( key );
	return ( p != myContents.end() );
}


/* static */
void ConfigFile::trim( wstring& s )
{
	// Remove leading and trailing whitespace
	static const wchar_t whitespace[] = L" \n\t\v\r\f";
	s.erase( 0, s.find_first_not_of(whitespace) );
	s.erase( s.find_last_not_of(whitespace) + 1U );
}


std::wostream& operator<<( std::wostream& os, const ConfigFile& cf )
{
	// Save a ConfigFile to os
	for( ConfigFile::mapci p = cf.myContents.begin();
	     p != cf.myContents.end();
		 ++p )
	{
		os << p->first << L" " << cf.myDelimiter << L" ";
		os << p->second << std::endl;
	}
	return os;
}


std::wistream& operator>>( std::wistream& is, ConfigFile& cf )
{
	// Load a ConfigFile from is
	// Read in keys and values, keeping internal whitespace
	typedef wstring::size_type pos;
	const wstring& delim  = cf.myDelimiter;  // separator
	const wstring& comm   = cf.myComment;    // comment
	const wstring& sentry = cf.mySentry;     // end of file sentry
	const pos skip = delim.length();        // length of separator
	
	wstring nextline = L"";  // might need to read ahead to see where value ends
	
	while( is || nextline.length() > 0 )
	{
		// Read an entire line at a time
		wstring line;
		if( nextline.length() > 0 )
		{
			line = nextline;  // we read ahead; use it now
			nextline = L"";
		}
		else
		{
			std::getline( is, line );
		}
		
		// Ignore comments
		line = line.substr( 0, line.find(comm) );
		
		// Check for end of file sentry
		if( sentry != L"" && line.find(sentry) != wstring::npos ) return is;
		
		// Parse the line if it contains a delimiter
		pos delimPos = line.find( delim );
		if( delimPos < wstring::npos )
		{
			// Extract the key
			wstring key = line.substr( 0, delimPos );
			line.replace( 0, delimPos+skip, L"" );
			
			// See if value continues on the next line
			// Stop at blank line, next line with a key, end of stream,
			// or end of file sentry
			bool terminate = false;
			while( !terminate && is )
			{
				std::getline( is, nextline );
				terminate = true;
				
				wstring nlcopy = nextline;
				ConfigFile::trim(nlcopy);
				if( nlcopy == L"" ) continue;
				
				nextline = nextline.substr( 0, nextline.find(comm) );
				if( nextline.find(delim) != wstring::npos )
					continue;
				if( sentry != L"" && nextline.find(sentry) != wstring::npos )
					continue;
				
				nlcopy = nextline;
				ConfigFile::trim(nlcopy);
				if( nlcopy != L"" ) line += L"\n";
				line += nextline;
				terminate = false;
			}
			
			// Store key and value
			ConfigFile::trim(key);
			ConfigFile::trim(line);
			cf.myContents[key] = line;  // overwrites if key is repeated
		}
	}
	
	return is;
}
