// elecstudy.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "elecstudy.h"


// 这是导出变量的一个示例
ELECSTUDY_API int nelecstudy=0;

// 这是导出函数的一个示例。
ELECSTUDY_API int fn_add(int a, int b)
{
    return a + b;
}

// 这是已导出类的构造函数。
Celecstudy::Celecstudy()
{
    return;
}
