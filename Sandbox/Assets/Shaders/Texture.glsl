#type vertex
#version 410 core

layout(location = 0) in vec3 a_Position; 
layout(location = 1) in vec2 a_TextCoord; 

out vec3 v_Position;
out vec2 v_TextCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
           
void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
    v_Position = a_Position;
    v_TextCoord = a_TextCoord;
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec3 v_Position; 
in vec2 v_TextCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
           
void main()
{
    //color = vec4(v_TextCoord, 0.0, 1.0);
    color = texture(u_Texture, v_TextCoord) * u_Color;
}
