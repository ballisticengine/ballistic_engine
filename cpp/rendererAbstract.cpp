#include "rendererAbstract.hpp"
#include "types.hpp"

renderer::renderer() {
	state=engineState::getInstance();
}

renderer::~renderer() {

}

void renderer::positionLights() {
 lights_list lights=this->w->getLights();
 //cout << "Lights" << lights.size() << endl;
 for(int i=0; i<lights.size(); i++) {
  this->lightSpecific(lights[i]);
 // cout << "Light " << i << endl;
 }
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
	 cursor.translation.x+=x;
	 cursor.translation.y+=y;
	 cursor.translation.z+=z;
	 this->translateSpecific(x,y,z);
 }

 void  renderer::translate(coords c) {
	 this->translate(c.translation.x,c.translation.y,c.translation.z);
 }

 void renderer::rotate(e_loc x,e_loc y,e_loc z,e_loc d) {
  cursor.rotation.x+=x*d;
  cursor.rotation.y+=y*d;
  cursor.rotation.z+=z*d;
  this->rotateSpecific(x,y,z,d);
 }

void renderer::renderAllEntities() { //to sie nie nadaje do poziomów bo transformuje
	obj_list ents=w->getModels();
	//cout << ents.size() << endl;
	
	for(int i=0; i<ents.size(); i++) {
		
		coords c=ents[i]->getCoords();
		this->reset();
		this->positionCamera();
		this->locate(c.translation.x,c.translation.y,c.translation.z);
		this->face(c.rotation.x,c.rotation.y,c.rotation.z);
		
		//this->assignMaterial(ents[i]->getMaterial());
		
		//this->drawBoundingBox(ents[i]->getBoundingBox());
		this->renderFaceTexShape(ents[i]->getModel());
		if(state->debug_visual) {
			this->drawBoundingBox(ents[i]->getBoundingBox());
		}
		
	}
}

void renderer::renderAllRooms() {
	rooms_list rooms=w->getRooms();
	for(size_t i=0; i<rooms.size(); i++) {
		
		this->renderFaceTexShape((faceTexShape *)rooms[i]->getModel());
		if(state->debug_visual) {
			for(size_t n=0; n<rooms[i]->boundings.size(); n++) {
				this->drawBoundingBox(rooms[i]->boundings[n]);
			}
		}
	}
}

void renderer::renderFaceTexShape(faceTexShape *s) {
    poly_list polys;
  
	polys = s->getPolys();

	for (int i = 0; i < polys.size(); i++) {
        texPoly *t=(texPoly *)polys[i];
		
		if(t->getTexture()) {
			this->assignTexture(t->getTexture());
			
		}

		//if(t->getMaterial()) {
		//	this->assignMaterial(t->getMaterial());	
		//}

		int count=s->getPolyCount();
		this->beginHinted(s);
		for (int n = 0; n < count; n++) {
			this->renderVertex(polys[i]->v[n],polys[i]->uvs[n]);
        }
		this->end();
    }
	
}

void renderer::setFlush(flushf flush_callback) {
    this->flush_callback = flush_callback;
}

void renderer::renderPShape(shape *s) {
    vert_list verts = s->getVertices();
	uv_list uvs=s->getUvs();
	this->begin();
	for (int i = 0; i < verts.size(); i++) {
        this->renderVertex(verts[i],uvs[i]);
    }
	this->end();
}

void renderer::renderShape(shape *s) {
    poly_list tris;
	tris = s->getPolys();
    this->begin();
	for (int i = 0; i < tris.size(); i++) {
       
		for (int n = 0; n < 3; n++) {
			this->renderVertex(tris[i]->v[n],tris[i]->uvs[n]);
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
	cursor.translation.x=0;
	cursor.translation.y=0;
	cursor.translation.z=0; //coœ nie dzia³a z frustum_start zmienionym
	cursor.rotation.x=0;
	cursor.rotation.y=0;
	cursor.rotation.z=0;
}

 void renderer::setCamera(camera *c) { //to przenieœæ do world
	 this->active_camera=c;
 }

 void renderer::positionCameraSpecific() {
	
 }

 void renderer::positionCamera() {
	// coords c=active_camera->getCoords();
	 coords c=w->getObserver()->getCoords();
	 rotate(1,0,0,c.rotation.x);
	 rotate(0,1,0,c.rotation.y);
	 rotate(0,0,1,c.rotation.z);
	 translate(c.translation.x,c.translation.y,c.translation.z);
	 //this->positionCameraSpecific();
 }