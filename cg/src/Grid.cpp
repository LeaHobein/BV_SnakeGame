#include "Grid.h"
using namespace std;  // Damit wir std::vector etc. nicht jedes Mal mit std:: schreiben müssen

// Konstruktor: Initialisiert Grid-Klasse mit Anzahl Spalten, Zeilen und Zellgröße
Grid::Grid(int cols, int rows, float cellSize)
        : cols(cols), rows(rows), cellSize(cellSize) {
    generateGrid();  // Sobald Objekt erzeugt wird, direkt Grid erstellen
    setupBuffers();
}

// Destruktor
Grid::~Grid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// Erstelle Gitterdaten: Vertices und Indices
void Grid::generateGrid() {
    vertices.clear();  // Alte Daten löschen, falls Funktion erneut aufgerufen wird
    indices.clear();

    // VERTEX-BERECHNUNG
    // Schleife über jede Position im Gitter, inklusive Rand
    for (int y = 0; y <= rows; ++y) {
        for (int x = 0; x <= cols; ++x) {
            float xpos = x * cellSize;     // x-Koordinate
            float ypos = 0.0f;             // y-Koordinate
            float zpos = y * cellSize;     // z-Koordinate

            // Speichert die Position als drei aufeinanderfolgende Werte
            vertices.push_back(xpos);
            vertices.push_back(ypos);
            vertices.push_back(zpos);
        }
    }

    // INDICES-BERECHNUNG
    // Schleife über jede Zelle
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // Berechne Index jedes der 4 Eckpunkte der Zelle
            int topLeft = y * (cols + 1) + x;              // Index oben links
            int topRight = topLeft + 1;                    // rechts daneben
            int bottomLeft = topLeft + (cols + 1);         // darunter
            int bottomRight = bottomLeft + 1;              // rechts davon

            // Jedes Quadrat wird aus 2 Dreiecken gezeichnet:
            // Dreieck 1: oben links, unten links, oben rechts
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            // Dreieck 2: oben rechts, unten links, unten rechts
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}

// Gibt Referenz auf die Vertices zurück
const vector<GLfloat>& Grid::getVertices() const {
    return vertices;
}

// Gibt Referenz auf die Indices zurück
const vector<GLuint>& Grid::getIndices() const {
    return indices;
}

// Gibt Anzahl der Vertices zurück
int Grid::getVertexCount() const {
    return vertices.size() / 3;  // (x, y, z) Werte pro Vertex
}

// Gibt Anzahl der Indices zurück
int Grid::getIndexCount() const {
    return indices.size();
}

GLuint Grid::getVAO() const {
    return VAO;
}


void Grid::setupBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertices in VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Indices in EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Vertex-Attribute definieren
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // unbind
}
