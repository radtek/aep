#ifndef __ALGORITHM_DATA_FILE_H__
#define __ALGORITHM_DATA_FILE_H__

#include "data_file.h"
#include "algorithm.h"
#include "internal_algorithm.h"

class AlgorithmDataFile : public DataFile
{
public:
    typedef Algorithm::ParamNameList ParamNameList;
public:
    AlgorithmDataFile(wstring fileName);
    virtual ~AlgorithmDataFile();

    AlgorithmList &GetAlgorithmList();
    InternalAlgorithmMap &GetInternalAlgorithmMap();
    RC InsertAlgorithm(const Algorithm &algorithm);
    RC RemoveAlgorithm(wstring name);
protected:
    virtual RC ParseLine(const wstring &line);

protected:
    AlgorithmList m_AlgorithmList;
    InternalAlgorithmMap m_InternalAlgorithmMap;
};

#endif // __ALGORITHM_DATA_FILE_H__
