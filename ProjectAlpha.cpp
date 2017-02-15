// ProjectAlpha.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <random>
#include <time.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <limits>

using namespace std;
int n = 5; //number of arms

#define jrand (rand()%90)+11;
#define orand double((rand()%100)+1)/10;
#define arand rand()%n;
#define rrand (rand()%11)/10;

class ARM {
public:
	int N;
	double mu;
	double sigma;
};

class AGENT {
public:
	double value;
};

//Box Muller taken from Wikipedia
//https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform#Implementation
double armoutput(double mu, double sigma) {
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
		return z1*sigma + mu;
			
	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	
	return z0*sigma + mu;
	
}

int main()
{
	srand(time(NULL));
	
	////////////////////////////////////////
	//MAKING THE ARMS

	vector<ARM> armvalues;
	
	for (int i = 0; i < n; i++) {
		
		ARM arm;

		arm.N = i + 1;
		arm.mu = jrand;
		arm.sigma = orand;

		armvalues.push_back(arm);
	}

	for (int i = 0; i < n; i++) {
		cout << armvalues.at(i).N << "\t" << armvalues.at(i).mu << "\t";
		cout << armvalues.at(i).sigma << endl;
	}

	//END OF MAKING THE ARMS
	///////////////////////////////////////
	//MANUAL ARM OUTPUT
	
	/*int N = 10000;
	cout << "Pick an Arm ";
	
	while (N != -1) {
		cin >> N;
		if (N != 0) {
			N = N - 1;

			cout << armoutput(armvalues.at(N).mu, armvalues.at(N).sigma) << endl;
		}
		else {
			N = -1;
		}
	}*/

	//END OF MANUAL ARM OUTPUT
	////////////////////////////////////////
	//AGENT CHOOSING
	
	vector<AGENT> agentvalues;
	
	double mistic = 0; //Value for optimistic or pessimistic
	
	for (int i = 0; i < n; i++) {
		AGENT agent;
		agent.value = mistic;
		agentvalues.push_back(agent);
	}

	double epsilon = 1.1;
	double alpha = .25;
	int cycles = 10000; // number of learning cycles the agent has to find the best arm
	
	for (int i = 0; i < cycles; i++) {
		double E = rrand;
		if (E >= epsilon) {

		}
		else {
			int randchoice = arand;
			double randout = armoutput(armvalues.at(randchoice).mu, armvalues.at(randchoice).sigma); //normal distribution output from random arm
			agentvalues.at(randchoice).value = randout*alpha - agentvalues.at(randchoice).value*(1 - alpha);
		}
	}

	//vt(a)=RaAL+vt-1(1-AL)

	for (int i = 0; i < n; i++) {
		cout << agentvalues.at(i).value << endl;
	}
	

	//END OF AGENT CHOOSING
	////////////////////////////////////////



	/*
	int mu = 100;
	int sigma = 10;
		
	//ofstream cout("PA.txt");
	for (int i = 0; i < 50; i++) {
		double out = armoutput(mu, sigma);
		cout << out << endl;
	}
	*/

	int a = 0;
	int j = 0;
	cin >> a;
	assert(a == j);
	return 0;
	return 0;
}
