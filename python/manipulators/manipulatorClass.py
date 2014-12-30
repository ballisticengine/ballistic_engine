class manipulatorClass(object):

    def onInit(self,world):
        print "init"
        self.world=world
        for m in self.world.active_room.models:
            if m.name=="Table1" or m.name=="Table2":
                m.velocity.t.x=-1
                m.velocity.t.y=-1
                m.velocity.t.z=-1


                print "Table velocided"

    def onEntityMovement(self,entity):
        pass

    def onEntityCollision(self,entitya,entityb,cvec):
        print entitya.name,"collided",entityb.name,"vector",cvec
        #cvec.write()

    def onLevelCollision(self,entity,room):
        print "world collision",entity.name,room.name


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
