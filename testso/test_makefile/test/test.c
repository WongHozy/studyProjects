#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

using namespace std;

int main(int argc, char** argv)
{
	
	typedef void (*pf_t)();

	char* err = NULL;

	void* handle = dlopen(argv[1], RTLD_LAZY);

	if(!handle) {
		cout << "load" << argv[1] << "failed!" << dlerror() << endl;
		return 0;
	}
	else {
		cout << "load:" << argv[1] << endl;
	}

	dlerror();

	pf_t pf = (pf_t)dlsym(handle, "fcn");
	err = dlerror();

	if(err) {
		cout << "can't find symbol fcn!" << err << endl;
		return 0;
	}

	pf();
	dlclose(handle);

	return 0;
}
