#include "world/generator/generator.h"
#include <easylogging++.h>
#include <vector>
#include <random>
#include <limits>
#include "noise/perlin.h"

namespace Teamup {
    namespace World {
        namespace Generator {
            /**
             * Generate a noise map that will be used to produce the heightmap
             * @param width The width of the noise map
             * @param height The height of the noise map
             * @param scale An indication of the scale of the noise map
             * @return the noise map
             */
            std::vector<std::vector<double>> generateNoiseMap(const unsigned int width, 
                    const unsigned int height, 
                    const double scale) {
                std::vector<std::vector<double>> noiseMap;
                noiseMap.resize(width);
                for (unsigned int w = 0; w < width; ++w) {
                    noiseMap[w].resize(height, 0.0);
                }

                Noise::Perlin noise;

                double frequency = scale;
                for (unsigned int x = 0; x < width; ++x) {
                    for (unsigned int y = 0; y < height; ++y) {
                        double next = noise((x * frequency) / width, (y * frequency) / height);
                        noiseMap[x][y] = next;
                    }
                }

                return std::move(noiseMap);
            }

            Heightmap generateHeightmap(const GeneratorSettings& settings) {
                Heightmap heightmap(settings.width, settings.height);
                auto noiseMap = generateNoiseMap(settings.width, settings.height, 5);
                
                for (unsigned int x = 0; x < settings.width; ++x) {
                    for (unsigned int y = 0; y < settings.height; ++y) {
                        const double noiseValue = noiseMap[x][y];
                        const short value = std::numeric_limits<short>::max() * noiseValue;
                        VLOG(8) << "(" << x << ", " << y << ") = [Noise: " << noiseValue << ", Value: " << value << "]";
                        heightmap.set(x, y, value);
                    }
                }

                return std::move(heightmap);
            }
        }
    }
}
