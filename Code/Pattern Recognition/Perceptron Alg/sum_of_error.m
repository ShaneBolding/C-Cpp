function w = sum_of_error(X1, X2)
length = size(X1) + size(X2);
for i=1:length(2),
    y(i) = 1;
end
for i=length(2)+1:length(1),
    y(i) = -1;
end
x = [X1;X2];
one = (ones(8,1));
x = [x one];
w = inv(x'*x)*x'*y';
end
