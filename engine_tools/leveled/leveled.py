import gtk
import gtk.glade
import math

from events import Handler

class Leveled(object):

    def draw_polygon(self,points,context,x=0,y=0):

        context.move_to(x, y)
        for px,py in points:

            context.line_to(x+px, y+py)

        context.fill()
        context.move_to(x, y)
        for px,py in points:

            context.arc(x+px, y+py, 1, 0.0, 2.0 * math.pi)
            context.fill()
        return

    def expose(self, widget, event):

        cr = widget.window.cairo_create()

        cr.set_line_width(9)
        cr.set_source_rgb(0.7, 0.2, 0.0)

        w = self.window.allocation.width
        h = self.window.allocation.height


        pts1=[(0,0),(10,0),(10,10),(0,10)]
        self.draw_polygon(pts1,cr,100,100)
        #cr.stroke_preserve()

        cr.set_source_rgb(0.3, 0.4, 0.6)
        cr.fill()

    def __init__(self):
       self.builder = gtk.Builder()
       self.builder.add_from_file("ui.glade")
       self.window = self.builder.get_object("MainWindow")
       self.window.connect("destroy", gtk.main_quit)

       self.window.show_all()
       drawable=self.builder.get_object("topView")
       self.style = drawable.get_style()
       self.gc = self.style.fg_gc[gtk.STATE_NORMAL]
       self.gc.set_foreground(  gtk.gdk.Color(red=255, green=0, blue=0))
       self.gc.set_background(  gtk.gdk.Color(red=255, green=0, blue=0))
       self.gc.set_fill(gtk.gdk.SOLID)
       drawable.set_size_request(800, 600)
       drawable.show()
       drawable.connect("expose-event", self.expose)

       gtk.main()




app=Leveled()
