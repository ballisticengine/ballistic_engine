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

import export_helper


class ExportXML(bpy.types.Operator):
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
        pass
