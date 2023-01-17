//**********************************************************************
// file name: PhonemMaker.h
//**********************************************************************

#ifndef _PHONEMMAKER_H_
#define _PHONEMMAKER_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
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

  void STR_T_COD(std::string PH_STR);
  void PH_TO_COD(void);
  void BLD_LIT_P(int RUL_INDX);
  void SC_RT_CTX(int RT_INDX, int& RUL_INDX, bool& FOUND);
  void SC_LF_CTX(int LEF_INDX, bool& FOUND);
  bool CMP_REF_S(void);
  void BLD_REF_S(int LEF_INDX, int& RT_INDX);
  void FI_LF_PAR(int& LEF_INDX);
  bool SCAN(void);
  void RUL_SRCH(int BLK_OFF, int BLK_SIZ);

  private:

  //*****************************************
  // Utility functions.
  //*****************************************
  bool IS_ALPHA(char PAR1);
  bool IS_VWL(char PAR1);
  bool IS_FR_VWL(char PAR1);
  bool IS_CST(char PAR1);
  bool IS_VO_CST(char PAR1);
  void RT_PS_VWL(int& PAR1, bool& PAR2);
  void LF_PS_VWL(int& PAR1, bool& PAR2);
  bool RT_PS_CST(int& PAR1, bool& PAR2);
  void LF_PS_CST(int& PAR1, bool& PAR2);

  //*****************************************
  // Attributes.
  //*****************************************
  char E_BUFFER[MAXLINE+1];
  char P_BUFFER[MAXPHO+1];
  std::string RUL_TBL[NUM_RULE+1];
  PhonemToCodeEntry PHO_TBL[NUM_PHON+1];

  std::string R_BUFFER;
  std::string REF_STR;
  std::string PH_STR[31];


  int E_LEN;
  int E_INDEX;
  int P_INDEX;

};

#endif // _PHONEMMAKER_H_
