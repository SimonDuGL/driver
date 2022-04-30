%temp = geometryPolygonJson(contiguoususa003); result = excel2json(temp);
%{
Property = propertyJson(cell);
Geometry = geometryPolygonJson(matric);
result = excel2json(Geometry, Property);
%}
function cell1_content = geometryPolygonJson(contiguoususa003)
cell1_content = {};
for i = 1:size(contiguoususa003,1)
    Continue = 1;
    j = 1;
    while Continue
        if isnan(contiguoususa003(i,j))
            Continue = 0;
            
        else %~isnan
            if isfirst(j) %besides, is odd
                cell1_content{i,1} = ['"geometry": {"type": "Polygon", "coordinates": [[[', num2str(contiguoususa003(i,j)), ','];
                %add "geometry": {"type": "Polygon", "coordinates": [[[ before the number
                
            else %~isfirst
                % normal or islast
                if isodd(j) %normal%odd
                    cell1_content{i,1} = [cell1_content{i,1}, num2str(contiguoususa003(i,j)), ','];
                    %add , after the number
                else %iseven
                    if islast(contiguoususa003(i,j:size(contiguoususa003,2)))%islast%iseven %besides, even
                        cell1_content{i,1} = [cell1_content{i,1}, num2str(contiguoususa003(i,j)), ']]]}'];
                        %add ]]]} after the number
                        Continue = 0;
                    else %~islast(normal)%iseven
                        cell1_content{i,1} = [cell1_content{i,1}, num2str(contiguoususa003(i,j)), '], ['];
                        %add ], [ after the number
                    end
                end
                
            end
        end
        
        if j >= size(contiguoususa003,2)
            Continue = 0;
        else % j <
            j = j + 1;%Continue
        end
    end
end

function flag = islast(contiguoususa)
%inital
flag = 0;

%
if size(contiguoususa) <= 1
    flag = 1;
else %2 or more elements left
    if isnan(contiguoususa(2))%next
        flag = 1;
    else %~isnan
        %~islast
    end
end