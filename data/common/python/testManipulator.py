
class testManipulator(manipulatorClass):

    def __init__(self):
        self.ccount=0
        self.wccount=0

    """"""



    def onEntityMovement(self,entity):
        #print entity.name,"is moving"
        pass

    def onEntityCollision(self,entitya,entityb,cvec):
        self.ccount+=1
        print entitya.name,"collided",entityb.name,"vector",cvec,"Counter:",self.ccount
        #entityb.velocity.t.x=-entitya.velocity.t.x
        #entityb.velocity.t.y=-entitya.velocity.t.y
        #entityb.velocity.t.z=-entitya.velocity.t.z
        if entitya.type=="observer":
            cvec.write()
            entitya.translate3(cvec.z,-cvec.y,cvec.x)

        #cvec.write()

    def onLevelCollision(self,entity,room,cvec):
        #print "world collision",entity.name,room.name,"Type",entity.type,"Counter:",self.wccount
        #cvec.write()
        self.wccount+=1
        if entity.type=="object":
            #return
            #entity.velocity.t.x=-entity.velocity.t.x
            #entity.velocity.t.y=-entity.velocity.t.y
            #entity.velocity.t.z=-entity.velocity.t.z

            if cvec.y!=0:
                #entity.translate3(0,-cvec.y*100000,0)
                pass
            else:
                entity.translate3(-cvec.z*100,0,-cvec.x*100)
        elif entity.type=="observer":

            entity.translate3(cvec.z,cvec.y,cvec.x)





    def onSelfLoad(self):
        objects=self.world.active_room.models
        for o in objects:
            if not o.no_physics:
                o.acceleration.t.y=-9.2


        #uiHelperTest()


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


    def onMovementKey(self,type):
        print type

