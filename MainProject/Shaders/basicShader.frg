#version 130

// The lightcaster represents a celestial body
// which is an "infinite" distance away, so
// all light rays are paralell, position
// is thus not needed
struct LightCaster {
    vec3 direction;	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec4 fragmentColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 viewP;
uniform sampler2D texIm;
uniform LightCaster light;

void main(){
	//ambient component
    vec3 ambient = light.ambient *  fragmentColor.xyz;
    //vec3(texture(texIm, TexCoord));

	//diffuse
  	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * fragmentColor.xyz;  
    
    // Specular
    vec3 viewDir = normalize(viewP - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.0);
    vec3 specular = light.specular * spec * fragmentColor.xyz;
            
    color = vec4(diffuse, 1.0f);  
	//color = texture(texIm, TexCoord);
}