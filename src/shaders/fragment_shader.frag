#version 430 core      

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
                                                  
out vec4 color;                    
                                                  
uniform sampler2D ourTexture; 
uniform vec3 light_position;     
uniform vec3 view_position;
uniform Material material;
                                                  
in VS_OUT                          
{                                  
    vec4 color;                     
    vec2 texture_coord;   
    vec3 fragment_position;          
    vec3 normal;                                                            
} fs_in;                           
                                                  
                                                  
void main(void)                    
{
    vec3 light_color = vec3(0.9, 0.9, 0.9);
    vec3 object_color = vec3(texture(ourTexture, fs_in.texture_coord));

    vec3 ambient = light_color * material.ambient; 

    vec3 normal_normal = normalize(fs_in.normal);
    vec3 light_direction = normalize(light_position - fs_in.fragment_position);
    float diff = max(dot(normal_normal, light_direction), 0.0);
    vec3 diffuse = light_color * (diff * material.diffuse);
    
    vec3 view_direction = normalize(view_position - fs_in.fragment_position);
    vec3 reflect_direction = reflect(-light_direction, normal_normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light_color;  

    vec3 result = (ambient + diffuse + specular) * object_color;
    color = vec4(result, 1.0);
}                                  