// ControleFuzzy.h

#ifndef _CONTROLEFUZZY_h
#define _CONTROLEFUZZY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "eFLL\Fuzzy.h"
#include "eFLL\FuzzyComposition.h"
#include "eFLL\FuzzyInput.h"
#include "eFLL\FuzzyRule.h"
#include "eFLL\FuzzyRuleConsequent.h"
#include "eFLL\FuzzyOutput.h"
#include "eFLL\FuzzyIO.h"
#include "eFLL\FuzzySet.h"
#include "eFLL\FuzzyRuleAntecedent.h"


class ControleFuzzyClass
{
 private:


 public:
	void init();

	int output1fuzzy();  //pwm1
	int output2fuzzy();  //pwm2

	Fuzzy* fuzzy;


};

extern ControleFuzzyClass ControleFuzzyObj;

#endif

