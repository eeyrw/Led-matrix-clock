#ifndef __VERSION_H__
#define __VERSION_H__

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define MAJOR_VER 1
#define MINOR_VER 0
#define VER_STRING "V" STR(MAJOR_VER) "." STR(MINOR_VER)

#endif