#pragma once
#include <queue>
#include <memory>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Properties/Job Properties.h>

class JobQueue
{
public:
	JobQueue();
	void Push(std::shared_ptr<JobDeclaration> job);
	std::shared_ptr<JobDeclaration> Pop();
private:
	SpinLockLTM m_mutex;
	//moodycamel::ConcurrentQueue<JobDeclaration*> m_queue;
	//concurrency::concurrent_queue<std::shared_ptr<JobDeclaration>> m_queue;
	std::queue<std::shared_ptr<JobDeclaration>> m_queue;
};
