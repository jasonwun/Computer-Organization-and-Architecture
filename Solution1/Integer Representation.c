

int decode( int a, const char b[], char c[] )
{
  //field
  int PreConverted = a;
  int base = 0;
  int temp = 0;
  int index = 0;
  int tmpint = 0;
  char D[80];
  char tmpchar;

  //Set base that convert into
  if(b[0]=='b'&&b[1]=='i'&&b[2]=='n')
    base = 2;
  else if(b[0]=='h'&&b[1]=='e'&&b[2]=='x')
    base = 16;
  else if(b[0]=='o'&&b[1]=='c'&&b[2]=='t')
    base = 8;
  else if(b[0]=='d'&&b[1]=='e'&&b[2]=='c')
    base = 10;
  else
    return 0;

  //If the number is positive
  if(a>0)
    {
      //first convert the number into char and assign into a temp array
      while(PreConverted !=0)
	{
	  temp = PreConverted % base;
	  if(temp < 10)
	    temp =temp + 48;
	  else
	    temp = temp + 55;
	  D[index] = temp;
	  PreConverted = PreConverted / base;
	  index++;
	}
      index--;
      //reverse the temp array up side down and assign the value to the output
      //array
      while(index>=0)
	{
	  tmpchar = D[index];
	  c[tmpint] = tmpchar;
	  index--;
	  tmpint++;
	}
      c[tmpint] = '\0';
      
      temp = 0;
      return 1;
      
    }
  //if the number is negative
  else if(a<0)
    {
      PreConverted = PreConverted * -1;
      c[tmpint] = '-';//add a negative sign before the number
      tmpint++;

      //the rest is the same thing as above
      while(PreConverted !=0)
	{
	  temp = PreConverted % base;
	  if(temp<10)
	    temp = temp+48;
	  else
	    temp = temp + 55;
	  D[index] = temp;
	  PreConverted = PreConverted / base;
	  index++;
	}
      
      index--;
      while(index>=0)
	{
	  tmpchar = D[index];
	  c[tmpint] = tmpchar;
	  index--;
	  tmpint++;
	}
       temp = 0;
       c[tmpint] = '\0';
       return 1;
    }
  //if it is zero
  else if(a ==0)
    {
      
      c[index] = '0';
      
      return 1;
    }

}





