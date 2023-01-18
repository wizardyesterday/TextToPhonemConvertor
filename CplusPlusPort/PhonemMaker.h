//**********************************************************************
// file name: PhonemMaker.h
//**********************************************************************

#ifndef _PHONEMMAKER_H_
#define _PHONEMMAKER_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <ctype.h>
#include <string>

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// Buffer size defines.
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#define MAXLINE (80)    // Maximum length of input buffer.
#define MAXPHO (1000)   // Size of phonem buffer.
#define NUM_PHON (64)   // Number of phonems
#define NUM_RULE (100)  // Number of rules allowed.
#define NUM_PH_CH (30)  // Maximum number of phonem characters.

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

struct PhonemToCodeEntry
{
  std::string ALPHA;
  uint8_t CODE;
};

class PhonemMaker
{
  public:

  PhonemMaker(void);
  ~PhonemMaker(void);

  void acceptEnglishText(std::string& INBUF, uint8_t*& phonemBuffer,
                         uint32_t& phonemCount);


  private:

  //*****************************************
  // Utility functions.
  //*****************************************
  bool IS_ALPHA(char CH);
  bool IS_VWL(char CH);
  bool IS_FR_VWL(char CH);
  bool IS_CST(char CH);
  bool IS_VO_CST(char CH);
  void RT_PS_VWL(int& R_INDEX, bool& OCCURED);
  void LF_PS_VWL(int& R_INDEX, bool& OCCURED);
  void RT_PS_CST(int& R_INDEX, bool& OCCURED);
  void LF_PS_CST(int& R_INDEX, bool& OCCURED);

  void BLD_LIT_P(int RUL_INDX);
  void SC_RT_CTX(int RT_INDX, int& RUL_INDX, bool& FOUND);
  void SC_LF_CTX(int LEF_INDX, bool& FOUND);
  bool CMP_REF_S(void);
  void BLD_REF_S(int LEF_INDX, int& RT_INDX);
  void FI_LF_PAR(int& LEF_INDX);
  bool SCAN(void);
  void RUL_SRCH(int BLK_OFF, int BLK_SIZ);

  void STR_T_COD(std::string PH_STR);
  void PH_TO_COD(void);

  //*****************************************
  // Attributes.
  //*****************************************
  // English uppercase English text buffer.
  char E_BUFFER[MAXLINE+1];

  // Buffer used for phonem storage.
  uint8_t P_BUFFER[MAXPHO+1];

  // This table is used to map textual phonems to binary values.
  PhonemToCodeEntry PHO_TBL[NUM_PHON+1];

  // Storage for the current rule.
  std::string R_BUFFER;

  // This is used for string comparison with the English buffer.
  std::string REF_STR;

  // Storage for a phonem string to be evaluated.
  std::string PH_STR[31];

  // Number of entries in the English buffer.
  int E_LEN;

  // Next available location in the English buffer.
  int E_INDEX;

  // Next available location in the phonem buffer.
  int P_INDEX;
};

#endif // _PHONEMMAKER_H_
