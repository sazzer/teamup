#include "world/generator/generator.h"
#include <easylogging++.h>
#include <list>
#include <random>

namespace Teamup {
    namespace World {
        namespace Generator {

            /**
             * Generate the noise value to use for the given X and Y co-ordinate
             * @param x The X-Ordinate
             * @param y The Y-Ordinate
             * @return the noise value
             */
            double generateNoise(const double x, const double y) {
                return 0;
            }

            /**
             * Generate a noise map that will be used to produce the heightmap
             * @param width The width of the noise map
             * @param height The height of the noise map
             * @param octaves The number of octaves to use to produce the noise map
             * @param roughness An indication of how rough the noise map should be
             * @param scale An indication of the scale of the noise map
             * @return the noise map
             */
            std::vector<std::vector<double>> generateNoiseMap(const unsigned int width, const unsigned int height, const unsigned int octaves, const double roughness, const double scale) {
                std::vector<std::vector<double>> noiseMap;
                noiseMap.resize(width);
                for (unsigned int w = 0; w < width; ++w) {
                    noiseMap[w].resize(height, 0.0);
                }

                double layerFrequency = scale;
                double layerWeight = 1;
                double weightSum = 0;

                for (unsigned int octave = 0; octave < octaves; ++octave) {
                    LOG(DEBUG) << "Starting octave " << octave + 1 << " of " << octaves;
                    VLOG(1) << "Layer Frequency: " << layerFrequency;
                    VLOG(1) << "Layer Weight: " << layerWeight;
                    VLOG(1) << "Weight Sum: " << weightSum;
                    for (unsigned int x = 0; x < width; ++x) {
                        for (unsigned int y = 0; y < height; ++y) {
                            double current = noiseMap[x][y];
                            double next = generateNoise(x * layerFrequency, y * layerFrequency) * layerWeight;
                            VLOG(2) << "Current: " << current << ", Next: " << next << ", New: " << current + next;
                            noiseMap[x][y] = current + next;
                        }
                    }

                    layerFrequency *= 2;
                    weightSum += layerWeight;
                    layerWeight *= roughness;
                }

                return std::move(noiseMap);
            }

            Heightmap generateHeightmap(const GeneratorSettings& settings) {
                Heightmap heightmap(settings.width, settings.height);
                auto noiseMap = generateNoiseMap(settings.width, settings.height, 3, 0.4, 0.005);
                return std::move(heightmap);
            }
        }
    }
}
