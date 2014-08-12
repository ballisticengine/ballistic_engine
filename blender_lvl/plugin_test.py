import bpy
from bpy import context



scene = context.scene

objects=scene.objects

for o in objects:
    print (o)