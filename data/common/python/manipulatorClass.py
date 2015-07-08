def deg2rad(deg):
    f=3.141/180
    rad=deg*f
    return rad

def rad2deg(rad):
    deg = 180 * rad / 3.141
    return deg

class manipulatorClass(object):

    score=0


    def onInit(self, world, hud, engine_state):
        self.world = world
        self.hud = hud
        self.engine_state = engine_state


    def onEntityMovement(self, entity):
        pass

    def onEntityCollision(self,entitya,entityb, collision_info):
       pass

    def onLevelCollision(self,entity,room, collision_info):
       pass


    def onSelfLoad(self):
        pass

    def onEngineLoad(self):
        pass

    def onEntityLoop(self,entity):
        pass

    def onTestSig(self):
        pass

    """
    Rozwiazac jakos kilka klawiszy na raz. np argument cycles liczacy czy to ten sam cykl io
    """
    def onMovementKey(self):
        pass


    def onMouseMove(self,deltax, deltay):
        pass


    def onKeyDown(self,key):
        pass

    def onKeyUp(self,key):
        pass

    def onMouseClick(self,button):
        pass
