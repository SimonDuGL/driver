%temp = contiguous_usa_map(contiguoususa003); result = excel2json(temp);
%variable list:
%PropertyCell1_content
%GeometryCell1_content
%{
Property = propertyJson(cell);
Geometry = geometryPolygonJson(matric);
result = excel2json(Geometry, Property);
%}
function result = excel2json(GeometryCell1_content, PropertyCell1_content)
result = '';
for i = 1: size(GeometryCell1_content,1)
    if isfirst(i)
        result = ['{"type": "Feature",', PropertyCell1_content{i,1}, ', ', GeometryCell1_content{i,1}, '},'];
    else %~isfirst
        if i == size(GeometryCell1_content,1)%islast(GeometryCell1_content(i:size(GeometryCell1_content,1),1)')
            result = [result, '{"type": "Feature",', PropertyCell1_content{i,1}, ', ', GeometryCell1_content{i,1}, '}'];
            %add } after the group
        else%~islast
            %is normal
            result = [result, '{"type": "Feature",', PropertyCell1_content{i,1}, ', ', GeometryCell1_content{i,1}, '},'];
            %add { before the group, add } after the group
            %add ,{ after the }
        end
    end
end

