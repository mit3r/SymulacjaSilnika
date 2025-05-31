#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lights[2];
uniform vec4 lightsColors[2];

//Atrybuty
in vec2 texCoord0; //wspolrzedne     tekstury
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor wierzchołka
in vec4 normal; //wektor normalny wierzchołka w przestrzeni modelu


out vec2 iTexCoord0;
out vec4 iC;
out vec4 l[2];
out vec4 lc[2];
out vec4 n;
out vec4 v;

void main(void) {
    for (int i=0; i<lights.length(); i++){
        l[i] = normalize(V * (lights[i] - M * vertex));//znormalizowany wektor do światła w przestrzeni oka
        lc[i] = lightsColors[i];
    }
    
    n = normalize(V * M * normal);//znormalizowany wektor normalny w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //Wektor do obserwatora w przestrzeni oka
    // iC = color;
    iC = vec4(0.5f, 0.5f, 0.5f, 5.0f);

    iTexCoord0 = texCoord0; //przekazanie współrzędnych tekstury do fragment shadera
    gl_Position = P*V*M*vertex;
}
