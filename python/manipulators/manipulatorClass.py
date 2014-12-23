class ManipulatorClass(object):

    def onInit(self,world):
        print "init"
        self.world=world

    def onEntityCollision(self,entity,data):
        pass

    def onLevelCollision(self,entity,data):
        print "Collision"


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
