"""
<level>
<rooms>
 <room>
  <geom>
   <face>
   <vertex>
    <x></x>
    <y></y>
    <z></z>
    <u></u>
    <v></v>
   </vertex>
   </face>
  </geom>
 </room>
</rooms>
</level>
"""

import bpy
from bpy import context
import xml.etree.ElementTree as ET


bpy.ops.object.mode_set(mode='OBJECT')

scene = context.scene

objects=scene.objects
active=context.active_object

"""
for o in objects:
    print (o)
"""
root=ET.Element('level')
rooms=ET.SubElement(root,'rooms')
room=ET.SubElement(rooms,'room')
texture=ET.SubElement(room,'texture')
name=ET.SubElement(room,'name')
geom=ET.SubElement(room,'geom')

name.text=active.data.name

for t in active.data.uv_textures.active.data:
   if t.image:
        img = t.image.name

texture.text=img

for f in active.data.polygons:
    face=ET.SubElement(geom,'face')
    for idx in f.vertices:
        vertex=ET.SubElement(face,'vertex')
        x=ET.SubElement(vertex,'x')
        y=ET.SubElement(vertex,'y')
        z=ET.SubElement(vertex,'z')
        u=ET.SubElement(vertex,'u')
        v=ET.SubElement(vertex,'v')
        x.text=str(active.data.vertices[idx].co[0])
        y.text=str(active.data.vertices[idx].co[1])
        z.text=str(active.data.vertices[idx].co[2])
        for j,ul in enumerate(active.data.uv_layers):
            u.text=str(ul.data[idx].uv[0])
            v.text=str(ul.data[idx].uv[1])

ET.dump(root)