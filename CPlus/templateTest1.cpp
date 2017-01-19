#include <iostream>

template <typename T> struct Base {
   typedef int MyType;
};

template <typename T> struct Derived : Base<T> {
   void g() {
	   // A. error: ‘MyType’ was not declared in this scope
	   // MyType k = 2;

	   // B. error: need ‘typename’ before ‘Base<T>::MyType’ because
	   // ‘Base<T>’ is a dependent scope
	   Base<T>::MyType k = 2;

	   // C. works!
	   typename Base<T>::MyType k = 2;

	   std::cerr << "Derived<T>::g --> " << k << "\n";
   }
};

int main()
{
	Derived<float> df;
	df.g();
	return 0;
}