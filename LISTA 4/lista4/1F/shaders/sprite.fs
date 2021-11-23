#version 450 core
in vec4 ourColor;
in vec2 TexCoord;

out vec4 color;

// pixels da textura
uniform sampler2D tex1;
uniform int ChannelID;

void main()
{
    color = texture(tex1, TexCoord);

    if (ChannelID == 0)
    {
    color = vec4(color.r+0.05, color.g, color.b-0.1, 1.0);
    }

    else if (ChannelID == 1)
    {
    color = vec4(color.r-0.1, color.g+0.05, color.b, 1.0);
    }

    else
    {
    color = vec4(color.r-0.1, color.g, color.b+0.1, 1.0);
    }
    //para esse exerc�cio juntei a cor colorizadora em 3 op��es como no exerc�cio 1A, agora com uma cor em destaque em cada op��o
    //a op��o pode ser mudada no main do origem.cpp
    //s�o coloriza��es bem sutis pois achei que se aumentasse mais ficava muito forte
}
