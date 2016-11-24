function [ train_input,train_target,test_input,test_target ] = SigFeedback_draw( )
%% 0表示恶意，1表示良性
train = load('trainSet2.mat');
test = load('newtestSet.mat');

 [train_input, train_target] = inputAndTarget(train.trainSet2);
 [test_input, test_target] = inputAndTarget(test.newtestSet);
 
 train_input = train_input';
 train_target = train_target';
 test_input = test_input';
 test_target = test_target';
 
 
    fid = fopen('testSet2.txt', 'wt');
    [m, n] = size(test);
    for i = 1 : m
        for j = 1 : n % 逐行打印出来
             if j==n 
                 fprintf(fid, '%f\n', test.newtestSet(i, j)); % 注意%f后面有一个空格
             else fprintf(fid, '%f ', test.newtestSet(i, j));
             end
        end
    end
    
    fid = fopen('trainSet2.txt', 'wt');
    [m, n] = size(train);
    for i = 1 : m
        for j = 1 : n % 逐行打印出来
             if j==n 
                 fprintf(fid, '%f\n', train.trainSet2(i, j)); % 注意%f后面有一个空格
             else fprintf(fid, '%f ', train.trainSet2(i, j));
             end
        end
    end
end

