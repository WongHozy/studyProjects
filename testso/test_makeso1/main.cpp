
#include <iostream>
#include <dlfcn.h>
#include "test.h"

using namespace std;

typedef Test* (*so_init)();

struct Plugin {
	void* handle;
	Test* sym_set;

	Plugin():handle(NULL), sym_set(NULL) { }
	~Plugin() {
		if(sym_set) { delete sym_set; }
		if(handle) { dlclose(handle); }
	}
};

int create_instance(const char* so_file, Plugin& p) {

	p.handle = dlopen(so_file, RTLD_NOW | RTLD_DEEPBIND);
	if (!p.handle) {
		cout << "Cannot open library: " << dlerror() << endl;
		return -1;
	}
	else {
		cout << "open library ok" << endl;
	}

	so_init create_fun = (so_init)dlsym(p.handle, "create");

	if(!create_fun) {
		cout << "Cannot load symbol" << endl;
		dlclose(p.handle);
		return -1;
	}
	else {
		cout << "load symbol ok" << endl;
	}

	p.sym_set = create_fun();

	return 0;
}

int main() {

	Plugin p1;
	Plugin p2;

	int r1, r2;
	r1 = create_instance("./libtest_1.so", p1);
	r2 = create_instance("./libtest_2.so", p2);

	if (0 != r1 || 0 != r2) {
		cout << "create_instance failed" << endl;
		return 0;
	}
	else {
		cout << "create_instance success" << endl;
	}

	p1.sym_set->setnumber(1);
	p2.sym_set->setnumber(2);

	cout << "t1 g_num is " << p1.sym_set->getnumber() << endl;
	cout << "t2 g_num is " << p2.sym_set->getnumber() << endl;

	return 0;
}

