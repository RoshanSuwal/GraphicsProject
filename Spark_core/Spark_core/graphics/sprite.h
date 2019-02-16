#pragma once
#include"../Renderer/renderable2d.h"

namespace sparky { namespace graphics {

	class Sprite:public Renderable2D {

		private:

		public:
			Sprite(float x, float y, float width, float height, const maths::vec4& color);
			void setTranslation(float x,float y,float z);
			void setrotation();

	};

} }
