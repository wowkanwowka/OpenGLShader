//
// Created by Vladimir on 03.06.2018.
//

#include "ShaderClass.h"
#include <fstream>

std::string ReadSource(const std::string& path) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(path);
    std::stringstream stream;
    stream << file.rdbuf();
//    std::cout << stream.str() << '\n\n\n';
    file.close();
    return stream.str();
}

ShaderClass::ShaderClass(const std::string &vertex_path, const std::string &fragment_path) {
//    std::string vertex_source;
//    std::string fragment_source;

    try {
        vertex_shader_source_ = ReadSource(vertex_path);
    } catch (std::ifstream::failure& err) {
        std::cerr << "ERROR::SHADER_CLASS::ERROR_WHILE_READING_VERTEX_SHADER_SOURCE\n";
    }

    try {
        fragment_shader_source_ = ReadSource(fragment_path);
    } catch (std::ifstream::failure& err) {
        std::cerr << "ERROR::SHADER_CLASS::ERROR_WHILE_READING_FRAGMENT_SHADER_SOURCE\n";
    }

//    vertex_shader_source_ = vertex_source_.c_str();
//    fragment_shader_source_ = fragment_source_.c_str();
//    std::cout << vertex_shader_source_ << '\n' << fragment_shader_source_ << '\n';
}

void CompileShader(unsigned int* shader, char* info_log, const char* source, ShaderClass::Type type) {
    if (type == ShaderClass::Type::Vertex) {
        *shader = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == ShaderClass::Type::Fragment) {
        *shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(*shader, 1, &source, nullptr);
    glCompileShader(*shader);

    int success;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*shader, 512, nullptr, info_log);
        throw std::runtime_error(info_log);
    }
}

void ShaderClass::Compile() {
    char info_log[512];

    CompileShader(&vertex_shader_, info_log, vertex_shader_source_.c_str(), Type::Vertex);

    CompileShader(&fragment_shader_, info_log, fragment_shader_source_.c_str(), Type::Fragment);


}

void ShaderClass::Link() {
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_shader_);
    glAttachShader(id_, fragment_shader_);

    char info_log[512];
    int success;

    glLinkProgram(id_);

    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, nullptr, info_log);
        std::cerr << "linking error\n";
        std::cerr << fragment_shader_source_ << std::endl;
//        std::cerr << vertex_shader_source_ << std::endl;

        throw std::runtime_error(info_log);
    }

    glDeleteShader(vertex_shader_);
    glDeleteShader(fragment_shader_);
}

void ShaderClass::Use() {
    glUseProgram(id_);
}

void ShaderClass::SetBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(id_, name.c_str()),
                static_cast<int>(value));
}

void ShaderClass::SetInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void ShaderClass::SetFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

unsigned int& ShaderClass::GetId() {
    return id_;
}
