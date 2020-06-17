clear
%start clock
tic
%loads data
load('Hw4_Data.mat');
%initalization of variables
xtest = 0;
z=0;
C = zeros();
xtr = 0;
Ctrain = zeros();
xtemp = 0;
counter = 0;
found = 0;
numFeat = 4;
numClass = 5;
testmean = 0;
xdelta = 0;
for i = numFeat:numFeat
    for j = 1:2
        xtemp = 0;
        counter = 0;
        bestmean = 0;
        for k = (3*numFeat/2):(3*numFeat)
            %fprintf('number of features %d, hidden network:    number in network: \n', i);
            % create the network 
            trainmean = 0;
            testmean = 0;
            if(j==1)
                previousTest = testmean/5;
                for q = 1:5
                    net=newff(d1trn(1:i,:),trntgt,k);
                    %training
                    net=train(net,d1trn(1:i,:),trntgt); 
                    %testing (on training set)
                    a=sim(net,d1trn(1:i,:));
                    % generate the confusion matrix and calculate classification rate 
                    Ctemptr = confmat(a,trntgt);
                    xtemptr = classifyrate(a,trntgt);
                    trainmean = trainmean + xtemptr;
                    %testing (on testing set)
                    a=sim(net,d1tst(1:i,:)); 
                    % generate the confusion matrix and calculate classification rate 
                    Ctemp = confmat(a,tsttgt);
                    testmean = testmean + classifyrate(a,tsttgt);
                    xtemp = classifyrate(a,tsttgt);
                    if(xtemp > xtest)
                        xtest = xtemp;
                        xtr = xtemptr;
                        Ctrain = Ctemptr;
                        C = Ctemp;
                        vector = [i j k z];
                        counter = 0;
                    end
                end
                xdelta = (testmean/5) - previousTest;
                if(xdelta < 0)
                    counter = counter + 1;
                end
                if(xdelta <= 3)
                    counter = counter + 1;
                end
                if counter == 2;
                    continue;
                end
                if((testmean/5) > bestmean)
                    besttestmean = (testmean/5);
                    xtrbestmean = (trainmean/5);
                    besttest = xtest;
                    xtrbest = xtr;
                    Cbesttrain = Ctrain;
                    Cbest = C;
                    vector = [i j k z];
                    counter = 0;
                end
                if(besttestmean >= 97 && (besttestmean-xtrbestmean) <= 10)
                    found = 1
                    break;
                end
            elseif(j==2)
                xtemp = 0;
                counter = 0;
                for z = numClass:(3*k/2)
                    testmean = 0;
                    trainmean = 0;
                    for q = 1:5
                        net=newff(d1trn(1:i,:),trntgt,[z k]);
                        %training
                        net=train(net,d1trn(1:i,:),trntgt); 
                        %testing (on training set)
                        a=sim(net,d1trn(1:i,:));
                        % generate the confusion matrix and calculate classification rate 
                        Ctemptr = confmat(a,trntgt);
                        xtemptr = classifyrate(a,trntgt);
                        trainmean = trainmean + xtemptr;
                        %testing (on testing set)
                        a=sim(net,d1tst(1:i,:)); 
                        % generate the confusion matrix and calculate classification rate 
                        Ctemp = confmat(a,tsttgt);
                        testmean = testmean + classifyrate(a,tsttgt);
                        xtemp = classifyrate(a,tsttgt);
                        if(xtemp > xtest)
                            xtr = xtemptr;
                            Ctrain = Ctemptr;
                            xtest = xtemp;
                            C = Ctemp;
                            vector = [i j k z];
                            counter = 0;
                        end
                    end
                    xdelta = (testmean/5) - previousTest;
                    if(xdelta < 0)
                        counter = counter + 1;
                    end
                    if(xdelta <= 3)
                        counter = counter + 1;
                    end
                    if counter == 2;
                        break;
                    end
                    if((testmean/5) > bestmean)
                        besttestmean = (testmean/5);
                        xtrbestmean = (trainmean/5);
                        besttest = xtest;
                        xtrbest = xtr;
                        Cbesttrain = Ctrain;
                        Cbest = C;
                        vector = [i j k z];
                        counter = 0;
                    end
                    if(besttestmean >= 97 && (besttestmean-xtrbestmean) <= 10)
                        found = 1
                        break;
                    end
                end
            end
            if(found == 1)
                break;
            end
        end
        if(found == 1)
            break;
        end
    end
    if(found == 1)
        break;
    end
end

fprintf('mean testing rate: %d and mean training rate: %s \n',besttestmean,num2str(xtrbestmean));
fprintf('best testing rate: %d and best training rate: %s \n',besttest,num2str(xtrbest));
fprintf('at feature number: %d hidden networks: %d \n',vector(1,1),vector(1,2));
fprintf('first hidden layer neurons: %d and second hidden layer neurons: %d\n',vector(1,3),vector(1,4));
fprintf('Confusion matrix on training set\n');
disp(Ctrain);
fprintf('Confusion matrix on testing set\n');
disp(C);
toc