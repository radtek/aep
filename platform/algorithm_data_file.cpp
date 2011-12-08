#include "algorithm_data_file.h"

AlgorithmDataFile::AlgorithmDataFile(wstring fileName)
:
DataFile(fileName)
{
}

AlgorithmDataFile::~AlgorithmDataFile()
{
}

AlgorithmList &AlgorithmDataFile::GetAlgorithmList()
{
    return m_AlgorithmList;
}

InternalAlgorithmMap &AlgorithmDataFile::GetInternalAlgorithmMap()
{
    return m_InternalAlgorithmMap;
}

RC AlgorithmDataFile::InsertAlgorithm(const Algorithm &algorithm)
{
    RC rc;

    if (m_Lines.find(algorithm.GetName()) != m_Lines.end())
    {
        return RC::ALGORITHM_INSERT_ERROR;
    }

    wostringstream ost;
    ost << algorithm.GetName()
        << TEXT(" ")
        << algorithm.GetDllFileName()
        << TEXT(" ")
        << algorithm.GetFuncName()
        << TEXT(" ")
        << algorithm.GetIconFileName()
        << endl;
    m_Lines[algorithm.GetName()] = ost.str();

    CHECK_RC(Save());

    return rc;
}

RC AlgorithmDataFile::RemoveAlgorithm(wstring name)
{
    RC rc;

    if (m_Lines.find(name) == m_Lines.end())
    {
        return RC::ALGORITHM_REMOVE_ERROR;
    }

    m_Lines.erase(name);

    CHECK_RC(Save());

    return rc;
}

/*
RC AlgorithmDataFile::ParseLine(const wstring &line)
{
    RC rc;

    wistringstream ist(line);

    UINT32 id;
    wstring name, dllFileName, funcName, iconFileName;
    ist >> id >> name >> dllFileName >> funcName >> iconFileName;

    ParamNameList paramNameList;
    while (!ist.eof())
    {
        wstring paramName;
        ist >> paramName;
        if (!paramName.empty())
        {
            paramNameList.push_back(paramName);
        }
    }

    m_AlgorithmList.push_back(Algorithm(id, name, dllFileName, funcName, iconFileName, paramNameList));

    return rc;
}
*/

RC AlgorithmDataFile::ParseLine(const wstring &line)
{
    RC rc;

    wistringstream ist(line);

    UINT32 algorithmId;
    wstring name, dllFileName, funcName, iconFileName;
    ist >> algorithmId >> name >> dllFileName >> funcName >> iconFileName;

    ParamNameList paramNameList;
    while (!ist.eof())
    {
        wstring paramName;
        ist >> paramName;
        if (!paramName.empty())
        {
            paramNameList.push_back(paramName);
        }
    }

    m_InternalAlgorithmMap[algorithmId] = InternalAlgorithm(algorithmId, name, dllFileName, funcName);

    return rc;
}
