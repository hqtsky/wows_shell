#pragma once

namespace shell {

// https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int
template <typename E>
constexpr typename std::underlying_type<E>::type toUnderlying(E e) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

namespace impact {
static constexpr unsigned int maxColumns = 13;
static constexpr unsigned int maxColumnsFit = 7;
enum class impactIndices {
    distance,
    launchAngle,
    impactAngleHorizontalRadians,  // Negative for Falling
    impactAngleHorizontalDegrees,  // Positive for Falling
    impactVelocity,
    timeToTarget,
    timeToTargetAdjusted,  // Adjusted for in game shell time
    rawPenetration,
    effectivePenetrationHorizontal,
    effectivePenetrationHorizontalNormalized,
    impactAngleDeckDegrees,
    effectivePenetrationDeck,
    effectivePenetrationDeckNormalized,
};
using indexT = typename std::underlying_type<impactIndices>::type;
static_assert(toUnderlying(impactIndices::effectivePenetrationDeckNormalized) ==
                  (maxColumns - 1),
              "Invalid standard columns");
}  // namespace impact

namespace angle {
static constexpr unsigned int maxColumns = 9;
enum class angleIndices {
    distance,
    ricochetAngle0Radians,
    ricochetAngle0Degrees,
    ricochetAngle1Radians,
    ricochetAngle1Degrees,
    armorRadians,
    armorDegrees,
    fuseRadians,
    fuseDegrees
};
using indexT = typename std::underlying_type<angleIndices>::type;
static_assert(toUnderlying(angleIndices::fuseDegrees) == (maxColumns - 1),
              "Invalid angle columns");
}  // namespace angle

namespace post {
static constexpr unsigned int maxColumns = 6;
enum class postPenIndices { angle, distance, x, y, z, xwf };
using indexT = typename std::underlying_type<postPenIndices>::type;
static_assert(toUnderlying(postPenIndices::xwf) == (maxColumns - 1),
              "Invaild postpen columns");
}  // namespace post

enum class numerical {
    forwardEuler,
    rungeKutta2,
    rungeKutta4,
    adamsBashforth5
};

template <numerical Numerical>
static constexpr bool isMultistep() {
    if constexpr (Numerical == numerical::adamsBashforth5) {
        return true;
    } else {
        return false;
    }
}
}  // namespace shell