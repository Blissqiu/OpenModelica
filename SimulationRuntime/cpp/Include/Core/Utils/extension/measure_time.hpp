#ifndef MEASURE_TIME_HPP
#define MEASURE_TIME_HPP

#if defined(_MSC_VER)
#include <intrin.h>
#endif

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>


class MeasureTime
{
public:
	virtual ~MeasureTime() {}

	struct data
	{
		unsigned long long sum_time;
		unsigned num_calcs;
		unsigned long long max_time;
	};

	static MeasureTime* getInstance();

	virtual unsigned long long getTime();

	static void deinitialize();

	void writeTimeToJason(std::string model_name, std::vector<data> times);

protected:
	MeasureTime() {}

	virtual unsigned long long getTimeP() = 0;

	static MeasureTime *instance;
};

class RDTSC_MeasureTime : public MeasureTime
{
protected:
	RDTSC_MeasureTime() : MeasureTime() {};

	virtual unsigned long long getTimeP();

public:
	virtual ~RDTSC_MeasureTime() {}

	static void initialize();

private:
	static unsigned long long RDTSC();


};
#endif // MEASURE_TIME_HPP
