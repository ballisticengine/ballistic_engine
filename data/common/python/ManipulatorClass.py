import rocket
from World import World, WorldManager
from Rendering import RenderingManager
from Engine import EngineState
from BallisticUI import UI

def deg2rad(deg):
    f = 3.141/180
    rad = deg*f
    return rad


def rad2deg(rad):
    deg = 180 * rad / 3.141
    return deg


def state_number(states):
    i = 0
    for s in states:
        if s:
            return i
        i += 1
    return -1


class ManipulatorClass(object):

    score=0

    #Those 4 temporary
    def player_forward(self):
        pass

    def player_backward(self):
        pass

    def player_left(self):
        pass

    def player_right(self):
        pass

    def __init__(self):
        self.world = WorldManager.get_instance().get_current_world()
        self.world_manager = WorldManager.get_instance()
        self.rendering_manager = RenderingManager.get_instance()
        self.engine_state = EngineState.get_instance()
        self.ui = UI.get_instance()

    def entity_movement(self, entity):
        pass

    def entity_collision(self, entitya, entityb, collision_info):
       pass

    def level_collision(self,entity,room, collision_info):
       pass

    def self_load(self):
        pass

    def engine_load(self):
        pass

    def entity_loop(self,entity):
        pass

    def test_sig(self):
        pass

    """
    Rozwiazac jakos kilka klawiszy na raz. np argument cycles liczacy czy to ten sam cykl io
    """

    def mouse_move(self,deltax, deltay):
        pass


    def key_down(self,key):
        pass

    def key_up(self, key):
        pass

    def key_press(self, key):
        pass

    def mouse_click(self,button):
        pass
