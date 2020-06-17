clear
%start clock
tic
%loads data
load('atdesk.mat'),load('jog2mph.mat'),load('jog3mph.mat');
%initalization of variables and cells
k = 5;
numSampSets = 3;
correct = 0;
for i = 1:numSampSets
    var = strcat('dummy',num2str(i));
    v{i} = genvarname(var);
end
vex{1} = atdesk; vex{2} = jog2mph; vex{3} = jog3mph;
%running values of k to 5
for k = 1 : 5
    numTotal = numSampSets*k;
    [v{1}, AD] = kmeans(vex{1},k);
    [v{2}, J2] = kmeans(vex{2},k);
    [v{3}, J3] = kmeans(vex{3},k);
    %creating prototype
    prototype = [AD;J2;J3];
    %testing
    fprintf('the number of prototypes in this test is %d\n',k);
    for z = 0 : (numSampSets - 1)
        [x y] = size(v{z+1});
        d = zeros();
        for i = 1:x
            for j = 1:numTotal
                d(j) = norm(vex{z+1}(i,:) - prototype(j,:));
            end
            c=find(d==min(d(:)));
            if(c(1)>=((z*k)+1)&&c(1)<=((z+1)*k))
                correct = correct + 1;
            end
        end
        fprintf('the number of correct results of the prototype is %d out of %d\n',correct,x);
        correct = 0;
    end
end
toc