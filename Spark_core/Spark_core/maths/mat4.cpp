#include "mat4.h"


namespace sparky {namespace maths {

	mat4::mat4() {
		for (int i = 0; i < 4 * 4; i++)
			element[i] = 0.0f;
	}

	mat4::mat4(float diagonal) {
		for (int i = 0; i < 4 * 4; i++)
			element[i] = 0.0f;

		for (int i = 0; i < 4; i++)
			element[i + i * 4] = diagonal;
	}

	vec4 mat4::getColumn(int index) {
		index *= 4;
		return vec4(element[index], element[index + 1], element[index + 2], element[index + 3]);
	}

	vec4 mat4::getRow(int index) {
		return vec4(element[index], element[index + 4], element[index + 8], element[index + 12]);
	}

	mat4 mat4::identity() {
		return mat4(1.0f);
	}
			
	mat4& mat4::multiply(const mat4& other) {
		float data[16];
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += element[x + e * 4] * other.element[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		memcpy(element, data, 4 * 4 * sizeof(float));
		return *this;
	}

	mat4 operator *(mat4 left, const mat4& right) {
		return left.multiply(right);
	}

	mat4& mat4::operator*=(const mat4& other) {
		return multiply(other);
	}

	mat4 mat4::othographic(float left, float right, float bottom, float top, float near, float far) {
		mat4 result(1.0f);

		result.element[0 + 0 * 4] = 2.0f / (right - left);
		result.element[1 + 1 * 4] = 2.0f / (top - bottom);
		result.element[2 + 2 * 4] = 2.0f / (near - far);
		
		result.element[0 + 3 * 4] =(right+left)/(left-right);
		result.element[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.element[2 + 3 * 4] = (far + near) / (far - near);

		return result;
			
	}

	mat4 mat4::perspective(float fov, float aspecrRatio, float near, float far) {
		mat4 result(1.0f);

		result.element[0 + 0 * 4] = 1.0f / tan(toRadians(0.5f*fov));
		result.element[1 + 1 * 4] = result.element[0 + 0 * 4] / aspecrRatio;
		result.element[2 + 2 * 4] = (near + far) / (near - far);
		result.element[3 + 2 * 4] = -1.0f;
		result.element[2 + 3 * 4] = (2.0f*near*far) / (near - far);

		return result;
	 }

	mat4 mat4::translation(const vec3& translation) {
		mat4 result(1.0f);

		result.element[0 + 3 * 4] = translation.x;
		result.element[1 + 3 * 4] = translation.y;
		result.element[2 + 3 * 4] = translation.z;

		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis) {
		
		mat4 result(1.0f);
		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.element[0 + 0 * 4] = x * omc + c;
		result.element[1 + 0 * 4] = y * x * omc + z * s;
		result.element[2 + 0 * 4] = x * z * omc - y * s;

		result.element[0 + 1 * 4] = x * y * omc - z * s;
		result.element[1 + 1 * 4] = y * omc + c;
		result.element[2 + 1 * 4] = y * z * omc + x * s;

		result.element[0 + 2 * 4] = x * z * omc + y * s;
		result.element[1 + 2 * 4] = y * z * omc - x * s;
		result.element[2 + 2 * 4] = z * omc + c;

		return result;
	}

	mat4 mat4::scale(const vec3& scale) {
		mat4 result(1.0f);

		result.element[0 + 0 * 4] = scale.x;
		result.element[1 + 1 * 4] = scale.y;
		result.element[2 + 2 * 4] = scale.z;

		return result;
	}



}}