#include "MemoryManager.hpp"

#include <iostream>

/*
//MyClass* MemoryManager::myClasses;
unsigned int MemoryManager::myClassCount = 0;

unsigned int MemoryManager::initialMyClassCount = 100;

void MemoryManager::init() {
//	myClasses = new MyClass[initialMyClassCount];
	myClassCount = 0;
}

void MemoryManager::log() {
//	static MyClass& object;
	for (int i = 0; i < myClassCount; ++i)
	{
		object = myClasses[i];
		object.log();
	}
}

void MemoryManager::deallocateAllMyClass() {
	static MyClass& object;
	for (int i = 0; i < myClassCount; ++i)
	{
		object = myClasses[i];
		object.reset();
	}
}

MyClass* MemoryManager::allocateMyClass() {
	static MyClass* object;
	if (myClassCount > initialMyClassCount) {
		std::cout << "RAN OUT OF MEMORY" << std::endl;
		return NULL;
	}

	object = &myClasses[myClassCount];
	myClassCount++;

	return object;
}
*/
