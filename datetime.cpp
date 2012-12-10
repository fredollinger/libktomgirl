/*
 * gnote
 *
 * Copyright (C) 2009 Hubert Figuiere
 *
 * 2012 Modified by Fred Ollinger <follinge@gmail.com> for KTomGirl
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o

#include <time.h>
#include <ctime>
#include <cstdio>
#include <sys/time.h>

#include "datetime.hpp"
#include "ktglib.hpp"

using namespace boost::posix_time;

namespace sharp {

const char* dt_months[] = {"Zero", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

#define SEC_PER_MINUTE 60
#define SEC_PER_HOUR (SEC_PER_MINUTE * 60)
#define SEC_PER_DAY (SEC_PER_HOUR * 24)

  DateTime::DateTime()
  {
    m_date.tv_sec = time(NULL);
    m_date.tv_usec = 0;
  }

  DateTime::DateTime(time_t t, glong _usec)
  {
    m_date.tv_sec = t;
    m_date.tv_usec = _usec;
  }

  DateTime::DateTime(const GTimeVal & v)
    : m_date(v)
  {
  }

  DateTime & DateTime::add_days(int days)
  {
    m_date.tv_sec += (days * SEC_PER_DAY);
    return *this;
  }

  DateTime & DateTime::add_hours(int hours)
  {
    m_date.tv_sec += (hours * SEC_PER_HOUR);
    return *this;
  }

  int DateTime::day() const
  {
    struct tm result;
    localtime_r(&m_date.tv_sec, &result);
    return result.tm_mday;
  }

  int DateTime::hour() const
  {
    struct tm result;
    localtime_r(&m_date.tv_sec, &result);
    return result.tm_hour;
  }

  int DateTime::minute() const
  {
    struct tm result;
    localtime_r(&m_date.tv_sec, &result);
    return result.tm_min;
  }

  int DateTime::month() const
  {
    struct tm result;
    localtime_r(&m_date.tv_sec, &result);
    return result.tm_mon + 1;
  }

  int DateTime::year() const
  {
    struct tm result;
    localtime_r(&m_date.tv_sec, &result);
    return result.tm_year + 1900;
  }

  int DateTime::day_of_year() const
  {
    struct tm result;
    localtime_r(&m_date.tv_sec, &result);
    return result.tm_yday;
  }

  bool DateTime::is_valid() const
  {
    return ((m_date.tv_sec != -1) && (m_date.tv_usec != -1));
  }

// FRED: FIX
/* If you just want a decent string, this is the choice to make... */
std::string DateTime::to_string() const{
	DateTime dt_now = now();
	ptime pt = from_time_t(m_date.tv_sec);
	char c_d[4];
	char c_y[10] = ", "; 
	char c_t[10] = ""; 
	sprintf(c_d, " %i", day());

	if (dt_now.year() != year())
		sprintf(c_y, ", %i", year());

	if (minute() > 9)	
		sprintf(c_t, " %i:%i", hour(), minute());
	else
		sprintf(c_t, " %i:0%i", hour(), minute());

	std::string st = dt_months[month()];
	st = st + c_d + c_y + c_t;
	if (hour() > 11) st = st + " PM";
	else st = st + " AM";
	return st;
  }

  std::string DateTime::_to_string(const char * format, struct tm * t) const
  {
    char output[256];
    strftime(output, sizeof(output), format, t);
    return std::string(output);
  }

  std::string DateTime::to_string(const char * format) const
  {
    struct tm result; 
    return _to_string(format, localtime_r(&m_date.tv_sec, &result));
  }


  std::string DateTime::to_short_time_string() const
  {
    struct tm result;
    return _to_string("%R", localtime_r(&m_date.tv_sec, &result));
  }

std::string DateTime::to_iso8601() const
{
	ptime pt(not_a_date_time);
	pt = from_time_t(m_date.tv_sec);
	return to_iso_extended_string(pt);
}

DateTime DateTime::now()
  {
	GTimeVal n;

	ptime pt = second_clock::local_time();

	tm t = to_tm(pt);
	time_t tt = mktime( &t );

	n.tv_sec = tt;
	n.tv_usec = 0;

	return DateTime(n);
}

/* strip_delimiters_from_iso8601():
 * Get rid of the hyphens and the colons from this the file 
 */
std::string DateTime::strip_delimiters_from_iso8601(std::string iso8601){
	std::string str = iso8601.c_str();
	std::string s_char = "-";
	str = KTGlib::erase(str, s_char);
	s_char = ":";
	str = KTGlib::erase(str, s_char);
	return str;
}

// FIXME: Busted need to implement this protocol
DateTime DateTime::from_iso8601(const std::string &raw_str)
{
	GTimeVal retval;
	ptime pt(not_a_date_time);
	// ptime pt = second_clock::local_time();
	std::string iso8601 = strip_delimiters_from_iso8601(raw_str);

	retval.tv_sec = 0;
	retval.tv_usec = 0;

	try {
        	pt = from_iso_string(iso8601);
  	}
  	catch (int e)
  	{
    		std::cout << "An exception occurred. Exception Nr. " << e << std::endl;
		goto bail;
  	}

	tm td_tm;
	try {
		td_tm = to_tm(pt);
		retval.tv_sec = mktime(&td_tm);
  	}
  	catch (int e)
  	{
    		std::cout << "An exception occurred. Exception Nr. " << e << std::endl;
		goto bail;
  	}

	bail:
		return DateTime(retval);
}


  int DateTime::compare(const DateTime &a, const DateTime &b)
  {
    if(a > b)
      return +1;
    if(b > a)
      return -1;
    return 0;
  }

  bool DateTime::operator==(const DateTime & dt) const
  {
    return (m_date.tv_sec == dt.m_date.tv_sec) 
      && (m_date.tv_usec == dt.m_date.tv_usec);
  }

  bool DateTime::operator>(const DateTime & dt) const
  {
    if(m_date.tv_sec == dt.m_date.tv_sec) {
      return (m_date.tv_usec > dt.m_date.tv_usec);
    }
    return (m_date.tv_sec > dt.m_date.tv_sec);
  }

} // namespace sharp
// Sun Jun 17 16:55:15 PDT 2012
