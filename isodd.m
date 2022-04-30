function flag = isodd(j)
%initial
flag = 0;

if rem(j, 2) == 1 %reminder
    flag = 1;%odd
    
else %rem(j, 2) != 1
    %is not odd, could be even
end