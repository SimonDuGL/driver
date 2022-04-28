%temp = propertyJson(cell_content); result = excel2json(temp);
%Property = propertyJson(cell); Geometry = geometryPolygonJson(matric); result = excel2json(Geometry, Property);
%{
Property = propertyJson(cell);
Geometry = geometryPolygonJson(matric);
result = excel2json(Geometry, Property);
%}
function Result = propertyJson(cell_content)
Result = {};

for i = 2 : size(cell_content,1) %first row is title
    for j = 1 : size(cell_content,2)
        %preact
        if isequal(cell_content{i,j},'')%isnan(cell_content{i,j})
            cell_content{i,j} = 'None';
        else %~isnan
        end
        Pair = keyValuePair(cell_content{1,j}, cell_content{i,j});
        
        if isfirst(j)
            Result{i - 1,1} = ['"properties": {', Pair, ', '];
            %add "properties": { before the Pair
            %add ,  after the Pair
            
        else %~isfirst
            if j == size(cell_content,2) %islast()
                Result{i - 1,1} = [Result{i - 1,1}, Pair, '}'];
                % add } after the Pair
            else% normal
                Result{i - 1,1} = [Result{i - 1,1}, Pair, ', '];
                %add ,  after the Pair
            end
            
        end
        
        
        
        
    end
end

function Str = keyValuePair(Key, Value)
%initial
Key = elementOfMatrxCell2Str(Key);

%key
Str = ['"', Key, '": '];
%add " before the Key
%add ":  after the Key

%value
Str_class = class(Value);
if isequal(Str_class(1:3),'int')%isInt
    Value = num2str(Value);
    Str = [Str, Value];
else %~isInt
    if isequal(Str_class,'double')
        Value = int64(Value);
        Value = num2str(Value);
        Str = [Str, Value];
    else %~isDouble
        if ~isequal(Value,'None')
        %could be boolean or %isChar
        Str = [Str, '"', Value, '"'];
        %add " before the Value
        %add ",  after the Value
        else %isequal(Value,'None')
        Str = [Str, Value];
        end
    end
end


