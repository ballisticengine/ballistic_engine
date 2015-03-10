#include "loaders/loaderMD2.hpp"

void LoaderMD2::md2ToShape(md2file *md2, Shape *s) {

    s->v_count = md2->header.num_tris * 3; //num_xyz
    s->vertices = new MathTypes::BasicVector[s->v_count];
    s->f_count = md2->header.num_tris;
    s->v_per_poly = 3;
    s->textures = new Texture*[s->f_count];
    s->materials = new Material*[s->f_count];
    cout << "T: " << md2->frames[0].translate[2] << endl;
    for (int i = 0; i < s->v_count; i++) {
        md2_vertex_t md2v = md2->frames[0].verts[i];
        float * scale = md2->frames[0].scale;
        vec3_t scaled;
        
        for (int n = 0; n < 3; n++) {
            if (n == 2) {
                if( md2->frames[0].translate[n]>=0) {
               
                scaled[n] = (float) md2v.v[n] * scale[n] * this->scale - md2->frames[0].translate[n]*(this->scale*5.4);
                } else {
                   scaled[n] = (float) md2v.v[n] * scale[n] * this->scale + md2->frames[0].translate[n]*(this->scale*4.5);
                }
            } else {
                scaled[n] = (float) md2v.v[n] * scale[n] * this->scale + md2->frames[0].translate[n] * this->scale;
            }
        }

        s->vertices[i].x = scaled[0];
        s->vertices[i].y = scaled[1];
        s->vertices[i].z = scaled[2];

    }

    cout << "MD2 Skin: " << md2->skin << endl;
    e_loc u, v;
    s->faces = new Face[s->f_count];
    for (int i = 0; i < s->f_count; i++) {
        s->faces[i].index = new unsigned int[s->v_per_poly];
        s->faces[i].uvs = new UV[s->v_per_poly];
        s->textures[i] = 0;
        s->materials[i] = 0;
        for (int vi = 0; vi < 3; vi++) {
            s->faces[i].index[vi] = md2->tris[i].vertex[vi];
            int iv = md2->tris[i].st[vi];
            s->faces[i].uvs[vi].u = (float) md2->st[iv].s / (float) md2->header.skinwidth;
            s->faces[i].uvs[vi].v = (float) md2->st[iv].t / (float) md2->header.skinheight;
        }
    }
    s->textures[0] = (Texture *) TextureFactory::getInstance()->get("@" + string((char *) md2->skin));
    s->calculateNormals();
    int cw=GL_CCW;
    s->renderer_hint=(void *)new int;
    *((int *)s->renderer_hint)=cw;
    //    for (int t = 0; t < md2->header.num_tris; t++) {
    //
    //
    //        for (int vi = 0; vi < 3; vi++) {
    //
    //            i = md2->tris[t].vertex[vi];
    //            iv = md2->tris[t].st[vi];
    //            // cout << i << endl;    
    //            md2_vertex_t md2v = md2->frames[0].verts[i];
    //            float * scale = md2->frames[0].scale;
    //            float *translate = md2->frames[0].translate;
    //            vec3_t scaled;
    //            float u, v;
    //
    //
    //            for (int n = 0; n < 3; n++) {
    //                scaled[n] = (float) md2v.v[n] * scale[n]; //+translate[n];
    //				//cout << "SC: " << this->scale;
    //				//scaled[n]*=this->scale;
    //			}
    //            
    //			u = (float) md2->st[iv].s / (float) md2->header.skinwidth;
    //            v = (float) md2->st[iv].t / (float) md2->header.skinheight;
    //            utmp[vi]=new uv();
    //			utmp[vi]->u=u;
    //			utmp[vi]->v=v;
    //			vs_tmp[vi] = new vertex(scaled[0], scaled[1], scaled[2]);
    //            // cout << scaled[0] << "," << scaled[1] << "," << scaled[2] << endl;
    //
    //        }
    //        vt = new triangle(vs_tmp[0], vs_tmp[1], vs_tmp[2]);
    //		for(i=0; i<vt->v.size(); i++) {
    //			vt->uvs.push_back(utmp[i]);
    //			}
    //		
    //		//vt->calculateNormals();
    //		
    //		s->addPoly(vt);
    //		
    //    }


}

bool LoaderMD2::loadMD2(string fn, Shape *s, e_loc scale) {
    this->scale = scale;
    cout << "MD2: " << fn << endl;
    FILE *f;
    f = fopen(fn.c_str(), "rb");
    if (!f) {
        return false;
    }
    md2file *md2 = new md2file;

    fread(&md2->header, 1, sizeof (md2header), f);
    if (md2->header.ident != MD2_MAGIC) {
        return false;
    }
    md2->tris = (md2triangle *) malloc(sizeof (md2triangle) * md2->header.num_tris);
    md2->frames = (md2frame *)
            malloc(sizeof ( md2frame) * md2->header.num_frames);
    md2->st = (md2st *) malloc(sizeof (md2st) * md2->header.num_st);
    fseek(f, md2->header.ofs_tris, SEEK_SET);
    fread(md2->tris, sizeof (md2triangle),
            md2->header.num_tris, f);
    fseek(f, md2->header.ofs_st, SEEK_SET);
    fread(md2->st, sizeof (md2st),
            md2->header.num_st, f);
    fseek(f, md2->header.ofs_frames, SEEK_SET);
    for (int i = 0; i < md2->header.num_frames; ++i) {
        /* Memory allocation for vertices of this frame */
        md2->frames[i].verts = (md2_vertex_t *)
                malloc(sizeof (md2_vertex_t) * md2->header.num_xyz);

        /* Read frame data */
        fread(md2->frames[i].scale, sizeof (vec3_t), 1, f);
        fread(md2->frames[i].translate, sizeof (vec3_t), 1, f);
        fread(md2->frames[i].name, sizeof (char), 16, f);
        fread(md2->frames[i].verts, sizeof (struct md2_vertex_t),
                md2->header.num_xyz, f);
        break; //no support for animations for now
    }
    fseek(f, md2->header.ofs_skins, SEEK_SET);
    fread(md2->skin, sizeof (unsigned char), 64, f);
    fclose(f);

    this->md2ToShape(md2, s);
    return true;
}