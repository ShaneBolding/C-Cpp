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
numFeat = 20;
numClass = 5;
for i = numFeat:numFeat
    testfeat = i;
    for j = 1:2
        xtemp = 0;
        counter = 0;
        for k = (3*testfeat/2):(5*testfeat/2)
            %fprintf('number of features %d, hidden network:    number in network: \n', i);
            % create the network 
            if(j==1)
                net=newff(d1trn(1:i,:),trntgt,k);
                %training
                net=train(net,d1trn(1:i,:),trntgt); 
                %testing (on training set)
                a=sim(net,d1trn(1:i,:));
                % generate the confusion matrix and calculate classification rate 
                Ctemptr = confmat(a,trntgt);
                xtemptr = classifyrate(a,trntgt);
                %testing (on testing set)
                a=sim(net,d1tst(1:i,:)); 
                % generate the confusion matrix and calculate classification rate 
                Ctemp = confmat(a,tsttgt);
                deltatemp = xtemp;
                xtemp = classifyrate(a,tsttgt);
                xdelta = xtemp - deltatemp;
                if(xdelta < 0)
                    counter = counter + 1;
                end
                if (counter >= 3)
                    break;
                end
                if(xtemp > xtest && xtemptr > xtr)
                    xtest = xtemp;
                    xtr = xtemptr;
                    Ctrain = Ctemptr;
                    C = Ctemp;
                    vector = [i j k z];
                    if(xdelta > 3)
                        counter = 0;
                    end
                end
                if(xtest >= 97 && (xtest - xtr) <= 10)
                    found = 1;
                    break;
                end
            elseif(j==2)
                xtemp = 0;
                counter = 0;
                for z = numClass:k
                    net=newff(d1trn(1:i,:),trntgt,[k z]);
                    %training
                    net=train(net,d1trn(1:i,:),trntgt); 
                    %testing (on training set)
                    a=sim(net,d1trn(1:i,:));
                    % generate the confusion matrix and calculate classification rate 
                    Ctemptr = confmat(a,trntgt);
                    xtemptr = classifyrate(a,trntgt);
                    %testing (on testing set)
                    a=sim(net,d1tst(1:i,:)); 
                    % generate the confusion matrix and calculate classification rate 
                    Ctemp = confmat(a,tsttgt);
                    %marks down previous testing rate
                    deltatemp = xtemp;
                    %finds new testing rate
                    xtemp = classifyrate(a,tsttgt);
                    %compares testing rates
                    xdelta = xtemp - deltatemp;
                    %if testing rate decreases increment counter
                    if(xdelta < 0)
                        counter = counter + 1;
                    end
                    %if counter is too high move on to start another NN
                    if (counter >= 3)
                        break;
                    end
                    %if testing rate is higher than best testing rate save
                    %the info of the NN
                    if(xtemp > xtest)
                        xtr = xtemptr;
                        Ctrain = Ctemptr;
                        xtest = xtemp;
                        C = Ctemp;
                        vector = [i j k z];
                        %if testing rate is increasing rapidly reset var
                        if(xdelta > 2)
                            counter = 0;
                        end
                    end
                    %if we find a good NN stop testing combinations
                    if(xtest >= 98 && (xtest - xtr) <= 10)
                        found = 1;
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


fprintf('best testing rate: %d and best training rate: %s \n',xtest,num2str(xtr));
fprintf('at feature number: %d hidden networks: %d \n',vector(1,1),vector(1,2));
fprintf('first hidden layer neurons: %d and second hidden layer neurons: %d\n',vector(1,3),vector(1,4));
fprintf('Confusion matrix on training set\n');
disp(Ctrain);
fprintf('Confusion matrix on testing set\n');
disp(C);
toc