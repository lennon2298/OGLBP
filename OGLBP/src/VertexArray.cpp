#include "VertexArray.h"
#include "ErrorHandling.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_Renderer));
}

VertexArray::~VertexArray()
{
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	unsigned int count = 0;
	for (const auto& element : elements) {
		//const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(count));
		GLCall(glVertexAttribPointer(count, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (GLvoid*)offset));
		offset += element.count * LayoutElement::GetSizeofType(element.type);
		count++;
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Renderer);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
