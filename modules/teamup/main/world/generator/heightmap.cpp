#include "world/generator/heightmap.h"
#include <cassert>

namespace Teamup {
    namespace World {
        namespace Generator {
            Heightmap::Heightmap(const unsigned int width, const unsigned int height) {
                cells_.resize(width);
                for (unsigned int w = 0; w < width; ++w) {
                    cells_[w].resize(height);
                }
            }

            unsigned int Heightmap::width() const {
                return cells_.size();
            }

            unsigned int Heightmap::height() const {
                unsigned int result = 0;
                if (!cells_.empty()) {
                    result = cells_[0].size();
                }
                return result;
            }

            void Heightmap::set(const unsigned int x, const unsigned int y, const short height) {
                cells_[x][y] = height;
            }

            short Heightmap::get(const unsigned int x, const unsigned int y) const {
                return cells_[x][y];
            }
        }
    }
}
