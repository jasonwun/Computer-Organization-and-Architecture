
/******************************************************************************
  Project #4 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal);


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal Init, Clock, w, x, y, z, W,X,Y,Z;
  

  Pulser ((SD("1a"), "i - Init"), Init, 'i',1000);
  Pulser ((SD("2a"), "c - Clk" ), Clock, 'c', 1000);   

  Dff ((SD("2c"), "Dff3"), (Zero, Z, Clock, Init), z);
  Dff ((SD("3c"), "Dff2"), (Init, Y, Clock, Zero), y);
  Dff ((SD("4c"), "Dff1"), (Zero, X, Clock, Init), x);
  Dff ((SD("5c"), "Dff0"), (Init, W, Clock, Zero), w);

  circuits( SD("6c-9c"), Init, Clock, w, x, y, z, W,X,Y,Z);

  Probe( (SD("1g"),"W"), w);
  Probe( (SD("2g"),"X"), x);
  Probe( (SD("3g"),"Y"), y);
  Probe( (SD("4g"),"Z"), z);

}


/******************************************************************************
  Function "circuits" -- implementation of student circuits
******************************************************************************/

void circuits( SD sd, Signal Init, Signal Clock, 
	       Signal w, Signal x, Signal y, Signal z, Signal W, Signal X, Signal Y, Signal Z )
{
  Module( (sd, "circuits"), (Init, Clock), (w, x, y, z, W,X,Y,Z) );
  
  Signal notw,notx,noty,notz,and1,and2,and3,and4,and5,or1,or2,or3,or4,and6,and7;
  
  
  
  // Replace with declarations for any auxiliary Signala
  Not((SD(sd,"1a")),w,notw);
  Not((SD(sd,"2a")),x,notx);
  Not((SD(sd,"3a")),y,noty);
  Not((SD(sd,"4a")),z,notz);
  
  And((SD(sd,"1b")),(noty,notz),and1);
  And((SD(sd,"2b")),(z,w),and2);
  And((SD(sd,"3b")),(x,z),and3);
  And((SD(sd,"4b")),(w,noty),and4);
  

  Or((SD(sd,"1c")),(notw,and1),W);
  Or((SD(sd,"2c")),(y,and2),X);
  Or((SD(sd,"3c")),and3,Y);
  Or((SD(sd,"4c")),and4,Z);

  
      
  // Replace with circuit implementation (Not, And, Or gates)
  
}

