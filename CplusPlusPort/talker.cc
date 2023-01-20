//**********************************************************************
// file name: talker.cc
//**********************************************************************

#include <stdio.h>
#include <string>
#include <stdint.h>

#include "PhonemMaker.h"

static PhonemToCodeEntry phonemTable[128];
static std::string rules[100];
static char rule[100];

/**************************************************************************

  Name: getSystemParameters

  Purpose: The purpose of this function is to set the operating point
  of the AGC.

  Calling Sequence: success = getSystemParameters(ruleCount,phonemCount)

  Inputs:

    ruleCount - A reference variable for the number of rules returned by
    this function.

    phonemCount - A reference variable for the number of phonems returned
    by this function

  Outputs:

    success - An indicator of the outcome of this function.  A value of
    true indicates that the system parameters were successfully retrieved,
    and a value of false indicates failure.

**************************************************************************/
static bool getSystemParameters(int& ruleCount,int& phonemCount)
{
   bool success;
   bool done;
   int i;
   FILE *phonemStream;
   FILE *ruleStream;
   char *statusPtr;
   char buffer[1000];
   int code;
   char alpha[100];
   int numberOfExistingFiles;

   // Default to failure.
   success = false;
   numberOfExistingFiles = 0;

   // We're using 1-based arrays, so start with 1.
   phonemCount = 1;
   ruleCount = 1;

   // Open the textual phonem to binary code mapping file.
   phonemStream = fopen("phonems.txt","r");

   if (phonemStream != NULL)
   {
      // The phonem file exists.
      numberOfExistingFiles++;

      // Set up for loop entry.
      done = false;

      while (!done)
      {
         statusPtr = fgets(buffer,100,phonemStream);

         if (statusPtr != NULL)
         {
            sscanf(buffer,"%d %s",&code,alpha);

            // Populate the phonem structure.
            phonemTable[phonemCount].ALPHA = alpha;
            phonemTable[phonemCount].CODE = code;

            // Reference the next storage element.
            phonemCount++;
         } // if
         else
         {
            // Bail out.
            done = true;
         } // else

      } // while */

      // We're done with this file.
      fclose(phonemStream);
   } // if

   // Open the phonetic rules file.
   ruleStream = fopen("rules.txt","r");

   if (ruleStream != NULL)
   {
      // The rules file exists.
      numberOfExistingFiles++;

      // Set up for loop entry.
      done = false;

      while (!done)
      {
         statusPtr = fgets(buffer,100,ruleStream);

         if (statusPtr != NULL)
         {
            // Just copy it so deal with literal whitespace.
            strncpy(rule,buffer,sizeof(rule));

            // Nuke the \n.
            rule[strlen(rule)-1] = '\0';

            // Populate the rule.
            rules[ruleCount] = rule;

            // Reference the next storage element.
            ruleCount++;
         } // if
         else
         {
            // Bail out.
            done = true;
         } // else

      } // while */

      // We're done with this file.
      fclose(ruleStream);
   } // if

   // Does the phonem file and the phonetic rules exist?
   if (numberOfExistingFiles == 2)
   {
      // We're good to go!
      success = true;
   } // if

   return (success);

} // getSystemParameters

int main(int argc, char **argv)
{
   int ruleCount;
   int phonemCount;
   PhonemMaker *makerPtr;

   // Now that information has been loaded, create the PhonemMaker object.
   makerPtr = new PhonemMaker(rules,
                              ruleCount,
                              phonemTable,
                              phonemCount);

   // Release resources.
   delete makerPtr;

   return (0);

} // main

