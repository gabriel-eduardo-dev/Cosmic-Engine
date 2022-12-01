#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Types.hpp"

std::string get_file_contents(const char* filename);

class Shader 
{
	public:

		UINT32 ID;
		Shader(const char* vert_file, const char* frag_file);
		~Shader();
		
		void use() const;
		void del() const;

		void set_bool(const char* var_name, bool value) const;
		void set_int(const char* var_name, i32 value) const;
		void set_uint(const char* var_name, u32 value) const;
		void set_int_array(const char* var_name, std::size_t length, const i32* array) const;
		void set_float(const char* var_name, f32 value) const;
		void set_ivec2(const char* var_name, glm::ivec2& vec2) const;
		void set_ivec3(const char* var_name, glm::ivec3& vec3) const;
		void set_ivec4(const char* var_name, glm::ivec4& vec4) const;
		void set_vec2(const char* var_name, glm::vec2& vec2) const;
		void set_vec3(const char* var_name, glm::vec3& vec3) const;
		void set_vec4(const char* var_name, glm::vec4& vec4) const;
		void set_mat3(const char* var_name, const glm::mat3& mat3) const;
		void set_mat4(const char* var_name, const glm::mat4& mat4) const;
	
	private:
		
		void compile_errors(GLuint shader, GLenum type);
};

#endif
