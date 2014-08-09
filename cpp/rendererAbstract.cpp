#include "rendererAbstract.hpp"
#include "types.hpp"

renderer::renderer() {

}

renderer::~renderer() {

}

void renderer::setupTextures() {
	textureFactory *tf=textureFactory::getInstance();
	vector<void *> ts=tf->getAll();
	for(int i=0; i<ts.size(); i++) {
		this->setupTexture((texture *)ts[i]);
	}
}

void renderer::init() {
	
	config *c=config::getInstance();
	frustum_start = c->getVD()->frustum_start;
	frustum_end = c->getVD()->frustum_end;
	frustum_x = c->getVD()->frustum_x;
	frustum_y = c->getVD()->frustum_y;
    this->vd = vd;
    this->w = (world *) world::getInstance();
    skybox *sky = this->w->getSkybox();

    sky->makeShape(frustum_x, frustum_y);
	
    gx=0;
    gy=0;
    gz=0;
    gr=0;
     this->specificInit();
	 this->setupTextures();

}

 void renderer::translate(e_loc x, e_loc y, e_loc z) {
	 cursor.x+=x;
	 cursor.y+=y;
	 cursor.z+=z;
	 this->translateSpecific(x,y,z);
 }

 void  renderer::translate(coords c) {
	 this->translate(c.x,c.y,c.z);
 }

 void renderer::rotate(e_loc x,e_loc y,e_loc z,e_loc d) {
  cursor.rx+=x*d;
  cursor.ry+=y*d;
  cursor.rz+=z*d;
  this->rotateSpecific(x,y,z,d);
 }

void renderer::renderAllEntities() {
	obj_list ents=w->getModels();
	for(int i=0; i<ents.size(); i++) {
		
		coords c=ents[i]->getCoords();
		this->reset(); // do origin
		this->locate(c.x,c.y,c.z);
		this->face(c.rx,c.ry,c.rz);
		this->assignTexture(ents[i]->getTexture());
		this->renderShape(ents[i]->getModel());
		
	}
}

void renderer::setFlush(flushf flush_callback) {
    this->flush_callback = flush_callback;
}

void renderer::renderPShape(shape *s) {
    vert_list verts = s->getVertices();
   
	this->begin();
	for (int i = 0; i < verts.size(); i++) {
        this->renderVertex(verts[i]);
    }
	this->end();
}

void renderer::renderShape(shape *s) {
    tris_list tris;
  
	tris = s->getTris();

    this->begin();
	for (int i = 0; i < tris.size(); i++) {
       
		for (int n = 0; n < 3; n++) {
            this->renderVertex(tris[i]->v[n]);
        }
    }
	this->end();
}

void renderer::operator()() {
    this->init();
	while (true) {
        this->render();
		
    }
}

void renderer::locate(e_loc x,e_loc y,e_loc z) {
	//this->face(-cursor.rx,-cursor.ry,-cursor.rz);
	/*cout << cursor.x << ", " << cursor.y << ", " << cursor.rx << ", " << cursor.ry << ", " << cursor.rz << endl;
	x-=cursor.x;
	y-=cursor.y;
	z-=cursor.z;
	*/
	this->translate(x,y,z);
}

void renderer::face(e_loc x,e_loc y,e_loc z) { //tu Ÿle, bo powinien mno¿yæ, wywaliæ rotateSpecific(x,y,z) zostawiæ to z x,y,z,d
	/*static int i=0;
	x-=cursor.rx;
	y-=cursor.ry;
	z-=cursor.rz;
	//cout << i++ << ": " <<cursor.rx << ", " << x << endl;*/
	this->rotate(1,0,0,x);
	this->rotate(0,1,0,y);
	this->rotate(0,0,1,z);

	
}

void renderer::reset() {
	this->resetSpecific();
	cursor.x=0;
	cursor.y=0;
	cursor.z=0; //coœ nie dzia³a z frustum_start zmienionym
	cursor.rx=0;
	cursor.ry=0;
	cursor.rz=0;
}

 void renderer::setCamera(camera *c) { //to przenieœæ do world
	 this->active_camera=c;
 }

 void renderer::positionCamera() {
	 coords c=active_camera->getCoords();
	 translate(c.x,c.y,c.z);
	 rotate(1,0,0,c.rx);
	 rotate(0,1,0,c.ry);
	 rotate(0,0,1,c.rz);
 }