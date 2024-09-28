#pragma once
#include <cstdint>
#include <string>
#include <memory>

namespace Trengine {
	class Texture {
	public:
		virtual ~Texture() = default;
		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void bind(uint32_t slot) const = 0;


	};

	class Texture2D : public Texture {
	public:
		static std::shared_ptr<Texture2D> create(const std::string& path);

		static std::shared_ptr<Texture2D> create(uint32_t width, uint32_t height);

		virtual void setData(void* data, uint32_t size) = 0;

		virtual bool operator == (const Texture2D& other) = 0;
	};
}
