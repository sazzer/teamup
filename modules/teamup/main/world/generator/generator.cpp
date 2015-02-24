#include "world/generator/generator.h"
#include <easylogging++.h>
#include <list>

namespace Teamup {
    namespace World {
        namespace Generator {
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
                    VLOG(1) << "Setting value for cell (" << x << ", " << y << ") to " << v;
                    heightmap.set(x, y, v);
                    record[x][y] = true;
                } else {
                    VLOG(1) << "Cell (" << x << ", " << y << ") already set";
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
                        VLOG(1) << "Adding region (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ")";
                        regions.push_back(region);
                    } else {
                        VLOG(1) << "Not adding region (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ") as area is zero";
                    }
                }
            };

            /**
             * Update the heightmap by dividing the region
             * @param heightmap The heightmap to update
             * @param record The record of cells we've updated
             * @param region The region to subdivide
             * @param value The fixed value to use
             */
            void updateHeightmap(Heightmap& heightmap, std::vector<std::vector<bool>>& record, const Region& region, const short value) {
                VLOG(1) << "Setting fixed values for region centres (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ") to " << value;
                // Top Middle
                setCell(heightmap, record, region.mx, region.y1, value);
                // Bottom Middle
                setCell(heightmap, record, region.mx, region.y2, value);
                // Middle Left
                setCell(heightmap, record, region.x1, region.my, value);
                // Middle Right
                setCell(heightmap, record, region.x2, region.my, value);
                // Center
                setCell(heightmap, record, region.mx, region.my, value);
            }

            /**
             * Update the heightmap by dividing the region
             * @param heightmap The heightmap to update
             * @param record The record of cells we've updated
             * @param region The region to subdivide
             */
            void updateHeightmap(Heightmap& heightmap, std::vector<std::vector<bool>>& record, const Region& region) {
                short value;
                VLOG(1) << "Setting generated values for region centres (" << region.x1 << ", " << region.y1 << ") - (" << region.x2 << ", " << region.y2 << ")";
                
                // Top Middle
                value = (heightmap.get(region.x1, region.y1) + heightmap.get(region.x2, region.y1)) / 2;
                setCell(heightmap, record, region.mx, region.y1, value);
                
                // Bottom Middle
                value = (heightmap.get(region.x1, region.y2) + heightmap.get(region.x2, region.y2)) / 2;
                setCell(heightmap, record, region.mx, region.y2, value);
                
                // Middle Left
                value = (heightmap.get(region.x1, region.y1) + heightmap.get(region.x1, region.y2)) / 2;
                setCell(heightmap, record, region.x1, region.my, value);
                
                // Middle Right
                value = (heightmap.get(region.x2, region.y1) + heightmap.get(region.x2, region.y2)) / 2;
                setCell(heightmap, record, region.x2, region.my, value);

                // Center
                value = (heightmap.get(region.x1, region.y1) 
                        + heightmap.get(region.x2, region.y1)
                        + heightmap.get(region.x1, region.y2)
                        + heightmap.get(region.x2, region.y2)) / 4;
                setCell(heightmap, record, region.mx, region.my, value);
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
                for (int w = 0; w < settings.width; ++w) {
                    setCell(heightmap, calculated, w, 0, -1);
                    setCell(heightmap, calculated, w, settings.height - 1, -1);
                }
                for (int h = 0; h < settings.height; ++h) {
                    setCell(heightmap, calculated, 0, h, -1);
                    setCell(heightmap, calculated, settings.width - 1, h, -1);
                }

                // Step 2 - Set some higher seed points
                LOG(DEBUG) << "Setting seed points";
                std::list<Region> regions;
                regions.push_back(Region(0, 0, settings.width - 1, settings.height - 1));
                for (int i = 0; i < 2; ++i) {
                    std::list<Region> newRegions;
                    for (Region& region : regions) {
                        updateHeightmap(heightmap, calculated, region, 10000);
                        region.divide(newRegions);
                    }
                    std::swap(regions, newRegions);
                }

                // Step 3 - Generate the rest of the seed points
                LOG(DEBUG) << "Generating heightmap";
                while (!regions.empty()) {
                    std::list<Region> newRegions;
                    for (Region& region : regions) {
                        updateHeightmap(heightmap, calculated, region);
                        region.divide(newRegions);
                    }
                    std::swap(regions, newRegions);
                }
                
                return std::move(heightmap);
            }
        }
    }
}

