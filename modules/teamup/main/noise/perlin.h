#ifndef TEAMUP_NOISE_PERLIN_H
#define TEAMUP_NOISE_PERLIN_H

#include <vector>

namespace Noise {
    /**
     * Implementation of Perlin Noise
     */
    class Perlin {
        public:
            /**
             * Default constructor with the reference implementation
             */
            Perlin();

            /**
             * Generate noise for the given X, Y and Z Co-Ordinate.
             * The use of operator() means that we can treat instances of this class as
             * a functor to generate noise
             * @param x The X-Ordinate
             * @param y The Y-Ordinate
             * @param z The Z-Ordinate
             * @return the noise
             */
            double operator()(const double x, const double y, const double z) const;

            /**
             * Generate noise for the given X and Y Co-Ordinate.
             * The use of operator() means that we can treat instances of this class as
             * a functor to generate noise
             * @param x The X-Ordinate
             * @param y The Y-Ordinate
             * @return the noise
             */
            double operator()(const double x, const double y) const {
                return (*this)(x, y, 0);
            }
        protected:
        private:
            /** The permutations array */
            std::vector<unsigned char> permutations_;
    };
}

#endif // TEAMUP_NOISE_PERLIN_H
