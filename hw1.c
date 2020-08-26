/*
 * ONOMATEPWNYMO:
 * ONOMATEPWNYMO:
  *
*/
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include "hw1.h"

int main(int argc, char *argv[])
{
  int i, j;
  int isValidRange = 0;
  int numberOfChoices = 0;
  int minimumRange = (MIN_CHOICE - 'A' + 1);
  int maximumRange = (MAX_CHOICE - 'A' + 1);

  int histogram[10];
  int countOfNotAnswered[NUM_STUDENTS];

  double average = 0;
  double deviation = 0;
  double wrongAnswerPenalty = 0.1;
  double studentScore[NUM_STUDENTS][3];

  char minimumChoice = MIN_CHOICE;
  char maxChoice = MAX_CHOICE;
  char input = 'a';
  char rightAnswers[NUM_QUESTIONS];
  char studentAnswers[NUM_STUDENTS][NUM_QUESTIONS];

  static char *separator = "\n##\n\0";

  initialize(&numberOfChoices, &maxChoice, &minimumChoice, minimumRange, maximumRange);

  readRightAsnwers(maxChoice, minimumChoice, rightAnswers);

  readPenalty(&wrongAnswerPenalty);

  readStudentAnswers(studentAnswers, maxChoice, minimumChoice, countOfNotAnswered);

  calculateStudentScore(studentScore, studentAnswers, rightAnswers, wrongAnswerPenalty);

  calculateAverage(studentScore, &average);

  calculateDeviation(studentScore, &deviation, average);

  calculateHistogram(histogram, studentScore);

  while (1)
  {
    printf("\n[M/m] Print mean");
    printf("\n[S/s] Print standard deviation");
    printf("\n[G/g] Print grade range");
    printf("\n[I/i] Print student info in range");
    printf("\n[H/h] Draw histogram");
    printf("\n[Q/q] Quit\n");

    scanf(" %c", &input);

    if (tolower(input) == 'm')
    {
      printf("\n%.2lf%s", average, separator);
    }
    else if (tolower(input) == 's')
    {
      printf("\n%.2lf%s", deviation, separator);
    }
    else if (tolower(input) == 'g')
    {
      int low = -1;
      int high = 11;
      char c;

      while (low < 0 || high > 10 || low >= high || (char)low == '-' || (char)low == '-')
      {
        printf("\nEnter grade range: ");
        scanf(" %d%c%d", &low, &c, &high);
      }

      int count = 0;

      for (int i = 0; i < NUM_STUDENTS; i++)
      {
        if (studentScore[i][2] >= low && (high == 10
                                              ? (studentScore[i][2] <= high)
                                              : (studentScore[i][2] < high)))
        {
          count++;
        }
      }

      printf("\n%d%s", count, separator);
    }
    else if (tolower(input) == 'h')
    {
      for (int i = 0; i < 10; i++)
      {
        i < 9 ? printf("[ %d, %d): ", i, i + 1)
              : printf("[ %d,%d]: ", i, i + 1);

        for (int j = 0; j < histogram[i] / (NUM_STUDENTS <= 100 ? 1 : 10); j++)
        {
          printf("*");
        }
        printf("\n");
      }
      printf("%s", separator);
    }
    else if (tolower(input) == 'i')
    {
      int low = -1;
      int high = 11;
      char c;

      while (low < 0 || high >= NUM_STUDENTS || low >= high || (char)low == '-' || (char)low == '-')
      {
        printf("\nEnter index range: ");
        scanf(" %d%c%d", &low, &c, &high);
      }

      for (int i = low; i <= high; i++)
      {
        printf("\n%03d:%4d,%4d,%4d,%6.2lf",
               i,
               (int)studentScore[i][0],
               (int)studentScore[i][1],
               countOfNotAnswered[i],
               studentScore[i][2]);
      }
      printf("%s", separator);
    }
    else if (tolower(input) == 'q')
    {
      return 1;
    }
    else
    {
      printf("\nError. Invalid option.");
    }
  }

  return 0;
}
//Reads maximum choice from the user
void initialize(int *numberOfChoices, char *maxChoice,
                char *minimumChoice, int minimumRange, int maximumRange)
{
  while (*numberOfChoices < 1 || *numberOfChoices > maximumRange - minimumRange + 1)
  {
    printf("\nEnter number of choices (1-%d): ", maximumRange - minimumRange + 1);
    scanf(" %d", numberOfChoices);
  }

  *maxChoice = MIN_CHOICE + (*numberOfChoices - 1);
  *minimumChoice = minimumRange + 'A' - 1;
}
void readRightAsnwers(int maxChoice,
                      int minimumChoice, char rightAnswers[NUM_QUESTIONS])
{
  int i = 0;
  char input;
  int isValidRange;

  printf("\nEnter answer key: ");

  while (i < NUM_QUESTIONS)
  {
    scanf(" %c", &input);
    isValidRange = (int)input >= minimumChoice && (int)input <= maxChoice ? 1 : 0;

    if (!isValidRange)
    {
      printf("\nError. Enter value %c-%c: ", minimumChoice, maxChoice);
      continue;
    }

    rightAnswers[i++] = input;
  }
}

void readPenalty(double *wrongAnswerPenalty)
{
  printf("\nEnter wrong answer penalty: ");

  do
  {
    scanf(" %lf", wrongAnswerPenalty);
    if (*wrongAnswerPenalty > 0)
    {
      printf("\nError. Enter non-positive value: ");
    }
  } while (*wrongAnswerPenalty > 0);
}

void readStudentAnswers(char studentAnswers[NUM_STUDENTS][NUM_QUESTIONS],
                        int maxChoice,
                        int minimumChoice,
                        int countOfNotAnswered[NUM_STUDENTS])
{
  int i, j;
  i = j = 0;
  char input;
  int isValidRange;

  for (i = 0; i < NUM_STUDENTS; i++)
  {
    countOfNotAnswered[i] = 0;
  }
  i = 0;

  while (i < NUM_STUDENTS)
  {
    printf("\nEnter student choices: ");

    while (j < NUM_QUESTIONS)
    {
      scanf(" %c", &input);

      isValidRange = (int)input >= minimumChoice && (int)input <= maxChoice ? 1 : 0;

      if (input != '-' && !isValidRange)
      {

        printf("\nError. Enter valid choice: ");
        // j = 0;
        continue;
      }

      if (input == '-')
      {
        countOfNotAnswered[i]++;
      }

      studentAnswers[i][j] = input;
      j++;
    }
    i++;
    j = 0;
  }
}

void calculateStudentScore(double studentScore[NUM_STUDENTS][3],
                           char studentAnswers[NUM_STUDENTS][NUM_QUESTIONS],
                           char rightAnswers[NUM_QUESTIONS],
                           double wrongAnswerPenalty)
{
  double score = 0;

  for (int i = 0; i < NUM_STUDENTS; i++)
  {
    for (int j = 0; j < NUM_QUESTIONS; j++)
    {
      if (studentAnswers[i][j] == rightAnswers[j])
      {
        studentScore[i][0]++; //Increase wright answers by one
      }
      else
      {
        if (studentAnswers[i][j] != '-')
        {
          studentScore[i][1]++; //Increase wrong answers by one
        }
      }
    }

    score = ((studentScore[i][0] + studentScore[i][1] * wrongAnswerPenalty) / NUM_QUESTIONS) * 10;
    if (score < 0)
    {
      score = 0;
    }

    studentScore[i][2] = score;
  }
}

void calculateAverage(double studentScore[NUM_STUDENTS][3], double *average)
{
  for (int i = 0; i < NUM_STUDENTS; i++)
  {
    *average += studentScore[i][2];
  }
  *average /= NUM_STUDENTS;
}
void calculateDeviation(double studentScore[NUM_STUDENTS][3], double *deviation, double average)
{
  double temp = 0;
  for (int i = 0; i < NUM_STUDENTS; i++)
  {
    temp += pow(studentScore[i][2] - average, 2);
  }
  temp /= NUM_STUDENTS;

  *deviation = sqrt(temp);
}

void calculateHistogram(int histogram[10], double studentScore[NUM_STUDENTS][3])
{
  int position = -1;
  for (int i = 0; i < 10; i++)
  {
    histogram[i] = 0;
  }
  for (int i = 0; i < NUM_STUDENTS; i++)
  {
    position = (int)floor(studentScore[i][2]);
    if (position == 10)
    {
      histogram[9]++;
    }
    else
    {
      histogram[position]++;
    }
  }
}