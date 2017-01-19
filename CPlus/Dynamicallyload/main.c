#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "somelib.h"

// Prototype for a function pointer for add_data
typedef DataPoint (*add_data_fn_t)(const DataPoint* dps, unsigned n);

int main(int argc, const char* argv[])
{
	void* libhandle = dlopen("./libsomelib.so", RTLD_LAZY);
	if (!libhandle) {
		fprintf(stderr, "dlopen error: %s\n", dlerror());
		exit(1);
	}

	printf("dlopen success: handle %p\n", libhandle);

	// We know the prototype of add_data so we can directly assign it to a
	// function pointer of the correct type.
	add_data_fn_t add_data_fn = dlsym(libhandle, "add_data");
	char* err = dlerror();
	if (err) {
		fprintf(stderr, "dlsym failed: %s\n", err);
		exit(1);
	}

	DataPoint dp[4] = {{2, 2.2}, {3, 3.3}, {4, 4.4}, {5, 5.5}};

	printf("Calling add_data\n");
	DataPoint dout = add_data_fn(dp, sizeof(dp) / sizeof(DataPoint));

	printf("dout = {%d, %lf}\n", dout.num, dout.dnum);
	return 0;
}