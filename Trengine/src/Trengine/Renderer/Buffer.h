#pragma once
#include "Log.h"

namespace Trengine {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool

	};

	extern uint32_t ShaderDataTypeSize(ShaderDataType type);

	extern uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type);

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized = false;

		BufferElement(ShaderDataType type, const std::string& name)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0)
		{

		}

		uint32_t GetComponentCount() const {
			switch (type) {
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3: return 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;
			case ShaderDataType::Bool: return 1;
			}

			TR_CORE_ASSERT(false, "Unknown Shader Data Type");
			return 0;
		}
	};

	class BufferLayout {
	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	private:
		void calculateOffsetAndStride() {
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : elements) {
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements) {
			calculateOffsetAndStride();
		}
		uint32_t getStride() const { return stride; }

		const std::vector<BufferElement>& getElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
	};

	class VertexBuffer {
	protected:
		BufferLayout layout;

	public:
		virtual ~VertexBuffer() {}
		virtual void bind() const = 0;
		virtual void unBind() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;
		virtual BufferLayout& getLayout() = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	protected:
		uint32_t count;
	public:
		virtual ~IndexBuffer() {}
		virtual void bind() const = 0;
		virtual void unBind() const = 0;
		const uint32_t getCount() const { return count; }

		static IndexBuffer* Create(unsigned int* indices, uint32_t size);
	};
}
