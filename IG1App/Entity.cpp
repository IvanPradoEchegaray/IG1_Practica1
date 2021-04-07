#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::modColor(dvec4 Color) {
	mColor = Color;
}

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------
 
Poligono::Poligono(GLuint numL, GLdouble rd) {
	mMesh = Mesh::generaPoligono(numL, rd);
}

Poligono::~Poligono() {
	delete mMesh; mMesh = nullptr;
}

void Poligono::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(3);
		mMesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

Serpinski::Serpinski(GLdouble rd, GLuint numP) {
	mMesh = Mesh::generaSierpinski(rd, numP);
}

Serpinski::~Serpinski() {
	delete mMesh; mMesh = nullptr;
}

void Serpinski::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(3);
		mMesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

TrianguloRGB::TrianguloRGB() {
	mMesh = Mesh::createTrianguloRGB();
}

TrianguloRGB::~TrianguloRGB() {
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(3);
		mMesh->render();
		glLineWidth(1);
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(1, 1, 1);
	}
}

void TrianguloRGB::update() {
	rotationL += 5;
	translationL += 5;
	GLdouble x = 250 * cos(radians(translationL));
	GLdouble y = 250 * sin(radians(translationL));

	mModelMat = translate(dmat4(1), dvec3(x, y, 0));

	mModelMat = rotate(mModelMat, -radians(rotationL), dvec3(0, 0, 1));
}

Rectangulo::Rectangulo(GLdouble w, GLdouble h) {
	mMesh = Mesh::generaRectangulo(w, h);
}

Rectangulo::~Rectangulo() {
	delete mMesh; mMesh = nullptr;
}

void Rectangulo::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(3);
		mMesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) {
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB() {
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr)
	{
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
	}
}

Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h) {
	/*LINEAS*/
	//mMesh = Mesh::generaEstrella3D(re, np, h);
	/*TEXTURAS*/
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
}

Estrella3D::~Estrella3D() {
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr)
	{
		/*      LINEAS        */
		/*dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(3);
		mMesh->render();

		aMat = scale(aMat, dvec3(1, 1, -1));
		upload(aMat);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1, 1, 1);*/

		/*      TEXTURAS      */
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);
		mMesh->render();

		aMat = scale(aMat, dvec3(1, 1, -1));
		upload(aMat);
		mMesh->render();

		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
	}
}

void Estrella3D::update() {
	mModelMat = translate(dmat4(1), posL);
	mModelMat = rotate(mModelMat, -radians(rotationYL), dvec3(0.0, 1.0, 0.0));
	mModelMat = rotate(mModelMat, radians(rotationZL), dvec3(0.0, 0.0, 1.0));

	rotationYL += 5;
	rotationZL += 5;
}

Caja::Caja(GLdouble ld) {
	mMesh = Mesh::generaContCubo(ld);
}

Caja::~Caja() {
	delete mMesh; mMesh = nullptr;
}

void Caja::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat; //glm matrix multiplication
	upload(aMat);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3d(mColor.r, mColor.g, mColor.b);
	glLineWidth(3);
	mMesh->render();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	glColor3d(1, 1, 1);
}

CajaConFondo::CajaConFondo(GLdouble ld) {
	mMesh = Mesh::generaContCuboTexCor(ld);
	ldL = ld;

	//suelo
	fondo = Mesh::generaRectanguloTexCor(ld, ld, 1, 1);
	fondoModelmat = rotate(fondoModelmat, radians(90.0), dvec3(1.0, 0.0, 0.0));
	fondoModelmat = translate(fondoModelmat, posL);
}

CajaConFondo::~CajaConFondo() {
	delete mMesh; mMesh = nullptr;
}

void CajaConFondo::setTexture(Texture* const& tex, Texture* const& texF) {
	Abs_Entity::setTexture(tex);
	fondoTexture = texF;
}

void CajaConFondo::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr)
	{
		dmat4 aMat = modelViewMat * mModelMat; //glm matrix multiplication
		upload(aMat);
	
		// Paredes
		//Exterior
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);	//elimina esta
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();

		//Interior
		glCullFace(GL_FRONT);
		fondoTexture->bind(GL_REPLACE);
		mMesh->render();
		fondoTexture->unbind();

		// Suelo
		upload(modelViewMat * fondoModelmat);
		//Exterior
		glCullFace(GL_BACK);	//elimina esta
		mTexture->bind(GL_REPLACE);
		fondo->render();
		mTexture->unbind();

		//Interior
		glCullFace(GL_FRONT);
		fondoTexture->bind(GL_REPLACE);
		fondo->render();
		fondoTexture->unbind();

		//Reset
		glDisable(GL_CULL_FACE);
	}
}

void CajaConFondo::update() {
	mModelMat = translate(dmat4(1), posL);
	mModelMat = rotate(mModelMat, -radians(rotationZL), dvec3(0.0, 0.0, 1.0));
	fondoModelmat = translate(mModelMat, dvec3(0.0, -ldL/2, 0.0));
	fondoModelmat = rotate(fondoModelmat, -radians(-90.0), dvec3(1.0, 0.0, 0.0));
	rotationZL += 5;
}

void CajaConFondo::setTranslation(dvec3 pos) {
	posL = pos;
	fondoModelmat = rotate(fondoModelmat, radians(90.0), dvec3(1, 0, 0));
}

Suelo::Suelo(GLdouble ld, GLuint r) {
	mMesh = Mesh::generaRectanguloTexCor(ld, ld, r, r); 
	mModelMat = rotate(mModelMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
}

Suelo::~Suelo() {
	delete mMesh; mMesh = nullptr;
}

void Suelo::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr)
	{
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
	}
}

Foto::Foto(GLdouble ld) {
	mMesh = Mesh::generaRectanguloTexCor(ld, ld, 1, 1);
	mModelMat = translate(dmat4(1), posL);
	mModelMat = rotate(mModelMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
}

Foto::~Foto() {
	delete mMesh; mMesh = nullptr;
}

void Foto::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
	}
}

void Foto::update() {
	mTexture->loadColorBuffer(IG1App::s_ig1app.winWidth(), 
							  IG1App::s_ig1app.winHeight(), 
							  GL_FRONT);

	mModelMat = translate(dmat4(1), posL);
	mModelMat = rotate(mModelMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
}

Grass::Grass(GLuint r, GLdouble w, GLdouble h, dvec3 pos)
{
	mMesh = Mesh::generaGrassTexCor(w, h, 1, 1);
	mModelMat = translate(dmat4(1), pos);
	mMats_.push_back(mModelMat);
	for (int i = 0; i < r - 1; i++) {
		dmat4 mMat = translate(mModelMat, dvec3(0.0, 0.0, 0.0));
		mMat = translate(mMat, dvec3(w / 2, 0.0, 0.0));
		mMat = rotate(mMat, radians(180.0 / r * (i + 1)), dvec3(0.0, 1.0, 0.0));
		mMat = translate(mMat, dvec3(-w / 2, 0.0, 0.0));
		mMats_.push_back(mMat);
	}
}

Grass::~Grass()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Grass::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		for (int i = 0; i < mMats_.size(); i++) {
			dmat4 aMat = modelViewMat * mMats_[i];
			upload(aMat);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.5);
			mTexture->bind(GL_REPEAT);
			mMesh->render();
			mTexture->unbind();
			glDisable(GL_ALPHA_TEST);
		}
	}
}

Cristalera::Cristalera(GLdouble ld) {
	mMesh = Mesh::generaContCristal(ld);
}

Cristalera::~Cristalera() {
	delete mMesh; mMesh = nullptr;
}

void Cristalera::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();

		glDisable(GL_BLEND);
	}
}
