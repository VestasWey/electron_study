#include <string>
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ELECSTUDY_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ELECSTUDY_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ELECSTUDY_EXPORTS
#define ELECSTUDY_API __declspec(dllexport)
#else
#define ELECSTUDY_API __declspec(dllimport)
#endif

// 此类是从 dll 导出的
class ELECSTUDY_API Celecstudy {
public:
	Celecstudy(void);
	// TODO: 在此处添加方法。
};

extern ELECSTUDY_API int nelecstudy;

extern "C"
{
    ELECSTUDY_API int fn_add(int a, int b);


    typedef void(*fnStrCallback1) (const std::string& str);
    ELECSTUDY_API void fn_set_str_callback1(fnStrCallback1 callback);

    typedef void(*fnStrCallback2) (std::string& str);
    ELECSTUDY_API void fn_set_str_callback2(fnStrCallback2 callback);

    typedef void(*fnStrCallback3) (std::string str);
    ELECSTUDY_API void fn_set_str_callback3(fnStrCallback3 callback);


    typedef void(*fnpCharCallback1) (const char* str);
    ELECSTUDY_API void fn_set_pchar_callback1(fnpCharCallback1 callback);

    typedef void(*fnpCharCallback2) (const char* const str);
    ELECSTUDY_API void fn_set_pchar_callback2(fnpCharCallback2 callback);

    typedef void(*fnpCharCallback3) (char* str);
    ELECSTUDY_API void fn_set_pchar_callback3(fnpCharCallback3 callback);


    typedef void(*fnppCharCallback1) (const char** str);
    ELECSTUDY_API void fn_set_ppchar_callback1(fnppCharCallback1 callback);

    typedef void(*fnppCharCallback2) (const char** const str);
    ELECSTUDY_API void fn_set_ppchar_callback2(fnppCharCallback2 callback);

    typedef void(*fnppCharCallback3) (char** str);
    ELECSTUDY_API void fn_set_ppchar_callback3(fnppCharCallback3 callback);
}
