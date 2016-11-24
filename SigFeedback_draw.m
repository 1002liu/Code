function [ train_input,train_target,test_input,test_target ] = SigFeedback_draw( )
%% 0��ʾ���⣬1��ʾ����
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
        for j = 1 : n % ���д�ӡ����
             if j==n 
                 fprintf(fid, '%f\n', test.newtestSet(i, j)); % ע��%f������һ���ո�
             else fprintf(fid, '%f ', test.newtestSet(i, j));
             end
        end
    end
    
    fid = fopen('trainSet2.txt', 'wt');
    [m, n] = size(train);
    for i = 1 : m
        for j = 1 : n % ���д�ӡ����
             if j==n 
                 fprintf(fid, '%f\n', train.trainSet2(i, j)); % ע��%f������һ���ո�
             else fprintf(fid, '%f ', train.trainSet2(i, j));
             end
        end
    end
end

