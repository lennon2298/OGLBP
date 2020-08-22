#pragma once

#include <glad/glad.h>
#include <vector>

struct LayoutElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static int GetSizeofType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			break;
		}
		return 0;
	}
};

class BufferLayout
{
private:
	std::vector<LayoutElement> m_Elements;
	unsigned int m_Stride;

public:
	BufferLayout()
		: m_Stride(0) {}
	~BufferLayout(){};

	template <typename T>
	void Push(unsigned int count)
	{
		static_assert(true);
	}

	inline const std::vector<LayoutElement> &GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

template <>
void BufferLayout::Push<float>(unsigned int count)
{
	m_Elements.push_back({GL_FLOAT, count, false});
	m_Stride += count * LayoutElement::GetSizeofType(GL_FLOAT);
}

template <>
void BufferLayout::Push<unsigned int>(unsigned int count)
{
	m_Elements.push_back({GL_UNSIGNED_INT, count, false});
	m_Stride += count * LayoutElement::GetSizeofType(GL_UNSIGNED_INT);
}

template <>
void BufferLayout::Push<unsigned char>(unsigned int count)
{
	m_Elements.push_back({GL_UNSIGNED_BYTE, count, true});
	m_Stride += count * LayoutElement::GetSizeofType(GL_UNSIGNED_BYTE);
}
