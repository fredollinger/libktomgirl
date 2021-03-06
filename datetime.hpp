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
#ifndef __SHARP_DATETIME_HPP__
#define __SHARP_DATETIME_HPP__

#include <time.h>

#include <string>


namespace sharp {

typedef long glong;

class DateTime
{
// BEGIN DateTime public:
public:
  DateTime();
  explicit DateTime(time_t t, glong _usec = 0);
  
  DateTime & add_days(int days);
  DateTime & add_hours(int hours);

  int hour() const;
  int minute() const;
  int day() const;
  int month() const;
  int year() const;
  int day_of_year() const;

  bool is_valid() const;
  bool operator>(const DateTime & dt) const;

  static std::string strip_delimiters_from_iso8601(std::string);
  std::string to_string(const char * format) const;
  std::string to_string(const std::string & format) const
    {
      return to_string(format.c_str());
    }
  std::string to_string() const;
  std::string to_short_time_string() const;
  std::string to_iso8601() const;

  static DateTime now();
  static DateTime from_iso8601(const std::string &);
  static int compare(const DateTime &, const DateTime &);

  bool operator==(const DateTime & dt) const;

  glong sec() const
    {
      return m_date.tv_sec;
    }
  glong usec() const
    {
      return m_date.tv_usec;
    }
  void set_usec(glong _usec) 
    {
      m_date.tv_usec = _usec;
    }
// END DateTime public:

private:
struct GTimeVal {
  glong tv_sec;
  glong tv_usec;
};

  // return the string formatted according to strftime
  std::string _to_string(const char * format, struct tm *) const;
  // implementation detail. really make public if needed.
  explicit DateTime(const GTimeVal & v);
  GTimeVal m_date;
}; // class datetime


} // namespace sharp

#endif
