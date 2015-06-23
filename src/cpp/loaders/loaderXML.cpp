#include "loaders/LoaderXML.hpp"

bool LoaderXML::load(string fn, ModelInfo *mi, bool force_common) {
    this->force_common = force_common;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
    ptree shp = pt.get_child("shape");
    ptree geom = shp.get_child("geom");
    this->toShape(geom, shp, mi);
    return true;
}

void LoaderXML::toShape(ptree &geom, ptree &shape_xml, ModelInfo *mi) {

    ptree
    verts = geom.get_child("vertices"),
            faces = geom.get_child("faces"),
            uvs = geom.get_child("uvs")
            ;
    size_t
    v_count = geom.get<size_t>("counts.vertices"),
            f_count = geom.get<size_t>("counts.faces"),
            uv_count = geom.get<size_t>("counts.uvs"),
            vpf = geom.get<size_t>("counts.v_p_f")
            ;


    string type;
    try {
        type = shape_xml.get<string>("type");
    } catch (std::exception e) {
        type = "level";
    }
    Shape *s=mi->s;
    s->f_count = f_count;
    s->v_count = v_count;
    s->v_per_poly = vpf;
    s->uv_count = uv_count;
    s->vertices = new v_type[v_count];
    s->normals = new n_type[v_count];
    s->faces = new Face[f_count];
    //s->uvs = new uv[uv_count];
    s->textures = new Texture*[f_count];
    s->materials = new Material*[f_count];
    s->frame_count = 0;
    int i;

    i = 0;

    BOOST_FOREACH(const ptree::value_type &vx, verts) {
        ptree
        coords = vx.second.get_child("coords"),
                normal = vx.second.get_child("normal")
                ;
        e_loc
        x = coords.get<e_loc>("x"),
                y = coords.get<e_loc>("y"),
                z = coords.get<e_loc>("z"),
                nx = normal.get<e_loc>("x"),
                ny = normal.get<e_loc>("y"),
                nz = normal.get<e_loc>("z")
                ;
        s->vertices[i].x = x;
        s->vertices[i].y = y;
        s->vertices[i].z = z;
        s->normals[i].x = nx;
        s->normals[i].y = ny;
        s->normals[i].z = nz;

        Vector3d norm;

        i++;
    }

    i = 0;

    int n = 0, uvc = 0;

    BOOST_FOREACH(const ptree::value_type &face, faces) {
        ptree f_verts = face.second.get_child("vertices");
        s->faces[i].index = new unsigned int[vpf];
        s->faces[i].uvs=new UV[vpf];
        s->faces[i].normals= new Vector3d[vpf];
        try {
            
            
            string texname = face.second.get<string>("texture");
            
            Texture *t = (Texture *) TextureFactory::getInstance()->get(texname, this->force_common);
            
            s->textures[i] = t;
        } catch (std::exception e) {
            s->textures[i] = 0;

        }

        try {
            ptree material = face.second.get_child("material");
            ColorRGBA sc, dc;

            sc.r = material.get<e_loc>("specular.r");
            sc.g = material.get<e_loc>("specular.g");
            sc.b = material.get<e_loc>("specular.b");
            dc.r = material.get<e_loc>("diffuse.r");
            dc.g = material.get<e_loc>("diffuse.g");
            dc.b = material.get<e_loc>("diffuse.b");
            e_loc shin = material.get<e_loc>("shining"),
                    emit = material.get<e_loc>("emit")
                    ;
            Material *m = new Material();
            m->setShininess(shin);
            m->setEmission(emit);
            m->setDiffuse(dc);
            m->setSpecular(sc);
            s->materials[i] = m;
        } catch (std::exception e) {
            s->materials[i] = 0;
        }

        n = 0;
       
        BOOST_FOREACH(const ptree::value_type &f_vx, f_verts) {
            size_t index = f_vx.second.get<size_t>("i");
            s->faces[i].index[n] = index;
            ptree uv = f_vx.second.get_child("uv");
            s->faces[i].uvs[n].u = uv.get<e_loc>("u");
            s->faces[i].uvs[n].v = uv.get<e_loc>("v");
            s->faces[i].normals[n]=s->normals[index];
            uvc++;
            n++;

        }
        i++;
    }

    
    if (type == "animation") {
        ptree frames = shape_xml.get_child("frames");
        size_t frame_count = shape_xml.get<size_t>("frame_count");
        s->frame_count = frame_count;
        s->frames = new Frame[frame_count];
        s->frame_times = new e_loc[frame_count];
        size_t frame_i = 0, vert_i;

        BOOST_FOREACH(const ptree::value_type &frame, frames) {
            ptree frame_verts = frame.second.get_child("vertices");
            s->frames[frame_i].verts = new v_type[v_count];
            s->frames[frame_i].fnum = frame.second.get<e_loc>("fnum");
            s->frames[frame_i].fval = frame.second.get<e_loc>("fval");
            s->frame_times[frame_i] = frame.second.get<e_loc>("ftime");
            vert_i = 0;

            BOOST_FOREACH(const ptree::value_type &vert, frame_verts) {
                e_loc
                x = vert.second.get<e_loc>("x"),
                        y = vert.second.get<e_loc>("y"),
                        z = vert.second.get<e_loc>("z")
                        ;
                s->frames[frame_i].verts[vert_i].x = x;
                s->frames[frame_i].verts[vert_i].y = y;
                s->frames[frame_i].verts[vert_i].z = z;
                vert_i++;

            }
            frame_i++;

        }
    }
    
    mi->s=s;
    e_loc slocx=0,slocy=0,slocz=0;
            
    try {
            slocx=shape_xml.get<e_loc>("loc.x");
            slocy=shape_xml.get<e_loc>("loc.y");
            slocz=shape_xml.get<e_loc>("loc.z");
    }catch (std::exception e) {
        cout << "No loc for " << type;
    }
    try {
        ptree bounds_xml=shape_xml.get_child("bounds");
        BOOST_FOREACH(const ptree::value_type &bound_xml, bounds_xml) {
            cout << "SLC " << slocx << endl;
            e_loc
                        locx=bound_xml.second.get<e_loc>("loc.x"),
                        locy=bound_xml.second.get<e_loc>("loc.y"),
                        locz=bound_xml.second.get<e_loc>("loc.z"),
                        minx = bound_xml.second.get<e_loc>("min.x")-slocx+locx,
                        miny = bound_xml.second.get<e_loc>("min.y")-slocy+locy,
                        minz = bound_xml.second.get<e_loc>("min.z")-slocz+locz,
                       
                        maxx = bound_xml.second.get<e_loc>("max.x")-slocx+locx,
                        maxy = bound_xml.second.get<e_loc>("max.y")-slocy+locy,
                        maxz = bound_xml.second.get<e_loc>("max.z")-slocz+locz
                        ;
            string name=bound_xml.second.get<string>("name");
            BoundingCube *bc = new BoundingCube(minx, miny, minz, maxx, maxy, maxz);
            bc->name = name;
            cout << "Bounding names:\n";
            cout << bc->name << endl;
            mi->boundings.push_back(bc);
            
        }
        
    } catch (std::exception e) {
        
    }

}

string LoaderXML::loadXML(ptree &tree, Shape *s) {
    ptree & geom = tree.get_child("shape.geom"),
            &shape = tree.get_child("shape")
            ;

    string name = this->getName(tree);
    ModelInfo *mi=new ModelInfo();
    mi->s=s;
    this->toShape(geom, shape, mi);
    
    return name;
}

string LoaderXML::getName(ptree &tree) {
    string name = tree.get<string>("shape.name");
    return name;
}

