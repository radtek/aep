function [f1 f2 f3 f4 f5] = SubFunc(a, b, c1, c2, c3, c4, c5)
f1 = a - b - c1(1, 1);
f2 = a - b - c2(1, 1);
f3 = a - b - c3(1, 1);
f4 = a - b - c4(1, 1);
f5 = a - b - c5(1, 1);