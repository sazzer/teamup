#include "world/generator/generator.h"
#include <easylogging++.h>
#include <list>
#include <random>

/** The value to use for the borders */
static const short BORDER_VALUE = -5000;
/** The value to use for the seeds */
static const short SEED_VALUE = 5000;
/** The number of loops to run seeds for */
static const unsigned int SEED_LOOP_COUNT = 3;
namespace Teamup {
    namespace World {
        namespace Generator {

            std::random_device rd;
            std::default_random_engine e1(rd());

            /**
             * Helper to update a cell on the heightmap, only if it's not already set
             * @param heightmap The heightmap to update
             * @param record The record of what cells we've updated
             * @param x The X-Ordinate to set
             * @param y The Y-Ordinate to set
             * @param v The value to set
             */
            static void setCell(Heightmap& heightmap, std::vector<std::vector<bool>>& record, unsigned int x, unsigned int y, short v) {
                if (!record[x][y]) {
                    VLOG(3) << "Setting value for cell (" << x << ", " << y << ") to " << v;
                    heightmap.set(x, y, v);
                    record[x][y] = true;
                } else {
                    VLOG(3) << "Cell (" << x << ", " << y << ") already set";
                }
            }

            /**
             * A region in the Diamond-Square algorithm
             */
            struct Region {
                /**
                 * Construct the region
                 * @param x1_ The top left X-Ordinate
                 * @param y1_ The top left Y-Ordinate
                 * @param x2_ The bottom right X-Ordinate
                 * @param y2_ The bottom right Y-Ordinate
                 */
                Region(unsigned int x1_, unsigned int y1_, unsigned int x2_, unsigned int y2_) {
                    x1 = x1_;
                    y1 = y1_;
                    x2 = x2_;
                    y2 = y2_;
                    mx = x1 + ((x2 - x1) / 2);
                    my = y1 + ((y2 - y1) / 2);
                }

                unsigned int x1;
                unsigned int y1;
                unsigned int x2;
                unsigned int y2;
                unsigned int mx;
                unsigned int my;

                /**
                 * Divide this region into quarters and put those onto the provided list
                 * @param regions The regions list to add to
                 */
                void divide(std::list<Region>& regions) const {
                    if ((x2 - x1) > 1 && (y2 - y1) > 1) {
                        add(regions, Region(x1, y1, mx, my));
                        add(regions, Region(mx, y1, x2, my));
                        add(regions, Region(x1, my, mx, y2));
                        add(regions, Region(mx, my, x2, y2));
                    }
                }

                /**
                 * Add the given region to the given list iff the region is a non-zero area
                 * @param regions The regions list
                 * @param region The region to add
                 */
                void add(std::list<Region>& regions, Region region) const {
                    if (region.x1 != region.x2 && region.y1 != region.y2) {
                        VLOG(3) << "Adding region (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ")";
                        regions.push_back(region);
                    } else {
                        VLOG(3) << "Not adding region (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ") as area is zero";
                    }
                }
            };

            /**
             * Test if the given X and Y Co-ordinates are on the edge of the heightmak
             * @param  heightmap The heightmap
             * @param  x         The X-Ordinate
             * @param  y         The Y-Ordinate
             * @return           True if they are on the edge. False if not
             */
            bool isEdge(const Heightmap& heightmap, const unsigned int x, const unsigned int y) {
                const unsigned int maxX = heightmap.width() - 1;
                const unsigned int maxY = heightmap.height() - 1;

                return (x == 0 || x == maxX || y == 0 || y == maxY);
            }

            /**
             * Calculate the seed point change based on the distance into the heightmap a position is
             * @param heightmap the heightmap to use
             * @param x The X-Ordinate
             * @param y The Y-Ordinate
             * @return the percentage chance of placing a seed
             */
            double seedPointChance(const Heightmap& heightmap, const unsigned int x, const unsigned int y) {
                const unsigned int mx = heightmap.width() - 1;
                const unsigned int my = heightmap.height() - 1;

                const double halfWidth = mx / 2;
                const double halfHeight = my / 2;

                const double hx = (x > halfWidth) ? mx - x : x;
                const double hy = (y > halfHeight) ? my - y : y;

                double px = hx / halfWidth;
                double py = hy / halfHeight;

                return std::max(px, py);
            }

            void seed(Heightmap& heightmap, std::vector<std::vector<bool>>& record, const unsigned int x, const unsigned int y, const short value) {
                std::uniform_real_distribution<double> seedChoice(0, 1);
                const double chance = seedPointChance(heightmap, x, y);
                const double choice = seedChoice(e1);
                VLOG(1) << "Will we generate this seed? (" << x << ", " << y << ") = " << chance << " > " << choice;
                if (chance > choice) {
                    VLOG(1) << "Generating seed at (" << x << ", " << y << ")";
                    setCell(heightmap, record, x, y, value);
                }
            }

            /**
             * Update the heightmap by dividing the region
             * @param heightmap The heightmap to update
             * @param record The record of cells we've updated
             * @param region The region to subdivide
             * @param value The fixed value to use
             */
            void updateHeightmap(Heightmap& heightmap, std::vector<std::vector<bool>>& record, const Region& region, const short value) {
                VLOG(1) << "Setting fixed values for region centres (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ") to " << value;
                double heightmapArea = heightmap.width();
                double regionArea = region.x2 - region.x1;
                double areaPercentage = 2 * (regionArea / heightmapArea);

                std::uniform_real_distribution<double> dist(-0.5, 3);

                // Top Middle
                seed(heightmap, record, region.mx, region.y1, value * dist(e1) * areaPercentage);
                // Bottom Middle
                seed(heightmap, record, region.mx, region.y2, value * dist(e1) * areaPercentage);
                // Middle Left
                seed(heightmap, record, region.x1, region.my, value * dist(e1) * areaPercentage);
                // Middle Right
                seed(heightmap, record, region.x2, region.my, value * dist(e1) * areaPercentage);
                // Center
                seed(heightmap, record, region.mx, region.my, value * dist(e1) * areaPercentage);
            }

            /**
             * Update the heightmap by dividing the region
             * @param heightmap The heightmap to update
             * @param record The record of cells we've updated
             * @param region The region to subdivide
             */
            void updateHeightmap(Heightmap& heightmap, std::vector<std::vector<bool>>& record, const Region& region) {
                short value;
                VLOG(2) << "Setting generated values for region centres (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ")";
                double heightmapArea = heightmap.width();
                double regionArea = region.x2 - region.x1;
                double areaPercentage = 2 * (regionArea / heightmapArea);

                std::uniform_real_distribution<float> dist(1 - areaPercentage, 1 + areaPercentage);

                // Top Middle
                value = (heightmap.get(region.x1, region.y1) + heightmap.get(region.x2, region.y1)) / 2;
                setCell(heightmap, record, region.mx, region.y1, value * dist(e1));
                
                // Bottom Middle
                value = (heightmap.get(region.x1, region.y2) + heightmap.get(region.x2, region.y2)) / 2;
                setCell(heightmap, record, region.mx, region.y2, value * dist(e1));
                
                // Middle Left
                value = (heightmap.get(region.x1, region.y1) + heightmap.get(region.x1, region.y2)) / 2;
                setCell(heightmap, record, region.x1, region.my, value * dist(e1));
                
                // Middle Right
                value = (heightmap.get(region.x2, region.y1) + heightmap.get(region.x2, region.y2)) / 2;
                setCell(heightmap, record, region.x2, region.my, value * dist(e1));

                // Center
                value = (heightmap.get(region.x1, region.y1) 
                        + heightmap.get(region.x2, region.y1)
                        + heightmap.get(region.x1, region.y2)
                        + heightmap.get(region.x2, region.y2)) / 4;
                setCell(heightmap, record, region.mx, region.my, value * dist(e1));
            }

            Heightmap generateHeightmap(const GeneratorSettings& settings) {
                Heightmap heightmap(settings.width, settings.height);

                std::vector<std::vector<bool>> calculated;
                calculated.resize(settings.width);
                for (unsigned int w = 0; w < settings.width; ++w) {
                    calculated[w].resize(settings.height, false);
                }


                // Step 1 - Mark all of the borders as ocean
                LOG(DEBUG) << "Setting borders to Ocean";
                for (unsigned int w = 0; w < settings.width; ++w) {
                    setCell(heightmap, calculated, w, 0, BORDER_VALUE);
                    setCell(heightmap, calculated, w, settings.height - 1, BORDER_VALUE);
                }
                for (unsigned int h = 0; h < settings.height; ++h) {
                    setCell(heightmap, calculated, 0, h, BORDER_VALUE);
                    setCell(heightmap, calculated, settings.width - 1, h, BORDER_VALUE);
                }

                // Step 2 - Set some higher seed points
                LOG(DEBUG) << "Setting seed points";
                std::list<Region> regions;
                regions.push_back(Region(0, 0, settings.width - 1, settings.height - 1));
                for (int i = 0; i < SEED_LOOP_COUNT; ++i) {
                    std::list<Region> newRegions;
                    for (Region& region : regions) {
                        updateHeightmap(heightmap, calculated, region, SEED_VALUE);
                        region.divide(newRegions);
                    }
                    std::swap(regions, newRegions);
                }

                // Step 3 - Generate the rest of the seed points
                LOG(DEBUG) << "Generating heightmap";
                while (!regions.empty()) {
                    std::list<Region> newRegions;
                    VLOG(1) << "Next set of regions: " << regions.size();
                    for (Region& region : regions) {
                        updateHeightmap(heightmap, calculated, region);
                        region.divide(newRegions);
                    }
                    std::swap(regions, newRegions);
                }
                
                LOG(DEBUG) << "Finished";
                return std::move(heightmap);
            }
        }
    }
}

