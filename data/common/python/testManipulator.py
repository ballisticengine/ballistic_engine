class testManipulator(object):

    def __init__(self):
        self.ccount=0
        self.wccount=0

    """"""
    def onInit(self,world):
        print "init"

        self.world=world
        for m in self.world.active_room.models:
            if m.name=="Table1" or m.name=="Table2":
                #m.velocity.t.x=-1
                #m.velocity.t.y=-1
                #m.velocity.t.z=-1


                print "Table velocided"

    def onEntityMovement(self,entity):
        pass

    def onEntityCollision(self,entitya,entityb,cvec):
        self.ccount+=1
        print entitya.name,"collided",entityb.name,"vector",cvec,"Counter:",self.ccount
        #entityb.velocity.t.x=-entitya.velocity.t.x
        #entityb.velocity.t.y=-entitya.velocity.t.y
        #entityb.velocity.t.z=-entitya.velocity.t.z
        #cvec.write()

    def onLevelCollision(self,entity,room,cvec):
        #print "world collision",entity.name,room.name,"Type",entity.type,"Counter:",self.wccount
        cvec.write()
        self.wccount+=1
        if entity.type=="object":
            entity.velocity.t.x=-entity.velocity.t.x
            entity.velocity.t.y=-entity.velocity.t.y
            entity.velocity.t.z=-entity.velocity.t.z

            if cvec.y!=0:
                entity.translate3(0,-cvec.y*100000,0)
            else:
                entity.translate3(-cvec.z*100,0,-cvec.x*100)
        elif entity.type=="observer":

            entity.translate3(cvec.z,0,cvec.x)





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

