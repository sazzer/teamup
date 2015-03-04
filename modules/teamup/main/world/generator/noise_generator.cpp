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
             * @param octaves The number of octages to use
             * @param frequency An indication of the frequency of the noise map
             * @return the noise map
             */
            std::vector<std::vector<double>> generateNoiseMap(const unsigned int width, 
                    const unsigned int height, 
                    const unsigned int octaves,
                    const double frequency,
                    const double amplitudeScale) {
                std::vector<std::vector<double>> noiseMap;
                noiseMap.resize(width);
                for (unsigned int w = 0; w < width; ++w) {
                    noiseMap[w].resize(height, 0.0);
                }

                Noise::Perlin noise;

                double scale = 1/frequency;
                double amplitude = 1;
                double scaleFactor = 0;

                for (unsigned int o = 0; o < octaves; ++o) {
                    LOG(DEBUG) << "Starting octave " << (o + 1);
                    VLOG(1) << "Scale: " << scale;
                    VLOG(1) << "Amplitude: " << amplitude;
                    for (unsigned int x = 0; x < width; ++x) {
                        for (unsigned int y = 0; y < height; ++y) {
                            double current = noiseMap[x][y];
                            double next = noise(x / (scale * width), y / (scale * height));
                            noiseMap[x][y] = current + (next * 1);
                        }
                    }

                    scaleFactor+= 1;
                    scale *= 2;
                    amplitude *= amplitudeScale;
                }
                VLOG(1) << "Scale Factor: " << scaleFactor;


                // Now scale all of the values to [-1, 1]
                for (unsigned int x = 0; x < width; ++x) {
                    for (unsigned int y = 0; y < height; ++y) {
                        noiseMap[x][y] /= scaleFactor;
                    }
                }
                return std::move(noiseMap);
            }

            Heightmap generateHeightmap(const GeneratorSettings& settings) {
                Heightmap heightmap(settings.width, settings.height);
                auto noiseMap = generateNoiseMap(settings.width, settings.height, 4, 2, 0.75);
                
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
