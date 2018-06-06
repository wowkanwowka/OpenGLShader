//
// Created by Vladimir on 03.06.2018.
//

#ifndef SHADERCLASS_SHADERCLASS_H
#define SHADERCLASS_SHADERCLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderClass {
public:
    enum class Type {
        Vertex,
        Fragment
    };

    ShaderClass(const std::string& vertex_path, const std::string& fragment_path);
    void Compile();
    void Link();
    void Use();
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string&name, float value);
    unsigned int& GetId();
private:
    // shader program ID
    unsigned int vertex_shader_;
    unsigned int fragment_shader_;
    unsigned int id_;
    std::string vertex_shader_source_;
    std::string fragment_shader_source_;
};


#endif //SHADERCLASS_SHADERCLASS_H
