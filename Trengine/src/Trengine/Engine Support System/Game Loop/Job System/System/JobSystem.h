#pragma once
#include <memory>
#include <cstdint>
#include <Trengine/Engine Support System/Game Loop/CPUSpecs/CPUSpecs.h>
#include <vector>
#include <Trengine/Engine Support System/Game Loop/Job System/Thread/ThreadLTM.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Properties/Job Properties.h>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Queue/JobQueue.h>

class JobSystem {
public:
	static void init();
	static void destroy();

	void KickJob(const JobDeclaration& decl);
	void KickJobs(int count, const JobDeclaration aDecl[]);
	// wait for job to terminate (for its Counter to become zero)
	void WaitForCounter(Counter* pCounter);
	// kick jobs and wait for completion
	void KickJobAndWait(const JobDeclaration& decl);
	void KickJobsAndWait(int count, const JobDeclaration aDecl[]);
private:
	static std::unique_ptr<JobSystem> s_instance;

	std::vector<ThreadLTM> m_threadPool;
	std::shared_ptr<JobQueue> m_queueObj;

	JobSystem();
};