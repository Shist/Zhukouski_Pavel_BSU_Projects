#include <stdlib.h> 
#include <math.h> 
#include <stdio.h> 

int main() 
{ 
const double Rad = 57.295779513; 
double A = 0.0, B = 0.0, C = 0.0, k1 = 0.0, k2 = 0.0, k3 = 0.0; 
printf("Enter the value of the side A: "); 
scanf("%lf", &A); 
printf("Enter the value of the side B: "); 
scanf("%lf", &B); 
printf("Enter the value of the side C: "); 
scanf("%lf", &C); 
if ((A + B <= C) || (A + C <= B) || (B + C <= A)) 
printf("There are no cush a trinagle!!!"); 
else 
{ 
k1 = Rad*acos(((B*B) + (C*C) - (A*A)) / (2.0*B*C)); 
printf("The value of the angle opossite the side A: %lf\n", k1); 
k2 = Rad*acos(((A*A) + (C*C) - (B*B)) / (2.0*A*C)); 
printf("The value of the angle opossite the side B: %lf\n", k2); 
k3 = Rad*acos(((A*A) + (B*B) - (C*C)) / (2.0*A*B)); 
printf("The value of the angle opossite the side C: %lf\n", k3); 
} 
return 0; 
}