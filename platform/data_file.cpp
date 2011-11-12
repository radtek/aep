#include "data_file.h"
#include "utility.h"

DataFile::DataFile(wstring fileName, wstring comment)
:
m_FileName(fileName),
m_Comment(comment)
{
	wifstream in(fileName.c_str());
    in.imbue(locale("chs"));
	in >> (*this);
    in.close();
}

DataFile::~DataFile()
{
}

RC DataFile::Parse()
{
    RC rc;

    for(map<wstring, wstring>::const_iterator it = m_Lines.begin();
        it != m_Lines.end();
		++it)
	{
        CHECK_RC(ParseLine(it->second));
	}

    return rc;
}

RC DataFile::Save()
{
    RC rc;

    wofstream out(m_FileName.c_str());
    out.imbue(locale("chs"));
    out << (*this);
    if (out.fail())
    {
        out.close();
        return RC::FILE_OPEN_ERROR;
    }
    out.close();

    return rc;
}

wostream &operator<<(wostream &os, const DataFile &file)
{
    for(map<wstring, wstring>::const_iterator it = file.m_Lines.begin();
        it != file.m_Lines.end();
		++it)
	{
        os << it->second << endl;
	}
	return os;
}

wistream &operator>>(wistream &is, DataFile &file)
{
	wstring nextLine = L"";  // might need to read ahead to see where value ends
	
	while(is || nextLine.length() > 0 )
	{
		// Read an entire line at a time
		wstring line;
		if(nextLine.length() > 0)
		{
			line = nextLine;  // we read ahead; use it now
			nextLine = L"";
		}
		else
		{
			getline(is, line);
		}
		
		// Ignore comments
		line = line.substr(0, line.find(file.m_Comment));

        if (line.length() == 0)
        {
            continue;
        }

        // Extract the key
        wistringstream ist(line);
        wstring key;
        ist >> key;
	
        file.m_Lines[key] = line;
	}
	
	return is;
}
