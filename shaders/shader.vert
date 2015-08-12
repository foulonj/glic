#version 130

in vec3  vertex_position;
out vec3 fragmentColor; 

uniform mat4 MVP;

void main(){
  //Position du sommet, dans l'espace de découpe : MVP * position
  gl_Position = MVP * vec4(vertex_position, 1);
  fragment_color = vec3(0.0f, 0.0f, 0.7f);
}
