#pragma once

namespace ctre {
namespace phoenix {
namespace motion {

enum TrajectoryDuration {
	TrajectoryDuration_5ms = 5,
	TrajectoryDuration_10ms = 10,
	TrajectoryDuration_15ms = 15,
	TrajectoryDuration_20ms = 20,
	TrajectoryDuration_30ms = 30,
	TrajectoryDuration_40ms = 40,
	TrajectoryDuration_50ms = 50,
	TrajectoryDuration_100ms = 100,
};

/**
 * Motion Profile Trajectory Point
 * This is simply a data transer object.
 */
struct TrajectoryPoint {
	double position; //!< The position to servo to.
	double velocity; //!< The velocity to feed-forward.
	double headingDeg;

	/**
	 * Which slot to get PIDF gains.
	 * PID is used for position servo.
	 * F is used as the Kv constant for velocity feed-forward.
	 * Typically this is hardcoded to the a particular slot, but you are free
	 * gain schedule if need be.
	 * Choose from [0,3].
	 */
	uint32_t profileSlotSelect0;

	/**
	 * Which slot to get PIDF gains for cascaded PID.
	 * This only has impact during MotionProfileArc Control mode.
	 * Choose from [0,1].
	 */
	uint32_t profileSlotSelect1;
	/**
	 * Set to true to signal Talon that this is the final point, so do not
	 * attempt to pop another trajectory point from out of the Talon buffer.
	 * Instead continue processing this way point.  Typically the velocity
	 * member variable should be zero so that the motor doesn't spin indefinitely.
	 */
	bool isLastPoint;
	/**
	 * Set to true to signal Talon to zero the selected sensor.
	 * When generating MPs, one simple method is to make the first target position zero,
	 * and the final target position the target distance from the current position.
	 * Then when you fire the MP, the current position gets set to zero.
	 * If this is the intent, you can set zeroPos on the first trajectory point.
	 *
	 * Otherwise you can leave this false for all points, and offset the positions
	 * of all trajectory points so they are correct.
	 */
	bool zeroPos;

	/**
	 * Duration to apply this trajectory pt.
	 */
	TrajectoryDuration timeDur;
};
} // namespace motion
} // namespace phoenix
} // namespace ctre
