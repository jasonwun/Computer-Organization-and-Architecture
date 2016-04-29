#include <stdio.h>


unsigned getvalue(reg) 
{
  return reg | reg << (2*4) | reg << (4*4) | reg << (6*4);
}

unsigned update( unsigned nPC, unsigned PC, unsigned IR, unsigned PSR)
{
  unsigned op, op2, op3, rs1, rs2, cond, disp22, simm13, disp30, result, i;

  unsigned N,Z,V,C;
  
  op = IR >> 30;

  op2 = (IR >> 22) & 0x7;

  op3 = (IR >> 19) & 0x3f;

  rs1 = (IR >> 14) & 0x1f;

  rs2 = IR & 0x1f;

  cond = (IR >> 25) & 0xf;

  disp22 = (IR << 10) >> 10;

  simm13 = (IR << 19) >> 19;

  disp30 = (IR << 2) >>2;

  N = PSR << 8 >> 31;

  Z = PSR << 9 >> 31;

  V = PSR << 10 >> 31;

  C = PSR << 11 >> 31;

  i = (IR << 18 >> 31) & 0x1;
  
  

  if(op == 1)
    {
      result = disp30 * 4 + PC;                  //Call Instruction//
    }

  else if(op == 0)
    {
      if(op2 == 4)
	{
	  result = nPC + 4; 	                //SETHI// 
	}
      else if(op2 == 2)                         //Branch Instruction//
	{
	  if(cond == 7 && V)                    //BVS//
	    {
	      result = PC + disp22 * 4;
	    }
	  else if(cond == 15 && ~V)             //BVC//
	    {
	      result = PC + disp22 * 4;
	    }
	  else if(cond == 6 && N)               //BNEG//
	    {
	      result = PC + disp22 *4;
	    }

	  else if(cond == 14 && ~N)             //BPOS//
	    {
	      result = PC + disp22 *4;
	    }

	  else if(cond == 5 && C)               //BCS//
	    {
	      result = PC + disp22 * 4;
	    }

	  else if(cond == 13 && ~C)             //BCC//
	    {
	      result = PC + disp22 * 4;
	    }

	  else if(cond == 4 && (C|Z))           //BLEU//
	    {
	      result = PC + disp22 * 4;
	    }
	  else if(cond == 12 && ~(C|Z))         //BGU//
	    {
	      result = PC + disp22 * 4;
	    }
	  else if(cond == 3 && (N ^ V))         //BL//
	    {
	      result = PC + disp22 * 4;
	    }

	  else if(cond == 11 && ~(N ^ V))       //BGE//
	    {
	      result = PC + disp22 * 4;
	    }

	  else if(cond == 2 && (Z | (N ^ V)))   //BLE//
	    {
	      result = PC + disp22 * 4;
	    }

	  else if(cond == 10 && ~(Z|(N^V)))     //BG//
	    {
	      result = PC + disp22*4;
	    }

	  else if(cond == 1 && Z)               //BE//
	    {
	      result = PC + disp22 * 4;
	    }

	  else if(cond == 9 && ~Z)              //BNE//
	    {
	      result = PC + disp22 * 4;
	    }

	  else if(cond == 8)                    //BN & BA//
	    {
	      result = PC + disp22 * 4;
	    }

	  else
	    {
	      result = nPC +4;
	    }
	}
    }
  else if(op == 2 || op ==3)                   //JMPL instruction//
    {
      if(i == 0)                               //rs1 & rs2//
	{
	  result = getvalue(rs1) + getvalue(rs2);
	}


      else if(i == 1)                          //rs1 & simm13//
	{
	  
	  
	  unsigned simm13_sign = simm13 >> 12;
	  
	  if(simm13_sign == 0)
	    { 
	      result = getvalue(rs1) + simm13 ;
	    }
	  else if(simm13_sign == 1)
	    { 
	      signed signed_simm13 = simm13 | 0xffffe000;
	      result = getvalue(rs1) + signed_simm13;
	    }
	}
    }
  
      

  nPC = result;
  return result;
}

