function [A,B] = randomization(M)
%A����ȡ������ѵ�����ݼ�
%B����ȡ�����Ĳ������ݼ�
%w,h�Ǿ�����к���
[w h] = size(M);
n=round(w*0.6);
idx=randperm(w);
idx=idx(1:n);
A=M(idx,:);
B=M;
B(idx,:)=[];

end

