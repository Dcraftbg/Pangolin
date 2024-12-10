#pragma once
#include <kpanic.h>
#define assert(x) if(!(x)) kpanic("Assertion failed: %s", #x)
