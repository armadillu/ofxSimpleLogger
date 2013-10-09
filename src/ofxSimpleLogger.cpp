//
//  ofxSimpleLogging.cpp
//  CityScapeRenderer
//
//  Created by Oriol Ferrer Mesià on 09/10/13.
//
//

#include "ofxSimpleLogger.h"

ofxSimpleLogger::ofxSimpleLogger(){

	repeatedMessageCount = 0;
	repeatedMessageLimit = MESSAGE_REPEAT_MULTIPLIER;

}

ofxSimpleLogger::~ofxSimpleLogger(){
	closeLog();
}

void ofxSimpleLogger::startLog(string name){

	char aux[255];
	sprintf(aux, name.c_str());
	logFile_ = fopen( ofToDataPath(aux, true).c_str()  , "a");	//append to current log file

	printf("\n%s ## Opening Log ##########################################\n", ofGetTimestampString().c_str() );
	fprintf(logFile_, "\n%s ## Opening Log ##########################################\n", ofGetTimestampString().c_str() );


}


void ofxSimpleLogger::closeLog(){
	if (logFile_ != NULL){
		printf("%s ## Closing Log ##########################################\n",ofGetTimestampString().c_str() );
		fprintf(logFile_, "%s ## Closing Log ##########################################\n",ofGetTimestampString().c_str() );
		if (logFile_) fclose (logFile_);
		logFile_ = NULL;
	}else{
		printf("ofxSimpleLogger::closeLog() > Log File is already closed!\n");
	}
}


void ofxSimpleLogger::addLine( char* format, ... ){
	va_list args;
	va_start(args, format);

	if ( processInput( auxLine_, format,  args ) ){
		printf(logLine_);


		if (logFile_ != NULL){
			fprintf(logFile_, logLine_);
			fflush(logFile_);
		}
	}
}


bool ofxSimpleLogger::processInput(char* buffer, char * format, va_list args){

	vsprintf(auxLine_, format,  args);
	bool ret = false;

	if ( strcmp(auxLine_, auxLine_prev) == 0 ){ //dont logo same message twice, count instead
		repeatedMessageCount++;
		if ( 0 == (repeatedMessageCount%repeatedMessageLimit) ){
			repeatedMessageLimit *= MESSAGE_REPEAT_MULTIPLIER;
			sprintf(logLine_, "%s  (%dx) %s\n",ofGetTimestampString().c_str(), repeatedMessageCount, auxLine_ );
			ret = true;
		}
	}else{
		repeatedMessageCount = 0;
		repeatedMessageLimit = MESSAGE_REPEAT_MULTIPLIER;
		sprintf(logLine_, "%s  %s\n",ofGetTimestampString().c_str(), auxLine_ );
		ret = true;
	}
	strcpy(auxLine_prev, auxLine_);
	return ret;
}