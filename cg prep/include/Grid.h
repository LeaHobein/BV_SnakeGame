#ifndef CGSNAKEGAME_GRID_H
#define CGSNAKEGAME_GRID_H

#include <vector>
#include <glad/glad.h>

using namespace std;

class Grid {
public:
    // Konstruktor
    Grid(int cols, int rows, float cellSize);

    // Destruktor
    ~Grid();

    // Getter-Funktion: Gibt Liste aller Vertex-Positionen zurück
    const vector<GLfloat>& getVertices() const;

    // Getter-Funktion: Gibt Liste aller Indices zurück
    const vector<GLuint>& getIndices() const;

    // Gibt Anzahl der Vertices zurück
    int getVertexCount() const;

    // Gibt Anzahl der Indices zurück
    int getIndexCount() const;

    GLuint getVAO() const;
private:
    void generateGrid();
    void setupBuffers();

    // Anzahl Spalten und Zeilen im Gitter
    int cols;
    int rows;

    // Größe einer einzelnen Gitterzelle
    float cellSize;

    // Enthält alle Eckpunkte (Vertices) des Gitters
    vector<GLfloat> vertices;

    // Enthält die Indices, die angeben, wie aus den Vertices Dreiecke gebildet werden
    vector<GLuint> indices;

    GLuint VAO{}, VBO{}, EBO{};
};

#endif //CGSNAKEGAME_GRID_H
