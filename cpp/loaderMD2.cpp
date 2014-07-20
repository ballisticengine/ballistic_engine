#include "loaderMD2.hpp"

bool loaderMD2::loadMD2(string fn,shape *s) {
    FILE *f;
    f=fopen(fn.c_str(),"rb");
    if(!f) {
        return false;
    }
    md2header header;
    md2triangle *tris;
    md2frame *frames;
    fread (&header, 1, sizeof (struct header), f);
    if (header.ident!=MD2_MAGIC) {
        return false;
    }
    tris = (md2triangle *)malloc (sizeof (md2triangle) * header.num_tris);
    frames = ( md2frame *)
    malloc (sizeof ( md2frame) * header.num_frames);
    
    fclose(f);
}