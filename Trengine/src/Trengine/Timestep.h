#pragma once

namespace Trengine {
	class Timestep {
	private:
		float time;
	public:
		Timestep(float time = 0.0f)
			: time(time) {}

		float getSeconds() const { return time; }
		float getMiliseconds() const { return time * 1000.0f; }

		operator float() const { return time; }
		float operator *(const float& value) const { return this->getMiliseconds() * value; }
	};
}
