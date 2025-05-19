#pragma once
#include <queue>
#include <memory>
#include <Trengine/Engine Support System/Game Loop/Job System/Job Properties/Job Properties.h>

class JobQueue
{
public:
	JobQueue();
	void Push();
	std::shared_ptr<JobDeclaration> Pop();
private:
	std::queue<std::shared_ptr<JobDeclaration>> m_queue;
};

