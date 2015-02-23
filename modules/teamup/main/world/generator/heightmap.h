#ifndef TEAMUP_WORLD_GENERATOR_HEIGHTMAP_H
#define TEAMUP_WORLD_GENERATOR_HEIGHTMAP_H

#include <vector>

namespace Teamup {
    namespace World {
        namespace Generator {
            /**
             * The heightmap for the generated world
             */
            class Heightmap {
                public:
                    /**
                     * Construct the heightmap
                     * @param width The width of the heightmap
                     * @param height The height of the heightmap
                     */
                    Heightmap(const unsigned int width, const unsigned int height);

                    /**
                     * Get the width of the heightmap
                     * @return the width of the heightmap
                     */
                    unsigned int width() const;

                    /**
                     * Get the height of the heightmap
                     * @return the height of the heightmap
                     */
                    unsigned int height() const;

                    /**
                     * Set the heightmap value at the given co-ordinate
                     * @param x The X-Ordinate
                     * @param y The Y-Ordinate
                     * @param height The height
                     */
                    void set(const unsigned int x, const unsigned int y, const short height);

                    /**
                     * Get the heightmap value at the given co-ordinate
                     * @param x The X-Ordinate
                     * @param y The Y-Ordinate
                     * @return The height
                     */
                    short get(const unsigned int x, const unsigned int y) const;
                private:
                    /** The actual contents of the heightmap */
                    std::vector<std::vector<short>> cells_;
            };
        }
    }
}

#endif // TEAMUP_WORLD_GENERATOR_HEIGHTMAP_H
