#ifndef sr04_h
#define sr04_h


// Shoudln't need to changed these values unless you have a specific need to do so.
#define MAX_SENSOR_DISTANCE 500 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back.
#define US_ROUNDTRIP_CM 57      // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space.
#define DISABLE_ONE_PIN false   // Set to "true" to save up to 26 bytes of compiled code space if you're not using one pin sensor connections.

// Probably shoudln't change these values unless you really know what you're doing.
#define NO_ECHO 0               // Value returned if there's no ping echo within the specified MAX_SENSOR_DISTANCE or max_cm_distance.
#define MAX_SENSOR_DELAY 18000  // Maximum uS it takes for sensor to start the ping (SRF06 is the highest measured, just under 18ms).
#define PING_MEDIAN_DELAY 29    // Millisecond delay between pings in the ping_median method.

// Conversion from uS to distance (round result to nearest cm or inch).
#define SR04Convert(echoTime, conversionFactor) (max((echoTime + conversionFactor / 2) / conversionFactor, (echoTime ? 1 : 0)))


class SR04 {
	public:
		SR04(uint8_t trigger_pin, uint8_t echo_pin, int max_cm_distance = MAX_SENSOR_DISTANCE);
		unsigned int ping();
		unsigned int ping_cm();
		unsigned int ping_median(uint8_t it = 5);
		unsigned int convert_cm(unsigned int echoTime);
	private:
		boolean ping_trigger();
		uint8_t _triggerPin;
		uint8_t _echoPin;
		unsigned int _maxEchoTime;
		unsigned long _max_time;
};

#endif