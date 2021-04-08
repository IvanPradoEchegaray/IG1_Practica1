#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{	
	setGL();  // OpenGL settings

	if (mId == 0)	//Escena 0
	{
		glClearColor(47.0 / 255.0, 47.0 / 255.0, 63.0 / 255.0, 1.0);
		RectanguloRGB* rRGB = new RectanguloRGB(1000, 800);
		rRGB->setModelMat(translate(dmat4(1), dvec3(0, 0, -100)));

		Poligono* c = new Poligono(100, 250);
		c->modColor(dvec4(1.0, 0.0, 1.0, 1.0));

		Serpinski* s = new Serpinski(250, 30000);
		s->modColor(dvec4(1.0, 1.0, 0.0, 1.0));

		TrianguloRGB* t = new TrianguloRGB();

		gObjects.push_back(rRGB);
		gObjects.push_back(new EjesRGB(400.0));
		gObjects.push_back(t);
		gObjects.push_back(c);
		gObjects.push_back(s);
	}   //Escena 0

	else if (mId == 1)		//Escena 1
	{
		glClearColor(40.0 / 255.0, 24.0 / 255.0, 42.0 / 255.0, 1.0);
		
		gObjects.push_back(new EjesRGB(400.0));
		
		/*CAJA*/
		Texture* texCaj = nullptr;
		Texture* texFon = nullptr;

		CajaConFondo* box = new CajaConFondo(100);
		gObjects.push_back(box);
		
		texCaj = new Texture();
		texFon = new Texture();
		texCaj->load("../Bmps/container.bmp");
		texFon->load("../Bmps/papelC.bmp");
		gTextures.push_back(texCaj);
		gTextures.push_back(texFon);

		dvec3 posBox = dvec3(-160.0, 50, -160.0);
		gObjects.back()->setModelMat(translate(dmat4(1), posBox));
		box->setModelMatSuelo(translate(dmat4(1), posBox));
		box->setTranslation(posBox);
		box->setTexture(texCaj, texFon);

		/*SUELO*/
		Texture* texSuel = nullptr;

		gObjects.push_back(new Suelo(800.0, 8));

		texSuel = new Texture();
		texSuel->load("..\\Bmps\\baldosac2.bmp");
		gTextures.push_back(texSuel);

		gObjects.back()->setTexture(texSuel);
	    gObjects.back()->modColor(dvec4(1.0, 0.5, 1.0, 1));
		gObjects.back()->setModelMat(rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0)));
		
		/*ESTRELLA*/
		Texture* texEst = nullptr;

		Estrella3D* est = new Estrella3D(50, 4, 60);
		gObjects.push_back(est);

		texEst = new Texture();
		texEst->load("../Bmps/baldosaP2.bmp");
		gTextures.push_back(texEst);

		dvec3 posEst = dvec3(-160.0, 200.0, -160.0);
		gObjects.back()->setModelMat(translate(dmat4(1), posEst));
		est->setTranslation(posEst);
		gObjects.back()->setTexture(texEst);

		/*FOTO*/
		Texture* texFot;
		
		Foto* foto = new Foto(200);
		gObjects.push_back(foto);
		
		texFot = new Texture();
		gTextures.push_back(texFot);
		
		dvec3 posFot = dvec3(0.0, 1.0, 0.0);
		gObjects.back()->setModelMat(rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0)));
		foto->setTranslation(posFot);
		foto->setTexture(texFot);

		/*PLANTA*/
		Texture* tex_grass = new Texture();
		tex_grass->load("../Bmps/grass.bmp", u8vec3(0, 0, 0), 0);
		dvec3 posGrass = dvec3(100, 0, -100);
		gObjects.push_back(new Grass(5, 120, 120, posGrass));//ej18
		gObjects.back()->setTranslation(posGrass);
		gObjects.back()->setTexture(tex_grass);

		/*CRISTALERA*/
		Texture* texCris;

		GLdouble ladoCrist = 800.0;
		Cristalera* crist = new Cristalera(ladoCrist);
		gObjects.push_back(crist);

		texCris = new Texture();
		texCris->load("../Bmps/windowV2.bmp", 255 / 2);
		gTextures.push_back(texCris);

		crist->setTexture(texCris);
		crist->setModelMat(translate(dmat4(1), dvec3(0.0, ladoCrist/6, 0.0)));
	}

	else if (mId == 2) {
		
	}

    // Graphics objects (entities) of the scene
	//-------------------------------------------------------------------------
	//EJER 1
	/*Poligono* n = new Poligono(3, 100);
	n->modColor(dvec4(1.0, 1.0, 0.0, 1.0));
	Poligono* c = new Poligono(100, 100);
	c->modColor(dvec4(1.0, 0.0, 1.0, 1.0));

	gObjects.push_back(n);
	gObjects.push_back(c);*/
	//-------------------------------------------------------------------------
	//EJER4
		//Rectangulo
	//Rectangulo* rect = new Rectangulo(20, 10);
	//rect->modColor((dvec4(0.5, 0.0, 0.5, 1.0)));
	//	//RectangulorRGB
	/*RectanguloRGB* rRGB = new RectanguloRGB(1000, 800);
	gObjects.push_back(rRGB);
	rRGB->setModelMat(translate(dmat4(1), dvec3(0, 0, -100)));*/
	//gObjects.push_back(new EjesRGB(400.0));
	//-------------------------------------------------------------------------
	//EJER2
	//Poligono* c = new Poligono(100, 250);
	//c->modColor(dvec4(1.0, 0.0, 1.0, 1.0));

	//Serpinski* s = new Serpinski(250, 30000);
	//s->modColor(dvec4(1.0, 1.0, 0.0, 1.0));

	////gObjects.push_back(new EjesRGB(400.0));
	//gObjects.push_back(s);
	//gObjects.push_back(c);
	//-------------------------------------------------------------------------
	//EJER3
	/*TrianguloRGB* t = new TrianguloRGB();

	gObjects.push_back(t);
	gObjects.push_back(new EjesRGB(700.0));*/
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   
	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	for (Texture* tex : gTextures)
	{
		delete tex; tex = nullptr;
	}
	gObjects.clear();
	gTextures.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);	//activamos la textura
}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 
	glDisable(GL_TEXTURE_2D);	//desactivamos la textura
}
//-------------------------------------------------------------------------
void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------
void Scene::update() {
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------
void Scene::changeScene(int id) {
	free();
	mId = id;
	init();
}
//-------------------------------------------------------------------------

void Scene::screenShot() {
	Texture* tex = new Texture();
	tex->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT);
	tex->save("screenshot.bmp");
	delete tex;
}