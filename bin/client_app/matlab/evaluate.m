function [output] = evaluate(algorithmOutput, origin)
msgbox(int2str(size(algorithmOutput)))
msgbox(int2str(size(origin)))
msgbox(algorithmOutput(1))
msgbox(algorithmOutput(2))
msgbox(origin(1))
msgbox(origin(2))
output = [1 2 3 4];