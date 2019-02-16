#pragma once

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"../maths/maths.h"

namespace sparky {
	namespace graphics {

#define MAX_KEYS    1024
#define MAX_BUTTONS 32

		class Window
		{
		private:
			const char *m_title;
			int m_width, m_height;
			GLFWwindow *m_window;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			double m_MouseX, m_MouseY;


		public:
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }
			inline void setWidth(int width) { m_width = width; }
			inline void setHeight(int height) { m_height = height; }

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button)const;
			void getMousePosition(double &x, double &y)const;

		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};

	}
}
