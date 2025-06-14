#pragma once
#include <random>

namespace Trengine {
	class Random
	{
	public:
		static void Init();

		static float Float();
	private:
		static std::mt19937 randomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> distribution;
	};
}