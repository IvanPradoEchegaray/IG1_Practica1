#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }
    if (vTextCoords.size() > 0) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTextCoords.data()); //components number (rgba=4), type
    }
	draw();

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}

Mesh* Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(0.8, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.8, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 0.8, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.8, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 0.8, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 0.8, 1.0);
 
  return mesh;
}

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {

    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = numL;
    mesh->vVertices.reserve(mesh->mNumVertices);

    for (GLuint i = 0; i < numL; i++)
    {
        mesh->vVertices.emplace_back(rd * cos(radians(((360.0 / numL) * i) + 90)), 
                                     rd * sin(radians(((360.0 / numL) * i) + 90)), 0.0);
    }

    return mesh;
}

Mesh* Mesh::createTrianguloRGB() {
    Mesh* mesh = generaPoligono(3, 30);

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 3;

    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
    Mesh* triangulo = generaPoligono(3, rd);

    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_POINTS;

    mesh->mNumVertices = numP;
    mesh->vVertices.reserve(mesh->mNumVertices);

    dvec3 p = triangulo->vertices()[rand() % 3];
    dvec3 p1;

    dvec3 vertices[3] = { triangulo->vertices()[0], triangulo->vertices()[1], triangulo->vertices()[2] };

    // An arbitrary initial point inside the triangle
    mesh->vVertices.emplace_back(p);
    // compute and store N-1 new points
    for (int i = 1; i < numP; ++i) {
        int j = rand() % 3; // pick a vertex at random
        // Compute the point halfway between the selected vertex
        // and the previous point
        p1 = (p + vertices[j]) / 2.0;
        mesh->vVertices.emplace_back(p1);
        p = p1;
    }

    delete triangulo; triangulo = nullptr;
    return mesh;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(dvec3{ -w / 2, h / 2, 0.0 });
    mesh->vVertices.emplace_back(dvec3{ -w / 2, -h / 2, 0.0 });
    mesh->vVertices.emplace_back(dvec3{ w / 2, h / 2, 0.0 });
    mesh->vVertices.emplace_back(dvec3{ w / 2, -h / 2, 0.0 });

    return mesh;
}

Mesh* Mesh::generaGrassTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) 
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0, h, 0.0); //v0
    mesh->vVertices.emplace_back(0, 0, 0.0); //v1
    mesh->vVertices.emplace_back(w, h, 0.0); //v2
    mesh->vVertices.emplace_back(w, 0, 0.0); //v3

    //Coordenadas de texturas
    mesh->vTextCoords.reserve(mesh->mNumVertices);
    mesh->vTextCoords.emplace_back(0, 1.0 * rh);
    mesh->vTextCoords.emplace_back(0, 0);
    mesh->vTextCoords.emplace_back(1.0 * rw, 1.0 * rh);
    mesh->vTextCoords.emplace_back(1.0 * rw, 0);

    return mesh;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 1.0, 0.5, 1.0);
    mesh->vColors.emplace_back(0.5, 0.2, 0.5, 1.0);
    mesh->vColors.emplace_back(0.2, 0.6, 0.2, 1.0);
    mesh->vColors.emplace_back(0.2, 0.2, 0.6, 1.0);

    return mesh;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h) {
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_FAN;
    mesh->mNumVertices = np * 2 + 2;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //Central
    GLdouble x = 0, y = 0;
    mesh->vVertices.emplace_back(dvec3(x, y, 0));

    //Vértices
    GLdouble angle = 90;
    for (int i = 0; i < 2 * np; i++)
    {
        if (i % 2 == 0)
        {
            x = re * cos(radians(angle));
            y = re * sin(radians(angle));
        }

        else
        {
            x = re / 2.0f * cos(radians(angle));
            y = re / 2.0f * sin(radians(angle));
        }

        mesh->vVertices.emplace_back(dvec3(x, y, h + ((re * 2.0f) / 3.0f)));  // h + ((re * 2.0) / 3.0) Distancia de la estrella al centro.
        
        angle -= 360.0f / (np * 2.0f);
    }

    //Último
    x = re * cos(radians(90.0f));
    y = re * sin(radians(90.0f));
    mesh->vVertices.emplace_back(dvec3(x, y, h + ((re * 2.0f) / 3.0f)));  // h + ((re * 2.0) / 3.0) Distancia de la estrella al centro.

    return mesh;
}

Mesh* Mesh::generaContCubo(GLdouble ld) {
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //V0
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 2.0, ld / 2.0));

    //V1
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 2.0, ld / 2.0));
    //V2
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, ld / 2.0, ld / 2.0));
    //V3
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, -ld / 2.0, ld / 2.0));
    //V4
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, ld / 2.0, -ld / 2.0));
    //V5
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, -ld / 2.0, -ld / 2.0));
    //V6
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 2.0, -ld / 2.0));
    //V7
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 2.0, -ld / 2.0));

    //2 para cerrar
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 2.0, ld / 2.0));
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 2.0, ld / 2.0));

    return mesh;
}

Mesh* Mesh::generaContCuboTexCor(GLdouble nl) {
    Mesh* mesh = generaContCubo(nl);
    
    mesh->vTextCoords.reserve(mesh->mNumVertices);

    //V0
    mesh->vTextCoords.emplace_back(0, 1);

    //V1
    mesh->vTextCoords.emplace_back(0, 0);
    //V2
    mesh->vTextCoords.emplace_back(1, 1);
    //V3
    mesh->vTextCoords.emplace_back(1, 0);
    //V4
    mesh->vTextCoords.emplace_back(2, 1);
    //V5
    mesh->vTextCoords.emplace_back(2, 0);
    //V6
    mesh->vTextCoords.emplace_back(3, 1);
    //V7
    mesh->vTextCoords.emplace_back(3, 0);
    //V8
    mesh->vTextCoords.emplace_back(4, 1);
    mesh->vTextCoords.emplace_back(4, 0);

    //2 mas para cerrar
    mesh->vTextCoords.emplace_back(0, 1);
    mesh->vTextCoords.emplace_back(0, 0);

    return mesh;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vTextCoords.reserve(mesh->mNumVertices);

    mesh->vTextCoords.emplace_back(0, rh);
    mesh->vTextCoords.emplace_back(0, 0);
    mesh->vTextCoords.emplace_back(rw, rh);
    mesh->vTextCoords.emplace_back(rw, 0);

    return mesh;
}

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = generaEstrella3D(re, np, h);

    mesh->vTextCoords.reserve(mesh->mNumVertices);

    // V0 central
    float x = 0.5f, y = 0.5f;
    mesh->vTextCoords.emplace_back(x, y);

    // Vértices de la textura
    GLdouble angle = 90;
    for (int i = 0; i < mesh->mNumVertices - 1; i++) {
        if (i % 2 == 0) {
            x = cos(radians(angle)) / 2;
            y = sin(radians(angle)) / 2;
            
            x = x * 0.5f + 0.5f;
            y = y * 0.5f + 0.5f;
        }

        else {
            x = cos(radians(angle)) / 2;
            y = sin(radians(angle)) / 2;

            x = x * 0.5f + 0.5f;
            y = y * 0.5f + 0.5f;
        }

        mesh->vTextCoords.emplace_back(x, y);

        angle -= 360.0f / (np * 2.0f);
    }
    return mesh;
}

Mesh* Mesh::generaContCristal(GLdouble ld)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //V0
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 6.0, ld / 2.0));

    //V1
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 6.0, ld / 2.0));
    //V2
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, ld / 6.0, ld / 2.0));
    //V3
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, -ld / 6.0, ld / 2.0));
    //V4
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, ld / 6.0, -ld / 2.0));
    //V5
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, -ld / 6.0, -ld / 2.0));
    //V6
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 6.0, -ld / 2.0));
    //V7
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 6.0, -ld / 2.0));

    //2 para cerrar
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 6.0, ld / 2.0));
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 6.0, ld / 2.0));


    mesh->vTextCoords.reserve(mesh->mNumVertices);

    //V0
    mesh->vTextCoords.emplace_back(0, 1);

    //V1
    mesh->vTextCoords.emplace_back(0, 0);
    //V2
    mesh->vTextCoords.emplace_back(1, 1);
    //V3
    mesh->vTextCoords.emplace_back(1, 0);
    //V4
    mesh->vTextCoords.emplace_back(2, 1);
    //V5
    mesh->vTextCoords.emplace_back(2, 0);
    //V6
    mesh->vTextCoords.emplace_back(3, 1);
    //V7
    mesh->vTextCoords.emplace_back(3, 0);
    //V8
    mesh->vTextCoords.emplace_back(4, 1);
    mesh->vTextCoords.emplace_back(4, 0);

    //2 mas para cerrar
    mesh->vTextCoords.emplace_back(0, 1);
    mesh->vTextCoords.emplace_back(0, 0);

    return mesh;
}
