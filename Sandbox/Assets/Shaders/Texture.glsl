#type vertex
#version 410 core

layout(location = 0) in vec3 a_Position; 
layout(location = 1) in vec4 a_Color; 
layout(location = 2) in vec2 a_TextCoord; 

out vec4 v_Color;
out vec2 v_TextCoord;

uniform mat4 u_ViewProjection;
           
void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
    v_Color = a_Color;
    v_TextCoord = a_TextCoord;
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec4 v_Color; 
in vec2 v_TextCoord;

uniform sampler2D u_Texture;
uniform vec2 u_Tiling;
uniform vec2 u_Offset;
uniform vec4 u_Tint;
           
void main()
{
    //color = vec4(v_TextCoord, 0.0, 1.0);
    //color = texture(u_Texture, v_TextCoord * u_Tiling + u_Offset) * u_Tint * v_Color;
    
    color = v_Color;
}
