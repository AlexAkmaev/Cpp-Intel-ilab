#version 450

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec3 inTrace;

layout (location = 0) out vec4 outFragColor;

void main() 
{
  float scalar = 1 - max(dot(inNormal, inTrace), 0);
  if (scalar < 0.3)
      scalar = 0.3;
  outFragColor = vec4(inColor * scalar, 1.0);
}
