function [ ] = test()
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
[a,b] = SVM();
[c,d] = H_SVM();
[e,f] = SigFeedback();
plotroc(a,b,'SVM',c,d,'H_SVM',e,f,'SigFeedback') ;

end

