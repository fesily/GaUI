#ifndef defines_h__
#define defines_h__

#if (defined _MSC_VER )&&(_MSC_VER <= 1600)
#define __USE_STD_EX__
#endif

#ifdef __USE_STD_EX__
#define  ENUM_CLASS_BEGIN(name) class name { enum name{
#define ENUM_CLASS_END() };};
#else
#define  ENUM_CLASS_BEGIN(name) enum class name{
#define ENUM_CLASS_END() };
#endif // __USE_STD_EX__


#define SAFE_DELETE(ptr) if (ptr) { delete ptr; ptr = nullptr; }
#define SAFE_DELETE_AR(ptr) if (ptr) { delete [] ptr; ptr = nullptr; }

#endif // defines_h__
