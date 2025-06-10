#pragma once
#include <memory>
#include <cstdint>
#include <Trengine/Engine Support System/Game Loop/CPUSpecs/CPUSpecs.h>
#include <vector>
#include <cassert>
#include <Trengine/Engine Support System/Game Loop/Job System/Thread/ThreadLTM.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Properties/Job Properties.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Queue/JobQueue.h>
#include <Trengine/Engine Support System/Game Loop/Mutex/Mutex.h>
#include <Trengine/Engine Support System/Game Loop/Spin Lock/SpinLockLTM.h>
#include <Trengine/Engine Support System/Game Loop/GameLoopManager/GameLoopManager.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Fiber/FiberLTM.h>


class JobSystem {
public:
	static void init();
	static void destroy();

	static void kickJob(std::shared_ptr<JobDeclaration>& decl);
	static void kickJobs(int count, std::shared_ptr<JobDeclaration> aDecl[]);
	// wait for job to terminate (for its Counter to become zero)
	static void waitForCounter(std::atomic<std::shared_ptr<Counter>>& pCounter);

	// kick jobs and wait for completion
	static void kickJobAndWait(std::shared_ptr<JobDeclaration>& decl);
	static void kickJobsAndWait(int count, std::shared_ptr<JobDeclaration> aDecl[]);

private:
	static std::unique_ptr<JobSystem> s_instance;

	std::vector<std::shared_ptr<ThreadLTM>> m_threadPool;
	std::shared_ptr<JobQueue> m_queueObj;
	std::shared_ptr<std::mutex> m_mutexThread = std::shared_ptr<std::mutex>(new std::mutex());
	std::shared_ptr<std::condition_variable> m_condVarQueue = std::shared_ptr<std::condition_variable>(new std::condition_variable());
	std::shared_ptr<bool> m_queueReady = std::shared_ptr<bool>(new bool(false));;

	JobSystem();
	//void initCounter(JobDeclaration& decl);
};