function Result = main(dataUrl1, dataUrl2)
clc
%clear all
%'https://raw.githubusercontent.com/SimonDuGL/driver/GeopandasApp/contiguous_usa_013_success_cell.csv'
%'https://raw.githubusercontent.com/SimonDuGL/driver/GeopandasApp/contiguous_usa_013_success_matric.csv'
dataUrl = dataUrl1;
data = splitlines(webread(dataUrl));
Cell = split(data(1 : size(data,1) - 1, :), ',');

dataUrl = dataUrl2;
data = splitlines(webread(dataUrl));
data = split(data(1 : size(data,1) - 1, :), ',');
data(cellfun(@isempty,data)) = {'NaN'};
%Matric =  cell2mat(data);
for i = 1: size(data,1)
    for j = 1: size(data,2)
        Matric(i,j) = str2num(data{i,j});
    end
end

Property = propertyJson(Cell);
Geometry = geometryPolygonJson(Matric);
Result = excel2json(Geometry, Property);