#pragma once
#include <algorithm>
#include <cmath>

namespace gle {

    struct Range {
        float min, max;

        constexpr Range() : min(0.0f), max(0.0f) {
        }

        constexpr Range(float value) : min(value), max(value) {
        }

        constexpr Range(float min, float max) : min(min), max(max) {
        }

        constexpr float Size() const {
            return max - min;
        }

        constexpr float Mid() const {
            return (min + max) * 0.5f;
        }

        constexpr bool Contains(float v) const {
            return v >= min && v <= max;
        }

        constexpr float Clamp(float v) const {
            return std::clamp(v, min, max);
        }

        constexpr float Normalize(float v) const {
            return (v - min) / (max - min);
        }

        constexpr float Denormalize(float t) const {
            return min + (max - min) * t;
        }

        static constexpr float Lerp(const Range &r, float t) {
            return r.min + (r.max - r.min) * t;
        }

        constexpr bool operator==(const Range &r) const {
            return min == r.min && max == r.max;
        }

        constexpr bool operator!=(const Range &r) const {
            return !(*this == r);
        }

        Range &operator+=(float v) {
            min += v;
            max += v;
            return *this;
        }

        Range &operator-=(float v) {
            min -= v;
            max -= v;
            return *this;
        }

        Range &operator*=(float v) {
            min *= v;
            max *= v;
            return *this;
        }

        Range &operator/=(float v) {
            min /= v;
            max /= v;
            return *this;
        }
    };

} // namespace gle