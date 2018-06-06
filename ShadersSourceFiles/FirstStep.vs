#version 330 core
layout (location = 0) in vec3 aPos;
uniform float Offset;
void main()
{
     gl_Position = vec4(Offset + aPos.x, aPos.y, aPos.z, 1.0);
}