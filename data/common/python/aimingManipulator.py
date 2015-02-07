class aimingManipulator(manipulatorClass):
    def onEntityCollision(self,entitya,entityb,ci):
        if entitya.subtype=="bullet" and "target" in entityb.name:
            score=int(entitya.name.replace("[BOUNDING]",""))
            manipulatorClass.score+=score

            print "ambullet",entityb.name