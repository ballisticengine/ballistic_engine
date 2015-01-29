#include "loaders/loaderXML.hpp"

bool loaderXML::load(string fn, modelInfo *mi, bool force_common) {
    this->force_common = force_common;
    ptree pt;
    read_xml(fn, pt, boost::property_tree::xml_parser::trim_whitespace);
    ptree shp = pt.get_child("shape");
    ptree geom = shp.get_child("geom");
    this->toShape(geom, shp, mi);
    return true;
}

void loaderXML::toShape(ptree &geom, ptree &shape_xml, modelInfo *mi) {

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
    shape *s=mi->s;
    s->f_count = f_count;
    s->v_count = v_count;
    s->v_per_poly = vpf;
    s->uv_count = uv_count;
    s->vertices = new v_type[v_count];
    s->normals = new n_type[v_count];
    s->faces = new face[f_count];
    //s->uvs = new uv[uv_count];
    s->textures = new texture*[f_count];
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

        MathTypes::vector norm;

        i++;
    }

    i = 0;

    int n = 0, uvc = 0;

    BOOST_FOREACH(const ptree::value_type &face, faces) {
        ptree f_verts = face.second.get_child("vertices");
        s->faces[i].index = new unsigned int[vpf];
        s->faces[i].uvs=new uv[vpf];
        s->faces[i].normals= new MathTypes::BasicVector[vpf];
        try {
            
            
            string texname = face.second.get<string>("texture");
            
            texture *t = (texture *) textureFactory::getInstance()->get(texname, this->force_common);
            
            s->textures[i] = t;
        } catch (std::exception e) {
            s->textures[i] = 0;

        }

        try {
            ptree material = face.second.get_child("material");
            colorRGBA sc, dc;

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
//    face *nfs=new face[f_count];
//    int q=f_count-1;
//    for(int p=0; p<f_count; p++) {
//        nfs[p]=s->faces[p];
//        nfs[p].uvs=s->faces[q].uvs;
//        q--;
//    }
//    
//    s->faces=nfs;
    
    if (type == "animation") {
        ptree frames = shape_xml.get_child("frames");
        size_t frame_count = shape_xml.get<size_t>("frame_count");
        s->frame_count = frame_count;
        s->frames = new frame[frame_count];
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
    try {
        ptree bounds_xml=shape_xml.get_child("bounds");
        BOOST_FOREACH(const ptree::value_type &bound_xml, bounds_xml) {
            /*
               e_loc
                minx = entobj.second.get<float>("min.x"),
                        miny = entobj.second.get<float>("min.y"),
                        minz = entobj.second.get<float>("min.z"),
                        maxx = entobj.second.get<float>("max.x"),
                        maxy = entobj.second.get<float>("max.y"),
                        maxz = entobj.second.get<float>("max.z")
                        ;
                cout << "Found bounding\n";
                cout << minx << ", " << miny << ", " << minz << ", " << maxx << ", " << maxy << ", " << maxz << endl;
                BoundingCube *bc = new BoundingCube(minx, miny, minz, maxx, maxy, maxz);
                bc->name = name;
                roomE->boundings.push_back(bc);
             */
            e_loc
                minx = bound_xml.second.get<float>("min.x"),
                        miny = bound_xml.second.get<float>("min.y"),
                        minz = bound_xml.second.get<float>("min.z"),
                        maxx = bound_xml.second.get<float>("max.x"),
                        maxy = bound_xml.second.get<float>("max.y"),
                        maxz = bound_xml.second.get<float>("max.z")
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

string loaderXML::loadXML(ptree &tree, shape *s) {
    ptree & geom = tree.get_child("shape.geom"),
            &shape = tree.get_child("shape")
            ;

    string name = this->getName(tree);
    modelInfo *mi=new modelInfo();
    mi->s=s;
    this->toShape(geom, shape, mi);
    
    return name;
}

string loaderXML::getName(ptree &tree) {
    string name = tree.get<string>("shape.name");
    return name;
}

