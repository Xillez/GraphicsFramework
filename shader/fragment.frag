#version 330 core
out vec4 FragColor;

in vec3 aPosFrag;
in vec2 TexCoords;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
in vec3 normal;
uniform sampler2D texture_diffuse1;

uniform vec3 heightLevels;
uniform bool smoothBorders;

vec4 Color;

float lerpColor(float x, float y, float t)
{
    return (1 - t) * x + y * t;
}

void main()
{    
	vec3 phong = ambient + diffuse + specular;
    // At water level
    if (aPosFrag.y >= 0.0f && aPosFrag.y < heightLevels.x)
        Color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    // At vegetation level    
    else if (aPosFrag.y < heightLevels.y && aPosFrag.y >= heightLevels.x)
        Color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    // At scarce level    
    else if (aPosFrag.y < heightLevels.z && aPosFrag.y >= heightLevels.y)
        Color = vec4(0.6f, 0.5f, 0.2f, 1.0f);
    // At mountain-top level        
    else if (aPosFrag.y >= heightLevels.z)
        Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if(!smoothBorders)
    {
        /*if ((aPosFrag.y >= heightLevels.x - 2.0f && aPosFrag.y < heightLevels.x + 2.0f))
        {
            Color = vec4(0.0f, 
                        lerp(0.0f, 1.0f, (aPosFrag.y - heightLevels.x - 2.0f) / 4.0f), 
                        lerp(1.0f, 0.0f, (aPosFrag.y - heightLevels.x - 2.0f) / 4.0f), 
                        1.0f);
        }
        else if ((aPosFrag.y >= heightLevels.y - 2.0f && aPosFrag.y < heightLevels.y + 2.0f))
        {
            Color = vec4(lerp(0.0f, 0.6f, (aPosFrag.y - heightLevels.y - 2.0f) / 4.0f), 
                        lerp(1.0f, 0.5f, (aPosFrag.y - heightLevels.y - 2.0f) / 4.0f), 
                        lerp(0.0f, 0.2f, (aPosFrag.y - heightLevels.y - 2.0f) / 4.0f), 
                        1.0f);
        }
        else if ((aPosFrag.y >= heightLevels.z - 2.0f && aPosFrag.y < heightLevels.z + 2.0f))
        {
            Color = vec4(lerp(0.6f, 1.0f, (aPosFrag.y - heightLevels.z - 2.0f) / 4.0f), 
                        lerp(0.5f, 1.0f, (aPosFrag.y - heightLevels.z - 2.0f) / 4.0f), 
                        lerp(0.2f, 1.0f, (aPosFrag.y - heightLevels.z - 2.0f) / 4.0f), 
                        1.0f);
        }*/

        if ((aPosFrag.y >= heightLevels.x - 0.25f && aPosFrag.y < heightLevels.x + 0.25f) || 
            (aPosFrag.y >= heightLevels.y - 0.25f && aPosFrag.y < heightLevels.y + 0.25f) || 
            (aPosFrag.y >= heightLevels.z - 0.25f && aPosFrag.y < heightLevels.z + 0.25f))
                Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }

    // Set color and apply phong lighting (flat shading)
    FragColor = vec4((vec3(Color) * phong), 1.0);
}