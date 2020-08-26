#ifndef _HW1_H
#define _HW1_H

#define NUM_STUDENTS 50
#define NUM_QUESTIONS 20
#define MIN_CHOICE 'A'
#define MAX_CHOICE 'Z'

void readRightAsnwers(int maxChoice,
                      int minimumChoice,
                      char rightAnswers[NUM_QUESTIONS]);

void readStudentAnswers(char studentAnswers[NUM_STUDENTS][NUM_QUESTIONS],
                        int maxChoice,
                        int minimumChoice,
                        int countOfNotAnswered[NUM_STUDENTS]);

void readPenalty(double *wrongAnswerPenalty);

void initialize(int *numberOfChoices,
                char *maxChoice,
                char *minimumChoice,
                int minimumRange,
                int maximumRange);

void calculateStudentScore(double studentScore[NUM_STUDENTS][3],
                           char studentAnswers[NUM_STUDENTS][NUM_QUESTIONS],
                           char rightAnswers[NUM_QUESTIONS],
                           double wrongAnswerPenalty);

void calculateAverage(double studentScore[NUM_STUDENTS][3],
                      double *average);

void calculateDeviation(double studentScore[NUM_STUDENTS][3],
                        double *deviation,
                        double average);

void calculateHistogram(int histogram[10], double studentScore[NUM_STUDENTS][3]);

#endif
