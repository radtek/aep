function [f1 f2 f3 f4 f5] = transfer(a, b, c1, c2, c3, c4, c5)
f1 = b;
f2 = 0;
f3 = 0;
f4 = 0;
f5 = zeros(1, 2);
f5(1, 1) = 10;
f5(1, 2) = 10;
