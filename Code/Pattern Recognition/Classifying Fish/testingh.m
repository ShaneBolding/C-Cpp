clear

load('Hw4_Data.mat');
xtest = 0;
z=0;
C = zeros();
xtr = 0;
Ctrain = zeros();
xtemp = 0;
numF = 20;

net=newff(d1trn(1:numF,:),trntgt,[35,5]);
%training
net=train(net,d1trn(1:numF,:),trntgt); 
%testing (on training set)
a=sim(net,d1trn(1:numF,:));
% generate the confusion matrix and calculate classification rate 
Ctemptr = confmat(a,trntgt)
xtemptr = classifyrate(a,trntgt)
%testing (on testing set)
a=sim(net,d1tst(1:numF,:)); 
% generate the confusion matrix and calculate classification rate 
Ctemp = confmat(a,tsttgt)
%testing rate
xtemp = classifyrate(a,tsttgt)

               

