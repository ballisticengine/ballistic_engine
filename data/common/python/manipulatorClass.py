class manipulatorClass(object):

    score=0


    def onInit(self,world,hud):
        self.world=world
        self.hud=hud


    def onEntityMovement(self,entity):
        pass

    def onEntityCollision(self,entitya,entityb,cvec):
       pass

    def onLevelCollision(self,entity,room,cvec):
       pass


    def onSelfLoad(self):
        pass

    def onEngineLoad(self):
        pass

    def onEntityLoop(self,entity):
        pass


    """
    Rozwiazac jakos kilka klawiszy na raz. np argument cycles liczacy czy to ten sam cykl io
    """
    def onMovementKey(self):
        pass


    def onObserverStateChange(self,state):
        pass

    def onMouseMove(self):
        pass

    def onMouseClick(self,button):
        pass
