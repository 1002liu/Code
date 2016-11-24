function [ A,B ] = SigFeedback( )
%% 样本提取
%%[ train_input,train_target,test_input,test_target ] = data_draw( );
[ train_input,train_target,test_input,test_target ] = SigFeedback_draw( );
 train_input = train_input';
 train_target = train_target';
 test_input = test_input';
 test_target = test_target';
%% SVM训练
SVM = svmtrain(train_input,train_target);
%% 网络预测输出;
SVMoutput= svmclassify(SVM,test_input);
test = [test_input,test_target];
[c, d] = size(test);
%% 结果分析
SVMoutput(find(SVMoutput<0.5))=0;
SVMoutput(find(SVMoutput>=0.5))=1;

test1 = test_target';
[a, b]= size(SVMoutput);
%sum1 = sum(SVMoutput);
benign_cnt = 0;
malware_cnt = 0;
cnt = 0;

fid = fopen('data_mal2.txt', 'wt');

for i=1:a
    if SVMoutput(i)==test1(i)
        if test1(i) == 1
            benign_cnt = benign_cnt+1;
        else
            malware_cnt = malware_cnt+1;
            for j=1:d
                if j==d 
                    fprintf(fid, '%f\n', test(i, j));
                else fprintf(fid, '%f ', test(i, j));
                end 
            end
        end
    elseif SVMoutput(i) == 1
        cnt = cnt +1;
    else 
        for j=1:d
           if j==d
              fprintf(fid, '%f\n', test(i, j));
           else fprintf(fid, '%f ', test(i, j));
           end 
       end
    end
end

sprintf('newSVM测试结果中恶意样本个数=%d\n判别为恶意的个数=%d',cnt+malware_cnt,malware_cnt)
sprintf('newSVM测试结果中良性样本个数=%d\n判别为良性的个数=%d',a-(cnt+malware_cnt),benign_cnt)

rightNumber=0;
for i=1:size(test_target,1)
    if SVMoutput(i)==test_target(i)
        rightNumber=rightNumber+1;
    end
end
% rightNumber = sum(SVMoutput==test_target);
rightratio=rightNumber/size(test_target,1)*100;
sprintf('newSVM准确个数=%d',rightNumber)
sprintf('newSVM测试准确率=%0.2f',rightratio)

% hold on;  
% plot(test_input(:,1),test_input(:,2),'ro','MarkerSize',12);       % testing  
% hold off
A =  test_target';
B = SVMoutput';
end

