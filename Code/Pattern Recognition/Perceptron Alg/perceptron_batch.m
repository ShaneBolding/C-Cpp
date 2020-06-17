function W = perceptron_batch(X1, X2, ro, maxiter)
% function W = perceptron_batch(X1, X2, ro, maxiter) The function accepts
% an M1*n matrix X1 representing samples from class 1 (each row is a
% sample) and an M2*n X2 representing samples from class 2, a learning rate
% ro and a maximum number of iterations maxiter and uses the batch version
% of the perceptron algorithm to find a weight vector W of size n+1 that
% separtes the two classes. A solution W is found when all samples from
% class 1 satisfy W*x > 0 and all samples from class 2 satisfy W*x < 0. If
% the maximum number of iterations is reatched with no solution found, the
% function will let the user know and return W of the last iteration.

% get number of samples from each class
[m1 n1] = size(X1);
[m2 n2] = size(X2);

% check feature vector dimensions
if n1 ~= n2
    disp ('ERROR! Size of feature vectors from both classes must be equal! Exiting...');
else
    n = n1;
    % initialize W0
    W = rand(1,n+1);
    % initialize termination conditions
    found = 0;
    t = 0;
    while (found == 0 && t < maxiter)
        t = t+1;
        correction = zeros(1,n+1);
        missclassified = 0;
        for i=1:m1,
            if W*[X1(i,:), 1]' < 0
                correction = correction - [X1(i,:), 1];
                missclassified = missclassified + 1;
            end
        end
        for i=1:m2,
            if W*[X2(i,:), 1]' > 0
                correction = correction + [X2(i,:), 1];
                missclassified = missclassified + 1;
            end
        end
        % apply correction to current weights
        W = W - ro * correction
        if missclassified == 0;
            found = 1;
        end
    end
    if found == 0
        disp ('ERROR! Maximum number of iterations reached without finding')
        disp ('a solution. Returned W is the latest solution achieved.')
    end
end
    