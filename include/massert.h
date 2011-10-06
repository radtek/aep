#ifndef __MASSERT_H__
#define __MASSERT_H__

extern void AssertFail(const char *file, int line, const char *function, const char *cond);

#ifdef _DEBUG
   #define MASSERT(cond) ((void)((cond) || (AssertFail(__FILE__, __LINE__, __FUNCSIG__, #cond), 0)))
#else
   #define MASSERT(cond) ((void)0)
#endif

#endif // __MASSERT_H__
