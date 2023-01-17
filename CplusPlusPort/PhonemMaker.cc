//**********************************************************************
// file name: PhonemMaker.cc
//**********************************************************************

#include "PhonemMaker.h"
   
//*************************************************************************

// STR_T_COD - CONVERT LITERAL PHONEM STRING TO CODE

//*************************************************************************

void PhonemMaker::STR_T_COD(std::string PH_STR)
{
   int INDEX;
   bool MATCH;

   // Point to begining of phonem table.
   INDEX = 1;

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

//****************************************************************************

// PH_TO_COD - CONVERT ARRAY OF PHONEM STRINGS INTO PHONEM CODES
//****************************************************************************

void PhonemMaker::PH_TO_COD(void)
{
   int INDEX;

   // Point to beginning of array.
   INDEX = 1;

   while (PH_STR[INDEX] != ";")
   {
      // Convert phonems to codes.
      STR_T_COD(PH_STR[INDEX]);

      // Reference next entry.
      INDEX = INDEX+1;
   } // while

  return;

} // PH_TO_COD

//**************************************************************************

// BLD_LIT_P - BUILD LITERAL PHONEM STRING IN ARRAY OF PHONEM STRING 

//*************************************************************************

void PhonemMaker::BLD_LIT_P(int RUL_INDX)
{
   int INDEX;
   int RES_INDX;
   int R_INDEX;
   bool DONE;

   // Point to beginning of result buffer.
   RES_INDX = 1;

   // Point past '=' sign.
   R_INDEX = RUL_INDX + 1;

   if (R_BUFFER[R_INDEX] != ';')
   {
      for (INDEX = 1; INDEX <= NUM_PH_CH; INDEX++)
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

               if (R_BUFFER[R_INDEX] = ',')
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

//***************************************************************************

// SC_RT_CTX - SCAN RIGHT CONTEXT OF A RULE

// **************************************************************************

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
      if ((E_INDEX + REF_STR.length()) <= E_LEN)
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

//***************************************************************************

// SC_LF_CTX - SCAN LEFT CONTEXT OF A RULE IF IT EXISTS

//***************************************************************************

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

   if (E_INDEX > 1)
   {
      // Point to the left of parent.
      RUL_INDX = LEF_INDX - 1;

      // Set up running index in English buffer.
      R_INDEX = E_INDEX - 1;

      // Clear initially.
      DONE = false;

      while ((!DONE) && (RUL_INDX >= 1))
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

         if (R_INDEX < 1)
         {
            // Exit scan loop.
            DONE = true;

            if (RUL_INDX >= 1)
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

//***************************************************************************

// CMP_REF_S - COMPARE REFERENCE STRING TO A SEGMENT IN THE ENGLISH STRING
//             RETURN RESULT AS TRUE OR FALSE

//***************************************************************************

bool PhonemMaker::CMP_REF_S(void)
{
   bool result;
   int INDEX;
   int LIMIT;
   bool DONE;

   // Point to the beginning of the reference string.
   INDEX = 1;

   // Set upper limit.
   LIMIT = REF_STR.length();

   // Set up for loop entry.
   DONE = false;

   while (!DONE)
   {
      if (REF_STR[INDEX] != (E_BUFFER[E_INDEX + INDEX - 1]))
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

//****************************************************************************

// BLD_REF_S - BUILD REFERENCE STRING FROM RULE BUFFER
//             AND RETURN RIGHT PARENT INDEX 

//****************************************************************************

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

//***************************************************************************

// FI_LF_PAR - SCAN RULE BUFFER UNTIL LEFT PARENT IS FOUND

//***************************************************************************

void PhonemMaker::FI_LF_PAR(int& LEF_INDX)
{

   // Point to beginning of buffer.
   LEF_INDX = 1;

   while (R_BUFFER[LEF_INDX] != '(')
   {
      // Bump left parent index.
      LEF_INDX = LEF_INDX + 1;
   } // while

   return;

} // FI_LF_PAR

#if 0

{****************************************************************************

 SCAN - SCAN A RULE STRING AND RETURN RESULT WHETHER FOUND

****************************************************************************}

FUNCTION SCAN:BOOLEAN;

VAR
   LEF_INDX,RT_INDX,RUL_INDX:INTEGER;
   WI_RULES:BOOLEAN;

BEGIN (* FUNCTION *)
   WI_RULES:=FALSE;             (* CLEAR INITIALLY *)
   FI_LF_PAR(LEF_INDX);         (* FIND INDEX OF LEFT PARENT *)
   BLD_REF_S(LEF_INDX,RT_INDX); (* BUILD REF STRING AND RETURN RIGHT PARENT *)
   IF CMP_REF_S THEN BEGIN      (* COMPARE REFERENCE STRING TO ENGLISH *)
      IF LEF_INDX > 1 THEN BEGIN
         SC_LF_CTX(LEF_INDX,WI_RULES); (* SCAN LEFT CONTEXT *)
         IF WI_RULES THEN       (* IF THERE IS A LEFT CONTEXT *)
            SC_RT_CTX(RT_INDX,RUL_INDX,WI_RULES) (* SCAN RIGHT CONTEXT *)
      END ELSE
         SC_RT_CTX(RT_INDX,RUL_INDX,WI_RULES)    (* SCAN RIGHT CONTEXT *)
   END; (* IF *)
   IF WI_RULES THEN BEGIN
      BLD_LIT_P(RUL_INDX);    (* BUILD LITERAL PHONEM STRING *)
      PH_TO_COD;              (* CONVERT TO PHONEM CODES *)
      E_INDEX:=E_INDEX+LENGTH(REF_STR)  (* BUMP ENGLISH INDEX *)
   END; (* IF *)
   SCAN:=WI_RULES             (* RETURN VALUE *)
END; (* FUNCTION *)

(*$E+*)
{*****************************************************************************

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

*****************************************************************************}

PROCEDURE RUL_SRCH(BLK_OFF,BLK_SIZ:INTEGER);

VAR
   U_BOUNDS,BLK_INDX:INTEGER;
   DONE,FOUND:BOOLEAN;

BEGIN (* PROCEDURE *)
   U_BOUNDS:=BLK_OFF+BLK_SIZ-1;    (* SET UPPER BOUNDS *)
   BLK_INDX:=BLK_OFF;              (* SET LOWER BOUNDS *)
   DONE:=FALSE;                    (* CLEAR INITIALLY *)
   WHILE NOT DONE DO BEGIN
      R_BUFFER:=RUL_TBL[BLK_INDX]; (* GET CURRENT RULE *)
      FOUND:=SCAN;                 (* SCAN USING CURRENT RULE *)
      BLK_INDX:=BLK_INDX+1;        (* BUMP TO NEXT RULE *)
      IF (BLK_INDX > U_BOUNDS) OR (FOUND) THEN
         DONE:=TRUE                (* EXIT SCAN *)
   END; (* WHILE *)
   IF NOT FOUND THEN
      E_INDEX:=E_INDEX+1           (* BUMP INDEX *)
END; (* PROCEDURE *)

#endif
