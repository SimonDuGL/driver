function Result = elementOfMatrxCell2Str(cell_content)
Str = class(cell_content);
Result = cell_content;
switch Str
    case 'char'
        %skip
    otherwise
        Result = num2str(cell_content);
end