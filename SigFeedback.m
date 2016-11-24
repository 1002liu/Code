function [ A,B ] = SigFeedback( )
%% ������ȡ
%%[ train_input,train_target,test_input,test_target ] = data_draw( );
[ train_input,train_target,test_input,test_target ] = SigFeedback_draw( );
 train_input = train_input';
 train_target = train_target';
 test_input = test_input';
 test_target = test_target';
%% SVMѵ��
SVM = svmtrain(train_input,train_target);
%% ����Ԥ�����;
SVMoutput= svmclassify(SVM,test_input);
test = [test_input,test_target];
[c, d] = size(test);
%% �������
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

sprintf('newSVM���Խ���ж�����������=%d\n�б�Ϊ����ĸ���=%d',cnt+malware_cnt,malware_cnt)
sprintf('newSVM���Խ����������������=%d\n�б�Ϊ���Եĸ���=%d',a-(cnt+malware_cnt),benign_cnt)

rightNumber=0;
for i=1:size(test_target,1)
    if SVMoutput(i)==test_target(i)
        rightNumber=rightNumber+1;
    end
end
% rightNumber = sum(SVMoutput==test_target);
rightratio=rightNumber/size(test_target,1)*100;
sprintf('newSVM׼ȷ����=%d',rightNumber)
sprintf('newSVM����׼ȷ��=%0.2f',rightratio)

% hold on;  
% plot(test_input(:,1),test_input(:,2),'ro','MarkerSize',12);       % testing  
% hold off
A =  test_target';
B = SVMoutput';
end

