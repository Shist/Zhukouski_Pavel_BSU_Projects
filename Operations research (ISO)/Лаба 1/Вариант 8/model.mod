param parameters; # number of parameters
param product; # number of products
param cost{i in 1..parameters, j in 1..product};
param supply{i in 1..parameters}; #supply at parameter i
param price{i in 1..product}; #price at product j
var amount{j in 1..product};
maximize Cost:
sum{j in 1..product} price[j]*amount[j];
subject to Supply {i in 1..parameters}:
sum{j in 1..product} amount[j]*cost[i, j]  <= supply[i];
subject to positive{j in 1..product}:
amount[j]>=0;

