#version 410

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 TurnView;

uniform vec4 colorID;
uniform bool colorCheck;

void main()
{
    gl_Position = Projection * TurnView * ModelView * vPosition;
    color = colorCheck ? colorID : vColor;
}
