//**********************************************************************
// file name: PhonemMaker.cc
//**********************************************************************

#include "PhonemMaker.h"

/************************************************************************

  Name: PhonemMaker

  Purpose: The purpose of this function is to serve as the constructor
  of a PhonemMaker object.

  Calling Sequence: PhonemMaker(rules,
                                numberOfRules,
                                phonemMapPtr,
                                numberOfPhonems)

  Inputs:

    rules - An array of strings that represent the phonetic rules.

    numberOfRules - The number of phonetic rules.

    phonemTable - An array of structures that maps textual phonems to
    the binary phonem code that is presented to the voice synthesizer.

    numberOfPhonems - The number of phonems in the phonem table.

  Outputs:

    None.

**************************************************************************/
PhonemMaker::PhonemMaker(std::string rules[],
                         int numberOfRules,
                         PhonemToCodeEntry *phonemMapPtr,
                         int numberOfPhonems)
{
   int i;

   // Populate the rule table.
   for (i = 0; i < numberOfRules; i++)
   {
      RUL_TBL[i] = rules[i];
   } // for

   // Populate the phonem table.
   for (i = 0; i < numberOfPhonems; i++)
   {
      PHO_TBL[i].ALPHA = phonemMapPtr[i].ALPHA;
      PHO_TBL[i].CODE = phonemMapPtr[i].CODE;
   } // for

} // PhonemMaker

/************************************************************************

  Name: PhonemMaker

  Purpose: The purpose of this function is to serve as the constructor
  of a PhonemMaker object.

  Calling Sequence: PhonemMaker(rules,
                                numberOfRules,
                                phonemMapPtr,
                                numberOfPhonems)

  Inputs:

    rules - An array of strings that represent the phonetic rules.

    numberOfRules - The number of phonetic rules.

    phonemTable - An array of structures that maps textual phonems to
    the binary phonem code that is presented to the voice synthesizer.

    numberOfPhonems - The number of phonems in the phonem table.

  Outputs:

    None.

**************************************************************************/
PhonemMaker::~PhonemMaker(void)
{

} // ~PhonemMaker

/*****************************************************************************

 acceptEnglishText - CONVERT ENGLISH TEXT TO PHONEM STRING
 This is really the entry point into the phonem processing engine.

*****************************************************************************/

void PhonemMaker::acceptEnglishText(std::string& INBUF,
                                    uint8_t*& phonemBuffer,
                                    uint32_t& phonemCount)

{
   int INDEX;

   // Set to the beginning of the buffers.
   P_INDEX = 0;
   E_INDEX = 0;

   // Compute message length.  Yes, this is redundant.
   E_LEN = INBUF.length();

   for (INDEX = 0; INDEX < E_LEN; INDEX++)
   {
      // Convert to upper case.
      E_BUFFER[INDEX] = toupper(INBUF[INDEX]);
   } // for

   while (E_INDEX < E_LEN)
   {
      switch (E_BUFFER[E_INDEX])
      {
         case 'A':
         {
            // Process with the rules of A.
            RUL_SRCH(0,5);
            break;
         } // case

         case 'B':
          {
            // Process with the rules of B.
            RUL_SRCH(5,1);
            break;
         } // case

         case 'C':
         {
            // Process with the rules of C.
            RUL_SRCH(6,3);
            break;
         } // case

         case 'D':
         {
            // Process with the rules of D.
            RUL_SRCH(9,1);
            break;
         } // case

         case 'E':
         {
            // Process with the rules of E.
            RUL_SRCH(10,8);
            break;
         } // case

         case 'F':
         {
            // Process with the rules of F.
            RUL_SRCH(18,1);
            break;
         } // case

         case 'G':
         {
            // Process with the rules of G.
            RUL_SRCH(19,1);
            break;
         } // case

         case 'H':
         {
            // Process with the rules of H.
            RUL_SRCH(20,2);
            break;
         } // case

         case 'I':
         {
            // Process with the rules of I.
            RUL_SRCH(22,5);
            break;
         } // case

         case 'J':
         {
            // Process with the rules of J.
            RUL_SRCH(27,1);
            break;
         } // case

         case 'K':
         {
            // Process with the rules of K.
            RUL_SRCH(28,1);
            break;
         } // case

         case 'L':
         {
            // Process with the rules of L.
            RUL_SRCH(29,2);
            break;
         } // case

         case 'M':
         {
            // Process with the rules of M.
            RUL_SRCH(31,1);
            break;
         } // case

         case 'N':
         {
            // Process with the rules of N.
            RUL_SRCH(32,2);
            break;
         } // case

         case 'O':
         {
            // Process with the rules of O.
            RUL_SRCH(34,4);
            break;
         } // case

         case 'P':
         {
            // Process with the rules of P.
            RUL_SRCH(38,1);
            break;
         } // case

         case 'Q':
         {
            // Process with the rules of Q.
            RUL_SRCH(39,2);
            break;
         } // case

         case 'R':
         {
            // Process with the rules of R.
            RUL_SRCH(41,1);
            break;
         } // case

         case 'S':
         {
            // Process with the rules of S.
            RUL_SRCH(42,5);
            break;
         } // case

         case 'T':
         {
            // Process with the rules of T.
            RUL_SRCH(47,6);
            break;
         } // case

         case 'U':
         {
            // Process with the rules of U.
            RUL_SRCH(53,2);
            break;
         } // case

         case 'V':
         {
            // Process with the rules of V.
            RUL_SRCH(55,1);
            break;
         } // case

         case 'W':
         {
            // Process with the rules of W.
            RUL_SRCH(56,2);
            break;
         } // case

         case 'X':
         {
            // Process with the rules of X.
            RUL_SRCH(58,1);
            break;
         } // case

         case 'Y':
         {
            // Process with the rules of Y.
            RUL_SRCH(59,2);
            break;
         } // case

         case 'Z':
         {
            // Process with the rules of Z.
            RUL_SRCH(61,1);
            break;
         } // case

         default:
         {
            // Process as a digit or symbol.
            RUL_SRCH(62,15);
            break;
         } // case
      } // switch
   } // while

   // Set return values.  Note that references are being used.
   phonemCount = P_INDEX;
   phonemBuffer = P_BUFFER;

fprintf(stderr,"P_INDEX: %d\n",P_INDEX);

   return;

} // ENG_TO_PH
   
/******************************************************************************

 IS_ALPHA - RETURN FLAG DETERMINING IF ARGUMENT IS AN ALPHABETIC CHARACTER

******************************************************************************/

bool PhonemMaker::IS_ALPHA(char CH)
{
   bool result;

   // Leverage the standard library function.
   result = isalpha((int)CH);

   return (result);

} // IS_ALPHA

/*****************************************************************************

 IS_VWL - RETURN FLAG DETERMINING IF ARGUMENT IS A VOWEL

*****************************************************************************/

bool PhonemMaker::IS_VWL(char CH)
{
   bool result;

   switch(CH)
   {
      case 'A':
      case 'E':
      case 'I':
      case 'O':
      case 'U':
      case 'Y':
      {
         // The character is a vowel.
         result = true;
         break;
      } // case

      default:
      {
         // The character is not a vowel.
         result = false;;
         break;
      } // case
   } // switch

   return (result);

} // IS_VWL

/****************************************************************************

 IS_FR_VWL - RETURN FLAG DETERMINING IF ARGUMENT IS A FRONT VOWEL

****************************************************************************/

bool PhonemMaker::IS_FR_VWL(char CH)
{
   bool result;

   switch(CH)
   {
      case 'E':
      case 'I':
      case 'Y':
      {
         // The character is a front vowel.
         result = true;
         break;
      } // case

      default:
      {
         // The character is not a front vowel.
         result = false;;
         break;
      } // case
   } // switch

   return (result);

} // IS_VWL

/*****************************************************************************


 IS_CST - RETURN FLAG DETERMINING IF ARGUMENT IS A CONSONANT

*****************************************************************************/

bool PhonemMaker::IS_CST(char CH)
{
   bool result;

   if (IS_ALPHA(CH) && (!IS_VWL(CH)))
   {
      result = true;
   } // if
   else
   {
      result = false;
   } // else

   return (result);

} // IS_CST

/****************************************************************************

 IS_VO_CST - RETURN FLAG DETERMINING IF ARGUMENT IS A VOICED CONSONANT

*****************************************************************************/

bool PhonemMaker::IS_VO_CST(char CH)
{
   bool result;

   switch(CH)
   {
      case 'B':
      case 'D':
      case 'G':
      case 'J':
      case 'L':
      case 'M':
      case 'N':
      case 'R':
      case 'V':
      case 'W':
      case 'Z':
      {
         // The character is a front vowel.
         result = true;
         break;
      } // case

      default:
      {
         // The character is not a front vowel.
         result = false;;
         break;
      } // case
   } // switch

   return (result);

} // IS_VO_CST


/*****************************************************************************

 RT_PS_VWL - MOVE INDEX RIGHT PAST VOWELS IN ENGLISH BUFFER

******************************************************************************/

void PhonemMaker::RT_PS_VWL(int& R_INDEX, bool& OCCURED)
{
   bool DONE;

  // Clear initially.
   OCCURED = false;

   if (R_INDEX < E_LEN)
   {
      // Clear initially.
      DONE = false;

      while (!DONE)
      {
         if (IS_VWL(E_BUFFER[R_INDEX]))
         {
            // Indicate occurance.
            OCCURED = true;

            // Reference next character.
            R_INDEX = R_INDEX + 1;
         } // if
         else
         {
            // Bail out of scan.
            DONE = true;
         } // else

         if (R_INDEX > E_LEN-1)
         {
            // Bail out if past buffer limits.
            DONE = true;
         } // if
      } // while
   } // if

   return;

} // RT_PS_VWL

/*****************************************************************************

 RT_PS_CST - MOVE INDEX RIGHT PAST CONSONANTS IN ENGLISH BUFFER

******************************************************************************/

void PhonemMaker::RT_PS_CST(int& R_INDEX, bool& OCCURED)
{
   bool DONE;

   if (R_INDEX < E_LEN)
   {
      // Set up for loop entry.
      DONE = false;

      while (!DONE)
      {
         if (!IS_CST(E_BUFFER[R_INDEX]))
         {
            // Bail out of scan.
            DONE = true;
         } // if
         else
         {
            // Reference next character.
            R_INDEX = R_INDEX + 1;
         } // else

         if (R_INDEX > E_LEN-1)
         {
            // Bail out if past buffer limits.
            DONE = true;
         } // if
      } // while
   } // if

   // Indicate outcome of occurrance.
   OCCURED = true;

   return;

} // RT_PS_CST


/*****************************************************************************

 LF_PS_VWL - MOVE INDEX OF ENGLISH BUFFER LEFT PAST VOWELS

******************************************************************************/

void PhonemMaker::LF_PS_VWL(int& R_INDEX, bool& OCCURED)
{
   bool DONE;

   // Clear initially.
   OCCURED = false;

   if (R_INDEX >= 0)
   {
      // Set up for loop entry.
      DONE = false;

      while (!DONE)
      {
         if (IS_VWL(E_BUFFER[R_INDEX]))
         {
            // Indicate occurance.
            OCCURED = true;

            // Reference character to the left.
            R_INDEX = R_INDEX - 1;
         } // if
         else
         {
            // Bail out of scan.
            DONE = true;
         } // else

         if (R_INDEX < 0)
         {
            // Bail out if past lower bounds.
            DONE = true;
         } // if
      } // while
   } // if

   return;

} // LF_PS_VWL


/****************************************************************************

 LF_PS_CST - MOVE INDEX OF ENGLISH BUFFER LEFT PAST CONSONANTS

*****************************************************************************/

void PhonemMaker::LF_PS_CST(int& R_INDEX, bool& OCCURED)
{
   bool DONE;

   if (R_INDEX >= 0)
   {
      // Set up for loop entry.
      DONE = false;

      while (!DONE)
      {
         if (!IS_CST(E_BUFFER[R_INDEX]))
         {
            // Bail out of scan.
            DONE = true;
         } // if
         else
         {
            // Reference character to the left.
            R_INDEX = R_INDEX - 1;
         } // else

         if (R_INDEX < 0)
         {
            // Bail out if past lower bounds.
            DONE = true;
         } // if
      } // while
   } // if

   // Indicate occurance.
   OCCURED = true;

   return;

} // LF_PS_CST

/**************************************************************************

 BLD_LIT_P - BUILD LITERAL PHONEM STRING IN ARRAY OF PHONEM STRING 

**************************************************************************/

void PhonemMaker::BLD_LIT_P(int RUL_INDX)
{
   int INDEX;
   int RES_INDX;
   int R_INDEX;
   bool DONE;

   // Point to beginning of result buffer.
   RES_INDX = 0;

   // Point past '=' sign.
   R_INDEX = RUL_INDX + 1;

   if (R_BUFFER[R_INDEX] != ';')
   {
      for (INDEX = 0; INDEX < NUM_PH_CH; INDEX++)
      {
         // Clear phonem string array.
         PH_STR[INDEX] = "";
      } // for

      do
      {
         // Set up for loop entry.
         DONE = false;

         while (!DONE)
         {
            if (R_BUFFER[R_INDEX] != ';')
            {
               PH_STR[RES_INDX] = PH_STR[RES_INDX] + R_BUFFER[R_INDEX];

               // Bump rule index.
               R_INDEX = R_INDEX + 1;

               if (R_BUFFER[R_INDEX] == ',')
               {
                  // bump index past comma.
                  R_INDEX = R_INDEX + 1;

                  // Exit comma scan.
                  DONE = true;
               } // if
            } // if
            else
            {
               // Exit rule scan.
               DONE = true;
            } // else
         } // while

         // Bump result index.
         RES_INDX = RES_INDX + 1;

      } while (R_BUFFER[R_INDEX] != ';');
   } // if

   // Store terminator.
   PH_STR[RES_INDX] = ';';

  return;

} // BLD_LIT_P

/***************************************************************************

// SC_RT_CTX - SCAN RIGHT CONTEXT OF A RULE

***************************************************************************/

void PhonemMaker::SC_RT_CTX(int RT_INDX, int& RUL_INDX, bool& FOUND)
{
   int R_INDEX;
   bool WI_RULES;
   bool EITHER;
   bool OCCURED;
   bool DONE;

   // Clear initially.
   WI_RULES = false;
   OCCURED = false;

   // Set up rule index.
   RUL_INDX = RT_INDX + 1;

   if (R_BUFFER[RUL_INDX] != '=')
   {
      if ((E_INDEX + REF_STR.length()) < E_LEN)
      {
         // Set up running index.
         R_INDEX = E_INDEX + REF_STR.length();

         // Set up for loop entry.
         DONE = false;

         while ((!DONE) && (R_BUFFER[RUL_INDX] != '='))
         {          
            switch (R_BUFFER[RUL_INDX])
            {
               case '!':
               {
                  WI_RULES = !IS_ALPHA(E_BUFFER[R_INDEX]);
                  break;
               } // case

               case '#':
               {
                  RT_PS_VWL(R_INDEX,OCCURED);
                  break;
               } // case

               case ':':
               {
                  RT_PS_CST(R_INDEX,OCCURED);
                  break;
               } // case


               case '+':
               {
                  WI_RULES = IS_FR_VWL(E_BUFFER[R_INDEX]);
                  break;
               } // case

               case '$':
               {
                  WI_RULES = IS_CST(E_BUFFER[R_INDEX]);
                  break;
               } // case

               case '.':
               {
                  WI_RULES = IS_VO_CST(E_BUFFER[R_INDEX]);
                  break;
               } // case

               default:
               {
                  WI_RULES = (R_BUFFER[RUL_INDX] == E_BUFFER[R_INDEX]);
                  break;
               } // case
            } // switch

            // Bump rule index.
            RUL_INDX = RUL_INDX + 1;

            if (WI_RULES)
            {
               // Bump running index.
               R_INDEX = R_INDEX + 1;
            } // if

            // Accept either case.
            EITHER = ((WI_RULES) || (OCCURED));

            // Clear flags.
            WI_RULES = false;
            OCCURED = false;

            if (R_INDEX > E_LEN)
            {
               // Exit scan loop..
               DONE = true;

               if (R_BUFFER[RUL_INDX] != '=')
               {
                  // Return false.
                  EITHER = false;
               } // if
            } // if

            if (!EITHER)
            {
               // Exit loop if no match for rule.
               DONE = true;
            } // if
         } // while

         // Return result.
         FOUND = EITHER;
      } // if
      else
      {
         FOUND = false;
      } // else
   } // if
   else
   {
      // Return true if at '=' sign.
      FOUND = true;
   } // else

   return;

} // SC_RT_CTX

/***************************************************************************

 SC_LF_CTX - SCAN LEFT CONTEXT OF A RULE IF IT EXISTS

****************************************************************************/

void PhonemMaker::SC_LF_CTX(int LEF_INDX, bool& FOUND)
{
   int R_INDEX;
   int RUL_INDX;
   bool EITHER;
   bool OCCURED;
   bool DONE;
   bool WI_RULES;

   // Clear initially.
   WI_RULES = false;
   OCCURED = false;

   if (E_INDEX > 0)
   {
      // Point to the left of parent.
      RUL_INDX = LEF_INDX - 1;

      // Set up running index in English buffer.
      R_INDEX = E_INDEX - 1;

      // Clear initially.
      DONE = false;

      while ((!DONE) && (RUL_INDX >= 0))
      {
         switch (R_BUFFER[RUL_INDX])
         {
            case '!':
            {
               WI_RULES = !IS_ALPHA(E_BUFFER[R_INDEX]);
               break;
            }  // case

            case '#':
            {
               LF_PS_VWL(R_INDEX,OCCURED);
               break;
            }  // case

            case ':':
            {
               LF_PS_CST(R_INDEX,OCCURED);
               break;
            }  // case

            case '+':
            {
               WI_RULES = IS_FR_VWL(E_BUFFER[R_INDEX]);
               break;
            }  // case

            case '$':
            {
               WI_RULES = IS_CST(E_BUFFER[R_INDEX]);
               break;
            }  // case

            case'.':
            {
               WI_RULES = IS_VO_CST(E_BUFFER[R_INDEX]);
            }  // case
               break;

            default:
            {
               WI_RULES = (R_BUFFER[RUL_INDX] == E_BUFFER[R_INDEX]);
               break;
            }  // case
         } // switch

         if (WI_RULES)
         {
            // Decrement running index.
            R_INDEX = R_INDEX - 1;
         } // if

         // Save either true result.
         EITHER = WI_RULES || OCCURED;

         // Clear flags.
         WI_RULES = false;
         OCCURED = false;

         // Decrement rule index.
         RUL_INDX = RUL_INDX - 1;

         if (R_INDEX < 0)
         {
            // Exit scan loop.
            DONE = true;

            if (RUL_INDX >= 0)
            {
               EITHER = false;
            } // if
         } // if

         if (!EITHER)
         {
            // Exit if scan failed.
            DONE = true;
         } // if
      } // while

      // Return result.
      FOUND = EITHER;
   } // if
   else
   {
      FOUND = false;
   } // else

   return;

} // SC_LF_CTX

/***************************************************************************

 CMP_REF_S - COMPARE REFERENCE STRING TO A SEGMENT IN THE ENGLISH STRING
             RETURN RESULT AS TRUE OR FALSE

****************************************************************************/

bool PhonemMaker::CMP_REF_S(void)
{
   bool result;
   int INDEX;
   int LIMIT;
   bool DONE;

   // Point to the beginning of the reference string.
   INDEX = 0;

   // Set upper limit.
   LIMIT = REF_STR.length() - 1;

   // Set up for loop entry.
   DONE = false;

   while (!DONE)
   {
//      if (REF_STR[INDEX] != (E_BUFFER[E_INDEX + INDEX - 1]))
      if (REF_STR[INDEX] != (E_BUFFER[E_INDEX + INDEX]))
      {
         DONE = true;
      } // if
      else
      {
         // Reference next item.
         INDEX = INDEX + 1;

         if (INDEX > LIMIT)
         {
            // Exit from loop.
            DONE = true;
         } // if
      } // else
   } // while

   if (INDEX > LIMIT)
   {
      result = true;
   } // if
   else
   {
      result = false;
   } // if

   return (result);

} // CMP_REF_S

/****************************************************************************

 BLD_REF_S - BUILD REFERENCE STRING FROM RULE BUFFER
             AND RETURN RIGHT PARENT INDEX 

****************************************************************************/

void PhonemMaker::BLD_REF_S(int LEF_INDX, int& RT_INDX)
{

   // Clear initially.
   REF_STR = "";

   // Bump past left parent.
   RT_INDX = LEF_INDX + 1;

   while (R_BUFFER[RT_INDX] != ')')
   {
      // Build string.
      REF_STR = REF_STR + R_BUFFER[RT_INDX];

      // Bump right parent index.
      RT_INDX = RT_INDX + 1;
   } // while

   return;

} // BLD_REF_S

/***************************************************************************

 FI_LF_PAR - SCAN RULE BUFFER UNTIL LEFT PARENT IS FOUND

***************************************************************************/

void PhonemMaker::FI_LF_PAR(int& LEF_INDX)
{

   // Point to beginning of buffer.
   LEF_INDX = 0;

   while (R_BUFFER[LEF_INDX] != '(')
   {
      // Bump left parent index.
      LEF_INDX = LEF_INDX + 1;
   } // while

   return;

} // FI_LF_PAR

/***************************************************************************

 SCAN - SCAN A RULE STRING AND RETURN RESULT WHETHER FOUND

***************************************************************************/

bool PhonemMaker::SCAN(void)
{
   bool result;
   int LEF_INDX;
   int RT_INDX;
   int RUL_INDX;
   bool WI_RULES;

   // Clear initially.
   WI_RULES = false;

   // Find left parent.
   FI_LF_PAR(LEF_INDX);

   // Build reference string, and return right parent.
   BLD_REF_S(LEF_INDX,RT_INDX);

   // Compare reference string to English.
   if (CMP_REF_S())
   {
      if (LEF_INDX > 0)
      {
         // Scan left context.
         SC_LF_CTX(LEF_INDX,WI_RULES);

         // If there is a left context.
         if (WI_RULES)
         {
            // Scan right context.
            SC_RT_CTX(RT_INDX,RUL_INDX,WI_RULES);
         } // if
      } // if
      else
      {
         // Scan right context.
         SC_RT_CTX(RT_INDX,RUL_INDX,WI_RULES);
      } // else
   } // if

   if (WI_RULES)
   {
      // Build literal phonem string.
      BLD_LIT_P(RUL_INDX);

      // Convert to phonem codes.
      PH_TO_COD();

      // Bump English index.
      E_INDEX = E_INDEX + REF_STR.length();
   } // if

   // Set return value based upon result.  Yes, it's redundant.
   result  = WI_RULES;

   return (result);

} // SCAN


/*****************************************************************************

 RUL_SRCH - SCAN RULES OF A LETTER OR NUMBER AND GENERATE PHONEMS

 RULE FORMAT - #(SED)!=Z,D;

               # - LEFT CONTEXT
               ( - LEFT CONTEX DELIMITER
               SED - STRING TO BE MATCHED
               ) - RIGHT CONTEXT DELIMITER
               ! - RIGHT CONTEX
               = - RIGHT CONTEX TERMINATOR
               Z - PHONEM CODE
               , - PHONEM SEPARATOR
               D - PHONEM CODE
               ; - RULE TERMINATOR

MEANING OF RULE SYMBOLS

              ! - INVOKES PROCEDURE THAT ATTEMPTS TO MATCH ANY NONALPHABETIC
                  CHARACTER IN ENGLISH INPUT STRING. IF MATCH FAILS, REPORTS
                  FAILURE. IF MATCH SUCCEEDS, MOVES RULE-STRIG POINTER BY
                  ONE CHARACTER IN RULE AND MOVES INPUT STRING POINTER BY
                  ONE CHARACTER IN THE ENGLISH STRING. THE DIRECTION OF
                  MOVEMENT IS DETERMINED AS:
                                1. FORWARD IF RIGHT CONTEXT IS BEING SCANNED
                                2. BACKWARD IF LEFT CONTEXT IS BEING SCANNED

             # - INVOKES PROCEDURE THAT ATTEMPTS TO MATCH ONE OR MORE
                 VOWELS (A,E,I,O,U, OR Y). IF MATCH FAILS, REPORTS FAILURE.
                 IF MATCH SUCCEEDS, MOVES RULE POINTER BY ONE CHARACTER IN
                 RULES AND MOVES STRING POINTER BY THE NUMBER OF VOWELS
                 MATCHED IN ENGLISH STRING. THE DIRECTION OF MOVEMENT IS
                 DETERMINED AS:
                               1. FORWARD IF RIGHT CONTEXT IS BEING SCANNED
                               2. BACKWARD IF LEFT CONTEXT IS BEING SCANNED

            : - INVOKES PROCEDURE THAT ATTEMPTS TO MATCH ZERO OR MORE
                CONSONANTS. MATCH ALWAYS SUCCEEDS. MOVES RULE POINTER BY
                ONE CHARACTER IN RULES AND MOVES STRING POINTER BY THE
                NUMBER OF CONSONANTS MATCHED IN ENGLISH INPUT STRING. THE
                DIRECTION OF MOVEMENT IS DETERMINED AS:
                              1. FORWARD IF RIGHT CONTEXT IS BEING SCANNED
                              2. BACKWARD IF LEFT CONTEXT IS BEING SCANNED

           + - INVOKES PROCEDURE THAT ATTEMPTS TO MATCH A FRONT VOWEL
               (E,I, OR Y). IF MATCH FAILS, REPORTS FAILURE. IF MATCH
               SUCCEEDS, MOVES RULE POINTER BY ONE CHARACTER IN RULES
               AND MOVES STRING POINTER BY ONE CHARACTER IN INPUT STRING.
               DIRECTION OF MOVEMENT IS DETERMINED AS:
                             1. FORWARD IF RIGHT CONTEXT IS BEING SCANNED
                             2. BACKWARD IF LEFT CONTEXT IS BEING SCANNED

          $ - INVOKES PROCEDURE THAT ATTEMPTS TO MATCH ONE CONSONANT. IF
              MATCH FAILS, REPORTS FAILURE. IF MATCH SUCCEEDS, MOVES RULE
              POINTER BY ONE CHARACTER IN RULES AND MOVES STRING POINTER
              BY ONE CHARACTER IN ENGLISH INPUT STRING. DIRECTION OF MOVEMENT
              IS DETERMINED AS:
                            1. FORWARD IF RIGHT CONTEXT IS BEING SCANNED
                            2. BACKWARD IF LEFT CONTEXT IS BEING SCANNED

         . - INVOKES PROCEDURE THAT ATTEMPTS TO MATCH A VOICED CONSONANT
             (B,D,G,J,L,M,N,R,V,W, OR Z). IF MATCH FAILS, REPORTS FAILURE.
             IF MATCH SUCCEEDS, MOVES RULE POINTER BY ONE CHARACTER IN RULES
             AND MOVES STRING POINTER BY ONE CHARACTER IN ENGLISH INPUT
             STRING. DIRECTION OF MOVEMENT IS DETERMINED AS:
                            1. FORWARD IF RIGHT CONTEXT IS BEING SCANNED
                            2. BACKWARD IF LEFT CONTEXT IS BEING SCANNED

 AFTER A MATCH IS FOUND THE INDEX INTO THE ENGLISH BUFFER IS INCREMENTED
 BY THE NUMBER OF CHARACTERS INSIDE OF THE PARENTHESIS OF THE RULE.

*****************************************************************************/

void PhonemMaker::RUL_SRCH(int BLK_OFF, int BLK_SIZ)
{
   int U_BOUNDS;
   int BLK_INDX;
   bool DONE;
   bool FOUND;

   // Set upper bounds.
   U_BOUNDS = BLK_OFF + BLK_SIZ-1;

   // Set lower bounds.
   BLK_INDX = BLK_OFF;

   // Set up for loop entry.
   DONE = false;

   while (!DONE)
   {
      // Get current rule.
      R_BUFFER = RUL_TBL[BLK_INDX];

      // Scan using current rule.
      FOUND = SCAN();

      // bump to next rule.
      BLK_INDX = BLK_INDX + 1;

      if ((BLK_INDX > U_BOUNDS) || FOUND)
      {
         // Exit scan.
         DONE = true;
      } // if
   } // while

   if (!FOUND)
   {
      // Reference the next English item.
      E_INDEX = E_INDEX + 1;
   } // if

   return;

} // RUL_SRCH

/*************************************************************************

 STR_T_COD - CONVERT LITERAL PHONEM STRING TO CODE

*************************************************************************/

void PhonemMaker::STR_T_COD(std::string PH_STR)
{
   int INDEX;
   bool MATCH;

fprintf(stderr,"STR_T_COD(), PH_STR: %s\n",PH_STR.c_str());

   // Point to begining of phonem table.
   INDEX = 0;

   // Clear initially.
   MATCH = false;

   while (!MATCH)
   {
      if (PH_STR == PHO_TBL[INDEX].ALPHA)
      {
         // Store phonem code.
         P_BUFFER[P_INDEX] = PHO_TBL[INDEX].CODE;

         // Exit loop.
         MATCH = true;
      } // if
      else
      {
         // Reference the next item.
         INDEX = INDEX + 1;
      } // else

      // Reference the next phonem in the buffer.
      P_INDEX = P_INDEX + 1;
   } // while

  return;

} // STR_T_COD

/****************************************************************************

 PH_TO_COD - CONVERT ARRAY OF PHONEM STRINGS INTO PHONEM CODES

****************************************************************************/

void PhonemMaker::PH_TO_COD(void)
{
   int INDEX;

   // Point to beginning of array.
   INDEX = 0;

   while (PH_STR[INDEX] != ";")
   {
      // Convert phonems to codes.
      STR_T_COD(PH_STR[INDEX]);

      // Reference next entry.
      INDEX = INDEX + 1;
   } // while

  return;

} // PH_TO_COD



