clear
tic
load('Hw4_Data.mat');
xtest = 0;
z=0;
C = zeros();
xtr = 0;
Ctrain = zeros();
xtemp = 0;
counter = 0;
found = 0;
for i = 1:20
    for j = 1:2
        xtemp = 0;
        counter = 0;
        for k = 2:10
            %fprintf('number of features %d, hidden network:    number in network: \n', i);
            % create the network with 2 hidden layers and 8 neurons in the first layer and 6 in the second 
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
                if(xdelta < -3)
                    break;
                end
                if(xdelta <= 3)
                    counter = counter + 1;
                end
                if counter == 2;
                    break;
                end
                if(xtemp > xtest)
                    xtest = xtemp
                    xtr = xtemptr
                    Ctrain = Ctemptr
                    C = Ctemp
                    vector = [i j k z]
                end
                if(xtemp >= 97 && (xtemp - xtr) <= 10)
                    found = 1;
                    break;
                end
            elseif(j==2)
                xtemp = 0;
                counter = 0;
                for z = 2:10
                    net=newff(d1trn(1:i,:),trntgt,[z k]);
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
                    if(xdelta < -1)
                        break;
                        counter = counter + 1;
                    end
                    if(xdelta <= 2)
                        counter = counter + 1;
                    end
                    if counter == 2;
                        break;
                    end
                    if(xtemp > xtest)
                        xtr = xtemptr
                        Ctrain = Ctemptr
                        xtest = xtemp
                        C = Ctemp
                        vector = [i j k z]
                        counter = 0;
                    end
                    if(xtemp >= 97 && (xtemp - xtr) <= 10)
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