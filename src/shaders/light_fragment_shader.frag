#version 430 core                  
                                                  
out vec4 color;                                                             
                                                  
in VS_OUT                          
{                                  
    vec4 color;                     
    vec2 texture_coord;   
    vec3 fragment_position;          
    vec3 normal;                                                                
} fs_in;                           
                                                  
                                                  
void main(void)                    
{                                  
    color = vec4(1, 1, 1, 1);            
}                                  


