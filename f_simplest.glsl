#version 330


uniform sampler2D textureDiffuse;
uniform sampler2D textureReflect;


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela
in vec4 iC;

in vec2 iTexCoord0;
in vec4 l[2];
in vec4 lc[2];
in vec4 n;
in vec4 v;


void main(void) {

	vec4 kd = texture(textureDiffuse,iTexCoord0); // kolor powierzchni
	// vec4 kd = iC; // kolor powierzchni
	// vec4 ks = vec4(0.5,0.5,0.5,1);
	vec4 ks = texture(textureReflect,iTexCoord0); // kolor refleksów

	vec4 mn = normalize(n);
	vec4 mv = normalize(v);

	vec4 lightAmbient=vec4(0.05,0.05,0.05,1);
	pixelColor=vec4(kd.rgb*lightAmbient.rgb, kd.a); 

	for (int i=0; i<l.length(); i++){
		vec4 ml = normalize(l[i]);
		vec4 mr=reflect(-ml,mn); //Wektor odbity
		float nl = clamp(dot(mn, ml), 0, 1); //Kosinus kąta pomiędzy wektorami n i l.
		float rv = pow(clamp(dot(mr, mv), 0, 1), 25); // Kosinus kąta pomiędzy wektorami r i v podniesiony do 25 potęgi
		pixelColor=pixelColor+vec4(nl * kd.rgb * lc[i].rgb, kd.a) + vec4(ks.rgb * rv, 0);
	}

	//pixelColor= vec4(nl * kd.rgb, kd.a) + vec4(ks.rgb * rv, 0); 
}
