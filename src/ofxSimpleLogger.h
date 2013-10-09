//
//  ofxSimpleLogging.h
//  CityScapeRenderer
//
//  Created by Oriol Ferrer Mesià on 09/10/13.
//
//

#ifndef __CityScapeRenderer__ofxSimpleLogging__
#define __CityScapeRenderer__ofxSimpleLogging__

#include <iostream>
#include "ofMain.h"

#define MESSAGE_REPEAT_MULTIPLIER	5


class ofxSimpleLogger{

public:

	ofxSimpleLogger();
	~ofxSimpleLogger();


	void startLog(string name);

	void addLine( char* format, ...);

	void closeLog();

private:

	bool processInput(char* buffer, char * format, va_list args);


	FILE *						logFile_;
	char						auxLine_[1524];	//space to copy each line to before logging it
	char						logLine_[1524];	//space to copy each line to before logging it
	char						auxLine_prev[1524];

	int							repeatedMessageCount;
	int							repeatedMessageLimit;

};
#endif /* defined(__CityScapeRenderer__ofxSimpleLogging__) */
