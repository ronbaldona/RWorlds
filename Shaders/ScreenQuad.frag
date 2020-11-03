#version 330 core

in vec2 fragTexCoords;

uniform sampler2D screenTex;

out vec4 fragColor;

void main() {
    float depth = texture(screenTex, fragTexCoords).r;
    fragColor = vec4(vec3(depth), 1.0f);
    //fragColor = texture(screenTex, fragTexCoords);
}