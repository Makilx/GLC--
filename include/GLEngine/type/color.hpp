#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

namespace gle {

    struct Color {
        float r, g, b, a;

        struct HSV {
            float h;
            float s;
            float v;
        };

        constexpr Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {
        }

        constexpr Color(float r, float g, float b, float a = 1.0f)
            : r(r), g(g), b(b), a(a) {
        }

        Color(uint32_t hex, bool hasAlpha = false) {
            *this = FromHex(hex, hasAlpha);
        }

        Color(const std::string &hex) {
            *this = FromHex(hex);
        }

        Color(const HSV &hsv, float alpha = 1.0f) {
            *this = FromHSV(hsv.h, hsv.s, hsv.v, alpha);
        }

        static constexpr Color Black() {
            return {0, 0, 0, 1};
        }
        static constexpr Color White() {
            return {1, 1, 1, 1};
        }
        static constexpr Color Red() {
            return {1, 0, 0, 1};
        }
        static constexpr Color Green() {
            return {0, 1, 0, 1};
        }
        static constexpr Color Blue() {
            return {0, 0, 1, 1};
        }
        static constexpr Color Yellow() {
            return {1, 1, 0, 1};
        }
        static constexpr Color Cyan() {
            return {0, 1, 1, 1};
        }
        static constexpr Color Magenta() {
            return {1, 0, 1, 1};
        }

        constexpr Color operator-() const {
            return {-r, -g, -b, a};
        }

        constexpr Color operator+(const Color &c) const {
            return {r + c.r, g + c.g, b + c.b, a + c.a};
        }

        constexpr Color operator-(const Color &c) const {
            return {r - c.r, g - c.g, b - c.b, a - c.a};
        }

        Color &operator+=(const Color &c) {
            r += c.r;
            g += c.g;
            b += c.b;
            a += c.a;
            return *this;
        }

        Color &operator-=(const Color &c) {
            r -= c.r;
            g -= c.g;
            b -= c.b;
            a -= c.a;
            return *this;
        }

        constexpr Color operator*(float s) const {
            return {r * s, g * s, b * s, a * s};
        }

        constexpr Color operator/(float s) const {
            return {r / s, g / s, b / s, a / s};
        }

        Color &operator*=(float s) {
            r *= s;
            g *= s;
            b *= s;
            a *= s;
            return *this;
        }

        Color &operator/=(float s) {
            r /= s;
            g /= s;
            b /= s;
            a /= s;
            return *this;
        }

        friend constexpr Color operator*(float s, const Color &c) {
            return c * s;
        }

        constexpr bool operator==(const Color &c) const {
            return r == c.r && g == c.g && b == c.b && a == c.a;
        }

        constexpr bool operator!=(const Color &c) const {
            return !(*this == c);
        }

        Color Clamped() const {
            return {std::clamp(r, 0.0f, 1.0f), std::clamp(g, 0.0f, 1.0f),
                    std::clamp(b, 0.0f, 1.0f), std::clamp(a, 0.0f, 1.0f)};
        }

        constexpr Color RGB() const {
            return {r, g, b, 1.0f};
        }

        static constexpr Color Lerp(const Color &a, const Color &b, float t) {
            return {a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t,
                    a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t};
        }

        static constexpr Color Mix(const Color &a, const Color &b, float t) {
            return Lerp(a, b, t);
        }

        uint32_t ToRGBA8() const {
            auto c = [](float v) {
                return (uint8_t)(std::clamp(v, 0.0f, 1.0f) * 255.0f);
            };

            return (c(r) << 24) | (c(g) << 16) | (c(b) << 8) | (c(a));
        }

        static constexpr Color FromRGBA8(uint32_t rgba) {
            return {((rgba >> 24) & 0xFF) / 255.0f,
                    ((rgba >> 16) & 0xFF) / 255.0f,
                    ((rgba >> 8) & 0xFF) / 255.0f, (rgba & 0xFF) / 255.0f};
        }

        std::string ToHex(bool includeAlpha = false) const {
            auto c = [](float v) {
                return (uint8_t)(std::clamp(v, 0.0f, 1.0f) * 255.0f);
            };

            std::ostringstream ss;
            ss << "#" << std::hex << std::setfill('0');

            ss << std::setw(2) << (int)c(r) << std::setw(2) << (int)c(g)
               << std::setw(2) << (int)c(b);

            if (includeAlpha)
                ss << std::setw(2) << (int)c(a);

            return ss.str();
        }

        static Color FromHex(uint32_t hex, bool hasAlpha = false) {
            if (hasAlpha) {
                return {((hex >> 24) & 0xFF) / 255.0f,
                        ((hex >> 16) & 0xFF) / 255.0f,
                        ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f};
            }

            return {((hex >> 16) & 0xFF) / 255.0f, ((hex >> 8) & 0xFF) / 255.0f,
                    (hex & 0xFF) / 255.0f, 1.0f};
        }

        static Color FromHex(const std::string &hex) {
            std::string h = hex;
            if (h[0] == '#')
                h = h.substr(1);

            uint32_t value = std::stoul(h, nullptr, 16);

            if (h.length() == 8)
                return FromHex(value, true);
            return FromHex(value, false);
        }

        HSV ToHSV() const {
            float max = std::max({r, g, b});
            float min = std::min({r, g, b});
            float delta = max - min;

            HSV out{};
            out.v = max;

            if (delta < 0.00001f) {
                out.h = 0.0f;
                out.s = 0.0f;
                return out;
            }

            out.s = (max > 0.0f) ? (delta / max) : 0.0f;

            if (max == r)
                out.h = (g - b) / delta;
            else if (max == g)
                out.h = 2.0f + (b - r) / delta;
            else
                out.h = 4.0f + (r - g) / delta;

            out.h *= 60.0f;
            if (out.h < 0.0f)
                out.h += 360.0f;

            return out;
        }

        static Color FromHSV(float h, float s, float v, float a = 1.0f) {
            h = std::fmod(h, 360.0f);
            if (h < 0.0f)
                h += 360.0f;

            float c = v * s;
            float x = c * (1.0f - std::fabs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
            float m = v - c;

            float rp, gp, bp;

            if (h < 60) {
                rp = c;
                gp = x;
                bp = 0;
            } else if (h < 120) {
                rp = x;
                gp = c;
                bp = 0;
            } else if (h < 180) {
                rp = 0;
                gp = c;
                bp = x;
            } else if (h < 240) {
                rp = 0;
                gp = x;
                bp = c;
            } else if (h < 300) {
                rp = x;
                gp = 0;
                bp = c;
            } else {
                rp = c;
                gp = 0;
                bp = x;
            }

            return {rp + m, gp + m, bp + m, a};
        }
    };

} // namespace gle