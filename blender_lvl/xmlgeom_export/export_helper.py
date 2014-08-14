import bpy
from bpy import context
import xml.etree.ElementTree as ET


bpy.ops.object.mode_set(mode='OBJECT')

def determineTexture(model):
    img=''
    for t in model.data.uv_textures.active.data:
     if t.image:
        img = t.image.name
    return img

def shapeExport(model,scale=1):
        scene = context.scene
        shape=ET.Element('shape')
        texture=ET.SubElement(shape,'texture')
        name=ET.SubElement(shape,'name')
        geom=ET.SubElement(shape,'geom')
        name.text=model.data.name
        texture.text=determineTexture(model)
        for f in model.data.polygons:
            face=ET.SubElement(geom,'face')
            for idx in f.vertices:
                vertex=ET.SubElement(face,'vertex')
                x=ET.SubElement(vertex,'x')
                y=ET.SubElement(vertex,'y')
                z=ET.SubElement(vertex,'z')
                u=ET.SubElement(vertex,'u')
                v=ET.SubElement(vertex,'v')
                x.text=str(model.data.vertices[idx].co[0]*scale)
                y.text=str(model.data.vertices[idx].co[1]*scale)
                z.text=str(model.data.vertices[idx].co[2]*scale)
            for j,ul in enumerate(model.data.uv_layers):
                u.text=str(ul.data[idx].uv[0])
                v.text=str(ul.data[idx].uv[1])
        return shape