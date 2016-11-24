function [ train_input,train_target,test_input,test_target ] = H_SVM_draw( )
%% 0表示恶意，1表示良性
 load('out12_beni.mat')
 [train0,test0] = randomization(out12_beni);
 load('out12_mal.mat')
 [train1,test1] = randomization(out12_mal);

 train = [train0;train1];
 test = [test0;test1];
 
 [train_input, train_target] = inputAndTarget(train);
 [test_input, test_target] = inputAndTarget(test);
 
 train_input = train_input';
 train_target = train_target';
 test_input = test_input';
 test_target = test_target';
 
 
    fid = fopen('testSet2.txt', 'wt');
    [m, n] = size(test);
    for i = 1 : m
        for j = 1 : n % 逐行打印出来
             if j==n 
                 fprintf(fid, '%f\n', test(i, j)); % 注意%f后面有一个空格
             else fprintf(fid, '%f ', test(i, j));
             end
        end
    end
    
    fid = fopen('trainSet2.txt', 'wt');
    [m, n] = size(train);
    for i = 1 : m
        for j = 1 : n % 逐行打印出来
             if j==n 
                 fprintf(fid, '%f\n', train(i, j)); % 注意%f后面有一个空格
             else fprintf(fid, '%f ', train(i, j));
             end
        end
    end
end

