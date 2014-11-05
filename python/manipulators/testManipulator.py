#import ManipulatorClass
import ctypes

class testManipulator(ManipulatorClass):
    def onSelfLoad(self):
        print "test manipulator self load signal"