
/******************************************************************************
  Project #3 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, 
  Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal w, x, y, z, Present, a, b, c, d, e, f, g;
  Signal Strobe(1);
  Signal ResetA(1);
  Signal ResetB(1);
  

  Pulser ((SD("1a"), "r -- Reset counter"), ResetA, 'r',10000);
  Pulser ((SD("2a"), "s -- Strobe counter"), Strobe, 's', 10000);

  Not(SD("1b"), ResetA, ResetB); 

  Counter((SD("1c-2c"), "4-bit counter"), (ResetB, Strobe), (w,x,y,z));

 circuits( SD("1d-4d"), w, x, y, z, Present, a, b, c, d, e, f, g);

  Probe(( SD("1g"),"Present"), Present );
  Probe( (SD("2f-2h"),"a"), a );
  Probe( (SD("3f-4f"),"f"), f );
  Probe( (SD("3h-4h"),"b"), b );  
  Probe( (SD("5f-5h"),"g"), g );
  Probe( (SD("6f-7f"),"e"), e);
  Probe( (SD("6h-7h"),"c"), c);
  Probe( (SD("8f-8h"),"d"), d); 
}


/******************************************************************************
  Function "circuits" -- implementation of student circuits

  Do not alter the interface -- function "circuits" must receive four
  signals as inputs and return eight signals as outputs.
******************************************************************************/

void circuits( SD sd, Signal w, Signal x, Signal y, Signal z, 
  Signal Present, Signal a, Signal b, Signal c, Signal d, Signal e,
  Signal f, Signal g )    
{
  Module( (sd, "circuits"), (w, x, y, z), (Present, a, b, c, d, e, f, g) );


  Signal notz, notw,notx, noty;
  Signal and1, and2, and3, and4, and5, and6, and7, and8, and9, and10, and11,and12, and13,and14;

  Not(SD(sd, "e1-f8"), z, notz);
  Not(SD(sd, "g1-h8"), w, notw);
  Not(SD(sd, "i1-j8"), x, notx); 
  Not(SD(sd, "k1-l8"), y, noty); 

  And(SD(sd,"ab-be"), (y, z, notw), and1);
  And(SD(sd,"cb-de"), (noty, notz, x, notw), and2);
  And(SD(sd,"eb-fe"), (w, notx, noty), and3);
  And(SD(sd,"gb-he"), (notw, x), and4);
  And(SD(sd,"ib-je"), (w,notx,noty), and5);
  And(SD(sd,"kb-le"), (y,z,notw), and6);
  And(SD(sd,"mb-ne"), (w,notx,noty), and7);
  And(SD(sd,"ob-pe"), (noty,notz,notw,x), and8);
  And(SD(sd,"qb-re"), (y,z,notw,x), and9);
  And(SD(sd,"sb-te"), (noty,notz,w,notx), and10);
  And(SD(sd,"ub-ve"), (notw, x,y,z), and11);
  And(SD(sd,"wb-xe"), (w,notx,noty,z),and12);


  Or(SD(sd,"bg-cl"), (and1, and2, and3), Present);
  Or(SD(sd,"dg-el"), (and4,and5),a);
  Or(SD(sd,"fg-gl"), (and6,and7),b); 
  Or(SD(sd,"hg-il"), (One, One),c );
  Or(SD(sd,"jg-kl"), (and8,and9,and10),d);
  Or(SD(sd,"lg-ml"), (and11,and12),e);
  Or(SD(sd,"og-pl"), (One, One), f);
  Or(SD(sd,"sg-tl"), (One, One), g); 

 
}

