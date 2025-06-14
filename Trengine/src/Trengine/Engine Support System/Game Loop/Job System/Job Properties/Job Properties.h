#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <Trengine/Engine Support System/Memory Management/Stack Allocator/StackAllocator.h>
#include <Trengine/Engine Support System/Memory Management/Double-Buffured Allocator/DoubleBufferedAllocator.h>
#include <Trengine/Engine Support System/Memory Management/Double-Ended Stack Allocator/DoubleEndedStackAllocator.h>
#include <Trengine/Engine Support System/Memory Management/Pool Allocator/PoolAllocator.h>
#include <Trengine/Engine Support System/Game Loop/Mutex/Mutex.h>
#include <condition_variable>
#include <Trengine/Engine Support System/Game Loop/Spin Lock/ScopedLock.h>	
#include <Trengine/Engine Support System/Game Loop/Spin Lock/SpinLockLTM.h>

enum class Priority {
	LOW, NORMAL, HIGH, CRITICAL
};

struct Counter {
	std::uint32_t m_count = 1;
	std::mutex m_mutex;
	std::condition_variable m_condVar;

	Counter() {

	}
	Counter(const Counter& c) {
		m_count = c.m_count;
	}
};

struct JobParams {
	//thread provides:
	std::shared_ptr<StackAllocator> m_stack = nullptr;
	std::shared_ptr<DoubleEndedStackAllocator> m_doubleEndedStack = nullptr;
	std::shared_ptr<DoubledBufferedAllocator> m_doubleBuffers = nullptr;

	std::atomic<std::shared_ptr<Counter>> m_pCounter = std::shared_ptr<Counter>(new Counter());
	PVOID m_fiberParent = nullptr;

	//caller provides:
	std::shared_ptr<void> m_funcParams = nullptr;

};
using EntryPoint = void(__stdcall*)(std::shared_ptr<JobParams>);

struct JobDeclaration {
	EntryPoint m_pEntryPoint = nullptr;
	std::shared_ptr<JobParams> m_params = nullptr;
};