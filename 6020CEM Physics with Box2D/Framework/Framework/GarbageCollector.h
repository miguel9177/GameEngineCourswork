#pragma once
#include <memory>

namespace GarbageCollector
{
	//this struct stores every allocated information
	struct MemoryAllocationInformation
	{
		uint32_t totalMemoryAllocated = 0;

		uint32_t currentUsage() { return totalMemoryAllocated; }
	};

	static MemoryAllocationInformation memoryAllocationInformation;

	//this returns the code that contains all the memory usage information
	static std::string GetMemoryUsageText()
	{
		std::string textToReturn = "Memory usage : " + std::to_string(memoryAllocationInformation.currentUsage()) + " bytes";
		return textToReturn;
	}
}

//overides the new operator so that we can know that a new memory was allocated
void* operator new(size_t size)
{
	GarbageCollector::memoryAllocationInformation.totalMemoryAllocated += size;
	return malloc(size);
}
//overides the delete operator so that we can know that a memory was deleted
void operator delete(void* memory, size_t size)
{
	GarbageCollector::memoryAllocationInformation.totalMemoryAllocated -= size;
	free(memory);
}