#include "/user/cse320/Projects/project06.support.h"
#include <stdio.h>



float mult( float a, float b)
{
  union sp_item num_1, num_2, num_3;
  
  unsigned true_exp_1, true_exp_2;

  unsigned fra_1, fra_2;
  unsigned long long int sign_1, sign_2;
  unsigned sig_1, sig_2;
  unsigned long long result_sig;
  unsigned result_sign;
  unsigned result_expo;

  
  
  num_1.frep = a;
  num_2.frep = b;
  

  //getsign
  sign_1 = num_1.irep >> 30;
  sign_1 = sign_1 <<31;
  sign_2 = num_2.irep >>30;
  sign_2 = sign_2 <<31;
  
  //get exponnet
  true_exp_1 = (num_1.irep >> 23) - 0x7f;
  true_exp_2 = (num_2.irep >> 23) - 0x7f;

  //get fraction
  fra_1 = (num_1.irep << 9);
  fra_1 = (fra_1 >> 9);
  fra_2 = (num_2.irep << 9);
  fra_2 = (fra_2 >> 9);
  
  
  //get significand
  sig_1 = fra_1 | 0x800000;
  sig_2 = fra_2 | 0x800000;
  
  //calculation
  result_sig = (unsigned long long)sig_1 *  (unsigned long long)sig_2;
  result_sig = (result_sig << 23);
  
  result_expo = true_exp_1 + true_exp_2;
  result_expo = result_expo + 0x7f;
  result_expo = (result_expo << 23);
  result_sign = sign_1 ^ sign_2;

    //Normalize
  if((result_sig>>46)==2||(result_sig>>46)==3)
    {
      result_sig = (result_sig>>1);
       result_expo +=1;
    }

  result_sig = (result_sig << 18) >> 41;
  
  
  //Combine
  num_3.frep = result_sign|result_expo|result_sig;


  
  //return the float in hex
  return num_3.irep;
  
}


