/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <Corrade/TestSuite/Tester.h>

#include "Magnum/Mesh.h"
#include "Magnum/Math/Vector3.h"
#include "Magnum/Primitives/Plane.h"
#include "Magnum/Trade/MeshData3D.h"

namespace Magnum { namespace Primitives { namespace Test { namespace {

struct PlaneTest: TestSuite::Tester {
    explicit PlaneTest();

    void solid();
    void solidTextured();
    void wireframe();
};

PlaneTest::PlaneTest() {
    addTests({&PlaneTest::solid,
              &PlaneTest::solidTextured,
              &PlaneTest::wireframe});
}

void PlaneTest::solid() {
    Trade::MeshData3D plane = Primitives::planeSolid();

    CORRADE_VERIFY(!plane.isIndexed());
    CORRADE_COMPARE(plane.primitive(), MeshPrimitive::TriangleStrip);
    CORRADE_COMPARE(plane.positions(0).size(), 4);
    CORRADE_COMPARE(plane.normals(0).size(), 4);
    CORRADE_COMPARE(plane.textureCoords2DArrayCount(), 0);
}

void PlaneTest::solidTextured() {
    Trade::MeshData3D plane = Primitives::planeSolid(Primitives::PlaneTextureCoords::Generate);

    CORRADE_VERIFY(!plane.isIndexed());
    CORRADE_COMPARE(plane.primitive(), MeshPrimitive::TriangleStrip);
    CORRADE_COMPARE(plane.positions(0).size(), 4);
    CORRADE_COMPARE(plane.normals(0).size(), 4);
    CORRADE_COMPARE(plane.textureCoords2DArrayCount(), 1);
    CORRADE_COMPARE(plane.textureCoords2D(0).size(), 4);
}

void PlaneTest::wireframe() {
    Trade::MeshData3D plane = Primitives::planeWireframe();

    CORRADE_VERIFY(!plane.isIndexed());
    CORRADE_COMPARE(plane.primitive(), MeshPrimitive::LineLoop);
    CORRADE_COMPARE(plane.positions(0).size(), 4);
}

}}}}

CORRADE_TEST_MAIN(Magnum::Primitives::Test::PlaneTest)
