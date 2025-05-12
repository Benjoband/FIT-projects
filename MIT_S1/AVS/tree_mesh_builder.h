/**
 * @file    tree_mesh_builder.h
 *
 * @author  Alexej Beňuš <xbenus01@stud.fit.vutbr.cz>
 *
 * @brief   Parallel Marching Cubes implementation using OpenMP tasks + octree
 *early elimination
 *
 * @date    03.12.2024
 **/

#ifndef TREE_MESH_BUILDER_H
#define TREE_MESH_BUILDER_H

#include "base_mesh_builder.h"
#include <limits>
#include <math.h>

class TreeMeshBuilder : public BaseMeshBuilder
{
    public:
        TreeMeshBuilder(unsigned gridEdgeSize);

    protected:
        unsigned marchCubes(const ParametricScalarField &field);
        float evaluateFieldAt(const Vec3_t<float> &pos,
                              const ParametricScalarField &field);
        void emitTriangle(const Triangle_t &triangle);
        unsigned processOctreeNode(const float x, const float y, const float z,
                                   float size,
                                   const ParametricScalarField &field);
        const Triangle_t *getTrianglesArray() const
        {
            return _triangles.data();
        }
        std::vector<Triangle_t> _triangles;
        static const unsigned SIZE_CUT_OFF = 1;
        static const unsigned TASK_CREATION_CUT_OFF = 4;
};

#endif // TREE_MESH_BUILDER_H
