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
        print entitya.name,"to",entityb.name
        entityb.velocity.t.x=-entitya.velocity.t.x
        entityb.velocity.t.y=-entitya.velocity.t.y
        entityb.velocity.t.z=-entitya.velocity.t.z
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
