#pragma once
#include <memory>
#include <thread>
#include <Trengine/Engine Support System/Memory Management/Double-Buffured Allocator/DoubleBufferedAllocator.h>
#include <Trengine/Engine Support System/Memory Management/Double-Ended Stack Allocator/DoubleEndedStackAllocator.h>
#include <Trengine/Engine Support System/Memory Management/Stack Allocator/StackAllocator.h>
#include <Trengine/Engine Support System/Memory Management/Pool Allocator/PoolAllocator.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Properties/Job Properties.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Properties/Job Properties.h>
#include <Windows.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Fiber/FiberLTM.h>
#include <Trengine/Engine Support System/Game Loop/Spin Lock/SpinLockLTM.h>
#include <Trengine/Engine Support System/Game Loop/Spin Lock/ScopedLock.h>
#include <Trengine/Engine Support System/Game Loop/GameLoopManager/GameLoopManager.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Queue/JobQueue.h>
#include <Trengine/Engine Support System/Game Loop/CPUSpecs/CPUSpecs.h>
#include <Trengine/Utilities/L-T-M Core Utilities.h>
#include <string>
#include <mutex>

class ThreadLTM {
public:
	ThreadLTM();
	ThreadLTM(std::shared_ptr<JobQueue> queue, std::uint8_t core_id, std::shared_ptr<std::mutex> m_mutexThread, std::shared_ptr<std::condition_variable> m_condVarQueue, std::shared_ptr<bool> m_queueReady);

	void destroy();
private:
	std::shared_ptr<std::thread> m_thread = nullptr;
	std::uint32_t m_threadID = 0;
	std::uint8_t m_coreID = 0;

	FiberLTM* m_masterFiber = nullptr;
	std::shared_ptr<JobDeclaration> m_masterJob;
	std::shared_ptr<JobQueue> m_queue;
	std::shared_ptr<StackAllocator> m_stack;
	std::shared_ptr<DoubleEndedStackAllocator> m_doubleEndedStack;
	std::shared_ptr<DoubledBufferedAllocator> m_doubleBuffers;

	SpinLockLTM m_lockRunning;
	std::shared_ptr<std::mutex> m_mutexThread = nullptr;
	std::shared_ptr<std::condition_variable> m_condVarQueue = nullptr;
	std::shared_ptr<bool> m_queueReady = nullptr;

	void entryPointThread();
};