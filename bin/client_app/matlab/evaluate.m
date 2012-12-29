function [output] = evaluate(algorithmOutput, origin, trueValue)
%msgbox(int2str(size(algorithmOutput)))
%msgbox(int2str(size(origin)))
%msgbox(algorithmOutput(1))
%msgbox(algorithmOutput(2))
%msgbox(origin(1))
%msgbox(origin(2))
imShow(algorithmOutput{1});
imShow(origin{1});
f = load(trueValue);
msgbox(int2str(f(1)));
output = [0.8];
