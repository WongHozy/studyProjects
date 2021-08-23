
#include <iostream>
#include "test.h"

int g_num = 0;

int Test::getnumber() { return g_num; }
void Test::setnumber(const int num) {
	g_num = num;
}

#ifdef __cplusplus
extern "C" {
#endif

Test* create() {
	return new Test;
}

#ifdef __cplusplus
}
#endif
