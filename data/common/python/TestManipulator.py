import math
from EngineTypes import Vector3d, Coords
# import rocket #zakomentowane nie wydupia
import os



class TestManipulator(ManipulatorClass):
    def __init__(self):
        super(TestManipulator, self).__init__()
        self.cc = 0
        self.mx = 0
        self.my = 0
        self.up = False
        self.uc = 0
        self.attach_mouse()
        
    def attach_mouse(self):
        self.engine_state.set_bool('attach_mouse', not self.engine_state.get_bool('attach_mouse'))

    def player_forward(self):
        self.move_player('f')

    def player_backward(self):
        self.move_player('b')

    def player_left(self):
        self.move_player('l')

    def player_right(self):
        self.move_player('r')

    def prinntest(self):
        print "test"

    def self_load(self):
        print "Contexts"
        self.ui.add_document("test.rml","test")
        
        self.ui.set_content_by_id("dummy", "xxx")
        self.ui.add_event_listener_id("clickme","click", "jajko")
        self.ui.show_doc("test")
        #print element
    
    def key_up(self, states):
        #TODO: KEYUP doesn't send upped key - fix
        self.uc += 1
        self.world.observer.velocity.reset()

    def key_press(self, key):

        if key == 1073741893: #F12
            self.engine_state.toggle_bool('edit_mode')
            print self.engine_state.get_bool('edit_mode')

        if key == 1073741892: #F11
            self.world.save_xml("test.xml")

        if key == 27:
            self.engine_state.set_bool('exit', True)
            print "EXIT"

    def key_down(self, states):
        return

    def move_player(self, dir):
        ocoords = self.world.observer.get_coords()
        step=5
        xdelta = deg2rad(ocoords.rotation.y)
        ydelta = deg2rad(ocoords.rotation.x)

        velocity = Coords()

        if dir == 'f':
            self.world.observer.velocity.t.x += -math.sin(xdelta)*step
            self.world.observer.velocity.t.z += math.cos(xdelta)*step
            self.world.observer.velocity.t.y += math.sin(ydelta)*step
        if dir == 'b':
            self.world.observer.velocity.t.x += math.sin(xdelta)*step
            self.world.observer.velocity.t.z += -math.cos(xdelta)*step
        if dir == 'l':
            self.world.observer.velocity.t.x += math.cos(xdelta)*step
            self.world.observer.velocity.t.z += math.sin(xdelta)*step
        if dir == 'r':
            self.world.observer.velocity.t.x += -math.cos(xdelta)*step
            self.world.observer.velocity.t.z += -math.sin(xdelta)*step




    def entity_collision(self,entitya,entityb, collision_info):
        print entitya.name, entityb.name


    def mouse_click(self, button):
        #print "Click"
        physics = self.world.get_physics()
        c = self.world.observer.get_coords()
        renderer = self.rendering_manager.get_renderer()
        #x = renderer.unproject(10, 10)


    def mouse_move(self, deltax, deltay):
        if not self.engine_state.get_bool('attach_mouse'):
            return
        self.world.observer.rotate(deltay, deltax, 0)
        self.mx = deltax
        self.my = deltay

    def level_collision(self,entity,room, collision_info):

        return
        diff=collision_info.A.diff
        #print collision_info.A.name, diff.write(),self.cc

        #if not diff.x and not diff.y and not diff.z:
            #print 'ret'
        #    return

        if collision_info.distance>-0.2:
            return
        #diff.write()
        c=entity.velocity
        #c.reset()
        t=entity.getCoords()
        margin=2
        if diff.x!=0:
           c.translation.x=0
        if diff.y!=0:

           c.translation.y=0
        if diff.z!=0:

            c.translation.z=0

        entity.translate3(diff.x*margin, diff.y*margin, diff.z*margin)
        #entity.setVelocity(c)

        self.cc+=1
