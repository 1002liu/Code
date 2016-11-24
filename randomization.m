function [A,B] = randomization(M)
%A是提取出来的训练数据集
%B是提取出来的测试数据集
%w,h是矩阵的行和列
[w h] = size(M);
n=round(w*0.6);
idx=randperm(w);
idx=idx(1:n);
A=M(idx,:);
B=M;
B(idx,:)=[];

end

