#include "misc/xmlHelper.hpp"

ptree makeTranslationNode(Coords c) {
    return makeLocationNode(c.translation.x, c.translation.y, c.translation.z);
}

ptree makeRotationNode(Coords c) {
    return makeLocationNode(c.rotation.x, c.rotation.y, c.rotation.z);
}

ptree makeLocationNode(scalar_t x, scalar_t y, scalar_t z) {
    ptree location, lx, ly, lz;

    lx.put("", x);
    ly.put("", y);
    lz.put("", z);
    location.add_child("x", lx);
    location.add_child("y", ly);
    location.add_child("z", lz);
    return location;
}

ptree makeRGBANode(scalar_t r, scalar_t g, scalar_t b, scalar_t a) {
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

ptree makeUVNode(scalar_t u, scalar_t v) {
    ptree uv, lu, lv;
    lu.put("", u);
    lv.put("", v);
    uv.add_child("u", lu);
    uv.add_child("v", lv);
    return uv;
}

ptree makeCoordsNode(Coords c) {
    ptree location, lx, ly, lz, rx, ry, rz;

    lx.put("", c.translation.x);
    ly.put("", c.translation.y);
    lz.put("", c.translation.z);
    rx.put("", c.rotation.x);
    ry.put("", c.rotation.y);
    rz.put("", c.rotation.z);
    location.add_child("x", lx);
    location.add_child("y", ly);
    location.add_child("z", lz);
    location.add_child("rx", lx);
    location.add_child("ry", ly);
    location.add_child("rz", lz);
    return location;
}