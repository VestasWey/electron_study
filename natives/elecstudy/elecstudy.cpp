// elecstudy.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "elecstudy.h"

namespace
{
    /*fnStrCallback1 str_cb1 = nullptr;
    fnStrCallback2 str_cb2 = nullptr;
    fnStrCallback3 str_cb3 = nullptr;

    fnpCharCallback1 pchar_cb1 = nullptr;
    fnpCharCallback2 pchar_cb2 = nullptr;
    fnpCharCallback3 pchar_cb3 = nullptr;

    fnppCharCallback1 ppchar_cb1 = nullptr;
    fnppCharCallback2 ppchar_cb2 = nullptr;
    fnppCharCallback3 ppchar_cb3 = nullptr;*/
}

// 这是导出变量的一个示例
ELECSTUDY_API int nelecstudy=0;

// 这是导出函数的一个示例。
ELECSTUDY_API int fn_add(int a, int b)
{
    return a + b;
}


ELECSTUDY_API void fn_set_str_callback1(fnStrCallback1 callback)
{
    callback("const std::string& str");
}

ELECSTUDY_API void fn_set_str_callback2(fnStrCallback2 callback)
{
    std::string str("std::string& str");
    callback(str);
}

ELECSTUDY_API void fn_set_str_callback3(fnStrCallback3 callback)
{
    callback("std::string& str");
}


ELECSTUDY_API void fn_set_pchar_callback1(fnpCharCallback1 callback)
{
    callback("const char* str");
}

ELECSTUDY_API void fn_set_pchar_callback2(fnpCharCallback2 callback)
{
    callback("const char* const str");
}

ELECSTUDY_API void fn_set_pchar_callback3(fnpCharCallback3 callback)
{
    callback(const_cast<char*>("char*"));
}


ELECSTUDY_API void fn_set_ppchar_callback1(fnppCharCallback1 callback)
{
    const char* pstr = "const char** str";
    callback(&pstr);
}

ELECSTUDY_API void fn_set_ppchar_callback2(fnppCharCallback2 callback)
{
    const char* pstr = "const char** const str";
    callback(&pstr);
}

ELECSTUDY_API void fn_set_ppchar_callback3(fnppCharCallback3 callback)
{
    const char* pstr = "char** str";
    callback(const_cast<char**>(&pstr));
}

// 这是已导出类的构造函数。
Celecstudy::Celecstudy()
{
    return;
}
