#pragma once
#include <vector>
#include <GL/glew.h>
//#include "GL_Calls.h"


struct VertexBufferElemnt
{
	unsigned int type;
	unsigned int count;
	unsigned int normalised;
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}

		ASSERT(false);
		return 0;
	}
};

class VertextBufferLayout
{
public:
	VertextBufferLayout() : m_stride(0) {};
	~VertextBufferLayout() {};

	template<typename t>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_elements.push_back({GL_FLOAT, count, GL_FALSE });
		m_stride += VertexBufferElemnt::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElemnt::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}


	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElemnt::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElemnt> GetElements() const& { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }

private:
	std::vector<VertexBufferElemnt> m_elements;
	unsigned int m_stride;
};

