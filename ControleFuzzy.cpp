// 
// 
// 

#include "ControleFuzzy.h"

void ControleFuzzyClass::init()
{
	//Passo 1 - Cria objeto
	fuzzy = new Fuzzy();

	//Passo 2 - Cria variaveis de entrada
	//Neste caso, 3 variaveis de entrada: yaw, pitch, linha
	
	//YAW
	FuzzyInput* yaw = new FuzzyInput(1);
	//Cria conjuntos fuzzy para yaw
	FuzzySet* esquerdaYaw = new FuzzySet(0, 20, 20, 40); //alterar valores para o seu robo
	yaw->addFuzzySet(esquerdaYaw); 
	FuzzySet* frenteYaw = new FuzzySet(30, 50, 50, 70); //alterar valores para o seu robo
	yaw->addFuzzySet(frenteYaw); 
	FuzzySet* direitaYaw = new FuzzySet(60, 80, 80, 80); //alterar valores para o seu robo
	yaw->addFuzzySet(direitaYaw); 
	fuzzy->addFuzzyInput(yaw); 
	
	//PITCH
	FuzzyInput* pitch = new FuzzyInput(2);
	//Cria conjuntos fuzzy para pitch
	FuzzySet* descendoPitch = new FuzzySet(0, 20, 20, 40); //alterar valores para o seu robo
	pitch->addFuzzySet(descendoPitch);
	FuzzySet* niveladoPitch = new FuzzySet(30, 50, 50, 70);//alterar valores para o seu robo
	pitch->addFuzzySet(niveladoPitch);
	FuzzySet* subindoPitch = new FuzzySet(60, 80, 80, 80);//alterar valores para o seu robo
	pitch->addFuzzySet(subindoPitch);
	fuzzy->addFuzzyInput(pitch);

	//LINHA
	FuzzyInput* linha = new FuzzyInput(3);
	//Cria conjuntos fuzzy para linha
	FuzzySet* esquerdaLinha = new FuzzySet(0, 20, 20, 40);//alterar valores para o seu robo
	linha->addFuzzySet(esquerdaLinha);
	FuzzySet* frenteLinha = new FuzzySet(30, 50, 50, 70);//alterar valores para o seu robo
	linha->addFuzzySet(frenteLinha);
	FuzzySet* direitaLinha = new FuzzySet(60, 80, 80, 80);//alterar valores para o seu robo
	linha->addFuzzySet(direitaLinha);
	fuzzy->addFuzzyInput(linha);

	//Passo 3 - Cria variaveis de saida
	//Neste caso, 2 variaveis de saida: pwm1 e pwm2

	//PWM1
	FuzzyOutput* pwm1 = new FuzzyOutput(1);
	FuzzySet* lentoPwm1 = new FuzzySet(0, 10, 10, 20); //alterar valores para o seu robo
	pwm1->addFuzzySet(lentoPwm1);
	FuzzySet* normalPwm1 = new FuzzySet(10, 20, 30, 40); //alterar valores para o seu robo
	pwm1->addFuzzySet(normalPwm1);
	FuzzySet* rapidoPwm1 = new FuzzySet(30, 40, 40, 50); //alterar valores para o seu robo
	pwm1->addFuzzySet(rapidoPwm1);
	fuzzy->addFuzzyOutput(pwm1);

	//PWM2
	FuzzyOutput* pwm2 = new FuzzyOutput(2);
	FuzzySet* lentoPwm2 = new FuzzySet(0, 10, 10, 20);//alterar valores para o seu robo
	pwm2->addFuzzySet(lentoPwm2);
	FuzzySet* normalPwm2 = new FuzzySet(10, 20, 30, 40);//alterar valores para o seu robo
	pwm2->addFuzzySet(normalPwm2);
	FuzzySet* rapidoPwm2 = new FuzzySet(30, 40, 40, 50);//alterar valores para o seu robo
	pwm2->addFuzzySet(rapidoPwm2);
	fuzzy->addFuzzyOutput(pwm2);

	//Passo 4 - Cria tabela de regras
	//Repare que join so aceita 2 argumentos, sendo assim, para se fazer um E com 3 argumentos
	//deve-se fazer um E e depois outro E com o resultado do primeiro E.

	//Regra 1(R1) - Se Picth=niveladoPitch e Yaw=frenteYaw e Linha=frenteLinha então pwm1=rapidoPwm1, pwm2=rapidoPwm2
	FuzzyRuleAntecedent* R1a = new FuzzyRuleAntecedent();
	R1a->joinWithAND(niveladoPitch, frenteYaw);
	FuzzyRuleAntecedent* R1b = new FuzzyRuleAntecedent();
	R1b->joinSingle(frenteLinha);
	FuzzyRuleAntecedent* R1 = new FuzzyRuleAntecedent();
	R1->joinWithAND(R1a, R1b);
	
	FuzzyRuleConsequent* aceleraPWM1ePWM2 = new FuzzyRuleConsequent();
	aceleraPWM1ePWM2->addOutput(rapidoPwm1);
	aceleraPWM1ePWM2->addOutput(rapidoPwm2);

	FuzzyRule* fuzzyRuleR1 = new FuzzyRule(1, R1, aceleraPWM1ePWM2);
	fuzzy->addFuzzyRule(fuzzyRuleR1);

	//Regra 2(R2) - Se Picth=niveladoPitch e Yaw=esquerdaYaw e Linha=esquerdaLinha então pwm1=normalPwm1, pwm2=lentoPwm2
	FuzzyRuleAntecedent* R2a = new FuzzyRuleAntecedent();
	R2a->joinWithAND(niveladoPitch, frenteYaw);
	FuzzyRuleAntecedent* R2b = new FuzzyRuleAntecedent();
	R2b->joinSingle(frenteLinha);
	FuzzyRuleAntecedent* R2 = new FuzzyRuleAntecedent();
	R2->joinWithAND(R2a, R2b);

	FuzzyRuleConsequent* viraParaDireitaPWM1ePWM2 = new FuzzyRuleConsequent();
	viraParaDireitaPWM1ePWM2->addOutput(normalPwm1);
	viraParaDireitaPWM1ePWM2->addOutput(lentoPwm2);

	FuzzyRule* fuzzyRuleR2 = new FuzzyRule(2, R2, viraParaDireitaPWM1ePWM2);
	fuzzy->addFuzzyRule(fuzzyRuleR2);

	//Regra 3


	//Regra 4


	//Regra 5

	//Regra 6...


}

int ControleFuzzyClass::output1fuzzy()  //pwm1
{
	return fuzzy->defuzzify(1);
}
int ControleFuzzyClass::output2fuzzy()  //pwm2
{
	return fuzzy->defuzzify(2);
}


ControleFuzzyClass ControleFuzzyObj;



