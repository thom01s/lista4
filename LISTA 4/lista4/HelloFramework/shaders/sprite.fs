#version 450 core
in vec4 ourColor;
in vec2 TexCoord;

out vec4 color;

// pixels da textura
uniform sampler2D tex1;
uniform int channelID;

void main()
{
    color = texture(tex1, TexCoord);
    if(channelID == 0)
    {
    color.r = color.r;
    color.g = color.r;
    color.b = color.r;
    }

    else if(channelID == 1)
    {
    color.r = color.g;
    color.g = color.g;
    color.b = color.g;
    }

    else
    {
    color.r = color.b;
    color.g = color.b;
    color.b = color.b;
    }
    

    //cor pode ser mudada trocando o numero no main por uma das outras cores
}
