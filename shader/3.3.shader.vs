#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float xOffset;
uniform float yOffset;
//uniform vec2 xyoffset

void main()
{
    gl_Position = vec4(aPos, 1.0);
    //上下颠倒
    //gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0f);
    //移动右侧
    //gl_Position = vec4(aPos.x+xOffset, aPos.y, aPos.z, 1.0f);
    gl_Position = vec4(aPos.x+xOffset, aPos.y+yOffset, aPos.z, 1.0f);
    ourColor = aColor;
}