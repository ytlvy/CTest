#include "generic_interface.h"
#include <iostream>
#include <windows.h>

using namespace std;

// A factory of IKlass-implementing objects looks thus
typedef IKlass* (__cdecl *iklass_factory)();


int main()
{
	// Load the DLL
	HINSTANCE dll_handle = ::LoadLibrary(TEXT("mylib.dll"));
	if (!dll_handle) {
		cerr << "Unable to load DLL!\n";
		return 1;
	}

	// Get the function from the DLL
	iklass_factory factory_func = reinterpret_cast<iklass_factory>(
		::GetProcAddress(dll_handle, "create_klass"));
	if (!factory_func) {
		cerr << "Unable to load create_klass from DLL!\n";
		::FreeLibrary(dll_handle);
		return 1;
	}

	// Ask the factory for a new object implementing the IKlass
	// interface
	IKlass* instance = factory_func();

	// Play with the object
	int t = instance->do_stuff(5);
	cout << "t = " << t << endl;
	instance->do_something_else(100.3);
	int t2 = instance->do_stuff(0);
	cout << "t2 = " << t2 << endl;

	// Destroy it explicitly
	instance->destroy();
	::FreeLibrary(dll_handle);

	return 0;
}