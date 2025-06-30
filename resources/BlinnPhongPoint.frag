#version 430 core

// Algorithm based on algorithmen from
// Sellers, Graham, Wright, Richard S., Haemel, Nicholas (2014).
// OpenGL Super Bible. 6th edition. Addison Wesley.
// Edited by Merijam Gotzes, 15.03.2024
// Modified by KI-Modell, 29.06.2024


// --- UNIFORMS ---
// Parameters of light source as uniform variables from application
layout (location = 4) uniform vec4 lightSourceAmbient;
layout (location = 5) uniform vec4 lightSourceDiffuse;
layout (location = 6) uniform vec4 lightSourceSpecular;
// Material parameters as uniform variables
layout (location = 7) uniform vec4 materialEmission;
layout (location = 8) uniform vec4 materialAmbient;
layout (location = 9) uniform vec4 materialDiffuse;
layout (location = 10) uniform vec4 materialSpecular;
layout (location = 11) uniform float materialShininess;

// Texture sampler
layout (binding = 0) uniform sampler2D tex;

// Control switch for using texture (NEU)
uniform bool useTexture;


// --- EINGABEN VOM VERTEX-SHADER ---
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 vUV;
} fs_in;


// --- AUSGABE ---
out vec4 FragColor;


void main(void)
{
    // --- Beleuchtungskomponenten berechnen ---
    vec3 emissiv = vec3(materialEmission);
    vec3 ambient = vec3(materialAmbient) * vec3(lightSourceAmbient);
    vec3 diffuseAlbedo = vec3(materialDiffuse) * vec3(lightSourceDiffuse);
    vec3 specularAlbedo = vec3(materialSpecular) * vec3(lightSourceSpecular);

    // Eingehende Vektoren normalisieren
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);
    vec3 H = normalize(L + V);

    // Diffuse und Spiegelkomponenten
    vec3 diffuse = max(dot(N, L), 0.0) * diffuseAlbedo;
    vec3 specular = pow(max(dot(N, H), 0.0), materialShininess) * specularAlbedo;

    // Grundfarbe der Beleuchtung (ohne Spiegelglanz)
    vec4 litColor = vec4(emissiv + ambient + diffuse, 1.0);
    vec4 finalColor;

    // --- NEUE LOGIK: Entscheiden, ob Textur verwendet wird ---
    if (useTexture)
    {
        // Für texturierte Objekte: Beleuchtete Farbe mit der Textur modulieren
        finalColor = litColor * texture(tex, fs_in.vUV);
    }
    else
    {
        // Für nicht-texturierte Objekte (die Augen): Nur die beleuchtete Farbe verwenden
        finalColor = litColor;
    }

    // Spiegelglanz wird am Ende hinzugefügt, damit er über der Textur liegt
    FragColor = finalColor + vec4(specular, 1.0);
}
