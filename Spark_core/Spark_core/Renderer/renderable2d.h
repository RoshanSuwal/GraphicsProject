#pragma once

#include"../graphics/buffer.h"
#include"../graphics/indexBuffer.h"
#include"../graphics/vertexArray.h"

#include"../maths/maths.h"
#include"../graphics/shader.h"


namespace sparky {namespace graphics {

	struct VertexData {
		maths::vec3 vertice;
		//maths::vec4 color;
		unsigned int color;
	};

	class Renderable2D {

	protected:
		maths::vec2 m_Size;
		maths::vec3 m_Position;
		maths::vec4 m_Color;

		

	public:
		Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
			:m_Position(position), m_Color(color), m_Size(size) {
		}

		virtual ~Renderable2D() {}

	public:
		inline const maths::vec3& getPositon ()const { return m_Position; }
		inline const maths::vec2& getSize() const { return m_Size; }
		inline const maths::vec4& getColor() const { return m_Color; }




	};

} }