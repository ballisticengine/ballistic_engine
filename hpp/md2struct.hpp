/* 
 * File:   md2stuct.hpp
 * Author: maciek
 *
 * Created on July 20, 2014, 5:52 PM
 */

#ifndef MD2STUCT_HPP
#define	MD2STUCT_HPP
#define MD2_MAGIC 844121161

/*
 Offset 	Data type 	Name 	Description
0 	int 	ident 	Magic number. Must be equal to "IDP2"
4 	int 	version 	MD2 version. Must be equal to 8
8 	int 	skinwidth 	Width of the texture
12 	int 	skinheight 	Height of the texture
16 	int 	framesize 	Size of one frame in bytes
20 	int 	num_skins 	Number of textures
24 	int 	num_xyz 	Number of vertices
28 	int 	num_st 	Number of texture coordinates
32 	int 	num_tris 	Number of triangles
36 	int 	num_glcmds 	Number of OpenGL commands
40 	int 	num_frames 	Total number of frames
44 	int 	ofs_skins 	Offset to skin names (each skin name is an unsigned char[64] and are null terminated)
48 	int 	ofs_st 	Offset to s-t texture coordinates
52 	int 	ofs_tris 	Offset to triangles
56 	int 	ofs_frames 	Offset to frame data
60 	int 	ofs_glcmds 	Offset to OpenGL commands
64 	int 	ofs_end 	Offset to end of file
 */

struct md2header {
    int ident,version,skinwidth,skinheight,framesize,num_skins,num_xyz,num_st,num_tris,num_glcmds,num_frames,
    ofs_skins,ofs_st,ofs_tris,ofs_frames,ofs_glcmds,ofs_end;
};

typedef float vec3_t[3];

struct md2frame
{
  vec3_t scale;               /* scale factor */
  vec3_t translate;           /* translation vector */
  char name[16];              /* frame name */
  struct md2_vertex_t *verts; /* list of frame's vertices */
};

struct md2triangle
{
  unsigned short vertex[3];
  unsigned short st[3];    
};

struct md2_vertex_t
{
  unsigned char v[3];        
  unsigned char normalIndex; /* nieużywanie */
};

struct md2st {
    short s,t;
};

#endif	/* MD2STUCT_HPP */

