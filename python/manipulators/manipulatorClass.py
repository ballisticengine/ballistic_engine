class ManipulatorClass(object):

    def onInit(self,world):
        print "init"
        self.world=world

    def onEntityMovement(self,entity):
        pass

    def onEntityCollision(self,entitya,entityb,cvec):
        # print "Entity collision",entitya,entityb
        velA=entitya.getVelocity()
        velA.t.write()
        #cvec.write()

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
