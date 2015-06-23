import math
from World import Coords

class TestManipulator(manipulatorClass):
    def __init__(self):
        self.cc=0

    def onMouseMove(self, deltax, deltay):
        self.world.observer.rotate(deltay, deltax, 0)

    def onSelfLoad(self):
        #self.world.observer.acceleration.translation.y=9
        pass


    def onKeyUp(self, states):
        self.world.observer.velocity.reset()

    def onKeyDown(self, states):
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

    def onLevelCollision(self,entity,room, collision_info):
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
