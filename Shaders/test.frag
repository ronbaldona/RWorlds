#version 330 core

#define COLOR_MODE_NORMAL 0
#define COLOR_MODE_TEXTURE_WRAP 1

in vec4 color;
in vec2 tcoord;

uniform int colorMode;
uniform sampler2D texImg;

out vec4 fragColor;

void main() {
    switch (colorMode) {
    case COLOR_MODE_NORMAL:
        fragColor = color;
        break;
    case COLOR_MODE_TEXTURE_WRAP:
        fragColor = texture(texImg, tcoord);
        break;
    }
}