#include "noise/perlin.h"
#include <easylogging++.h>

namespace Noise {
    /** The reference permutation array */
    static const std::vector<unsigned char> REFERENCE_PERMUTATIONS {151,160,137,91,90,15,
       131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
       190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
       88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
       77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
       102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
       135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
       5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
       223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
       129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
       251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
       49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
       138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

    Perlin::Perlin() {
        LOG(TRACE) << "Constructed reference Perlin Noise";
        permutations_.insert(permutations_.begin(), 
                REFERENCE_PERMUTATIONS.begin(), 
                REFERENCE_PERMUTATIONS.end());
        permutations_.insert(permutations_.end(), 
                permutations_.begin(), 
                permutations_.end());
    }

    /**
     * Compute the position on the fade curve for the given value.
     * The fade curve is 6x^5 - 15x^4 + 10x^3
     * @param t The input value
     * @return the faded value
     */
    double fade(const double t) {
        return (6*pow(t, 5)) - (15*pow(t, 4)) + (10*pow(t, 3));
    }

    /**
     * Compute the dot product between two provided vectors
     * @param a The first vector
     * @param b The second vector
     * @return The dot product of the two vectors
     */
    template<typename T, std::size_t N>
    double dot(const std::array<T, N>& a, const std::array<T, N>& b) {
        double res = 0;
        for (int i = 0; i < N; ++i) {
            res += (a[i] * b[i]);
        }

        return res;
    }

    double grad(const unsigned int hash, const double x, const double y, const double z) {
        double result;
        switch (hash & 0xF) {
            case 0x0: result =  x + y; break;
            case 0x1: result = -x + y; break;
            case 0x2: result =  x - y; break;
            case 0x3: result = -x - y; break;
            case 0x4: result =  x + z; break;
            case 0x5: result = -x + z; break;
            case 0x6: result =  x - z; break;
            case 0x7: result = -x - z; break;
            case 0x8: result =  y + z; break;
            case 0x9: result = -y + z; break;
            case 0xa: result =  y - z; break;
            case 0xb: result = -y - z; break;
            case 0xc: result =  y + x; break;
            case 0xd: result = -y + z; break;
            case 0xe: result =  y - x; break;
            case 0xf: result = -y - z; break;
            default: result = 0; break;
        }
        VLOG(9) << "Grad(" << hash << ", " << x << ", " << y << ", " << z << ") = " << result;
        return result;
    }

    /**
     * Perform Liner Interpolation between a and b by the value x
     * @param a The first value to interpolate from
     * @param b The second value to interpolate from
     * @param x The interpolation parameter
     * @return the interpolated value
     */
    double lerp(double a, double b, double x) {
        return a + x * (b - a);
    }

    double Perlin::operator()(const double x, const double y, const double z) const {
        VLOG(9) << "Generating noise for (" << x << ", " << y << ", " << z << ")";
        // (x0,y1)--------(x1,y1)
        //    |              |
        //    |     (x,y)    |
        //    |              |
        //    |              |
        //    |              |
        // (x0,y0)--------(x1,y0)
        //
        // Example: x = 0.359, y = 1.0625
        // x0 = 0, y0 = 1
        // x1 = 1, y1 = 2
        const int x0 = floor(x);
        const int y0 = floor(y);
        const int z0 = floor(z);
        const int x1 = x0 + 1;
        const int y1 = y0 + 1;
        const int z1 = z0 + 1;
        VLOG(9) << "Grid points at (" << x0 << ", " << y0 << ", " << z0 << ")-(" << x1 << ", " << y1 << ", " << z1 << ")";

        // Just the fractional parts of the provided X and Y
        const double xf = x - floor(x);
        const double yf = y - floor(y);
        const double zf = z - floor(z);
        VLOG(9) << "Fractional points: (" << xf << ", " << yf << ", " << zf << ")";

        const double u = fade(xf);
        const double v = fade(yf);
        const double w = fade(zf);
        VLOG(9) << "Faded points: (" << u << ", " << v << ", " << w << ")";

        // Quick alias for the permutations because otherwise the next lines are very long!
        const auto& p = permutations_;
        // Truncate x0 and y0 to the first 8 bits
        const unsigned int xi = x0 & 255;
        const unsigned int yi = y0 & 255;
        const unsigned int zi = z0 & 255;
        const unsigned int aaa = p[p[p[xi + 0] + yi + 0] + zi + 0];
        const unsigned int aba = p[p[p[xi + 0] + yi + 1] + zi + 0];
        const unsigned int aab = p[p[p[xi + 0] + yi + 0] + zi + 1];
        const unsigned int abb = p[p[p[xi + 0] + yi + 1] + zi + 1];
        const unsigned int baa = p[p[p[xi + 1] + yi + 0] + zi + 0]; 
        const unsigned int bba = p[p[p[xi + 1] + yi + 1] + zi + 0]; 
        const unsigned int bab = p[p[p[xi + 1] + yi + 0] + zi + 1]; 
        const unsigned int bbb = p[p[p[xi + 1] + yi + 1] + zi + 1];

        VLOG(9) << "AAA: " << aaa << ", ABA: " << aba << ", BAA: " << baa << ", BBA: " << bba << ", AAB: " << aab << ", ABB: " << abb << ", BAB: " << bab << ", BBB: " << bbb;
        
        const double lx1y1 = lerp(grad(aaa, xf    , yf    , zf    ), 
                                  grad(baa, xf - 1, yf    , zf    ),
                                  u);
        const double lx2y1 = lerp(grad(aba, xf    , yf - 1, zf    ), 
                                  grad(bba, xf - 1, yf - 1, zf    ),
                                  u);
        const double ly1 = lerp(lx1y1, lx2y1, v);
        VLOG(9) << "LERPed values for Y1: (" << lx1y1 << ", " << lx2y1 << ") = " << ly1;

        const double lx1y2 = lerp(grad(aab, xf    , yf    , zf - 1), 
                                  grad(bab, xf - 1, yf    , zf - 1),
                                  u);
        const double lx2y2 = lerp(grad(abb, xf    , yf - 1, zf - 1), 
                                  grad(bbb, xf - 1, yf - 1, zf - 1),
                                  u);
        const double ly2 = lerp(lx1y2, lx2y2, v);
        VLOG(9) << "LERPed values for Y2: (" << lx1y2 << ", " << lx2y2 << ") = " << ly2;

        const double result = (lerp(ly1, ly2, w) + 1) / 2;
        VLOG(9) << "Noise for (" << x << ", " << y << ", " << z << ") = " << result;
        return result;
    }
}
