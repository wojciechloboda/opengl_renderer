#version 430 core                                                    
                                                                      
layout (location = 0) in vec3 position;                                                     
layout (location = 1) in vec2 texture_coord;  
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 light_position; 
                                                                      
out VS_OUT                                                            
{                                                                     
    vec4 color;                     
    vec2 texture_coord;   
    vec3 fragment_position;          
    vec3 normal;                                            
} vs_out;                                                             
                                                                      
void main(void)                                                       
{                                                                     
    gl_Position =  projection * view * model * vec4(position, 1.0);                                      
    vs_out.texture_coord = texture_coord;   


    vs_out.fragment_position = vec3(model * vec4(position, 1));
    vs_out.normal = mat3(transpose(inverse(model))) * normal;                                                                                                   
}                                                                     