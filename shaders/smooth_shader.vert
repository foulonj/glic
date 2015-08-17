#version 130

in vec3 vertex_position;
in vec3 vertex_normal;
out vec3 fragmentColor;

uniform mat4 MVP;
uniform vec3 COL;

uniform mat4 M;//MODEL
uniform mat4 V;//VIEW


void main(){

  gl_Position = MVP * vec4(vertex_position, 1);

  vec3 Position_worldspace = (M * vec4(vertex_position,1)).xyz;


  /////////////////////////////////////////////////////////////////////////////////////////////////
  //                                        Préparation                                          //
  /////////////////////////////////////////////////////////////////////////////////////////////////

  vec3 LightColor            = vec3(1,1,0.8);//Lumière un peu jaune
  vec3 MaterialDiffuseColor  = COL;
  vec3 MaterialSpecularColor = vec3(1.0, 1.0, 1.0);
  float LightPower           = 8.0f;
  vec3 MaterialAmbientColor  = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
  vec3 LightPosition_worldspace = vec3(2,2,2);
  float distance = length(LightPosition_worldspace - gl_Position.xyz);
  float lobeSize = 5.0f;//Taille du lobe spéculaire



  /////////////////////////////////////////////////////////////////////////////////////////////////
  //                                         Diffusivité                                         //
  /////////////////////////////////////////////////////////////////////////////////////////////////

  // Vecteur allant du sommet vers la caméra, dans l'espace caméra.
  // Dans l'espace caméra, la caméra est à l'origine (0,0,0).
  vec3 vertexPosition_cameraspace = ( V * M * vec4(vertex_position,1)).xyz;
  vec3 EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

  // Vecteur allant du sommet vers la lumière, dans l'espace caméra. M est omise car c'est une matrice d'identité.
  vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
  vec3 LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

  // Normale du sommet, dans l'espace caméra
  // correct seulement si ModelMatrix ne redimensionne pas le modèle ! Utilisez sa transposée inverse sinon
  vec3 Normal_cameraspace = ( V * M * vec4(vertex_normal,0)).xyz;

  // Normale du fragment calculé, dans l'espace caméra
  vec3 n = normalize( Normal_cameraspace );
  // Direction de la lumière (du fragment vers la lumière)
  vec3 l = normalize( LightDirection_cameraspace );

  // Le cosinus de l'angle entre la normale et le rayon de lumière est toujours supérieur à 0
  float cosTheta = clamp( dot( n,l ), 0,1 );


  /////////////////////////////////////////////////////////////////////////////////////////////////
  //                                         Spécularité                                         //
  /////////////////////////////////////////////////////////////////////////////////////////////////

  // Vecteur de l'œil (vers la caméra)
  vec3 E = normalize(EyeDirection_cameraspace);

  // Direction dans laquelle le triangle reflète la lumière
  vec3 R = reflect(-l,n);

  // Cosinus de l'angle entre le vecteur œil et le vecteur de reflexion limité à 0
  float cosAlpha = clamp( dot( E,R ), 0,1 );


  //Sortie finale de couleur
  vec3 color = MaterialAmbientColor +
               MaterialDiffuseColor  * LightColor * LightPower * cosTheta        / (distance*distance) +
               MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,lobeSize) / (distance*distance) ;  //pow(...) = largeur du lobe speculaire
  fragmentColor = color;
}





