/**
* @file
* @brief MatLab辅助函数cpp文件.
* @author ruoxi
*
* 实现了MatLab辅助函数.
*/

#include "matlab_helper.h"

Array *MatLabHelper::CreateDoubleArray(UINT32 x, UINT32 y, const char *content)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    if (content)
    {
        double *p = mxGetPr(a);
        for (UINT32 i = 0; i < x * y; ++i)
        {
            p[i] = content[i];
        }
    }

    return a;
}

void MatLabHelper::DestroyArray(Array *a)
{
    mxDestroyArray(a);
}
