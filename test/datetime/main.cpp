#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>

using namespace sharp;

void nowTest(){
//	DateTime dt = DateTime::now();
  std::string st = "2012-12-07T23:50:57";
	//std::string st = "2011-08-09T09:01:20";
	DateTime dt = DateTime::from_iso8601(st);
	std::cout << "string: " << dt.to_string() << std::endl;
  /*
	qDebug() << "day: " << dt.day();
	qDebug() << "month: " << dt.month();
	qDebug() << "sec: " << dt.sec();
	qDebug() << "string: " << QString::fromStdString(dt.to_string());
  */
	//qDebug() << "hour: " << dt.hour();
}

void iso8601Test(std::string &st){
	DateTime dt = DateTime::from_iso8601(st);
//	qDebug() << "to short time string: " << QString::fromStdString(dt.to_short_time_string() );
}

void dateTest(std::string &st, std::string success){

	// test the strip delim separately
	std::string res = DateTime::strip_delimiters_from_iso8601(success);

	// now test the converter
	DateTime dt = DateTime::from_iso8601(st);
	res = dt.to_iso8601();

/*
	if (success.compare(st)) 
	else{
	  qDebug() << "date test failed: " <<  QString::fromStdString(res) << " != " << QString::fromStdString(success);
	  exit(0); 
	}
  */
}

int main( int argc, char *argv[] )
{

	std::string st;
	std::string success;

//	st = "2002-02-01T07:59:59";
//	st = "2012-08-09T09:01:20";
  st = "2012-12-07T23:50:57";

	success = "20020131T235959";

//	dateTest(success, st);
//	iso8601Test(success);
	//iso8601Test(st);
	nowTest();

}
// Sat May  5 10:26:49 PDT 2012
