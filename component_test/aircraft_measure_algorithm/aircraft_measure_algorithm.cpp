#include "component.h"
#include "simple_compare_algorithm.h"

extern "C" __declspec(dllexport) void RegisterAlgorithm(AlgorithmList &algorithmList)
{
    SimpleCompareAlgorithm *algorithm = new SimpleCompareAlgorithm();
    algorithm->m_Name = (LPWSTR)SimpleCompareAlgorithm::SimpleCompareAlgorithmName;
    algorithmList.push_back(algorithm);
}

extern "C" __declspec(dllexport) void RegisterGetComponentListFunc(Component::GetComponentListFunc getComponentListFunc)
{
    Component::GetComponentList = getComponentListFunc;
}
