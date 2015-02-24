#ifndef TEAMUP_WORLD_GENERATOR_GENERATOR_H
#define TEAMUP_WORLD_GENERATOR_GENERATOR_H

#include "world/generator/heightmap.h"

namespace Teamup {
    namespace World {
        namespace Generator {
            /**
             * The settings to use for the generator
             */
            struct GeneratorSettings {
                /** The width of the world */
                unsigned int width;
                /** The height of the world */
                unsigned int height;
            };

            /**
             * Generate a heightmap to use to represent the world
             * @param settings The settings to use for the generator
             * @return the heightmap to use for the world
             */
            Heightmap generateHeightmap(const GeneratorSettings& settings);
        }
    }
}

#endif // TEAMUP_WORLD_GENERATOR_GENERATOR_H
