//**********************************************************************
// file name: talker.cc
//**********************************************************************

#include <stdio.h>
#include <string>
#include <stdint.h>

#include "PhonemMaker.h"

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// Static storage for temporary information.
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
static PhonemToCodeEntry phonemTable[128];
static std::string rules[100];
static char  rule[100];
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//*************************************************************************
// This program provides the mainline code for a text-to-speech
// synthesizer.  It accepts input from stdin so that a user can type a
// line of text followed by a carriage return, or input can be taken from
// a text file by using I/O redirection.  In either case, when a newline
// occurrs, the text will be presented to the speech synthesis system.
// I ported the original program, written in Pascal/MT+, to C++.  It will
// be evident that I used an ancient compiler due to the short variable
// names and short procedure and function names.  I also used upper case
// text (we did that back then in the CP/M days).
//*************************************************************************

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

   // We're using zero-based arrays.
   phonemCount = 0;
   ruleCount = 0;

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
         statusPtr = fgets(buffer,64,phonemStream);

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

   // Account for extra increments.
   ruleCount--;
   phonemCount--;

   // Does the phonem file and the phonetic rules exist?
   if (numberOfExistingFiles == 2)
   {
      // We're good to go!
      success = true;
   } // if

   return (success);

} // getSystemParameters

//***********************************************************************
// Mainline code.
//***********************************************************************
int main(int argc, char **argv)
{
   bool success; 
   bool done;
   int ruleCount;
   int phonemCount;
   char *statusPtr;
   char englishBuffer[1000];
   std::string englishText;
   uint32_t phonemBufferLength;
   uint8_t *phonemCodePtr;
   PhonemMaker *makerPtr;

   // Retrieve the inputs to the PhonemMaker constructure.
   success = getSystemParameters(ruleCount,phonemCount);

   if (success)
   {
      // Instantiate our first object.
      makerPtr = new PhonemMaker(rules,
                                 ruleCount,
                                 phonemTable,
                                 phonemCount);

      // Set up for loop entry.
      done = false;

      while (!done)
      {
         statusPtr = fgets(englishBuffer,100,stdin);

         if (statusPtr != NULL)
         {
            // Nuke the newline!
            englishBuffer[strlen(englishBuffer)-1] = '\0';

            // Copy this in order to satify the interface.
            englishText = englishBuffer;

            // Generate the phonems.
            makerPtr->acceptEnglishText(englishText,
                                        phonemCodePtr,
                                        phonemBufferLength);

            // Send the phonems to the speech synthesizer.

         } // if
         else
         {
            // Bail out.
            done = true;
         } // else
      } // while
   } // if

   // Release resources.
   delete makerPtr;

   return (0);

} // main

