#include "Shader.hpp"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		
		return contents;
	}
	LOG("Failed to open shader...\n");
	return "";
}

Shader::Shader(const char* vert_file, const char* frag_file)
{
	std::string vert_code = get_file_contents(vert_file);
	std::string frag_code = get_file_contents(frag_file);

	const char* vert_source = vert_code.c_str();
	const char* frag_source = frag_code.c_str();

	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_shader, 1, &vert_source, nullptr);
	glCompileShader(vert_shader);
	compile_errors(vert_shader, GL_VERTEX_SHADER);

	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &frag_source, nullptr);
	glCompileShader(frag_shader);
	compile_errors(frag_shader, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();
	glAttachShader(ID, vert_shader);
	glAttachShader(ID, frag_shader);
	glLinkProgram(ID);
	compile_errors(ID, GL_PROGRAM);

	glDetachShader(ID, vert_shader);
	glDetachShader(ID, frag_shader);
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::del() const
{
	glDeleteProgram(ID);
}

void Shader::set_bool(const char* var_name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, var_name), static_cast<int>(value));
}

void Shader::set_int(const char* var_name, i32 value) const
{
	glUniform1i(glGetUniformLocation(ID, var_name), value);
}

void Shader::set_float(const char* var_name, f32 value) const
{
	glUniform1f(glGetUniformLocation(ID, var_name), value);
}

void Shader::set_uint(const char* var_name, u32 value) const
{
	glUniform1ui(glGetUniformLocation(ID, var_name), value);
}

void Shader::set_int_array(const char* var_name, std::size_t length, const i32* array) const
{
	glUniform1iv(glGetUniformLocation(ID, var_name), length, array);
}

void Shader::set_ivec2(const char* var_name, glm::ivec2& ivec2) const
{
	glUniform2i(glGetUniformLocation(ID, var_name), ivec2.x, ivec2.y);
}

void Shader::set_ivec3(const char* var_name, glm::ivec3& ivec3) const
{
	glUniform3i(glGetUniformLocation(ID, var_name), ivec3.x, ivec3.y, ivec3.z);
}

void Shader::set_ivec4(const char* var_name, glm::ivec4& ivec4) const
{
	glUniform4i(glGetUniformLocation(ID, var_name), ivec4.x, ivec4.y, ivec4.z, ivec4.w);
}

void Shader::set_vec2(const char* var_name, glm::vec2& vec2) const
{
	glUniform2f(glGetUniformLocation(ID, var_name), vec2.x, vec2.y);
}

void Shader::set_vec3(const char* var_name, glm::vec3& vec3) const
{
	glUniform3f(glGetUniformLocation(ID, var_name), vec3.x, vec3.y, vec3.z);
}

void Shader::set_vec4(const char* var_name, glm::vec4& vec4) const
{
	glUniform4f(glGetUniformLocation(ID, var_name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::set_mat3(const char* var_name, const glm::mat3& mat3) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, var_name), 1, GL_FALSE, glm::value_ptr(mat3));
}

void Shader::set_mat4(const char* var_name, const glm::mat4& mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, var_name), 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::compile_errors(GLuint shader, GLenum type)
{
	INT32 has_compiled;

	char info_log[1024];
	if (type != GL_PROGRAM)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
		if (has_compiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, info_log);
			ERROR("SHADER::COMPILATION_ERROR for: " << type << '\n' << info_log << '\n');
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &has_compiled);
		if (has_compiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, info_log);
			ERROR("SHADER_LINKING_ERROR for: " << type << '\n' << info_log << '\n');
		}
	}
}
