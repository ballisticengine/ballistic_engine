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

import export_helper as exp


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
        exp.shapeExport(context.active_object,1.0)
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