#include "world/generator/generator.h"

namespace Teamup {
    namespace World {
        namespace Generator {
            Heightmap generateHeightmap(const GeneratorSettings& settings) {
                Heightmap heightmap(settings.width, settings.height);

                for (int w = 0; w < settings.width; ++w) {
                    for (int h = 0; h < settings.height; ++h) {
                        heightmap.set(w, h, w);
                    }
                }

                return std::move(heightmap);
            }
        }
    }
}

