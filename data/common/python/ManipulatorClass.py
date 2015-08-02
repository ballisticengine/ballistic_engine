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


    def init(self, world, hud, engine_state, rendering_manager):
        self.world = world
        self.hud = hud
        self.engine_state = engine_state
        self.rendering_manager = rendering_manager


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
