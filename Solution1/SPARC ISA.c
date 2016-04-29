
#include <stdio.h>

#include "/user/cse320/Projects/project07.hardware.h"
#include "/user/cse320/Projects/project07.support.h"


void execute()
{
  //Filed
  signal5 rd, rs1, rs2;
  signal32 RS1, RS2, RD;
  signal2 op;
  signal3 op2;
  signal22 imm22;
  signal6 op3;
  signal1 i,f,c;
  signal13 simm13;


  //Bits movement
  op = IR >> 30;
  rd = (IR << 2) >> 27;
  op3 = (IR << 7) >> 26;
  op2 = (IR << 7) >> 29;
  i = (IR << 18) >> 31;
  rs1 = (IR << 13) >> 27;
  c = (PSR << 11) >> 31;
  rs2 = (IR << 27) >> 27;
  simm13 = (IR << 19)>>19;
  f = (IR <<19)>>31;


  //This one not my code
  read_reg_file( rs1, rs2, &RS1, &RS2 );


  //if op is zero,SETHI
  if(op == 0)
    {
      
      imm22 = (IR << 10);

      if(op == 0 && op2 == 4)
	{
	  rd = imm22;
	}  
    }
  //if op is two 
  else if(op ==2 || op==3)
    {

      //Integer operation in integer
      if(i==0)
	{
	  
	  if(op3 == 0)
	    RD = RS1+RS2;
	  else if(op3 == 1)
	    RD = RS1 & RS2;
	  else if(op3 == 2)
	    RD = RS1 | RS2;
	  else if(op3 == 3)
	    RD = RS1 ^ RS2;
	  else if(op3 == 4)
	    RD = RS1 - RS2;
	  else if(op3 == 5)
	    RD = RS1 & ~RS2;
	  else if(op3 == 6)
	    RD = RS1 | ~RS2;
	  else if(op3 == 7)
	    RD = RS1 ^ ~RS2;
	  else if(op3 == 8)
	    RD = RS1 + RS2 + c;
	  else if(op3 == 12)
	    RD = RS1 - RS2 - c;
	}

      //Integer operation : one operand and immediate value
      else if(i==1)
	{
	  //If the simm13 is negative
	  if(f==1)
	    simm13 = simm13 * 0xffffe000;
	  if(op3 == 0)
	    RD = RS1+ simm13;
	  else if(op3 == 1)
	    RD = RS1 & simm13;
	  else if(op3 == 2)
	    RD = RS1 | simm13;
	  else if(op3 == 3)
	    RD = RS1 ^ simm13;
	  else if(op3 == 4)
	    RD = RS1 - simm13;
	  else if(op3 == 5)
	    RD = RS1 & ~simm13;
	  else if(op3 == 6)
	    RD = RS1 | ~simm13;
	  else if(op3 == 7)
	    RD = RS1 ^ ~simm13;
	  else if(op3 == 8)
	    RD = RS1 + simm13 + c;
	  else if(op3 == 12)
	    RD = RS1 - simm13 - c;
	} 
    }
  
  write_reg_file( rd, RD );
};

