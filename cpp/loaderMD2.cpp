#include "loaderMD2.hpp"

 void loaderMD2::md2ToShape(md2file *md2,shape *s) {
 
 }

 bool loaderMD2::loadMD2(string fn, shape *s) {
    FILE *f;
    f = fopen(fn.c_str(), "rb");
    if (!f) {
        return false;
    }
    md2file *md2=new md2file;
   
    fread(&md2->header, 1, sizeof (md2header), f);
    if (md2->header.ident != MD2_MAGIC) {
        return false;
    }
    md2->tris = (md2triangle *) malloc(sizeof (md2triangle) * md2->header.num_tris);
    md2->frames = (md2frame *)
            malloc(sizeof ( md2frame) * md2->header.num_frames);
    fseek(f, md2->header.ofs_tris, SEEK_SET);
    fread(md2->tris, sizeof (md2triangle),
            md2->header.num_tris, f);
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

    fclose(f);
    return true;
}