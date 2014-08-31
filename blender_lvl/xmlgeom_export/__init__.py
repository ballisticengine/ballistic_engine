bl_info = {
    "name": "XML Geometry format",
    "author": "Maciej Zakrzewski",
    "blender": (2, 57, 0),
    "location": "File > Import-Export",
    "description": "Export to xml format",
    "warning": "",
    "category": "Import-Export"}



import bpy
from bpy.props import StringProperty, FloatProperty, BoolProperty, EnumProperty
from bpy_extras.io_utils import (ImportHelper,
                                 ExportHelper,
                                 axis_conversion,
                                 )

import xml.etree.ElementTree as ET
import math


#HELPER START

# bpy.ops.object.mode_set(mode='OBJECT')

def determineTexture(model):
    img=''
    for t in model.data.uv_textures.active.data:
     if t.image:
        img = t.image.name
        print (img)
    return img

class EmptyUV:
    uv = (0.0, 0.0)
    def __getitem__(self, index): return self

def shapeExport(model,scale=1):
        #scene = context.scene
        shape=ET.Element('shape')
        #texture=ET.SubElement(shape,'texture')
        name=ET.SubElement(shape,'name')
        geom=ET.SubElement(shape,'geom')
        name.text=model.data.name
        #texture.text=determineTexture(model)
        i=0



        verts = model.data.vertices
        loop_vert = {l.index: l.vertex_index for l in model.data.loops}
        scene = bpy.context.scene
        model=model.to_mesh(scene, True, 'PREVIEW', calc_tessface=False)
        for f in model.polygons:
            texfn=model.uv_textures.active.data[f.index].image.name
            uv_act = model.uv_layers.active
            uv_layer = uv_act.data if uv_act is not None else EmptyUV()
            print (texfn)
            face=ET.SubElement(geom,'face')
            vertices=ET.SubElement(face,'vertices')
            texture=ET.SubElement(face,'texture')
            texture.text=texfn
            for li in f.loop_indices:
               coords=verts[loop_vert[li]].co
               uv=uv_layer[li].uv
               vertex=ET.SubElement(vertices,'vertex')
               x=ET.SubElement(vertex,'x')
               y=ET.SubElement(vertex,'y')
               z=ET.SubElement(vertex,'z')
               u=ET.SubElement(vertex,'u')
               v=ET.SubElement(vertex,'v')
               x.text=str(coords[0]*scale)
               y.text=str(coords[1]*scale)
               z.text=str(coords[2]*scale)
               u.text=str(uv[0])
               v.text=str(uv[1])
            i+=1
        return shape

#HELPER END





class ExportXML(bpy.types.Operator,ExportHelper):
    bl_idname = "export_scene.xml_geom"
    bl_label = 'Export to XML Geometry'
    filename_ext = ".xml"
    scale = FloatProperty(
            name="Scale",
            description="",
            min=0.0, max=1000.0,
            default=1.0,
            )

    def execute(self, context):
        shape=shapeExport(context.active_object,self.scale)
        room=ET.Element('room')
        room.append(shape)
        level=ET.Element('level')
        level.append(room)
        tree = ET.ElementTree(level)
        keywords = self.as_keywords()
        f=open(self.filepath,"wb")
        print (self.filepath)
        tree.write(f)
        #tree.close()
        f.close()
        return {'FINISHED'}


def menu_func_export(self, context):
    self.layout.operator(ExportXML.bl_idname, text="XML Geomerty (.xml)")



def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
    register()