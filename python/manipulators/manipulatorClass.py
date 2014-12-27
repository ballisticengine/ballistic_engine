class ManipulatorClass(object):

    def onInit(self,world):
        print "init"
        self.world=world
        for m in self.world.active_room.models:
            if m.name=="Table1":
                #m.velocity.t.x=10

                print "Table velocided"

    def onEntityMovement(self,entity):
        pass

    def onEntityCollision(self,entitya,entityb,cvec):
        pass
        #cvec.write()

    def onLevelCollision(self,entity,room):
        print "world collision"


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
