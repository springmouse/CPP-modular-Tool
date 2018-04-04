#pragma once
#include <vector>
#include <GL/glew.h>

struct VertexBufferElemnt
{
	unsigned int count;
	unsigned int type;
	unsigned int normalised;
};

class VertextBufferLayout
{
public:
	VertextBufferLayout() : m_stride(0) {};
	~VertextBufferLayout() {};

	template<typename t>
	void Push(int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(int count)
	{
		m_elements.push_back({GL_FLOAT, count, false});
		m_stride += sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_stride += sizeof(GLuint);
	}


	template<>
	void Push<unsigned char>(int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, true });
		m_stride += sizeof(GLbyte);
	}

	inline const std::vector<VertexBufferElemnt> GetElements() const& { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }

private:
	std::vector<VertexBufferElemnt> m_elements;
	unsigned int m_stride;
};

