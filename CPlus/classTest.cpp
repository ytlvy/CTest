#include "iostream"
#include "string" 
#include <typeinfo>
using namespace std;


//class Zero {
//public:
//	virtual void f111() { }
//};
//
//class Base : public Zero {
//public:
//	virtual void f() { }
//};
//
//class Deri1234567890ve : public Base {
//};

typedef unsigned long DWORD;

struct PMD {
	int mdisp;  //member displacement
	int pdisp;  //vbtable displacement
	int vdisp;  //displacement inside vbtable
};

struct RTTIBaseClassDescriptor {
	struct TypeDescriptor* pTypeDescriptor; //type descriptor of the class
	DWORD numContainedBases; //number of nested classes following in the Base Class Array
	struct PMD where;        //pointer-to-member displacement info
	DWORD attributes;        //flags, usually 0
};


struct TypeDescriptor {
	DWORD ptrToVTable;
	DWORD spare;
	char name[ ];
};

struct RTTIClassHierarchyDescriptor {
	DWORD signature;      //always zero?
	DWORD attributes;     //bit 0 set = multiple inheritance, bit 1 set = virtual inheritance
	DWORD numBaseClasses; //number of classes in pBaseClassArray
	struct RTTIBaseClassArray* pBaseClassArray;
};

struct RTTICompleteObjectLocator {

	DWORD signature; //always zero ?

	DWORD offset;    //offset of this vtable in the complete class

	DWORD cdOffset;  //constructor displacement offset

	struct TypeDescriptor* pTypeDescriptor; //TypeDescriptor of the complete class

	//int * ptr;
	struct RTTIClassHierarchyDescriptor* pClassDescriptor; //describes inheritance hierarchy
};

class Base
{
public:
	Base(int base):iBase(base){sCount++;};
	virtual ~Base(void){};
 
	int getIBase() const{return iBase;};
	static int instanceCount(){return sCount;};
	virtual void print() const;
 
protected:
 
	int iBase;
	static int sCount;
};

int Base::sCount = 0;
void Base::print() const{
	printf("ibase: %d, count: %d", iBase, sCount);
}

void test_base_model()
{
	Base b1(1000);
	cout << "对象b1的起始内存地址：" << &b1 << endl;
	cout << "type_info信息：" << ((int*)*(int*)(&b1) - 1) << endl;
	
//	RTTICompleteObjectLocator str=
//		*((RTTICompleteObjectLocator*)*((int*)*(int*)(&b1) - 1));
//	//abstract class name from RTTI
//	string classname(str.pTypeDescriptor->name);
//	classname = classname.substr(4,classname.find("@@")-4);
//	cout << classname <<endl;

	cout << "虚函数表地址：\t\t\t" << (int*)(&b1) << endl;
	cout << "虚函数表 — 第1个函数地址：\t" << (int*)*(int*)(&b1) << endl;
//	cout << "虚函数表 — 即析构函数地址：" << (int*)*((int*)*(int*)(&b1)) << endl;
	cout << "虚函数表 — 第2个函数地址：\t" << ((int*)*(int*)(&b1) + 1) << "\t";
	typedef void(*Fun)(void);
	Fun pFun = (Fun)*(((int*)*(int*)(&b1)) + 1);
	pFun();
	b1.print();
	cout << endl;
	cout << "推测数据成员iBase地址：\t\t" << ((int*)(&b1) +1) << "\t通过地址取值iBase的值：" << *((int*)(&b1) +1) << endl;
	cout << "Base::getIBase(): " << b1.getIBase() << endl;
 
	b1.instanceCount();
	cout << "静态函数instanceCount地址： " << b1.instanceCount << endl;
}

int main()
{
	test_base_model();
	/*Base *pderive = new Deri1234567890ve();
	int **ptr = (int **)(&pderive);
	int *ptable = (int *)(*(int *)(*ptr)); 
	int * rtti = ptable -1;

	RTTICompleteObjectLocator * RIIT_locator =   (RTTICompleteObjectLocator *)( *(int*)rtti);
	cout<<RIIT_locator->pTypeDescriptor->name<<endl;*/


//	Base *pderive = new Deri1234567890ve();
//	int *ptable = (int*)*(int*)pderive;
//	int * rtti = ptable -1;

	// 显示当前类的名字“。。Deri1234567890ve。。”
//	RTTICompleteObjectLocator * RIIT_locator =   (RTTICompleteObjectLocator *)( *(int*)rtti);
//	cout<<RIIT_locator->pTypeDescriptor->name<<endl;

	// 显示自己和所有父类的名字
//	int * p1 = (int*)(RIIT_locator->pClassDescriptor->pBaseClassArray);
//	int * p2 = (int*)*(p1+2);
//	TypeDescriptor* pDesc = (TypeDescriptor*)(*p2);
//	cout<<"One of Base Classes: "<<pDesc->name<<endl;
//
//	p1 = (int*)(RIIT_locator->pClassDescriptor->pBaseClassArray);
//	p2 = (int*)*(p1 + 1);
//	pDesc = (TypeDescriptor*)(*p2);
//	cout<<"One of Base Classes: "<<pDesc->name<<endl;
//
//	p1 = (int*)(RIIT_locator->pClassDescriptor->pBaseClassArray);
//	p2 = (int*)*(p1);
//	pDesc = (TypeDescriptor*)(*p2);
//	cout<<"One of Base Classes: "<<pDesc->name<<endl;
}