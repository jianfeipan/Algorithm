/*
you have a random generator random(5) who can generate with equal propability [1,2,3,4,5]
how do you use this to make a random(7) ???

how to make random(10) with random(7) ??

idea is :
if we have a random(10) we can easily get random(9) by :

do{
  x = random(10)
}while(x>9);//event exclude 10, it don't change the fact that from 1-9 we are still euqal probability

return x; 
*/
int random7()
{
  int x = 0;
  do{
    x = (random(5) - 1)* 5 + random(5) // it's like binary, we have a five-nary number [1-25]
  }while(x>21);//filter >21 numbers instead of >7 make it easier to get out, since 21 is 7*n, so we can do a module to get the equal pobability
  
  return X%7 + 1;
}
