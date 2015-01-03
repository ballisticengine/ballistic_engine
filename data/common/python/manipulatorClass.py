class manipulatorClass(object):


    def onInit(self,world,hud):
        print "init"
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


    def onKeyDown(self):
        pass

    def onMouseMove(self):
        pass

    def onMouseClick(self):
        pass
