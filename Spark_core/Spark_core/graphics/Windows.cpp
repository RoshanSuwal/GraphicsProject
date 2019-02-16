#include"Windows.h"

namespace sparky {
	namespace graphics
	{

		void window_Resize(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		Window::Window(const char *title, int width, int height) {
			m_title = title;
			m_height = height;
			m_width = width;

			if (!init()) {
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++)
				m_Keys[i] = false;
			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseButtons[i] = false;
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW" << std::endl;
				return false;
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_window) {
				glfwTerminate();
				std::cout << "failed to create window" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_window);
			glfwSetWindowSizeCallback(m_window, window_Resize);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);
			glfwSwapInterval(0.0);

			if (glewInit() != GLEW_OK) {
				std::cout << "couldnot initialise glew" << std::endl;
				return false;
			}
			return true;

		}

		bool Window::isKeyPressed(unsigned int keycode) const {
			//TODO: log this
			if (keycode >= MAX_KEYS)
				return false;
			return  m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button)const {
			//TODO: log this
			if (button >= MAX_BUTTONS)
				return false;
			return  m_MouseButtons[button];
		}

		void Window::getMousePosition(double &x, double &y)const {
			x = m_MouseX;
			y = m_MouseY;
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_window) == 1;
		}

		void Window::clear()const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGl error: " << error << std::endl;			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}

		void window_Resize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;


		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;

		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseX = xpos;
			win->m_MouseY = ypos;
		}
	}
}
