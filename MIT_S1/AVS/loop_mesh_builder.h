/**
 * @file    loop_mesh_builder.h
 *
 * @author  Alexej Beňuš <xbenus01@stud.fit.vutbr.cz>
 *
 * @brief   Parallel Marching Cubes implementation using OpenMP loops
 *
 * @date    03.12.2024
 **/

#ifndef LOOP_MESH_BUILDER_H
#define LOOP_MESH_BUILDER_H

#include "base_mesh_builder.h"
#include <vector>

class LoopMeshBuilder : public BaseMeshBuilder
{
    public:
        LoopMeshBuilder(unsigned gridEdgeSize);

    protected:
        unsigned marchCubes(const ParametricScalarField &field);
        float evaluateFieldAt(const Vec3_t<float> &pos,
                              const ParametricScalarField &field);
        void emitTriangle(const Triangle_t &triangle);
        const Triangle_t *getTrianglesArray() const
        {
            return _triangles.data();
        }

    private:
        std::vector<Triangle_t> _triangles;
};

#endif // LOOP_MESH_BUILDER_H
