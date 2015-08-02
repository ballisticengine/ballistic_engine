import math
from World import Coords

class TestManipulator(manipulatorClass):
    def __init__(self):
        self.cc = 0
        self.mx = 0
        self.my = 0
        self.up = False


    def onSelfLoad(self):
        #self.world.observer.acceleration.translation.y=9
        pass


    def onKeyUp(self, states):
        #TODO: KEYUP doesn't send upped key - fix
        self.world.observer.velocity.reset()
        #print 'Up', state_number(states)

    def onKeyPress(self, key):

        if key == 1073741893: #F12
            self.engine_state.toggleBool('edit_mode')
            print self.engine_state.getBool('edit_mode')

        if key == 1073741892: #F11
            self.world.saveXml("test.xml")

        if key == 27:
            self.engine_state.setBool('exit', True)
            print "EXIT"

    def onKeyDown(self, states):
        #print 'Down', state_number(states)
        ocoords = self.world.observer.getCoords()
        step=5
        xdelta = deg2rad(ocoords.rotation.y)
        ydelta = deg2rad(ocoords.rotation.x)

        velocity=Coords()

        if states[26]:
            velocity.t.x += -math.sin(xdelta)*step
            velocity.t.z += math.cos(xdelta)*step
            velocity.t.y += math.sin(ydelta)*step
        if states[22]:
            velocity.t.x +=math.sin(xdelta)*step
            velocity.t.z +=-math.cos(xdelta)*step
        if states[4]:
            velocity.t.x+=math.cos(xdelta)*step
            velocity.t.z+=math.sin(xdelta)*step
        if states[7]:
            velocity.t.x+=-math.cos(xdelta)*step
            velocity.t.z+=-math.sin(xdelta)*step

        self.world.observer.velocity=velocity


    def onEntityCollision(self,entitya,entityb, collision_info):
        print entitya.name, entityb.name


    def onMouseClick(self, button):
        #print "Click"
        physics = self.world.get_physics()
        c = self.world.observer.getCoords()
        renderer = self.rendering_manager.get_renderer()
        


    def onMouseMove(self, deltax, deltay):
        self.world.observer.rotate(deltay, deltax, 0)
        self.mx = deltax
        self.my = deltay

    def onLevelCollision(self,entity,room, collision_info):

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
