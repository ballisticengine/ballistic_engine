#include "misc/xmlHelper.hpp"

ptree makeTranslationNode(Coords c) {
    return makeLocationNode(c.translation.x, c.translation.y, c.translation.z);
}

ptree makeRotationNode(Coords c) {
    return makeLocationNode(c.rotation.x, c.rotation.y, c.rotation.z);
}

ptree makeLocationNode(e_loc x, e_loc y, e_loc z) {
    ptree location, lx, ly, lz;

    lx.put("", x);
    ly.put("", y);
    lz.put("", z);
    location.add_child("x", lx);
    location.add_child("y", ly);
    location.add_child("z", lz);
    return location;
}

ptree makeRGBANode(e_loc r, e_loc g, e_loc b, e_loc a) {
    ptree color, lr, lg, lb, la;
    lr.put("", r);
    lg.put("", g);
    lb.put("", b);
    la.put("", a);
    color.add_child("r", lr);
    color.add_child("g", lg);
    color.add_child("b", lb);
    color.add_child("a", la);
    return color;
}

ptree makeRGBANode(ColorRGBA c) {
    return makeRGBANode(c.r, c.g, c.b, c.a);
}

ptree makeUVNode(e_loc u, e_loc v) {
    ptree uv, lu, lv;
    lu.put("", u);
    lv.put("", v);
    uv.add_child("u", lu);
    uv.add_child("v", lv);
    return uv;
}

