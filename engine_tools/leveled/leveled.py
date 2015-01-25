import gtk
import gtk.glade

class Leveled(object):

    def __init__(self):
       self.builder = gtk.Builder()
       self.builder.add_from_file("ui.glade")
       self.window = self.builder.get_object("MainWindow")
       self.window.show_all()
       gtk.main()




app=Leveled()
