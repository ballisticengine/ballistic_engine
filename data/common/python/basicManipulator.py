import math

def deg2rad(deg):
    f=3.141/180
    rad=deg*f
    return rad

def rad2deg(rad):
    deg = 180 * rad / 3.141
    return deg

class basicManipulator(manipulatorClass):

    def __init__(self):
        self.ccount=0
        self.wccount=0
        self.kcount=0
        self.spawnc=0
        self.nc=0
        self.pc=0


    """"""



    def onEntityMovement(self,entity):

        #print entity.name,"is moving",entity.weight
        if entity.type=="observer":
            entity.bobHead()
        else:
            return
            if entity.velocity.t.x!=0:
                entity.velocity.t.x/=entity.weight
            #if entity.velocity.t.y!=0:
            #    entity.velocity.t.y/=entity.weight
            if entity.velocity.t.z!=0:
                entity.velocity.t.z/=entity.weight



    def onEntityCollision(self,entitya,entityb,cvec):
        self.ccount+=1
        #print entitya.name,"collided",entityb.name,"vector",cvec,"Counter:",self.ccount

        if entitya.type!="observer":
            entitya.velocity.t.x=-entitya.velocity.t.x
            entitya.velocity.t.y=-entitya.velocity.t.y
            entitya.velocity.t.z=-entitya.velocity.t.z
            #entityb.velocity.t.x=-entityb.velocity.t.x
            #entityb.velocity.t.y=-entityb.velocity.t.y
            #entityb.velocity.t.z=-entityb.velocity.t.z
            entitya.translate3(-cvec.z,-cvec.y,-cvec.x)
        if entitya.type=="observer":
            #cvec.write()
            #entityb.velocity.t.x=-entitya.velocity.t.x
            #entityb.velocity.t.y=-entitya.velocity.t.y
            entityb.velocity.t.z=-entitya.velocity.t.z
            #entitya.translate3(cvec.z,-cvec.y,cvec.x)

        #cvec.write()

    def onLevelCollision(self,entity,room,cvec):
        #print "world collision",entity.name,room.name,"Type",entity.type,"Counter:",self.wccount
        #cvec.write()
        self.wccount+=1
        if entity.type=="object":
            if entity.subtype=="bullet":
                c=entity.getCoords()
                cvec.write()

                c.rotation.y=-90+c.rotation.y;

                if not cvec.y:
                    self.world.active_room.placePreloadDecal("decal",c)
                entity.velocity.x=entity.velocity.y=entity.velocity.z=0
                entity.no_collisions=True
            else:
                if cvec.y:
                    entity.velocity.t.y=0
                    entity.acceleration.t.y=0

                if cvec.x:
                 entity.velocity.t.x=-entity.velocity.t.x
                 entity.acceleration.t.x=0

                if cvec.z:
                    entity.velocity.t.z=-entity.velocity.t.z
                    entity.acceleration.t.z=0

            entity.translate3(-cvec.x*1000,-cvec.y,-cvec.z*1000)
            #entity.velocity.t.z=-oldz
        elif entity.type=="observer":
            entity.acceleration.t.y=0
            #if cvec.y:
            entity.velocity.t.y=0
            entity.translate3(cvec.x,-cvec.y,cvec.z)




    def showHudInfo(self):
        self.hud.getImage("weapon").setText(self.world.observer.current_weapon.display_name)

    def onSelfLoad(self):
        self.showHudInfo()
        objects=self.world.active_room.models
        observer=self.world.observer
        self.oldrotx=self.world.observer.getCoords().rotation.x
        observer.acceleration.t.y=9.2
        print observer
        for o in objects:
            if not o.no_physics:
                o.acceleration.t.y=-9.2
                pass
            if o.type=="object":
                o.weight=100
            if o.type=="observer":
                o.weight=80
                #o.face()


        #uiHelperTest()




    def onObserverStateChange(self,state):
        #print self.kcount,state.movement.up,state.movement.down,state.movement.left,state.movement.right,state.movement.forward,state.movement.back
        #print state.mouse.left ,state.mouse.right,state.mouse.middle,state.mouse.leftclick
        self.kcount+=1
        self.world.observer.velocity.reset()
        ocoords=self.world.observer.getCoords()
        from world import coords

        step=5
        xdelta=deg2rad(ocoords.rotation.y)
        ydelta=deg2rad(ocoords.rotation.x)

        ocoords.translation.x-=math.sin(xdelta)*50
        ocoords.translation.z+=math.cos(xdelta)*50

        if state.mouse.left:
                self.showHudInfo()
                x=self.world.active_room.spawnObject("bullet",ocoords,str(self.spawnc))
                x.translate3(0,10,0)
                x.subtype="bullet"
                #x.acceleration.t.y=-9.2
                xt=math.sin(xdelta)
                yt=-math.cos(xdelta)
                zt=-math.sin(ydelta)
                vel=self.world.observer.current_weapon.initial_velocity
                x.velocity.t.x=vel*xt
                x.velocity.t.z=vel*yt
                x.velocity.t.y=vel*zt
                ocoords.rotation.write()
                x.face(0,90-ocoords.rotation.y,-ocoords.rotation.x)
                x.weight=1.2
                self.spawnc+=1

        if state.movement.prev_weapon:
            self.pc+=1
            state.movement.prev_weapon=False
            print "Prev weapon",self.pc
            if self.world.observer.current_weapon.prev:
                self.world.observer.current_weapon=self.world.observer.current_weapon.prev

        if state.movement.next_weapon:
            self.nc+=1
            print "Next weapon",self.nc
            state.movement.next_weapon=False
            if self.world.observer.current_weapon.next:
                self.world.observer.current_weapon=self.world.observer.current_weapon.next


        if state.movement.forward:
            self.world.observer.velocity.t.x+=-math.sin(xdelta)*step
            self.world.observer.velocity.t.z+=math.cos(xdelta)*step

        if state.movement.back:
            self.world.observer.velocity.t.x+=math.sin(xdelta)*step
            self.world.observer.velocity.t.z+=-math.cos(xdelta)*step

        if state.movement.left:
            self.world.observer.velocity.t.x+=math.cos(xdelta)*step
            self.world.observer.velocity.t.z+=math.sin(xdelta)*step

        if state.movement.right:
            self.world.observer.velocity.t.x+=-math.cos(xdelta)*step
            self.world.observer.velocity.t.z+=-math.sin(xdelta)*step

        if state.movement.up:
            self.world.observer.velocity.t.y+=-step

        if state.movement.down:
            self.world.observer.velocity.t.y+=step