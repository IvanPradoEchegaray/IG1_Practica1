//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

using namespace glm;

//-------------------------------------------------------------------------
class IG1App;

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1), posL(0, 0, 0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update() {};
	
	// modeling matrix
	dmat4 const& modelMat() const { return mModelMat; }
	dvec3 const& color() const { return mColor; }
	void setModelMat(dmat4 const& aMat) { mModelMat = aMat; }
	void modColor(dvec4 newColor);
	void setTexture(Texture* tex) { mTexture = tex; }
	void setTranslation(dvec3 pos) { posL = pos; }

protected:

	Mesh* mMesh = nullptr;   // the mesh
	dmat4 mModelMat;    // modeling matrix
	dvec4 mColor;
	dvec3 posL;
	Texture* mTexture = nullptr;

	// transfers modelViewMat to the GPU
	virtual void upload(dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLuint numL, GLdouble rd);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Serpinski : public Abs_Entity
{
public:
	explicit Serpinski(GLdouble rd, GLuint numP);
	~Serpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class TrianguloRGB : public Abs_Entity
{
private:
	GLdouble rotationL = 0;
	GLdouble translationL = 0;
public:
	explicit TrianguloRGB();
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class Rectangulo : public Abs_Entity
{
public:
	explicit Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
class Estrella3D : public Abs_Entity
{
private:
	GLdouble rotationYL = 0;
	GLdouble rotationZL = 0;
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//-------------------------------------------------------------------------
class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
class CajaConFondo : public Abs_Entity {
private:
	Mesh* fondo = nullptr;
	dmat4 fondoModelmat = dmat4(1);
	Texture* fondoTexture = nullptr;
	GLdouble ldL = 0.0, rotationZL = 0;
public:
	explicit CajaConFondo(GLdouble ld);
	~CajaConFondo();
	void setTexture(Texture* const& tex, Texture* const& texF);
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
	virtual void setTranslation(dvec3 pos);
	void setModelMatSuelo(glm::dmat4 const& aMat) { fondoModelmat = aMat; };
};
//-------------------------------------------------------------------------
class Suelo : public Abs_Entity {
public:
	explicit Suelo(GLdouble ld, GLuint r);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
class Foto : public Abs_Entity {
public:
	explicit Foto(GLdouble ld);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//-------------------------------------------------------------------------
class Grass : public Abs_Entity
{
public:
	explicit Grass(GLuint r, GLdouble w, GLdouble h, glm::dvec3 pos);
	~Grass();
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	std::vector<glm::dmat4> mMats_;
};
//-------------------------------------------------------------------------
class Cristalera : public Abs_Entity {
public:
	explicit Cristalera(GLdouble ld);
	~Cristalera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
#endif //_H_Entities_H_