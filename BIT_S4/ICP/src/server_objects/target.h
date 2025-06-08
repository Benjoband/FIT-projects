/**
 * @file target.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for target object
 * @version 1.0
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef TARGET_H
#define TARGET_H

#include "object.h"

namespace server {
    /**
     * @brief Target object, for initialization of end tile.
     * 
     */
    class Target : public Object {
    public:
        // Constructors
        Target();
        Target(int x, int y);

        // Inherited methods
        void worldTick() override;
        std::string toString() const override;
        char mapRepresentation() const override;
        int 	    collision(std::vector<std::shared_ptr<server::Object>> objects) override;
    };
}

#endif // TARGET_H