#version 130

in vec3 fragmentColor;
out vec4 color;

void main(){
  color = vec4(fragmentColor, 0.3);
}
